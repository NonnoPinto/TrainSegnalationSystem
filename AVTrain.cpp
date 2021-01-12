/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità" */

#include "AVTrain.h"

 //costruttore di default
AVTrain::AVTrain() : Train() {};

//Costruttore
AVTrain::AVTrain(int n, int from_, std::vector<int>& timeTable, std::vector<std::string>& line) :
	Train(n) //se il treno parte dall'ultima stazione
									//la velocità si considera negativa
{
	time = timeTable; //importa la timetable

	train_type = 2;
	dist_max = 10 + 240 / 60;
	from = from_;
	vMax = 240 - (240 * 2 * from_);

	if (from_ == 1)
	{
		pos = std::stoi(line[line.size() - 1]); //se il treno parte dall'ultima stazione,
													//importa la lunghezza dell'intera linea 
		station_ = line.size() - 1;
		std::reverse(time.begin(), time.end());
	}
	else
	{
		station_ = 0.0;
	}
}


//calcola la posizione del treno
double AVTrain::update_pos() {		//se il treno è in marcia,
	if (status == 1 || status == 4)	//aggiungo i km percorsi in un minuto
		pos += (vCrociera / 60.0);
	if (pos < 1)
		pos = 0.0;
	return pos;
}


//calcola il ritardo
int AVTrain::myDelay(int clock_) {
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

int AVTrain::get_next_arrival() const {
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

int AVTrain::get_next_station() const {
	if (from == 0)
		return (station_ + 1);
	else
		return (station_ - 1);
}

/*AVTrain& AVTrain::operator=(const AVTrain &T){

	AVTrain(T.nTrain, T.from, &T.time, &T.line);
		vCrociera = T.vCrociera;
		pos = T.pos;
		delay = T.delay;
		station_ = T.station_;
		status = T.status;
	//else
		//std::cout << "Stai cercando di copiare due treni diversi, pirla!";

	return *this;
}*/