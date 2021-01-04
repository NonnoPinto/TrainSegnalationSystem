/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#pragma once
#include <iostream>
#include <algorithm>
#include <vector> 

template <typename L>  class Train{
	
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
	
	void get_status (const int s) {status = s;};
	
	const int set_status() const {return status;};
	
	virtual void set_speed (const int v) = 0;
	
	void update_pos(const int time_);
	
	virtual const int get_km() const = 0;
	
	virtual int myDelay (const int clock_) = 0;
	
	virtual void just_passed () = 0;
	
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	virtual void distance(L &T1, const L &T2) = 0;
	
	//tiene una lista dei treni in moto 
	virtual void running (std::vector<Train>& v) = 0;
	
	//elimina i treni dopo che sono arrivati al capolinea
	virtual void arrived (Train &T) = 0;
	
	virtual bool runningIsFree() = 0;
	
	//STL sort
	//my_sort
	virtual bool myDist (L &T1, L &T2) = 0;
	
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	virtual void onRailsSort (std::vector<Train>& v) = 0;
	
protected:
	//numero del treno
	const int nTrain;
	
	//varibiale di controllo sullo stato del treno
	//0 == alla stazione di partenza, 1 == in marcia,
	//2 == fermo (parcheggio o fermata), 3 == arrivato a destinazione
	int status = 0;
};