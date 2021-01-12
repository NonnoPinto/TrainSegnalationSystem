/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Treni Regionali" */

#ifndef RTrain_h
#define RTrain_h

#include "Train.h"

class RTrain : public Train {

public:
	//Costruttore di default
	RTrain();

	//costruttore di RTrain, chiama il costruttore della classe base Train e implementa
	//l'inizializzazione della altre varibiali
	RTrain(int n, int from_, std::vector<int>& timeTable, std::vector<std::string>& line);

	//override funzione che calcola il ritardo del treno ad ogni stazione raggiunta
	//e tiene il conto delle stazioni (comprese quelle in cui non si ferma)
	int myDelay(int clock_) override;

	//override della funzione principale che, ad ogni ciclo,
	//aggiorna la posizione del treno in base allo status e alla v di crociera
	double update_pos() override;
	
	//override funzioni "get"
	double get_pos() const override { return pos; };

	int get_status() const override { return status; };

	int get_time(int x) const override { return time[x]; };

	int get_rail() const override { return myRail; };

	int get_speed() const override { return vCrociera; };

	int get_delay() const override { return delay; };
	
	//override segnalazione dell'eventuale fermata
	bool stop_next_station() override { return true; };

	//restituisce il successivo tempo di arrivo in base al senso di marcia
	int get_next_arrival() const override;

	//restituisce la stazione successiva in base al senso di marcia
	int get_next_station() const override;

protected:
	//variabili membro protette trattabili solo attraverso le rispettive funzioni get e set
	//le funzioni membro protette invece servono a far accedere alla modifica delle variabili solo le eventuali classi derivate

	//velocità di crociera
	int vCrociera = 0;

	//funzione che aggiorna la velocità di crociera del treno
	void set_speed(const int v) { vCrociera = v; };

	//posizione attuale del treno lungo la linea ferroviaria
	double pos = 0;

	//ritardo accumulato
	int delay = 0;

	//stazioni raggiunte
	int station_;

	//varibiale di controllo sullo stato del treno
	//0 == alla stazione di partenza, 1 == in marcia,
	//2 == fermo (parcheggio o fermata), 3 == arrivato a destinazione
	//4 == nei pressi della stazione
	int status = 0;

	//funziona per la modifica dello stato del treno
	void set_status(const int s) { status = s; };

	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	std::vector<int> time;

	//binario su cui il treno sta correndo
	int myRail = 0;
	
	//imposta il vinario di percorrenza
	// -1 = stazione di parcheggio
	// 0 == tra le stazioni
	// poi, a seconda delle stazioni, quattro binari indicano la fermata
	// e altri due, solo nelle stazioni locali, indicano i binari per il passaggio senza fermata
	void set_rail(int x) override { myRail = x; };
};
#endif