/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#pragma once
#include "Train.h"
#include "RTrain.h"
#include "AVTrain.h"
#include "AVSTrain.h"

class Rails : public RTrain, public AVTrain, public AVSTrain{
public:
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(L &T1, L &T2) override;
	
	//tiene una lista dei treni in moto 
	void running (std::vector<Train>& v) override;
	
	//elimina i treni dopo che sono arrivati al capolinea
	void arrived (Train &T) override;
	
	bool runningIsFree() override;
	
	//STL sort
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	void onRailsSort (std::vector<Train>& v) override;
	
	//my_sort
	bool myDist (L &T1, L &T2) override;
	
private:
	//sono definiti private due vettori della sola classe Train
	//treni non fermi
	std::vector<Train> onRails_;
	
	//treni in marcia
	std::vector<Train> running_;
};