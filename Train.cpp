/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità Super" */

#include "Train.h"


//calcola la posizione del treno
//se il suo stato lo indica in movimento
double Train::update_pos(){		//se il treno è in marcia, aggiungo tanti km
	if(status == 1 || status == 4){			//i km percorsi in un  minuto
		pos += vCrociera/60;
	}
	return pos;
}


//calcola il ritardo quando il treno è ad una stazione di fermata;
//se il treno sta solo passando, aggiorna solo il numero di stazioni passate
int Train::myDelay(int clock_){
	station_ = get_next_station();
	if (time[station_] > 0)
		delay = time[station_] - clock_;
	if (delay > 0)
		std::cout << "\nTrain n. " << nTrain << " arrived ad station n. " << station_ +1
			<< " with a " << delay << " minutes delay\n";
	else
		std::cout << "\nTrain n. " << nTrain << " arrived ad station n. " << station_ +1
			<< " on time\n";

	return delay;
}

int Train::get_next_arrival() const{
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

int Train::get_next_station() const {
	if (from == 0)
		return (station_ + 1);
	else
		return (station_ - 1);
}

Train& Train::operator=(const Train &T){

	Train(T.nTrain);
		vCrociera = T.vCrociera;
		pos = T.pos;
		delay = T.delay;
		station_ = T.station_;
		status = T.status;
		time = T.time;
		train_type = T.train_type;
		vMax = T.vMax;
		dist_max = T.dist_max;
		from = T.from;
	//else
		//std::cout << "Stai cercando di copiare due treni diversi, pirla!";
	
	return *this;
}