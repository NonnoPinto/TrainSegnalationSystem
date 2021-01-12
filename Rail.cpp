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

	cout << "\n" <<  "***Importing data from files***\n";
	TS.read_inputs();
	cout << " \n " <<"***Data imported succesfully!***\n\n";

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
		case 1: //Treno Regionale
		{
			ptrTrain train(new RTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			trains.push_back(train);
			break;
		}
		case 2: //Treno Alta Velocità
		{
			//Creato Puntatore ausiliario
			ptrTrain train(new AVTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			//Inserito puntatore nel vettore trains
			trains.push_back(train);
			break;
		}

		case 3: //Treno Alta Velocità Super
		{
			//Creato Puntatore ausiliario
			ptrTrain train(new AVSTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			//Inserito puntatore nel vettore trains
			trains.push_back(train);
			break;
		}
		}
	}

	//Ogni cella dell vettore stations viene inizializzata con un oggetto di tipo Station
	//A seconda del tipo di stazione, viene chiamato il giusto costruttore
	for (int i = 0; i < lineDescription.size(); i++) {
		int x = stoi(lineDescription[i][1]);

		//lo switch decide il tipo di stazione e ne chiama il costruttore
		switch (x) {
		case 0: //Stazione principale
		{
			ptrStation station(new PStation(lineDescription[i][0], stoi(lineDescription[i][2]))); //stoi(lineDescription[lineDescription.size() - 1][2]))
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

	//Variabili ausiliarie (indici, contatori, parametri)
	//Ore
	int h;
	//Minuti
	int m;
	//Contatore del tempo
	int clock = 0;
	//Indice usato per scorrere i treni
	int i;
	//Variabile per lo status dei treni
	int status;
	while (!R.runningIsFree())
	{
		i = 0;
		//Calcolo Ore
		h = clock / 60;
		//Calcolo Minuti
		m = clock % 60;

		cout << "\nClock: " << h << " : " << m << endl;

		cout << " - Pos Train 0: " << trains[0]->get_pos() << "\n";

		//Ciclo while scorre tutti i treni e controlla la situazione di ciascuno ogni minuto
		while (i < trains.size())
		{
			//Controlla la variabile parametro "status" del treno
			//0 == Treno pronto alla sua prima partenza
			//1 == Treno in transito tra stazioni
			//2 == Treno in fermata in una stazione (su binari o parcheggio)
			//3 == Treno arrivato alla sua destinazione
			//4 == Treno in avvicinamento verso una stazione
			status = trains[i]->get_status();

			switch (status)
			{
				//Caso in cui status treno == 0 (treno pronto alla sua prima partenza)
			case 0:
			{
				//indica la stazione di partenza del treno in base al suo verso
				int n;
				//Caso in cui il treno ha il verso Origine -> Capolinea (from = 0) 
				//dunque parte dalla stazione d'origine
				if (trains[i]->from == 0)
					n = 0;
				//Caso in cui il treno ha il verso Capolinea -> Origine (from = 1) 
				//dunque parte dalla stazione capolinea
				else
					n = stations.size() - 1;

				//Controllo orario di partenza di un treno
				if (clock >= (trains[i]->get_time(n)))
				{
					stations[n]->parkTrain(stations[n]->signalResponse(true, trains[i]), trains[i]);
					stations[n]->startTrain(trains[i]);
				}

				break;
			}
			//Caso in cui status treno == 1 (transito tra stazioni) o status treno == 4 (transito intorno a stazioni e in fermata)
			case 1: case 4:
			{
				//indica la prossima stazione dell'i-esimo treno
				int n = trains[i]->get_next_station();
				//posizione dell'i-esimo treno
				double dt = trains[i]->get_pos();
				//posizione della prox stazione
				double ds = stations[trains[i]->get_next_station()]->distance;

				//cout << "STOP NEXT STATION: " << trains[i]->stop_next_station() << endl;
				//cout << "TIME NEXT STATION: " << trains[i]->get_time(trains[i]->get_next_station()) << endl;

				//Caso in cui il treno ha il verso Origine -> Capolinea (from = 0)
				if (trains[i]->from == 0)
				{
					//Situazione in cui il treno è a 6 km intorno dalla stazione, dunque si ferma e calcola il ritardo
					//I 6 km sono dovuti ad un'aprossimazione dato che la posizione del treno è di tipo double
					if (dt > ds - 3 && dt < ds + 3 && trains[i]->get_status() == 4)
					{
						stations[n]->parkTrain(trains[i]->get_rail(), trains[i]);
						trains[i]->myDelay(clock);
					}
					//Situazione in cui il treno è a meno di 5 km prima della prossima stazione e non rispetta il limite di 80 kmph
					//dunque gli viene imposto questo limite, se il treno ha comunicato che deve fermarsi
					else if (dt >= (ds - 5) && trains[i]->get_status() != 4) {
						stations[n]->approaching(trains[i]);
					}
					//Situazione in cui il treno è a meno di 20 km prima della prossima stazione, 
					//dunque deve inviare il segnale di controllo, il quale imposta già il binario su cui passerà nella stazione
					else if (dt >= (ds - 20) && trains[i]->get_rail() == 0)
						trains[i]->set_rail(stations[n]->signalResponse(trains[i]->stop_next_station(), trains[i]));
					//Situazione in cui il treno è a più di 5 km dopo l'ultima stazione da cui è partito, 
					//dunque è permesso passare ad una velocità superiore agli 80 kmph
					else if (dt >= (stations[n - 1]->distance + 5)
						&& dt < (ds - 20)
						&& trains[i]->get_speed() == 80)
					{
						stations[n - 1]->leaving(trains[i]);
					}
				}
				//Caso in cui il treno ha il verso Capolinea -> Origine (from = 1)
				else
				{
					//Situazione in cui il treno è a 6 km intorno dalla stazione, dunque si ferma e calcola il ritardo
					//I 6 km sono dovuti ad un'aprossimazione dato che la posizione del treno è di tipo double
					if (dt < ds + 3 && dt > ds - 3 && trains[i]->get_status() == 4) {


						stations[n]->parkTrain(trains[i]->get_rail(), trains[i]);
						trains[i]->myDelay(clock);
					}
					//Situazione in cui il treno è a meno di 5 km prima della prossima stazione e non rispetta il limite di 80 kmph
					//dunque gli viene imposto questo limite, se il treno ha comunicato che deve fermarsi
					else if (dt <= (ds + 5) && trains[i]->get_status() != 4) {
						stations[n]->approaching(trains[i]);
					}
					//Situazione in cui il treno è a meno di 20 km prima della prossima stazione, 
					//dunque deve inviare il segnale di controllo, il quale imposta già il binario su cui passerà nella stazione
					else if (dt <= (ds + 20) && trains[i]->get_rail() == 0)
						trains[i]->set_rail(stations[n]->signalResponse(trains[i]->stop_next_station(), trains[i]));
					//Situazione in cui il treno è a più di 5 km dopo l'ultima stazione da cui è partito, 
					//dunque è permesso passare ad una velocità superiore agli 80 kmph (accelera alla sua massima velocità)
					else if (dt <= (stations[n + 1]->distance - 5)
						&& dt > (ds + 20)
						&& trains[i]->get_speed() == -80)
						stations[n + 1]->leaving(trains[i]);
				}
				break;
			}
			//Caso in cui status treno == 2 (treno fermo in stazione o parcheggio)
			case 2:
			{
				//indica la prossima stazione del treno in base al suo verso
				int n;

				//Caso in cui il treno ha il verso Origine -> Capolinea (from = 0)
				if (trains[i]->from == 0)
					n = trains[i]->get_next_station() - 1;
				//Caso in cui il treno ha il verso Capolinea -> Origine (from = 1)
				else
					n = trains[i]->get_next_station() + 1;

				//Controllo se un treno è arrivato, distinguendo in due casi in base al verso
				//Caso in cui il treno ha il verso Origine -> Capolinea (from = 0)
				if (trains[i]->from == 0 && trains[i]->get_next_station() == stations.size()) {

					stations[n]->arrived(trains[i]);

					R.arrived(*trains[i]);

					break;
				}
				//Caso in cui il treno ha il verso Capolinea -> Origine (from = 1)
				else if (trains[i]->from == 1 && trains[i]->get_next_station() == -1) {
					stations[n]->arrived(trains[i]);
					R.arrived(*trains[i]);
					break;
				}

				//Partenza del treno (se non si trova nel parcheggio, ma su un binario)
				//Se si trovasse nel parcheggio, non parte, ma aspetta che si liberi un binario
				if (clock >= (trains[i]->get_time(n) + trains[i]->get_delay() + 5))
					stations[n]->startTrain(trains[i]);
				break;
			}
			default:
				break;
			}
			//Aggiorna la posizione dell'i-esimo treno
			trains[i]->update_pos();
			//Aumenta l'indice del treno
			i++;
		}

		//Chiamata funzione don't crash che controlla periodicamente le distanze tra i treni e altera le velocità
		//per mantenere la distanza di sicurezza (circa 10 km) tra i treni quando questa è obbligatoria
		R.dont_crash();
		//Aumenta il contatore del tempo (di tipo int, indica i minuti passati)
		clock++;
	}

	cout << endl;

	return 0;
}