/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità" */

#pragma once
#include "AVTrain.h"

//calcola la posizione del treno
void AVTrain::update_pos(const int time_){	//se il treno è in marcia, aggiungo tanti km
	if(status == 1) pos += vCrociera/60;}	//quanti ne fa in un minuto

//calcola il ritardo
int AVTrain::myDelay(const int clock_){
	station_++;
	delay = time[station_] - clock_;
	return delay;}