/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails"
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/

#ifndef Rails_h
#define Rails_h

#include "RTrain.h"
#include "AVTrain.h"
#include "AVSTrain.h"

class Rails : public RTrain, public AVTrain, public AVSTrain {

public:
	Rails() { throw std::invalid_argument("I need trains!"); };

	Rails(std::vector<std::shared_ptr<Train>>& v) {
		all_trains_.resize(v.size());
		for (int i = 0; i < v.size(); i++) {
			all_trains_[i] = v[i];
		}
	};

	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(std::shared_ptr<Train> T1, std::shared_ptr<Train> T2);

	//tiene una lista dei treni in moto 
	void running();

	//elimina i treni dopo che sono arrivati al capolinea
	void arrived(Train& T);

	bool runningIsFree();

	//STL sort
	//my_sort
	//bool myDist (Train &T1, Train &T2);

	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	void onRailsSort();

	void dont_crash();

	//private:
		//sono definiti private due vettori della sola classe Train
		//treni non fermi
	std::vector<std::shared_ptr<Train>> onRails_;

	//tutti i treni
	std::vector<std::shared_ptr<Train>> all_trains_;

	//treni arrivani
	int arrived_ = 0;

};

#endif