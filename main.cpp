#include "ReadTables.h"
#include "LStation.h"
#include "PStation.h"
#include "Rails.h"

using namespace std;

int main(){
	
	//lettura, controllo e ___elaborazione dei dati
	ReadTables TS;
	
	cout << "***Importing data from files***\n";
	TS.read_inputs();
	cout << "***Data importaned succesfully!***\n\n";
	
	//vettori ausialiari per lo storage dei dati
	//timetable
	vector<vector<int>> timeTable = TS.get_timeTable();
	//descrizione della linea ferroviaria
	vector<vector<string>> lineDescription = TS.get_lineDescription();
	
	//vettore delle sole distanze delle stazioni dalla prima
	vector<string> myLineDescription;
	
	//dalla descrizione di ogni stazione, prendo solo la distanza
	//che si trova sempre nella cella di posizione [i][2]
	//con i == numero della stazione
	for(int i = 0; i<lineDescription.size(); i++)
		myLineDescription.push_back(lineDescription[i][2]);
	
	//vettori dei costruttori
	//treni
	vector<Train> trains;
	//stazioni
	vector<Station> stations;
	
	//ogni cella dell vettore trains viene inizializzata con un oggetto di tipo Train
	//A seconda del tipo di treno, viene chiamato il giusto costruttore
	for(int i = 0; i < timeTable.size(); i++){
		int x = timeTable[i][2]; //tipo di treno (Regionale, Alta Velocità, Alta Velocità Super)
		
		//vettore con i soli orari dell'i-esimo treno, senza variaibli di controllo
		//Il vettore con gli orari di ogni treno ha la seguente forma
		//[n.treno][stazione di partenza][tipo teno][orari di arrivo]
		//Nel vettore tmp vengono inseriti solo gli orari
		vector<int> tmp (timeTable[i].begin()+3,timeTable[i].end());
		
		//lo switch decide il tipo di treno e ne chiama il costruttore
		switch(x){
		case 1: //RTrain constructor
			trains.push_back(RTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		case 2: //AVTrain constructor
			trains.push_back(AVTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		case 3: //AVSTrain constructor
			trains.push_back(AVSTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		}
		
	}
	
	for(int i = 0; i< trains.size(); i++)
		cout << trains[i].get_vMax() << endl;

	//ogni cella dell vettore stations viene inizializzata con un oggetto di tipo Station
	//A seconda del tipo di stazione, viene chiamato il giusto costruttore
	for(int i = 0; i < lineDescription.size(); i++){
		int x = stoi(lineDescription[i][1]);
		
		switch(x){
		case 0: //Stazione principale
			stations.push_back(PStation(lineDescription[i][0], stoi(lineDescription[i][2])));
			break;
		case 1: //Stazione locale
			stations.push_back(LStation(lineDescription[i][0], stoi(lineDescription[i][2])));
			break;
		}
	}
	
	cout << "********************************\n";
	cout << "Sono stati creati " << trains.size() << " treni\n";
	cout << "e " << stations.size() << " stazioni!\n";
	cout << "********************************\n";

	Rails R(trains);

	int clock = 0;
	int i;
	int status;
	char c;
	while (!R.runningIsFree())
	{
		i = 0;
		cout << "\nClock: " << clock << endl;
		while (i < trains.size())
		{
			status = trains[i].get_status();
			switch (status)
			{
			case 0:
			{
				if (clock == trains[i].get_time(0))
				{
					int n;
					if (trains[i].get_from() == 0)
						n = 0;
					else
						n = stations.size()-1;
					R.start(trains[i]);
					stations[n].parkTrain(stations[n].signalResponse(true, trains[i]), trains[i]);
					stations[n].startTrain(trains[i]);
				}
				break;
			}
			case 1: case 4:
			{
				if (trains[i].get_from() == 0 && trains[i].get_next_station() == stations.size()){
						trains[i].set_status(3);
						trains[i].set_speed(0);
						R.arrived(trains[i]);
						continue;
				}
				else if (trains[i].get_from() == 1 && trains[i].get_next_station() == 0){
						trains[i].set_status(3);
						trains[i].set_speed(0);
						R.arrived(trains[i]);
						continue;
				}
				double dt = trains[i].get_pos(); //posizione dell'i-esimo treon treno
				double ds = stations[trains[i].get_next_station()].distance; //posizione della prox stazione
				if (trains[i].get_from() == 0)
				{
					if (dt > ds - 1.5 && dt < ds + 1.5)
						trains[i].myDelay(clock);
					else if (dt >= (ds - 5) && trains[i].get_speed() != 80)
						stations[i].approaching(trains[i]);
					else if (dt >= (ds - 20) && trains[i].get_status() != 4)
					{
						trains[i].set_rail(stations[trains[i].get_next_station()].signalResponse(true, trains[i]));
						trains[i].set_status(4);
					}
					else if (dt >= (stations[trains[i].get_next_station() - 1].distance) + 5
						&& dt < (ds-20)
						&& trains[i].get_speed() == 80)
					{
						trains[i].set_speed(trains[i].get_vMax());
						trains[i].set_status(1);
						cout << "\nTrain n. " << trains[i].nTrain << " accelerated to " << trains[i].get_vMax()
							<< " cuz it's mor than 5 km far from the station"<< endl;
					}
				}
				else
				{
					if (dt > ds - 1.5 && dt < ds + 1.5)
						trains[i].myDelay(clock);
					else if (dt >= (ds + 5) && trains[i].get_speed() != -80)
						stations[i].approaching(trains[i]);
					else if (dt >= (ds + 20) && trains[i].get_status() != 4)
					{
						trains[i].set_rail(stations[trains[i].get_next_station()].signalResponse(true, trains[i]));
						trains[i].set_status(4);
					}
					else if (dt >= (stations[trains[i].get_next_station() + 1].distance - 5)
						&& dt > (ds + 20)
						&& trains[i].get_speed() == -80)
					{
						trains[i].set_speed(trains[i].get_vMax());
						trains[i].set_status(1);
						cout << "\nTrain n. " << trains[i].nTrain << " accelerated to " << trains[i].get_vMax()
							<< " cuz it's mor than 5 km far from the station"<< endl;
					}
				}
				break;
			}
			case 2:
			{
				int n;
				if (trains[i].get_from() == 0)
					n = 0;
				else
					n = stations.size()-1;
			
				if (clock == (trains[i].get_time(trains[i].get_next_station() -1) + trains[i].get_delay() + 5))
					stations[n].startTrain(trains[i]);
				break;
			}
			}

			trains[i].update_pos();
			//cout << i;
			i++;
		}
		R.dont_crash();
		//cout << clock << " : " << endl;
		clock++;
	}

	cout << endl;
	
return 0;
}