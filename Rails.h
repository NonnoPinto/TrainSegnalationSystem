/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#pragma once
#include "RTrain.h"
#include "AVTrain.h"
#include "AVSTrain.h"
template <typename L>

class Rails : public RTrain<L>, public AVTrain<L>, public AVSTrain<L>{
public:
	Rails() {throw std::invalid_argument ("I need trains!");};
	
	Rails(std::vector<Train<L>> v): trains_(v){};
	
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(L &T1, const L &T2) override;
	
	//tiene una lista dei treni in moto 
	void running (std::vector<Train<L>>& v) override;
	
	//elimina i treni dopo che sono arrivati al capolinea
	void arrived () override;
	
	bool runningIsFree() override;
	
	//STL sort
	//my_sort
	bool myDist (L &T1, L &T2) override;
	
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	void onRailsSort (std::vector<Train<L>>& v) override;
	
private:
	//sono definiti private due vettori della sola classe Train
	//treni non fermi
	std::vector<Train<L>> onRails_;
	
	//treni in marcia
	std::vector<Train<L>> running_;
	
	//tutti i treni
	const std::vector<Train<L>> trains_;
};