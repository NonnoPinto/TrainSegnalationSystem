/* author: Andrei Ovidiu Danciu - 1224263
 * Header della classe derivata "Station"*/

#ifndef STATION_H
#define STATION_H

#include "TrainStation.h"
#include "Train.h"

/*#include <iostream>
#include <vector>
#include <queue>*/

class Station : public TrainStation
{
public:
	Station(std::string n, int d) : name(n), distance(d), ntrains(0) {};

	//Eliminazione costruttore di copia e assegnamendo di copia
	Station(const Station&) = delete;
	Station& operator=(const Station&) = delete;
	//virtual ~Station();
	//Controlla se i binari standard sono tutti occupati
	bool isFull() { return ntrains == 4; }

	//Controlla se il parcheggio è vuoto
	bool isParkAreaEmpty() { return (parking_area.size() == 0); }

	//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), 
	//verso del treno (dato dalla velocità) e condizione dei binari (se sono liberi o meno). 
	//Il segnale viene inviato a 20km di distanza dalla stazione
	virtual int signalResponse(bool stopping, std::shared_ptr<Train> t) = 0;

	//Comunica l'avvicinamento (5km) di un treno verso la stazione e impone un limite di velocità di 80km/h
	virtual void approaching(std::shared_ptr<Train> t) = 0;

	//Parcheggia il treno su un dato binario, oppure su un parcheggio se tutti i binari sono occupati
	//La scelta del binario viene gestita dalla funzione signalResponse
	virtual void parkTrain(int p, std::shared_ptr<Train> t) = 0;

	//Fa partire un treno dalla stazione con un limite di velocità di 80km/h e sposta un treno dal parcheggio
	//sul binario liberato
	virtual void startTrain(std::shared_ptr<Train> t) = 0;

	//Comunica quando un treno partito risulta a più di 5km da una stazione 
	//e lo fa accelerare alla sua massima velocità
	virtual void leaving(std::shared_ptr<Train> t) = 0;

	std::string printTrainType(std::shared_ptr<Train> t);

	 void set_rails(int n);

	 //Controlla se un dato binario è libero
	 bool isRailFree(int p);

	//Distanza (km) della stazione dall'origine
	const int distance;

	//Nome della stazione
	const std::string name;
protected:

	//Numero di treni parcheggiati sui binari standard (quelli in transito non si fermano)
	int ntrains;

	//Struttura per gestire i binari
	std::vector<std::shared_ptr<Train>> rails;

	//Struttura per gestire il parcheggio
	std::vector<std::shared_ptr<Train>> parking_area;

	//Che tipo di stazione è: 0 == Principale, 1 == Locale
	int station_type;
	//Funzione per impostare il numero di binari (usata nei costruttori delle figlie)
	void set_station_type(int ty) { station_type = ty; }

	//Numero di binari che possiede la stazione (4 per principali, 6 per locali)
	int nrails;
	//Funzione per impostare il numero di binari (usata nei costruttori delle figlie)
	void set_nrails(int nrl) { nrails = nrl; }
};

#endif // STATION_H