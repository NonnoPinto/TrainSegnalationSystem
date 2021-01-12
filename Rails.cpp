/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails"
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/

#include "Rails.h"

 //controlla la distanza tra due treni (T2 è più avanti di T1)
 //e se la distanza è < DIST_MAX, rallenta quello accodato
void Rails::distance(std::shared_ptr<Train> T1, std::shared_ptr<Train> T2) {
	double d = abs((*T1).get_pos() - (*T2).get_pos());
	
	if (abs(T2->get_speed()) <= abs(T1->get_speed()) && abs((*T2).get_speed()) != 80) {
		if (d < 10 && abs((*T1).get_speed()) != 100) {
			if (T1->from == 0)
				(*T1).set_speed(100);
			else
				(*T1).set_speed(-100);
			std::cout << "Train n. " << (*T1).nTrain << " has been slow down to "
				<< 100 << " kmph due to avoid a crash with train n. "
				<< (*T2).nTrain << std::endl;
			//std::cout << "VEL T1: " << (*T1).get_speed() << std::endl;
		}
		else if (d <= (*T1).dist_max && ((*T1).get_speed() != (*T2).get_speed())) {
			(*T1).set_speed((*T2).get_speed());
			std::cout << "Train n. " << (*T1).nTrain << " has been slow down to "
				<< abs((*T2).get_speed()) << " kmph due to avoid a crash with train n. "
				<< (*T2).nTrain << std::endl;
		}
	}
	else if (d <= (*T1).dist_max && d > 10 && abs((*T1).get_speed()) == 100)
	{
		(*T1).set_speed((*T2).get_speed());
		std::cout << "Train n. " << (*T1).nTrain << " has been speed up to "
			<< abs((*T2).get_speed()) << " kmph cause it's far enough from train n. "
			<< (*T2).nTrain << std::endl;
	}
}

//STL sort
//my_sort
/*static bool myDist(std::shared_ptr<Train> T1, std::shared_ptr<Train> T2) {
	return (T1->get_pos() < T2->get_pos());
}*/

//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
void Rails::onRailsSort() {
	std::shared_ptr<Train> tmp_ptr;
	for (int i = 0; i < onRails_.size(); i++) {
		for (int k = i; k < onRails_.size(); k++)
			if (onRails_[k] < onRails_[i]) {
				tmp_ptr = onRails_[i];
				onRails_[i] = onRails_[k];
				onRails_[k] = tmp_ptr;
			}
	}
}

//elimina i treni dopo che sono arrivati al capolinea
void Rails::arrived(Train& T) {
	arrived_++;
	std::cout << "*** Train n. " << T.nTrain << " is arrived to destination\n";
}

bool Rails::runningIsFree() {
	if (arrived_ == all_trains_.size())
	{
		std::cout << "*** All trains are arrived at their own destination! ***\n";
		return true;
	}
	return false;
}

//tiene una lista dei treni in moto 
void Rails::running() {

	if (all_trains_.size() == 0)
		return;

	/*	for (int i = 0; i < all_trains_.size(); i++)
			if ((*all_trains_[i]).get_status() == 1 || (*all_trains_[i]).get_status() == 4) {
				//std::cout << "L'HO MESSO DENTRO\n";
				n++;
			}*/

	onRails_.erase(onRails_.begin(), onRails_.end());
	
	for (int i = 0; i < all_trains_.size(); i++)
		if ((*all_trains_[i]).get_status() == 1 || (*all_trains_[i]).get_status() == 4) {
			onRails_.push_back(all_trains_[i]);
		
	}
	std::cout << std::endl;
}

void Rails::dont_crash() {

	std::vector<std::shared_ptr<Train>> straight;
	std::vector<std::shared_ptr<Train>> backwards;

	running();

	if (onRails_.size() >= 2)
	{

		onRailsSort();
		
		for (int i = 0; i < onRails_.size(); i++) {
			if (onRails_[i]->from == 0)
				straight.push_back(onRails_[i]);
			else
				backwards.push_back(onRails_[i]);
		}

		if (straight.size() >= 2)
			for (int i = 0; i < straight.size() - 1; i++)
				distance(straight[i], straight[i + 1]);

		if (backwards.size() >= 2)
			for (int i = backwards.size() - 1; i > 0; i--)
				distance(backwards[i], backwards[i-1]);
	}
}