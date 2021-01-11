/* author: Giovanni Zago - 1226024
 * Questo header + una prima classe derivata "Treni". A sua volta ha tre classi derivate.
 * Implementa le funzioni virtuali della classe base,
 * lasciando il costruttore ai diversi tipi di treno.*/

#ifndef Train_h
#define Train_h

#include "TrainStation.h"

/*#include <iostream>
#include <algorithm> 
#include <vector>*/

class Train : public TrainStation {
	
public:
	//Costruttore di defaue base della classe Train
	//Lancia "invlad argoument" se manca il numero del treno
	Train(): nTrain(0)
		{//throw std::invalid_argument("Input needed!");
	};

	//Costruttore
	//Il costruttore ha come unico argomento il numero del treno
	Train(int n): nTrain(n){};
	
	//blocco costruttore di copia e assegnamento di copia 
	Train(const Train& T) = delete;
	Train& operator=(const Train &T) = delete;
	
	//overload == per il confronto tra treni
	//il numero del treno lo identifica univocamente
	bool operator==(Train &T) {return nTrain == T.nTrain;};
	
	//overload != per il confronto tra treni
	bool operator!=(Train &T) {return nTrain != T.nTrain;};
	
	//variabili memebro pubbliche
	//è lasciata pubblica per facilitarne l'accesso alle altre classi
	//conservando l'incapsulamento grazia al suo essere const
	//numero del treno
	const int nTrain;
	
	//funzione principale che, ad ogni ciclo,
	//aggiorna la posizione del treno in base allo status e alla v di crociera
	virtual double update_pos() = 0;
	
	//funzione che calcola il ritardo del treno ad ogni stazione raggiunta
	//e tiene il conto delle stazioni (comprese quelle in cui non si ferma)
	virtual int myDelay (int clock_) = 0;

	virtual int get_status() const = 0;
	
	virtual int get_time(int x) const = 0;

	virtual int get_rail() const = 0 ;

	virtual double get_pos() const = 0;

	virtual int get_speed() const = 0;

	virtual int get_delay() const = 0;

	virtual bool stop_next_station() = 0;

	//tipo di treno
	int train_type;

	//velocità masssima
	int vMax;

	//distanza massima tra due treni (i 10 km di sicurezza + i km percorsi in un minuto)
	int dist_max;

	//variabile di controllo dell'orgine del treno
	int from;

	//restituisce il successivo tempo di arrivo in base al senso di marcia
	virtual int get_next_arrival() const = 0;

	//restituisce la stazione successiva in base al senso di marcia
	virtual int get_next_station() const = 0;
	
	//funzione che aggiorna la velocità di crociera del treno
	virtual void set_speed (const int v) = 0;
	
	//funzione per la modifica dello stato del treno
	virtual void set_status (const int s) = 0;
	
	//imposta il binario di transito
	virtual void set_rail(int x) = 0;
};

#endif