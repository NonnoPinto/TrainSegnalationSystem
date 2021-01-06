/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#include "Rails.h"

//controlla la distanza tra due treni (T2 è più avanti di T1)
//e se la distanza è < DIST_MAX, rallenta quello accodato
void Rails::distance(Train &T1, const Train &T2){
	if (abs(T1.pos - T2.pos)<T1.dist_max){
		T1.vCrociera = T2.vCrociera;
		std::cout << "Train n. " << T1.nTrain << "has been slow down to "
				<< T2.vCrociera << " kmph due to avoid a crash with train n. "
				<< T2.nTrain << std::endl;
	}
}

//tiene una lista dei treni in moto 
void Rails::running (std::vector<Train> &v){
	for (int i = 0; i < v.size(); i++)
		if(v[i].status == 1)
			onRails_.push_back(v[i]);
}

//STL sort
//my_sort
bool Rails::myDist (Train &T1, Train &T2){
	if (T1.from == 0)
		return (T1.pos < T2.pos);
	else
		return (T2.pos < T1.pos);
}

//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
void Rails::onRailsSort (std::vector<Train>& v){
	std::sort (v.begin(), v.end(), myDist);
}

//elimina i treni dopo che sono arrivati al capolinea
void Rails::arrived (){
	int i = 0;
	while(running_[i] != this)
		i++;
	running_.erase(running_.begin()+i);
	std::cout << "Train n. " << this.nTrain << " has arrived to destination\n";
}

bool Rails::runningIsFree() {
	int tmp = 0;
	for (int i = 0; i < trains_.size(); i++)
		if (trains_[i].status == 3)
			tmp++;
	if (tmp == trains_)
		std::cout << "All trains are arrived at their own destination!\n";
		return true;
	return false;
}

void Rails::dont_crash(){
	vector<Train> straigth;
	vector<Train> backwards;
	
	onRails_.clear();
	
	running(running_);
	
	onRailsSort(onRails_);
	
	for(int i = 0; i < onRails_.size(); i++){
		if (onRail_[i].from == 0)
			straigth.push_back(onRails_[i]);
		else
			back.push_bacwards(onRails_[i]);
	}
	
	for(int i = 0; i<straigth.size()-1; i++)
		distance(straigth[i], straight_[i+1]);
		
	for(int i = 0; i<backwards.size()-1; i++)
		distance(backwards[i], backwards[i+1];
	
}