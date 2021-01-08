/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni Regionali" */

#include "RTrain.h"

//costruttore di default
RTrain::RTrain(): Train(){
	set_vMax(0);
	set_dist_max(0);
	set_from(0);
}

//Costruttore
RTrain::RTrain(int n, int from_, std::vector<int> &timeTable, std::vector<std::string> &line):
	Train(n){
	set_from(from_);
	//se il treno parte dall'ultima stazione
								//la velocità si considera negativa
		
	set_dist_max(10 + (160/60));	//la distanza massima è la correzione da fare ai valori di default:
							//i chilometri che un regionale
							//(alla sua velocità massima)
							//può percorrere in un minuto (unità di tempo minima)
	
	set_timeTable(timeTable); //importa la timetable

	//set_time(0, -5);
	
	if (from_ == 1)
	{
		set_vMax(-160);
		pos = std::stoi(line[line.size() - 1]); //se il treno parte dall'ultima stazione,
													//importa la lunghezza dell'intera linea 
		set_station(line.size() + 1);
	}
	else
	{
		set_station(0);
		set_vMax(160);
	}
}


//calcola la posizione del treno
double RTrain::update_pos(){	//se il treno è in marcia,
	if(status == 1 || status == 4)						//aggiungo i km percorsi in un minuto
		pos += vCrociera/60;
	return pos;
}


//calcola il ritardo
int RTrain::myDelay(int clock_){
	station_ = get_next_station();
	delay = time[station_] - clock_;
		if (delay > 0)
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " with a " << delay << " minutes delay";
		else
			std::cout << "Train n. " << nTrain << " arrived ad station n. " << station_
				<< " on time";
	return delay;
}