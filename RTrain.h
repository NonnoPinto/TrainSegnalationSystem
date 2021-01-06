/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Treni Regionali" */

#ifndef RTrain_h
#define RTrain_h

#include "Train.h"

class RTrain : public Train{

public:
	//Costruttore di default
	RTrain() : Train(), vMax(0), dist_max(0), from(0){};
	
	//costruttore di RTrain, chiama il costruttore della classe base Train
	RTrain(int n, int from_, std::vector<int> &timeTable, std::vector<std::string> &line):
		Train(n), from(from_),
		vMax(160*(from_*(-1))),//se il treno parte dall'ultima stazione
												//la velocità si considera negativa
		dist_max(10 + (160/60))	//la distanza massima è la correzione da fare ai valori di default:
							//i chilometri che un regionale
							//(alla sua velocità massima)
							//può percorrere in un minuto (unità di tempo minima)
	{	set_timeTable(timeTable);
		if(from_==1) pos = std::stoi(line[line.size()-1]);}; 
	
	/*//calcola la posizione del treno
	double update_pos(const int time_) override;
	
	//calcola il ritardo
	int myDelay(const int clock_) override;*/
	
	//tipo di treno
	const int train_type = 1;
	
	//velocità massima
	const int vMax;
	
	//distanza massima tra due treni
	const int dist_max;
	
	//variabile di controllo dell'orgine del treno
	const int from;
	
protected:
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
	
};

#endif