// CMakeProject2.cpp: definisce il punto di ingresso dell'applicazione.
//

#include "ReadTables.h"
#include "LStation.h"
#include "PStation.h"
#include "Rails.h"

using namespace std;

int main() {

	//lettura, controllo e ___elaborazione dei dati
	ReadTables TS;

	cout << "***Importing data from files***\n";
	TS.read_inputs();
	cout << "***Data imported succesfully!***\n\n";

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
	for (int i = 0; i < lineDescription.size(); i++)
		myLineDescription.push_back(lineDescription[i][2]);

	//vettori dei costruttori
	//treni
	typedef std::shared_ptr<Train> ptrTrain;
	typedef std::shared_ptr<Station> ptrStation;
	vector<ptrTrain> trains;
	//stazioni
	vector<ptrStation> stations;

	//ogni cella dell vettore trains viene inizializzata con un oggetto di tipo Train
	//A seconda del tipo di treno, viene chiamato il giusto costruttore
	for (int i = 0; i < timeTable.size(); i++) {
		int x = timeTable[i][2]; //tipo di treno (Regionale, Alta Velocità, Alta Velocità Super)

		//vettore con i soli orari dell'i-esimo treno, senza variaibli di controllo
		//Il vettore con gli orari di ogni treno ha la seguente forma
		//[n.treno][stazione di partenza][tipo teno][orari di arrivo]
		//Nel vettore tmp vengono inseriti solo gli orari
		vector<int> tmp(timeTable[i].begin() + 3, timeTable[i].end());

		//lo switch decide il tipo di treno e ne chiama il costruttore
		switch (x) {
		case 1: //RTrain constructor
		{
			ptrTrain train(new RTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			trains.push_back(train);
			break;
		}
		case 2: //AVTrain constructor
		{
			ptrTrain train(new AVTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			trains.push_back(train);
			break;
		}

		case 3: //AVSTrain constructor
		{
			ptrTrain train(new AVSTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			trains.push_back(train);
			break;
		}
		}
		//cout << "Tipo treno: "<< trains[i]->get_train_type();

	}

	//for(int i = 0; i< trains.size(); i++)
	//	cout << trains[i]->vMax << endl;

	//ogni cella dell vettore stations viene inizializzata con un oggetto di tipo Station
	//A seconda del tipo di stazione, viene chiamato il giusto costruttore
	for (int i = 0; i < lineDescription.size(); i++) {
		int x = stoi(lineDescription[i][1]);

		switch (x) {
		case 0: //Stazione principale
		{
			ptrStation station(new PStation(lineDescription[i][0], stoi(lineDescription[i][2])));
			stations.push_back(station);
			break;
		}
		case 1: //Stazione locale
		{
			ptrStation station(new LStation(lineDescription[i][0], stoi(lineDescription[i][2])));
			stations.push_back(station);
			break;
		}
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
		cout << "\nClock: " << clock << " - Pos Train 1: " << trains[0]->get_pos() << " - Pos Train 2: " << trains[1]->get_pos() << endl;
		//cout << "\nV Train 1: " << trains[0].get_speed() << " - V Train 2: " << trains[1].get_speed() << endl;


		while (i < trains.size())
		{
			status = trains[i]->get_status();
			switch (status)
			{
			case 0:
			{
				int n;
				if (trains[i]->from == 0)
					n = 0;
				else
					n = stations.size() - 1;

				if (clock >= (trains[i]->get_time(n)))
				{
					stations[n]->parkTrain(stations[n]->signalResponse(true, trains[i]), trains[i]);
					stations[n]->startTrain(trains[i]);
				}
				/*else if (clock == (trains[i].get_time(0) + 5))*/

				break;
			}
			case 1: case 4:
			{
				int n = trains[i]->get_next_station();

				//posizione dell'i-esimo treno
				double dt = trains[i]->get_pos();
				//posizione della prox stazione
				double ds = stations[trains[i]->get_next_station()]->distance;
				//cout << "STOP NEXT STATION: " << trains[i]->stop_next_station() << endl;
				//cout << "TIME NEXT STATION: " << trains[i]->get_time(trains[i]->get_next_station()) << endl;
				if (trains[i]->from == 0)
				{
					if (dt > ds - 1.5 && dt < ds + 1.5)
					{
						stations[n]->parkTrain(trains[i]->get_rail(), trains[i]);
						trains[i]->myDelay(clock);
					}
					else if (dt >= (ds - 5) && trains[i]->get_speed() != 80)
						stations[n]->approaching(trains[i]);
					else if (dt >= (ds - 20) && trains[i]->get_rail() == 0)
						trains[i]->set_rail(stations[n]->signalResponse(trains[i]->stop_next_station(), trains[i]));
					else if (dt >= (stations[n - 1]->distance + 5)
						&& dt < (ds - 20)
						&& trains[i]->get_speed() == 80)
					{
						stations[n - 1]->leaving(trains[i]);
					}
				}
				else
				{
					if (dt > ds - 1.5 && dt < ds + 1.5)
					{
						stations[n]->parkTrain(trains[i]->get_rail(), trains[i]);
						trains[i]->myDelay(clock);
					}
					else if (dt <= (ds + 5) && trains[i]->get_speed() != -80)
						stations[n]->approaching(trains[i]);
					else if (dt <= (ds + 20) && trains[i]->get_rail() == 0)
						trains[i]->set_rail(stations[n]->signalResponse(trains[i]->stop_next_station(), trains[i]));
					else if (dt <= (stations[n + 1]->distance - 5)
						&& dt > (ds + 20)
						&& trains[i]->get_speed() == -80)
					{
						stations[n + 1]->leaving(trains[i]);
					}
				}
				break;
			}
			case 2:
			{
				int n;
				if (trains[i]->from == 0)
					n = trains[i]->get_next_station() - 1;
				else
					n = trains[i]->get_next_station() + 1;


				if (trains[i]->from == 0 && trains[i]->get_next_station() == stations.size()) {
					trains[i]->set_status(3);
					trains[i]->set_speed(0);
					R.arrived(*trains[i]);
					break;
				}
				else if (trains[i]->from == 1 && trains[i]->get_next_station() == -1) {
					trains[i]->set_status(3);
					trains[i]->set_speed(0);
					R.arrived(*trains[i]);
					break;
				}
				//cout << "N :" << n << "- DELAY :" << trains[i].get_delay() << endl;
				if (clock >= (trains[i]->get_time(n) + trains[i]->get_delay() + 5))
				{
					/*cout << "DELAY: " << trains[i].get_delay() << ", ARRIVAL TIME: " << trains[i].get_time(trains[i].get_next_station() - 1) << endl;
					cout << " SUPPOSED TIME : " << trains[i].get_time(trains[i].get_next_station() - 1) + trains[i].get_delay() + 5;*/
					stations[n]->startTrain(trains[i]);
				}
				break;
			}
			}

			trains[i]->update_pos();
			i++;
		}
		R.dont_crash();
		clock++;
	}

	cout << endl;

	return 0;
}