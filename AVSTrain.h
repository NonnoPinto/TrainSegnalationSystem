/* author: Giovanni Zago - 1226024
 * header della classe derivata "Treni ad Alta Velocit� Super"*/

#ifndef AVSTrain_h
#define AVSTrain_h

#include "Train.h"

class AVSTrain : public Train {

public:
	//Costruttore di default
	AVSTrain();

	//costruttore di RTrain, chiama il costruttore della classe base Train
	AVSTrain(int n, int from_, std::vector<int>& timeTable, std::vector<std::string>& line);

	//override funzione che calcola il ritardo del treno ad ogni stazione raggiunta
		//e tiene il conto delle stazioni (comprese quelle in cui non si ferma)
	int myDelay(int clock_) override;

	//override della funzione principale che, ad ogni ciclo,
	//aggiorna la posizione del treno in base allo status e alla v di crociera
	double update_pos() override;

	double get_pos() const override { return pos; };

	int get_status() const override { return status; };

	int get_time(int x) const override { return time[x]; };

	int get_rail() const override { return myRail; };

	int get_speed() const override { return vCrociera; };

	int get_delay() const override { return delay; };

	//funzione booleana
	//true se il treno si fermer� alla prossima stazione
	//false altrimenti
	bool stop_next_station() override { return time[get_next_station()] != -2; };

	//restituisce il successivo tempo di arrivo in base al senso di marcia
	int get_next_arrival() const override;

	//restituisce la stazione successiva in base al senso di marcia
	int get_next_station() const override;

protected:
	//velocit� di crociera
	int vCrociera = 0;

	//funzione che aggiorna la velocit� di crociera del treno
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
	int status = 0;

	//funziona per la modifica dello stato del treno
	void set_status(const int s) { status = s; };

	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario � espresso in minuti dopo la partenza
	std::vector<int> time;

	//binario su cui il treno sta correndo
	int myRail = 0;

	void set_rail(int x) override { myRail = x; };

};

#endif