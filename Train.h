/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#ifndef Train_h
#define Train_h

#include "TrainStation.h"

#include <iostream>
#include <algorithm> 
#include <vector>

class Train : public TrainStation {
	
public:
	//Costruttore della classe Train
	Train(): nTrain(0)								//costruttore di default
		{throw std::invalid_argument("Input needed!");};

	//Il costruttore ha come unico argomento il numero del treno
	Train(int n): nTrain(n){};
	
	//disabilito costruttore di copia e l'assegnamento di copia
	//Train(const Train&) = delete;
	Train& operator=(const Train&) = delete;
	
	//overload !=
	bool operator!=(Train &T) {return nTrain != T.nTrain;};
	
	//int get_status() const {return status;};
	
	double update_pos() override;
	
	int myDelay (const int clock_) override;
	
	/*//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < (km di sicurezza + dist_max), rallenta quello accodato
	virtual void distance(Train &T1, const Train &T2) = 0;
	
	//tiene una lista dei treni non fermi
	virtual void running (std::vector<Train>& v) = 0;
	
	//elimina i treni dopo che sono arrivati al capolinea
	virtual void arrived () = 0;
	
	virtual bool runningIsFree() = 0;
	
	//STL sort
	//my_sort
	virtual bool myDist (Train &T1, Train &T2) = 0;
	
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	virtual void onRailsSort (std::vector<Train>& v) = 0;*/
	
	//numero del treno
	const int nTrain;
	
	void set_speed (const int v) override {vCrociera = v;};
	
	void set_status (const int s) {status = s;};
	
	
//protected:
	void set_timeTable(std::vector<int>& t) {time = t;};
	
	//velocità di crociera
	int vCrociera = 0;
	
	//posizione attuale del treno lungo la linea ferroviaria
	double pos = 0;
	
	//ritardo accumulato
	int delay = 0;
	
	//stazioni raggiunte
	int station_ = 0;
	
	//varibiale di controllo sullo stato del treno
	//0 == alla stazione di partenza, 1 == in marcia,
	//2 == fermo (parcheggio o fermata), 3 == arrivato a destinazione
	int status = 0;
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	std::vector<int> time;
	
};

#endif