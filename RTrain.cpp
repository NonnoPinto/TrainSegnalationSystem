/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni Regionali" */

#include "RTrain.h"


//calcola la posizione del treno
double RTrain::update_pos(const int time_){	//se il treno è in marcia,
	if(get_status() == 1)						//aggiungo i km percorsi in un minuto
		pos += vCrociera/60;
	return pos;
}


//calcola il ritardo
int RTrain::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	if (delay > 0)
		std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " with a " << delay << " minutes delay";
	else
		std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " on time";
	return delay;
}