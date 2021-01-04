/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità" */

#pragma once
#include "AVTrain.h"
template <typename L>
//calcola la posizione del treno
void AVTrain<L>::update_pos(Train<L> &T, const int time_){	//se il treno è in marcia, aggiungo tanti km
	if(T.get_status() == 1) pos += vCrociera/60;}	//quanti ne fa in un minuto

template <typename L>
//calcola il ritardo
int AVTrain<L>::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	return delay;}