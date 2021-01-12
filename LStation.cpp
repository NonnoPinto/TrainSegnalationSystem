/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "LStation"*/

#include "LStation.h"

 //Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), verso del treno (dato dalla velocità)
 //e condizione dei binari (se sono liberi o meno). Il segnale viene inviato a 20km di distanza dalla stazione
int LStation::signalResponse(bool stopping, std::shared_ptr<Train> t)
{
	std::cout << "*** Signal received from station " << name << " by the " << printTrainType(t) << " Train n. " << t->nTrain << ". \n";
	std::cout << "Confirmed " << printTrainType(t) << " Train n. " << t->nTrain;

	//Caso in cui un treno non si ferma in una stazione
	if (!stopping)
	{
		//Status impostato a 1 (treno in transito tra stazioni)
		t->set_status(1);

		std::cout << " is just passing through Station " << name << " -> ";

		//Assegnamento del binario su cui passare
		if (t->from == 0)
		{
			std::cout << "Sent to Rail number 3" << std::endl;
			return 3;
		}
		else
		{
			std::cout << "Sent to Rail number 6" << std::endl;
			return 6;
		}
	}
	else
	{
		//Status impostato a 4 (treno in transito vicino a stazione e sta per fermarsi)
		t->set_status(4);

		std::cout << " is stopping at Station " << name << " -> ";

		//Nel caso in cui i binari non sono tutti occupati al treno viene viene assegnato un binario (che viene anche prenotato) in base al verso e disponibilità
		if (!isFull())
		{
			if (t->from == 0) //Origine -> Capolinea
			{
				//Se è libero uno dei binari con verso Origine -> Capolinea lo prenota e invia lì il treno
				if (isRailSaved(0))
				{
					std::cout << "Sent to Rail number 1" << std::endl;
					savedrails[0] = 1;
					return 1;
				}
				else if (isRailSaved(1))
				{
					std::cout << "Sent to Rail number 2" << std::endl;
					savedrails[1] = 1;
					return 2;
				}
				//Altrimenti lo invia al parcheggio
				else
				{
					std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
					return -1;
				}
			}
			else //Capolinea -> Origine
			{
				//Se è libero uno dei binari con verso Capolinea -> Origine lo prenota e invia lì il treno
				if (isRailSaved(3))
				{
					std::cout << "Sent to Rail number 4" << std::endl;
					savedrails[3] = 1;
					return 4;
				}
				else if (isRailSaved(4))
				{
					std::cout << "Sent to Rail number 5" << std::endl;
					savedrails[4] = 1;
					return 5;
				}
				//Altrimenti lo invia al parcheggio
				else
				{
					std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
					return -1;
				}
			}
		}
		//Altrimenti al treno viene assegnato un binario (che viene prenotato) in base al 
		else
		{
			std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
			return -1;
		}
	}
}

//Comunica l'avvicinamento (5km) di un treno verso la stazione e impone un limite di velocità di 80km/h
void LStation::approaching(std::shared_ptr<Train> t)
{
	std::cout << "*** " << printTrainType(t) << " Train n. " << t->nTrain << " approaching (about 5km left) station, " << name;
	if (t->get_status() == 4)
	{
		std::cout << "speed limit is 80kmph. \n";

		//Imposta la velocità del treno in base al verso (limite di 80kmph per i treni in fermata)
		if (t->from == 0)
			t->set_speed(80);
		else
			t->set_speed(-80);
	}
	else if (t->get_status() == 1)
		std::cout << "it may proceed at " << abs(t->get_speed()) << " kmph. \n";
}

//Parcheggia il treno su un dato binario, oppure su un parcheggio se tutti i binari sono occupati
//La scelta del binario viene gestita dalla funzione signalResponse
void LStation::parkTrain(int p, std::shared_ptr<Train> t)
{
	if (p < -1 || p > 6)
		throw std::invalid_argument("Position out of bounds");

	//Assegna al treno il binario p
	t->set_rail(p);

	//Nel caso in cui lo status del treno è 4 (treno in transito vicino alla stazione e sta per fermarsi)
	if (t->get_status() == 4)
	{
		//Se p corrisponde a -1, il treno viene inviato al parcheggio "infinito"
		if (p == -1)
		{
			if (t->from == 0)
			{
				if (isRailFree(0))
				{
					rails[0] = t;
					std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " stopped successfuly on rail n. 1 in Station " << name << "as it has been freed. It will leave in 5 minutes \n";
					ntrains++;
				}
				else if (isRailFree(1))
				{
					rails[1] = t;
					std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " stopped successfuly on rail n. 1 in Station " << name << "as it has been freed. It will leave in 5 minutes \n";
					ntrains++;
				}
				else
				{
					parking_area.push_back(t);
					std::cout << "*** Rails are all occupied, " << printTrainType(t) << " Train n. " << t->nTrain << " sent to the parking area in station " << name << ". \n";
				}
			}
			else if (t->from == 1)
			{
				if (isRailFree(3))
				{
					rails[3] = t;
					std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " stopped successfuly on rail n. 3 in Station " << name << "as it has been freed. It will leave in 5 minutes \n";
					ntrains++;
				}
				else if (isRailFree(4))
				{
					rails[4] = t;
					std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " stopped successfuly on rail n. 5 in Station " << name << "as it has been freed. It will leave in 5 minutes \n";
					ntrains++;
				}
				else
				{
					parking_area.push_back(t);
					std::cout << "*** Rails are all occupied, " << printTrainType(t) << " Train n. " << t->nTrain << " sent to the parking area in station " << name << ". \n";
				}
			}
		}
		//Altrimenti viene parcheggiato sul binario p (nel vettore corrisponde all'indice p - 1)
		else
		{
			rails[p - 1] = t;
			std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " stopped successfuly on rail n. " << p << " in Station " << name << ". It will leave in 5 minutes \n";
			ntrains++;
		}
		//Cambia status del treno a 2 (== Treno in fermata)
		t->set_status(2);
		//Cambia velocità del treno a 0 km/h
		t->set_speed(0);
	}
	else if (t->get_status() == 1)
	{
		std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " passed Station " << name << " without stopping at " << abs(t->get_speed()) << " kmph. \n";

		//Imposta il binario a myrail = 0 (== Binario di transito tra le stazioni)
		t->set_rail(0);
		//Imposta la velocità del treno alla sua massima velocità
		t->set_speed(t->vMax);
	}
}

//Fa partire un treno dalla stazione con un limite di velocità di 80km/h e sposta un treno dal parcheggio
//sul binario liberato
void LStation::startTrain(std::shared_ptr<Train> t)
{
	if (t->get_rail() != -1)
	{
		std::cout << " *** " << printTrainType(t) << "Train n. " << t->nTrain << " starting from station " << name << ", speed set to 80 kmph. \n";

		//Cambia la velocità del treno tenendo conto del suo verso
		if (t->from == 0)
			t->set_speed(80);
		else
			t->set_speed(-80);

		//Cambia lo status del treno a 4 (in transito vicino a stazione)
		t->set_status(4);

		//Controlla se ci sono treni nel parcheggio
		//Se ce ne sono nel pargheggio, controlla il verso e li inserisce sui binari se il verso corrisponde

		if (!isParkAreaEmpty())
		{
			int i = 0;
			bool parked = false;
			//Scorre il parcheggio
			while (i < parking_area.size() && !parked)
			{
				//Controllo del verso dei treni in parcheggio
				if (parking_area[i]->from == t->from)
				{
					std::cout << "Parking " << printTrainType(parking_area[0]) << " Train n. " << parking_area[0]->nTrain << " -> ";
					std::cout << "sent on the freed rail n. " << t->get_rail() << "of Station " << name << ". \n";
					rails[t->get_rail() - 1] = parking_area[i];
					parking_area.erase(parking_area.begin() + i);
					parked = true;
				}
			}
			//Se non ci sono treni col verso compatibile viene comunicato a video, svuotato il binario (impostato a nullptr) e diminuito il numero di treni parcheggiati
			if (!parked)
			{
				std::cout << "There are no other trains waiting in the parking area of station " << name << ". \n";
				rails[t->get_rail() - 1] = nullptr;
				savedrails[t->get_rail() - 1] = 0;
				ntrains--;
			}
		}
		//Se non ne sono, viene comunicato a video, svuotato il binario (impostato a nullptr) e diminuito il numero di treni parcheggiati
		else
		{
			std::cout << "There are no other trains waiting in the parking area of station " << name << ". \n";
			rails[t->get_rail() - 1] = nullptr;
			savedrails[t->get_rail() - 1] = 0;
			ntrains--;
		}

		//Imposta il treno sul binario 0 (binario tra le stazioni)
		t->set_rail(0);
	}
	else
		std::cout << "*** " << printTrainType(t) << "Train n. " << t->nTrain << " is in the parking area of Station " << name << " and it cannot start \n";
}

//Comunica quando un treno partito risulta a più di 5km da una stazione e lo fa accelerare alla sua massima velocità
void LStation::leaving(std::shared_ptr<Train> t)
{
	std::cout << "*** " << printTrainType(t) << " Train n. " << t->nTrain << " is 5km away from station " << name << " speed limit is no longer 80 kmph. \n";

	//Imposta la velocità del treno alla sua velocità massima
	t->set_speed(t->vMax);
	std::cout << printTrainType(t) << "Train n. " << t->nTrain << " successfully accelerated to its max speed (" << abs(t->vMax) << " kmph)\n";

	//Imposta il treno a status 1 (in transito tra stazioni)
	t->set_status(1);
	//Imposta il treno sul binario 0 (binario tra le stazioni)
	t->set_rail(0);
}
