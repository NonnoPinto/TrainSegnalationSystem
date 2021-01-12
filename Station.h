/* author: Andrei Ovidiu Danciu - 1224263
 * Header della classe "Station"*/

#ifndef STATION_H
#define STATION_H

#include "TrainStation.h"
#include "Train.h"

#include <iostream>
#include <vector>
#include <queue>

class Station : public TrainStation
{
public:
	//***COSTRUTTORE
	Station(std::string n, int d) : name(n), distance(d), ntrains(0) {};

	//***ELIMINAZIONE COSTRUTTORE DI COPIA E ASSEGNAMENTO DI COPIA
	Station(const Station&) = delete;
	Station& operator=(const Station&) = delete;

	//FUNZIONI AUSILIARIE
	bool isRailFree(int p);											//Controlla se un dato binario è libero

	bool isRailSaved(int p);										//Controlla se un dato binario è prenotato

	bool isFull() { return ntrains == 4; }							//Controlla se i binari standard sono tutti occupati

	bool isParkAreaEmpty() { return (parking_area.size() == 0); }	//Controlla se il parcheggio è vuoto

	std::string printTrainType(std::shared_ptr<Train> t);			//Restituisce una stringa col tipo di treno

	void set_rails(int n);											//Inizializza i binari


	//***FUNZIONI VIRTUALI IMPLEMENTATE DALLE CLASSI FIGLIE
	//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), verso del treno (dato dalla velocità) 
	//e condizione dei binari (se sono liberi o meno). Il segnale viene inviato a 20km di distanza dalla stazione
	virtual int signalResponse(bool stopping, std::shared_ptr<Train> t) = 0;

	//Comunica l'avvicinamento (5km) di un treno verso la stazione e impone un limite di velocità di 80km/h
	virtual void approaching(std::shared_ptr<Train> t) = 0;

	//Parcheggia il treno su un dato binario, oppure su un parcheggio se tutti i binari sono occupati
	//La scelta del binario viene gestita dalla funzione signalResponse
	virtual void parkTrain(int p, std::shared_ptr<Train> t) = 0;

	//Fa partire un treno dalla stazione con un limite di velocità di 80km/h 
	//e sposta un treno dal parcheggio sul binario liberato
	virtual void startTrain(std::shared_ptr<Train> t) = 0;

	//Comunica quando un treno partito risulta a più di 5km da una stazione 
	//e lo fa accelerare alla sua massima velocità
	virtual void leaving(std::shared_ptr<Train> t) = 0;


	//***COSTANTI (Pubbliche perchè non si possono modificare
	const int distance;		//Distanza (km) della stazione dall'origine

	const std::string name;	//Nome della stazione
protected:
	//***STRUTTURE IMPLEMENTATE
	//Struttura per gestire i binari
	std::vector<std::shared_ptr<Train>> rails;
	std::vector<int> savedrails;

	//Struttura per gestire il parcheggio
	std::vector<std::shared_ptr<Train>> parking_area;

	//Numero di treni parcheggiati sui binari standard (quelli in transito non si fermano)
	int ntrains;

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