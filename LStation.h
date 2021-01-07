/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "LStation"*/

#ifndef LSTATION_H
#define LSTATION_H

#include "Station.h"

class LStation : public Station
{
public:
	LStation(std::string n, int d) : Station(n, d){
		set_ntrains(0);
		set_nrails(4);
		set_station_type(0);
	};
	
	bool isParkAreaEmpty()  { return (parking_area.size() == 0); }
	bool isRailFree(int p) ;

	int signalResponse(bool stopping, int v, Train& t) ;
	void parkTrain(int p, Train& t) ;
	void approaching(Train& t) ;
	void startTrain(int p) ;
};

#endif // LSTATION_H