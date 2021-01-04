/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità Super" */

#pragma once
#include "AVSTrain.h"
template <typename L>

//calcola la posizione del treno
const int AVSTrain<L>::update_pos(const int time_){	//se il treno è in marcia, aggiungo tanti km
	if(this.get_status() == 1)						//i km percorsi in un  minuto
		pos += vCrociera/60;
	return pos;
}

template <typename L>
//calcola il ritardo
int AVSTrain<L>::myDelay(const int clock_){
	station_++;
	if (time[station_] > 0)
		delay = time[station_] - clock_;
		if (delay > 0)
			std::cout << "Train n. " << this.nTrain << " arrived ad station n. " << station_
				<< " with a " << delay << " minutes delay";
		else
			std::cout << "Train n. " << this.nTrain << " arrived ad station n. " << station_
				<< " on time";

	return delay;
}