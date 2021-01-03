/* author: Giovanni Zago - 1226024
 * Questo header fa da classe base di "Treni"
 * Oltre al costruttore, sono presenti funzioni che regolano la distanza tra due treni
 * e che tengono una lista ordinata dei treni in movimento*/

#include <iostream>
#include <algorithm>
#include <vector> 
 

class Train{
	
public:
	//Costruttore della classe Train
	//Ogni oggetto della classe ha le stesse variabili
	//Definite in base al tipo di treno
	Train(): nTrain(0), train_type(0), vMax(0), from (0)		//costruttore di default
		{throw std::invalid_argument("Input needed!");};

	//Il costruttore ha come argomenti
	//tipo del treno
	//stazione di partenza (in km) - 0 se la prima, altriemnti la lunghezza della linea
	//gli orari di arrivo previsti per ogni stazione
	Train(	int n, int type_, int v,							//costruttore - inizializza
			int from_, std::vector<int> &timeTable):			//tutte le varibiali membro
				nTrain(n), train_type(type_), vMax(v), from(from_),
				status(0), time(timeTable), vCrociera(0), delay(0), pos(0){
	//DA RISOLVERE LA QUESTIONE DELLA POSIZIONE DI CHI PARTE DALLA FINE
	if (from == 1){
		vMax = -vMax;		//se il treno parte dall'ultima stazione, inizializzo una
		pos = 200;}			//velcità negativa e con posizione == distanza massima
							//dalla prima fermata
	
	dist_max = 10 + v/60;}; //la distanza massima è la somma dei 10 km di sicurezza
							//più i chilometri che un treno (alla sua velocità massima)
							//può percorrere in un minuto (unità di tempo minima)
	
	//calcola la posizione del treno
	virtual void update_pos(const int time_) = 0;
	
	//controlla la distanza tra due treni (T2 è più avanti di T1)
	//e se la distanza è < DIST_MAX, rallenta quello accodato
	virtual void distance(Train &T1, const Train &T2) = 0;
	
	virtual void update_speed (int v) = 0;
	
	
	//***funzioni membro di Train***
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
	
	//***helper functions***
	//my_sort
	static bool myDist (Train &T1, Train &T2)
		{if (T1.from == 0) return (T1.pos < T2.pos);
		 else return (T2.pos < T1.pos);};
	
	//STL sort
	//mette in ordine i treni non fermi in base alla loro posizione lungo la ferrovia
	void onRailsSort (std::vector<Train>& v){
		std::sort (v.begin(), v.end(), myDist);
	};
	
	//overload ==
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
	};
	
	
	//***variabili membro pubbliche***
	//(sono definite pubbliche tutte le variabili const
	//per facilitare la comunicazioni tra classi
	//conservando la protezione dei dati)
	//numero del treno
	const int nTrain;
	
	//tipo di treno: 1 == R, 2 == AV, 3 == AVS
	const int train_type;
	
	//stazione di partenza: 0 == la prima, 1 == l'ultima
	const int from;
	
protected:
	//sono definite come protected tutte le varibili necessarie alle classi derivate
	
	//velocità massima del tipo di treno
	int vMax;
	
	//distanza massima tra due treni
	int dist_max;
	
	//velocità di crociera
	int vCrociera;
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	const std::vector<int> time;
	
	//varibiale di controllo sullo stato del treno
	//0 == alla stazione di partenza, 1 == in marcia
	//2 == al parcheggio, 3 == in una fermata, 4 == arrivato a destinazione
	int status;
	
	//posizione attuale del treno lungo la linea ferroviaria
	double pos;
	
	//ritardo accumulato
	int delay;
	
private:
	//sono definiti private due vettori della sola classe Train
	//treni non fermi
	static std::vector<Train> onRails_;

	//treni in marcia
	static std::vector<Train> running_;
};