/* author: Giovanni Zago - 1226024
 * Classe derivata "Treni ad Alta Velocità Super" */

#include "Train.h"


//calcola la posizione del treno
//se il suo stato lo indica in movimento
double Train::update_pos(){		//se il treno è in marcia, aggiungo tanti km
	if(status == 1){			//i km percorsi in un  minuto
		pos += vCrociera/60;
	}
	return pos;
}


//calcola il ritardo quando il treno è ad una stazione di fermata;
//se il treno sta solo passando, aggiorna solo il numero di stazioni passate
int Train::myDelay(const int clock_){
	station_++;
	if (time[station_] > 0)
		delay = time[station_] - clock_;
	if (delay > 0)
		std::cout << "\nTrain n. " << nTrain << " arrived ad station n. " << station_
			<< " with a " << delay << " minutes delay";
	else
		std::cout << "\nTrain n. " << nTrain << " arrived ad station n. " << station_
			<< " on time";

	return delay;
}

Train& Train::operator=(const Train &T){

	if(nTrain == T.nTrain){
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
	}
	else
		std::cout << "Stai cercando di copiare due treni diversi, pirla!";
	
	return *this;
}