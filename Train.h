/* author: Giovanni Zago - 1226024
 * Questo header + una prima classe derivata "Treni". A sua volta ha tre classi derivate.
 * Implementa le funzioni virtuali della classe base,
 * lasciando il costruttore ai diversi tipi di treno.*/

#ifndef Train_h
#define Train_h

#include "TrainStation.h"

#include <iostream>
#include <algorithm> 
#include <vector>

class Train : public TrainStation {
	
public:
	//Costruttore di defaue base della classe Train
	//Lancia "invlad argoument" se manca il numero del treno
	Train(): nTrain(0)
		{throw std::invalid_argument("Input needed!");};

	//Costruttore
	//Il costruttore ha come unico argomento il numero del treno
	Train(int n): nTrain(n){};
	
	Train& operator=(const Train &T);
	
	//overload == per il confronto tra treni
	//il numero del treno lo identifica univocamente
	bool operator==(Train &T) {return nTrain == T.nTrain;};
	
	//overload != per il confronto tra treni
	bool operator!=(Train &T) {return nTrain != T.nTrain;};
	
	//override della funzione principale che, ad ogni ciclo,
	//aggiorna la posizione del treno in base allo status e alla v di crociera
	double update_pos() override;
	
	//override in line della funzione che aggiorna la velocità di crociera del treno
	void set_speed (const int v) override {vCrociera = v;};
	
	//funziona per la modifica dello stato del treno
	void set_status (const int s) {status = s;};
	
	//override funzione che calcola il ritardo del treno ad ogni stazione raggiunta
	//e tiene il conto delle stazioni (comprese quelle in cui non si ferma)
	int myDelay (const int clock_) override;
	
	//variabili memebro pubbliche
	//è lasciata pubblica per facilitarne l'accesso alle altre classi
	//conservando l'incapsulamento grazia al suo essere const
	//numero del treno
	const int nTrain;
	
	int get_status() const {return status;};
	
	int get_vCrociera() const {return vCrociera;};
	
	int get_pos() const {return pos;};
	
	int get_dist_max() const {return dist_max;};
	
	int get_from() const {return from;};
	
	void set_rail(int x) {myRail = x;};
	
protected:
	
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
	
	//***Variabili membro che differiscono per ogni treno
	//***e rispettive funzioni per accedervi
	
	//vettore con gli orari di arrivo previsti in ogni stazione
	//l'orario è espresso in minuti dopo la partenza
	std::vector<int> time;
	
	void set_timeTable(std::vector<int>& t) override {time = t;};
	
	//tipo di treno
	int train_type;
	
	void set_train_type(int x) override {train_type=x;};
	
	//velocità massima
	int vMax;
	
	void set_vMax(int x) override {vMax = x;};
	
	//distanza massima tra due treni
	int dist_max;
	
	void set_dist_max(int x) override {dist_max = x;};
	
	//variabile di controllo dell'orgine del treno
	int from;
	
	void set_from(int x) override {from = x;};
	
	int myRail = 0;
	
//private:
	
/*	bool isParkAreaEmpty() override;
	
	bool isRailFree(int p) override;
	
	bool isFull() override;
	
	void startTrain(int p) override;
	
	bool runningIsFree() override;*/

};

#endif

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
	
	//int get_status() const {return status;};