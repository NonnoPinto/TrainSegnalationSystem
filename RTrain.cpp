/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni Regionali" */

#pragma once
#include "RTrain.h"
template <typename L>
//calcola la posizione del treno
void RTrain<L>::update_pos(Train<L> &T, const int time_){	//se il treno è in marcia,
	if(T.get_status() == 1) pos += vCrociera/60;}	//aggiungo tanti km quanti ne fa in un minuto

template <typename L>
//calcola il ritardo
int RTrain<L>::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	return delay;}