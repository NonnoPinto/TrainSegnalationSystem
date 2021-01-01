#include "Train.h"

class AVSTrain(){
	//Costruttore della classe Train
	//Ogni oggetto della classe ha le stesse variabili
	//Definite in base al tipo di treno
	Train(){										//costruttore di default
		throw std::invalid_argument("I need the train kind");
	}
	
	Train(int type_, int from_){					//costruttore
		train_type = type_; //inizializzo il tipo di treno
		
		switch(type_){		//inizializzo la massima velocità di crociera
		case 1 :
			vMax = 160;
		}
	}
	
	//calcola la posizione del treno
	void update_pos(int time_) override{}
	
	//mette in ordine i treni in marcia attualmente non fermi
	void onRails (std::vector<Train> v) override{}
	
	//controlla la distanza tra due treni
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void virtual distance(Train &T1, Train &T2) = 0;
	
	//tiene una lista dei treni in moto 
	void virtual running (Train &T) = 0;
	
	//elimina i treni dopo che sono arrivati al capolinea
	void virtual arrived (Train &T) = 0;
}