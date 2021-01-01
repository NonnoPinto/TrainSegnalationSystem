/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni ad Alta Velocità Super"
 * La classe derivata definisce unicamente il costruttore
 * lasciando ad altre sottoclassi derivate l'implementazione delle funzioni*/

//#pragma once
#include "Train.h"

class AVSTrain : public Train{
	//Costruttore di default
	AVSTrain() : Train(){};
	AVSTrain(int type_, int from_, std::vector<int> &timeTable) : Train(1, from_, timeTable){};

	//calcola la posizione del treno in base alla velocità di crociera
	void update_pos(int time_) override;
	
	//controlla la distanza tra due treni
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(Train &T1, Train &T2) override;
};