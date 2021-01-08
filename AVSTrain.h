/* author: Giovanni Zago - 1226024
 * header della classe derivata "Treni ad Alta Velocità Super"*/

#ifndef AVSTrain_h
#define AVSTrain_h

#include "Train.h"

class AVSTrain : public Train{
	
public:
	//Costruttore di default
	AVSTrain();
	
	//costruttore di RTrain, chiama il costruttore della classe base Train
	AVSTrain(int n, int from_, std::vector<int> &timeTable, std::vector<std::string> &line);

	//override funzione che calcola il ritardo del treno ad ogni stazione raggiunta
	//e tiene il conto delle stazioni (comprese quelle in cui non si ferma)
	int myDelay (int clock_) override;
	
	//override della funzione principale che, ad ogni ciclo,
	//aggiorna la posizione del treno in base allo status e alla v di crociera
	double update_pos() override;

};

#endif

	/*//variabili membro pubbliche
	//facilmente accessibili da chiunque, ma conservano l'incapsulamento
	//perchè definite const
	
	//tipo di treno
	const int train_type = 3;
	
	//velocità massima
	const int vMax;
	
	//distanza massima tra due treni
	const int dist_max;
	
	//variabile di controllo dell'orgine del treno
	const int from;*/
	
	/*//calcola la posizione del treno
	double update_pos(const int time_) override;
	
	//calcola il ritardo
	int myDelay(const int clock_) override;*/
	
	/*//aggiornamento della velocità (frenata, accelerata, stop...)
	void set_speed (const int v) override {vCrociera=v;};
	
	//velocità di crociera
	int vCrociera = 0;
	
	
	//posizione attuale del treno lungo la linea ferroviaria
	double pos = 0;
	
	//ritardo accumulato
	int delay = 0;
	
	//stazioni raggiunte
	int station_ = 0;*/
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	//const std::vector<int> time;
	