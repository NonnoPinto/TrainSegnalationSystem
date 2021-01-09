/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#include "Rails.h"

//controlla la distanza tra due treni (T2 è più avanti di T1)
//e se la distanza è < DIST_MAX, rallenta quello accodato
void Rails::distance(Train &T1, const Train &T2){
	if(T1.get_speed() <= T2.get_speed()){
		if(abs(T1.get_pos() - T2.get_pos()) < 10){
			T1.set_speed(T2.get_speed()/2);
			std::cout << "Train n. " << T1.nTrain << "has been slow down to "
					<< T2.get_speed() << " kmph due to avoid a crash with train n. "
					<< T2.nTrain << std::endl;
		}
		else if (abs(T1.get_pos() - T2.get_pos()) <= T1.get_dist_max()){
			T1.set_speed(T2.get_speed());
			std::cout << "Train n. " << T1.nTrain << "has been slow down to "
					<< T2.get_speed() << " kmph due to avoid a crash with train n. "
					<< T2.nTrain << std::endl;
		}
	}
}

//tiene una lista dei treni in moto 
void Rails::running (){
	
	if (all_trains_.size() == 0)
		return;
	for (int i = 0; i < all_trains_.size(); i++)
		if((*all_trains_[i]).get_status() == 1){
			//std::cout << "L'HO MESSO DENTRO\n";
			onRails_.push_back((*all_trains_[i]));
		}
}

//STL sort
//my_sort
static bool myDist (Train &T1, Train &T2){
		return (T1.get_pos() < T2.get_pos());
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
	
	running();
	
	//if((*all_trains_).size()>1)
	//std::cout << "STATO DEL PRIMO TRENO " << (*all_trains_[0]).get_status() << "\n";
	//std::cout << "TRENI CHE STO CONTROLLANDO " << onRails_.size() << "\n";
	
	//std::cin >> c;
	
	onRailsSort();
	for(int i = 0; i<onRails_.size(); i++)
		std::cout << onRails_[i].get_pos() << " ";
		
	for(int i = 0; i < onRails_.size(); i++){
		if (onRails_[i].get_from() == 0)
			straight.push_back(onRails_[i]);
		else
			backwards.push_back(onRails_[i]);
	}
	
	for (int i = 1; i < straight.size(); i++)
		distance(straight[i - 1], straight[i]);
		
	for(int i = backwards.size()-1; i>0; i++)
		distance(backwards[i], backwards[i-1]);
	
}