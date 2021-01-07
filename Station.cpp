/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe derivata "Station"*/

#include "Station.h"

//Risponde al lancio di segnale con il binario su cui deve andare il treno
int Station::signalResponse(bool stopping, int v, Train& t)
{
	std::cout << "Confirmed train n" << t.nTrain << " is approaching station " << name << " -> ";
	if (isFull())
	{
		std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
		return 0;
	}
	else
	{
		if (v > 0) //Origine -> Fine
		{
			if (isRailFree(0))
			{
				std::cout << "Sent to Rail number 1" << std::endl;
				return 1;
			}
			else
			{
				std::cout << "Sent to Rail number 2" << std::endl;
				return 2;
			}
		}
		else //Fine -> Origine
		{
			if (isRailFree(3))
			{
				std::cout << "Sent to Rail number 4" << std::endl;
				return 4;
			}
			else
			{
				std::cout << "Sent to Rail number 5" << std::endl;
				return 5;
			}
		}
	}
}
//Fa fermare il treno sul binario indicato (o nel parcheggio se pieno)
void Station::parkTrain(int p, Train& t)
{
	if (p < 0 || p>4)
		throw std::invalid_argument("Position out of bounds");
	t.set_rail(p);
	if (p == 0)
	{
		parking_area.push(t);
		t.set_speed(0);
		std::cout << "Rails are all occupied, train n " << t.nTrain << " sent to the parking area in station " << name << std::endl;
	}
	else
	{
		rails[p - 1] = t;
		t.set_speed(0);
		std::cout << "Train stopped successfuly on rail n " << p << " in station " << name << std::endl;
		ntrains++;
	}
}
//Modifica la velocità del treno quando si avvicina alla stazione
void Station::approaching(Train& t)
{
	std::cout << "Train n " << t.nTrain << " approaching (about 5km left) station " << name << ", maximum speed set to 80km/h. \n";
	if (t.get_from() == 0)
		t.set_speed(80);
	else
		t.set_speed(-80);
}
//Fa partire il treno
void Station::startTrain(int p)
{
	rails[p - 1].set_speed(80);
	rails[p - 1].update_pos();
	if (isParkAreaEmpty())
		int i = 0;
		//rails[p - 1] = Train(-1);
	else
	{
		rails[p - 1] = parking_area.front();
		parking_area.pop();
	}
}
//Comunica se un certo binario è libero o meno
bool Station::isRailFree(int p)
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");
	//Train TF(-1);
	return (false);//rails[p] == TF);
}