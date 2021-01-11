/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "Station"*/

#ifndef PSTATION_H
#define PSTATION_H

#include "Station.h"

class PStation : public Station
{
public:
	PStation(std::string n, int d) : Station(n, d) {
		//Inizializzazione variabili membro in base al tipo di stazione
		//Numero binari della stazione = 4 (principale)
		set_nrails(4);
		//Tipo di stazione = 0 (principale)
		set_station_type(0);
		//Impostazione dimensione del vettore rails = nrails(4)
		set_rails(nrails);
	}

	//bool isFull() override { return ntrains == 4; }

	//Comunica è libero il parcheggio (o se ci sono treni rimasti)
	//bool isParkAreaEmpty() override { return (parking_area.size() == 0); }

	//Comunica se un dato binario è libero
	//bool isRailFree(int p) override;

	//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), 
	//verso del treno (dato dalla velocità) e condizione dei binari (se sono liberi o meno). 
	//Il segnale viene inviato a 20km di distanza dalla stazione
	int signalResponse(bool stopping, std::shared_ptr<Train> t) override;

	//Comunica l'avvicinamento (5km) di un treno verso la stazione e impone un limite di velocità di 80km/h
	void approaching(std::shared_ptr<Train> t) override;

	//Parcheggia il treno su un dato binario, oppure su un parcheggio se tutti i binari sono occupati
	//La scelta del binario viene gestita dalla funzione signalResponse
	void parkTrain(int p, std::shared_ptr<Train> t) override;

	//Fa partire un treno dalla stazione con un limite di velocità di 80km/h e sposta un treno dal parcheggio
	//sul binario liberato
	void startTrain(std::shared_ptr<Train> t) override;

	//Comunica quando un treno partito risulta a più di 5km da una stazione 
	//e lo fa accelerare alla sua massima velocità
	void leaving(std::shared_ptr<Train> t) override;

	//Distruttore della figlia chiama il distruttore della classe derivata
	virtual ~PStation() { std::cout << "DISTRUTTORE CLASSE FIGLIA \n"; };

	//void printTrainType(std::shared_ptr<Train> t) override;

	//void set_rails(int n) override;
};

#endif // PSTATION_H