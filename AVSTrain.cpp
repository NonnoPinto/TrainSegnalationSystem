#include "AVSTrain.h"

//Costruttore della classe Train
//Ogni oggetto della classe ha le stesse variabili
//Definite in base al tipo di treno
AVSTrain::AVSTrain(){										//costruttore di default
	throw std::invalid_argument("I need the train kind");
}

AVSTrain::AVSTrain(int type_, int from_){					//costruttore
	train_type = type_; //inizializzo il tipo di treno
	
	switch(type_){		//inizializzo la massima velocità di crociera
	case 1 :
		vMax = 160;
	}
}

//calcola la posizione del treno
void AVSTrain::Train::update_pos(int time_) {}

//mette in ordine i treni in marcia attualmente non fermi
void AVSTrain::onRails (std::vector<Train> v) {}

//controlla la distanza tra due treni
//e se la distanza è < DIST_MAX, rallenta quello accodato
void AVSTrain::distance(Train &T1, Train &T2) {};

//tiene una lista dei treni in moto 
void AVSTrain::running (Train &T) {};

//elimina i treni dopo che sono arrivati al capolinea
void AVSTrain::arrived (Train &T) {};
