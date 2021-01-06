/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Treni ad Alta Velocità"*/
 
#ifndef AVTrain_h
#define AvTrain_h

#include "Train.h"

class AVTrain : public Train{

public:
	//Costruttore di default
	AVTrain() : Train(), vMax(0), dist_max(0), from(0){};
	
	//costruttore di RTrain, chiama il costruttore della classe base Train
	AVTrain(int n, int from_, std::vector<int> &timeTable, std::vector<std::string> &line):
		Train(n), from(from_),
		vMax(240*(from_*(-1))),//se il treno parte dall'ultima stazione
												//la velocità si considera negativa
		dist_max(10+(240/60))	//la distanza massima è la somma dei 10 km di sicurezza
								//più i chilometri che un regionale
								//(alla sua velocità massima)
								//può percorrere in un minuto (unità di tempo minima)
	{	set_timeTable(timeTable);
		if(from_==1) pos = std::stoi(line[line.size()-1]);};
	
	//calcola la posizione del treno
	//double update_pos(const int time_) override;
	
	//calcola il ritardo
	//int myDelay(const int clock_) override;
	
	//tipo di treno
	const int train_type = 2;
	
	//velocità massima
	const int vMax;
	
	//distanza massima tra due treni
	const int dist_max;
	
	//variabile di controllo dell'orgine del treno
	const int from;
	
protected:
	//aggiornamento della velocità (frenata, accelerata, stop...)
	//void set_speed (const int v) override {vCrociera=v;};
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	//const std::vector<int> time;
	
	
};

#endif