/* author: Andrei Ovidiu Danciu - 1224263
 * Header della classe derivata "Station"*/

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
	Station(std::string n, int d) : name(n), distance(d) {};

	//Eliminazione costruttore di copia e assegnamendo di copia
	//Station(const Station&) = delete;
	Station& operator=(const Station&) = delete;

	//Controlla se i binari standard sono tutti occupati
	bool isFull() override  { return (ntrains == 4); }

	//Controlla se il parcheggio è vuoto
	bool isParkAreaEmpty() override { return (parking_area.size() == 0); }

	//Controlla se un dato binario è libero
	bool isRailFree(int p) override;

	//Risponde al segnale ritornando il binario su cui il treno deve andare
	int signalResponse(bool stopping, Train& t);

	//Ferma il treno su un dato binario
	void parkTrain(int p, Train& t);

	//Impone limite di velocità a un treno che si sta avvicinando
	void approaching(Train& t);

	//Fa partire il treno di un dato binario
	void startTrain(Train& t);
	//void leaving();

	int getdistance() const { return distance; }

	const int distance;
	
protected:
	
	//Numero di treni parcheggiati sui binari standard (quelli in transito non si fermano)
	int ntrains;
	
	void set_ntrains(int x) {ntrains = x;};
	
	//Struttura per gestire i binari
	std::vector<Train> rails;

	void set_rails(int n) { rails.resize(n); }

	//Struttura per gestire il parcheggio
	std::queue<Train> parking_area;
	
	//Distanza (km) della stazione dall'origine
	
	
	//Nome della stazione
	const std::string name;
	
	//Che tipo di stazione è: 0 == Principale, 1 == Locale
	int station_type;
	void set_station_type(int ty) {station_type = ty;}
	
	//Numero di binari che possiede la stazione (4 per principali, 6 per locali)
	int nrails;
	void set_nrails(int nrl) {nrails = nrl;}
	
	/*double update_pos() override;
	
	int myDelay (const int clock_) override;
	
	void set_timeTable(std::vector<int> &t) override;
	
	void set_train_type(int x) override;
	
	void set_vMax(int x) override;
	
	void set_dist_max(int x) override;
	
	void set_from(int x) override;
	
	void set_speed (const int v) override;*/
	
};

#endif // STATION_H