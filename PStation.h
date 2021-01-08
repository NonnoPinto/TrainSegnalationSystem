/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "Station"*/

#ifndef PSTATION_H
#define PSTATION_H

#include "Station.h"

class PStation : public Station
{
public:
	PStation(std::string n, int d) : Station(n, d){
		set_ntrains(0);
		set_nrails(4);
		set_station_type(0);
		set_rails(nrails);
	}
	
	bool isParkAreaEmpty()  { return (parking_area.size() == 0); }
	bool isRailFree(int p);

	int signalResponse(bool stopping, Train& t);
	void parkTrain(int p, Train& t);
	void approaching(Train& t);
	void startTrain(Train& t);
	
	/*double update_pos() override {return 0;};
	
	int myDelay (const int clock_) override {return 0;};
	
	void set_timeTable(std::vector<int> &t) override {};
	
	void set_train_type(int x) override {};
	
	void set_vMax(int x) override {};
	
	void set_dist_max(int x) override {};
	
	void set_from(int x) override {};
	
	void set_speed (const int v) override {};*/
};

#endif // PSTATION_H