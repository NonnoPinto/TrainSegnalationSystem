/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "LStation"*/

#ifndef LSTATION_H
#define LSTATION_H

#include "Station.h"

class LStation : public Station
{
public:
	LStation(std::string n, int d) : Station(n, d) {
		//Inizializzazione variabili membro in base al tipo di stazione
		//Numero binari della stazione = 6 (locale)
		set_nrails(6);
		//Tipo di stazione = 1 (locale)
		set_station_type(1);
		//Impostazione dimensione del vettore rails = nrails (in questo caso 6)
		set_rails(nrails);
	};

	//bool isFull() override { return ntrains == 4; }

	//Comunica è libero il parcheggio (o se ci sono treni rimasti)
	//bool isParkAreaEmpty() override { return (parking_area.size() == 0); }

	//Comunica se un dato binario è libero o meno
	//bool isRailFree(int p) override;

	//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), 
	//verso del treno (dato dalla velocità) e condizione dei binari (se sono liberi o meno). 
	//Il segnale viene inviato a 20km di distanza dalla stazione
	int signalResponse(bool stopping, std::shared_ptr<Train> t) override;

	//Comunica l'avvicinamento (5km) di un treno verso la stazione e impone un limite di velocità di 80km/h
	void approaching(std::shared_ptr<Train> t);

	//Parcheggia il treno su un dato binario, oppure su un parcheggio se tutti i binari sono occupati
	//La scelta del binario viene gestita dalla funzione signalResponse
	void parkTrain(int p, std::shared_ptr<Train> t);

	//Fa partire un treno dalla stazione con un limite di velocità di 80km/h e sposta un treno dal parcheggio
	//sul binario liberato
	void startTrain(std::shared_ptr<Train> t);

	//Comunica quando un treno partito risulta a più di 5km da una stazione 
	//e lo fa accelerare alla sua massima velocità
	void leaving(std::shared_ptr<Train> t);

	//Distruttore della figlia chiama il distruttore della classe derivata
	virtual ~LStation() { std::cout << "DISTRUTTORE CLASSE FIGLIA \n"; };

	//void printTrainType(Train* t) override;

	//void set_rails(int n) override;
};

#endif // LSTATION_H