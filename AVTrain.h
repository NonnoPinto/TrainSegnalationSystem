/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Treni ad Alta Velocità"*/
 
#pragma once
#include "Train.h"

class AVTrain : public Train{
	public:
	//Costruttore di default
	AVTrain() : Train(), vMax(0), dist_max(0), from(0){};
	
	//costruttore di RTrain, chiama il costruttore della classe base Train
	//SISTEMARE LE VARIABILI
	AVTrain(int n, int from_, std::vector<int> &timeTable): Train(n),
		from(from_), time(timeTable),
		vMax(240*(from_*(-1))),//se il treno parte dall'ultima stazione
												//la velocità si considera negativa
		dist_max(10+(240/60))	//la distanza massima è la somma dei 10 km di sicurezza
								//più i chilometri che un regionale
								//(alla sua velocità massima)
								//può percorrere in un minuto (unità di tempo minima)
	{if(from_==1) pos = 200;}; //DA RISOLVERE, CAZZO
	
	//calcola la posizione del treno
	void update_pos(const int time_) override;
	
	//aggiornamento della velocità (frenata, accelerata, stop...)
	void set_speed (const int v) override {vCrociera=v;};
	
	const int get_km() const override {return pos;};
	
	//calcola il ritardo
	int myDelay(const int clock_) override;
	
	void just_passed() override {station_++;};
	
	//tipo di treno
	const int train_type = 2;
	
	//velocità massima
	const int vMax;
	
	//distanza massima tra due treni
	const int dist_max;
	
	//variabile di controllo dell'orgine del treno
	const int from;
	
protected:
	//velocità di crociera
	int vCrociera = 0;
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	const std::vector<int> time;
	
	//posizione attuale del treno lungo la linea ferroviaria
	double pos = 0;
	
	//ritardo accumulato
	int delay = 0;
	
	//stazioni raggiunte
	int station_ = 0;
};