#include "Train.h"

class AVSTrain : public Train{
	public:
	//Costruttore della classe Train
	//Ogni oggetto della classe ha le stesse variabili
	//Definite in base al tipo di treno
	AVSTrain();										//costruttore di default
	
	AVSTrain(int type_, int from_);					//costruttore
	
	//calcola la posizione del treno
	void update_pos(int time_) override;
	
	//mette in ordine i treni in marcia attualmente non fermi
	void onRails (std::vector<Train> v) override;
	
	//controlla la distanza tra due treni
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void distance(Train &T1, Train &T2) override;
	
	//tiene una lista dei treni in moto 
	void running (Train &T) override;
	
	//elimina i treni dopo che sono arrivati al capolinea
	void arrived (Train &T) override;
};