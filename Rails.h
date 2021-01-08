/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#ifndef Rails_h
#define Rails_h

#include "RTrain.h"
#include "AVTrain.h"
#include "AVSTrain.h"

class Rails : public RTrain, public AVTrain, public AVSTrain{

public:
	Rails() {throw std::invalid_argument ("I need trains!");};
	
	Rails(std::vector<Train> v){all_trains_=v;};
	
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(Train &T1, const Train &T2);
	
	//tiene una lista dei treni in moto 
	void running (std::vector<Train>& v);
	
	//elimina i treni dopo che sono arrivati al capolinea
	void arrived (Train &T);
	
	bool runningIsFree();
	
	//STL sort
	//my_sort
	//bool myDist (Train &T1, Train &T2);
	
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	void onRailsSort ();
	
	void dont_crash();
	
	void start(Train& T) {running_.push_back(T);};
	
private:
	//sono definiti private due vettori della sola classe Train
	//treni non fermi
	std::vector<Train> onRails_;
	
	//treni in marcia
	std::vector<Train> running_;
	
	//tutti i treni
	std::vector<Train> all_trains_;
	
	//treni arrivani
	int arrived_ = 0;

};

#endif