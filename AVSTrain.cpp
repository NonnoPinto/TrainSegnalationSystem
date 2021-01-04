/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità Super" */

#pragma once
#include "AVSTrain.h"
template <typename L>
//calcola la posizione del treno
void AVSTrain<L>::update_pos(Train<L> &T, const int time_){	//se il treno è in marcia, aggiungo tanti km
	if(T.get_status() == 1) pos += vCrociera/60;}	//quanti ne fa in un minuto

template <typename L>
//calcola il ritardo
int AVSTrain<L>::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	return delay;}