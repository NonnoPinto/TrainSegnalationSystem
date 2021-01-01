/* author: Giovanni Zago - 1226024
 * Questo header fa da classe principale di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#include <iostream>
#include <vector> 
 

class Train{
	
public:
	//Costruttore della classe Train
	//Ogni oggetto della classe ha le stesse variabili
	//Definite in base al tipo di treno
	Train();										//costruttore di default
	
	Train(int type_, int from_);					//costruttore
	
	//funzione che calcola la posizione del treno
	void virtual update_pos(int time_) = 0;
	

private:
	//velocità massima del tipo di treno
	const int VMAX;
	//velocità di crociera
	int vCrociera;
	//tipo di treno: 1 == R, 2 == AV, 3 == AVS
	int train_type;
	//stazione di partenza: 0 == la prima, 1 == l'ultima
	int from;
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	std::vector<int> time;
	//ritardo accumulato
	int delay;
	//varibiale di controllo sullo stato del treno
	//0 == in marcia, 1 == alla stazione di partenza
	//2 == al parcheggio, 3 == in una fermata
	int status;
	//posizione attuale del treno lungo la linea ferroviaria
	double pos;
};