/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità Super" */

#include "AVSTrain.h"

//costruttore di default
AVSTrain::AVSTrain(): Train(){
	set_vMax(0);
	set_dist_max(0);
	set_from(0);
}

//Costruttore
AVSTrain::AVSTrain(int n, int from_, std::vector<int> &timeTable, std::vector<std::string> &line):
	Train(n){
	set_from(from_);
	set_vMax(300*(from_*(-1)));//se il treno parte dall'ultima stazione
								//la velocità si considera negativa
		
	set_dist_max(10 + (300/60));	//la distanza massima è la correzione da fare ai valori di default:
							//i chilometri che un regionale
							//(alla sua velocità massima)
							//può percorrere in un minuto (unità di tempo minima)
	
	set_timeTable(timeTable); //importa la timetable
	
	if(from_==1) pos = std::stoi(line[line.size()-1]); //se il treno parte dall'ultima stazione,
													//importa la lunghezza dell'intera linea 
}


//calcola la posizione del treno
double AVSTrain::update_pos(){	//se il treno è in marcia, aggiungo tanti km
	if(status == 1)						//i km percorsi in un  minuto
		pos += vCrociera/60;
	return pos;
}


//calcola il ritardo
int AVSTrain::myDelay(const int clock_){
	station_++;
	if (time[station_] > 0)
		delay = time[station_] - clock_;
		if (delay > 0)
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " with a " << delay << " minutes delay";
		else
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " on time";

	return delay;
}