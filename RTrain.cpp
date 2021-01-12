/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni Regionali" */

#include "RTrain.h"

//costruttore di default
RTrain::RTrain() : Train() {};

//Costruttore
RTrain::RTrain(int n, int from_, std::vector<int>& timeTable, std::vector<std::string>& line) :
	Train(n) 
{
	time = timeTable; //importa la timetable

	train_type = 1;

	dist_max = 10 + 160 / 60;

	from = from_;

	vMax = 160 - (160 * 2 * from_);		//se il treno parte dall'ultima stazione
										//la velocità si considera negativa

	if (from_ == 1)
	{
		pos = std::stoi(line[line.size() - 1]);		//se il treno parte dall'ultima stazione,
													//importa la lunghezza dell'intera linea 
		station_ = line.size() - 1;

		std::reverse(time.begin(), time.end());
	}
	else
		station_ = 0.0;
}


//calcola la posizione del treno
double RTrain::update_pos() {			//se il treno è in marcia,
	if (status == 1 || status == 4)		//aggiungo i km percorsi in un minuto
		pos += (vCrociera / 60.0);
	if (pos < 1)
		pos = 0.0;
	return pos;
}


//calcola il ritardo
int RTrain::myDelay(int clock_) {
	station_ = get_next_station();

	if (time[station_] == -2)
		return delay;

	if (time[station_] < clock_)
	{
		delay = clock_ - time[station_];
		std::cout << "Train n. " << nTrain << " arrived at station n. " << station_ + 1
			<< " with a " << delay << " minutes delay \n";
		return delay;
	}
	else
	{
		delay = 0;
		std::cout << "Train n. " << nTrain << " arrived at station n. " << station_ + 1
			<< " on time \n";
		return delay;
	}
}

int RTrain::get_next_arrival() const {
	if (station_ < time.size())
	{
		return time[get_next_station()];
	}
	else
	{
		std::cout << "Out of bounds (non existant station)\n";
		return -1;
	}
}

int RTrain::get_next_station() const {
	if (from == 0)
		return (station_ + 1);
	else
		return (station_ - 1);
}