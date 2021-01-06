#pragma once

#include "Station.h"

class LStation : public Station
{
public:
	LStation(std::string n, double d) : Station(n, d) {};
	
	bool isParkAreaEmpty() override { return (parking_area.front()==nullptr); }
	bool isRailFree(int p) override;

	int signalResponse(bool stopping, int v, Train& t) override;
	void parkTrain(int p, Train& t) override;
	void approaching(Traint& t) override;
	void startTrain(int p) override;

	const int station_type = 1;			//Che tipo di stazione è: 0 == Principale, 1 == Locale

private:
	const int nrails = 6;		//Numero di binari che possiede la stazione (4 per principali, 6 per locali)
	int nTrains = 0;
};