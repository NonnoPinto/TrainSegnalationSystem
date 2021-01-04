/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni Regionali" */

#pragma once
#include "RTrain.h"
template <typename L>

//calcola la posizione del treno
const int RTrain<L>::update_pos(const int time_){	//se il treno è in marcia,
	if(this.get_status() == 1)						//aggiungo i km percorsi in un minuto
		pos += vCrociera/60;
	return pos;
}

template <typename L>
//calcola il ritardo
int RTrain<L>::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	if (delay > 0)
		std::cout << "Train n. " << this.nTrain << " arrived ad station n. " << station_
				<< " with a " << delay << " minutes delay";
	else
		std::cout << "Train n. " << this.nTrain << " arrived ad station n. " << station_
				<< " on time";
	return delay;
}