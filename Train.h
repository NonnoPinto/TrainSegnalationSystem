/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#pragma once
#include <iostream>
#include <algorithm>
#include <vector> 
 

class Train{
	
public:
	//Costruttore della classe Train
	Train(): nTrain(0)								//costruttore di default
		{throw std::invalid_argument("Input needed!");};

	//Il costruttore ha come unico argomento il numero del treno
	Train(int n): nTrain(n){};
	
	//disabilito costruttore di copia e l'assegnamento di copia
	Train(const Train&) = delete;
	Train& operator=(const Train&) = delete;
	
	//overload ==
	bool operator==(Train& T) {return nTrain == T.nTrain;};
	
	//funzione di riconoscimento del treno
	const int train_number(const Train &T) const {return T.nTrain;};
	
	virtual void update_pos(const int time_) = 0;
	
	virtual void set_speed (const int v) = 0;
	
	virtual void set_status (const int s) = 0;
	
	virtual int myDelay (const int clock_) = 0;
	
	virtual void just_passed () = 0;
	
	//SOTTO-SOTTOCLASSE
	//my_sort
	virtual bool myDist (Train &T1, Train &T2) = 0;/*
		{if (T1.from == 0) return (T1.pos < T2.pos);
		 else return (T2.pos < T1.pos);};*/
	
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	virtual void distance(Train &T1, const Train &T2) = 0;
	
	//tiene una lista dei treni in moto 
	virtual void running (std::vector<Train>& v) = 0;/* //DI QUESTA FA L'OVERRIDE UNA SOTTO-SOTTOCLASSE
		for (int i = 0; i < v.size(); i++)
			if(v[i].status == 1)
				onRails_.push_back(v[i]);};*/
	
	//elimina i treni dopo che sono arrivati al capolinea
	virtual void arrived (Train &T) = 0;/* //DI QUESTA FA L'OVERRIDE UNA SOTTO-SOTTOCLASSE
		int i = -1;
		do i++;
		while(running_[i] == T);
		running_.erase(running_.begin()+i);};*/
	
	//STL sort
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	virtual void onRailsSort (std::vector<Train>& v) = 0;/*{
		std::sort (v.begin(), v.end(), myDist);
	};*/
	
	virtual bool const runningIsFree() = 0; //{return running_.size() == 0;};
	
protected:
	//numero del treno
	const int nTrain;

//VIARIABILI MEMBRO DELLA SOTTO-SOTTOCLASSE
/*private:
	//sono definiti private due vettori della sola classe Train
	//treni non fermi
	static std::vector<Train> onRails_;

	//treni in marcia
	static std::vector<Train> running_;*/
};