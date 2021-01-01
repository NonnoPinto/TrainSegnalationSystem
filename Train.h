/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#include <iostream>
#include <vector> 
 

class Train{
	
public:
	//Costruttore della classe Train
	//Ogni oggetto della classe ha le stesse variabili
	//Definite in base al tipo di treno
	Train(): train_type(4)									//costruttore di default
		{throw std::invalid_argument("Input needed!");};

	//Il costruttore ha come argomenti
	//tipo del treno
	//stazione di partenza (in km) - 0 se la prima, altriemnti la lunghezza della linea
	//gli orari di arrivo previsti per ogni stazione
	Train(int type_, int from_, std::vector<int> &timeTable):	//costruttore - inizializza
		train_type(type_), vCrociera(0), pos(from_), from(from_), 	//tutte le varibiali membro
		status(0), delay(0), time(timeTable){					  	//che non dipendono dal tipo
		
			//velocità massima
			switch(type_){
				case 1: vMax = 160; break;
				case 2: vMax = 240; break;
				case 3: vMax = 300; break;
				default: throw std::invalid_argument("Invalid train type");
			}
	};
	
	//calcola la posizione del treno
	void virtual update_pos(int time_) = 0;
	
	//mette in ordine i treni in marcia attualmente non fermi
	void virtual onRailsSort (std::vector<Train> v) = 0;
	
	//controlla la distanza tra due treni
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	void virtual distance(Train &T1, Train &T2) = 0;
	
	bool operator==(Train& T){
		if(	train_type == T.train_type &&
			vCrociera == T.train_type &&
			pos == T.pos &&
			from == T.from &&
			status == T.status &&
			delay == T.delay &&
			time == T.time &&
			vMax ==T.vMax)
			return true;
		else
			return false;
	}
	
	//tiene una lista dei treni in moto 
	void running (std::vector<Train>& v) {
		for (int i = 0; i < v.size(); i++)
			if(v[i].status == 1)
				onRails_.push_back(v[i]);};
	
	//elimina i treni dopo che sono arrivati al capolinea
	void arrived (Train &T) {
		int i = -1;
		do i++;
		while(running_[i] == T);
		running_.erase(running_.begin()+i);};

protected:
	//distanza massima tra due treni
	const int DIST_MAX = 10; 					//DA CALCOLARE, NON LA RICORDO
	
	//velocità massima del tipo di treno
	int vMax;
	
	//velocità di crociera
	int vCrociera;
	
	//tipo di treno: 1 == R, 2 == AV, 3 == AVS
	const int train_type;
	
	//stazione di partenza: 0 == la prima, 1 == l'ultima
	int from;
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	std::vector<int> time;
	
	//varibiale di controllo sullo stato del treno
	//0 == alla stazione di partenza, 1 == in marcia
	//2 == al parcheggio, 3 == in una fermata, 4 == arrivato a destinazione
	int status;
	
	//posizione attuale del treno lungo la linea ferroviaria
	double pos;
	
	//ritardo accumulato
	int delay;
	
	//treni non fermi
	static std::vector<Train> onRails_;

private:
	//treni in marcia
	static std::vector<Train> running_;

};