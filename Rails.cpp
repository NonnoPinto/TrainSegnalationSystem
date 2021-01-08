/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#include "Rails.h"

//controlla la distanza tra due treni (T2 è più avanti di T1)
//e se la distanza è < DIST_MAX, rallenta quello accodato
void Rails::distance(Train &T1, const Train &T2){
	if(T1.get_status() == 1 && T2.get_status() == 1)
		if (abs(T1.get_pos() - T2.get_pos()) <= T1.get_dist_max() && abs(T1.get_pos() - T2.get_pos()) >= 10){
			T1.set_speed(T2.get_speed());
			std::cout << "Train n. " << T1.nTrain << "has been slow down to "
					<< T2.get_speed() << " kmph due to avoid a crash with train n. "
					<< T2.nTrain << std::endl;
		}
		else if(abs(T1.get_pos() - T2.get_pos()) < 10)
			T1.set_speed(T2.get_speed()/2);
}

//tiene una lista dei treni in moto 
void Rails::running (std::vector<Train> &v){
	if (v.size() == 0)
		return;
	for (int i = 0; i < v.size(); i++)
		if(v[i].get_status() == 1){
			std::cout << "L'HO MESSO DENTRO\n";
			onRails_.push_back(v[i]);
		}
}

//STL sort
//my_sort
static bool myDist (Train &T1, Train &T2){
	if (T1.get_from() == 0)
		return (T1.get_pos() < T2.get_pos());
	else
		return (T2.get_pos() < T1.get_pos());
}

//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
void Rails::onRailsSort (){
	std::sort (onRails_.begin(), onRails_.end(), myDist);
}

//elimina i treni dopo che sono arrivati al capolinea
void Rails::arrived (Train &T){
	arrived_++;
	std::cout << "Train n. " << T.nTrain << " has arrived to destination\n";
}

bool Rails::runningIsFree() {
	if (arrived_ == all_trains_.size())
	{
		std::cout << "All trains have arrived at their own destination!\n";
		return true;
	}
	return false;
}

void Rails::dont_crash(){
	std::vector<Train> straight;
	std::vector<Train> backwards;
	
	onRails_.clear();
	
	running(running_);
	
	//std::cout << "TRENI CHE STO CONTROLLANDO " << onRails_.size() << "\n";
	
	onRailsSort();
	
	for(int i = 0; i < onRails_.size(); i++){
		if (onRails_[i].get_from() == 0)
			straight.push_back(onRails_[i]);
		else
			backwards.push_back(onRails_[i]);
	}
	
	for (int i = 1; i < straight.size(); i++)
		distance(straight[i - 1], straight[i]);
		
	for(int i = 1; i<backwards.size(); i++)
		distance(backwards[i - 1], backwards[i]);
	
}