/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità" */

#include "AVTrain.h"


//calcola la posizione del treno
double AVTrain::update_pos(const int time_){	//se il treno è in marcia, aggiungo
	if(get_status() == 1) 						//i km percorsi in un minuto
		pos += vCrociera/60;
	return pos;
}


//calcola il ritardo
int AVTrain::myDelay(const int clock_){
	station_++;
	if (time[station_] > 0){
		delay = time[station_] - clock_;
		if (delay > 0)
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
					<< " with a " << delay << " minutes delay";
		else
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
					<< " on time";
	}
	return delay;}