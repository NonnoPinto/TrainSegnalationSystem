/* author: Giovanni Zago - 1226024
 * Header della classe derivata "Rails" 
 * Gestisce le funzioni di comunicazione tra i treni e le stazioni*/
 
#pragma once
#include "Rails.h"

template <typename L>
//controlla la distanza tra due treni (T2 è più avanti di T1)
//e se la distanza è < DIST_MAX, rallenta quello accodato
void Rails<L>::distance(L &T1, const L &T2){
	if (abs(T1.pos - T2.pos)<T1.dist_max)
		T1.vCrociera = T2.vCrociera;
}

template <typename L>
//tiene una lista dei treni in moto 
void Rails<L>::running (std::vector<Train<L>> &v){
	for (int i = 0; i < v.size(); i++)
		if(v[i].get_status() == 1)
			onRails_.push_back(v[i]);
}

//STL sort
template <typename L>
//my_sort
bool Rails<L>::myDist (L &T1, L &T2){
	if (T1.from == 0)
		return (T1.pos < T2.pos);
	else
		return (T2.pos < T1.pos);
}

template <typename L>
//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
void Rails<L>::onRailsSort (std::vector<Train<L>>& v){
	std::sort (v.begin(), v.end(), myDist);
}

template <typename L>
//elimina i treni dopo che sono arrivati al capolinea
void Rails<L>::arrived (Train<L> &T){
	int i = -1;
	do i++;
	while(running_[i] == T);
	running_.erase(running_.begin()+i);
}

template <typename L>
bool Rails<L>::runningIsFree() {return running_.size() == 0;}