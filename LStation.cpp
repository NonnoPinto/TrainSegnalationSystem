#include "LStation.h"
//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), verso del treno (dato dalla velocità)
//e condizione dei binari (se sono liberi o meno)
int LStation::signalResponse(bool stopping, Train& t)
{
	std::cout << "Signal received from station " << name << " by the train n " << t.nTrain << std::endl;
	if (!stopping)
	{
		std::cout << "Confirmed train n" << t.nTrain << " is just passing through -> ";
		if (t.get_from() == 0)
		{
			std::cout << "Sent to Rail number 3" << std::endl;
			return 3;
		}
		else
		{
			std::cout << "Sent to Rail number 3" << std::endl;
			return 6;
		}
	}
	else
	{
		std::cout << "Confirmed train n" << t.nTrain << " is stopping at station " << name << " -> ";
		if (isFull())
		{
			std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
			return 0;
		}
		else
		{
			if (t.get_from() == 0) //Origine -> Fine
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
}

void LStation::parkTrain(int p, Train& t)
{
	if (p < 0 || p>6)
		throw std::invalid_argument("Position out of bounds");
	t.set_rail(p);
	if (p == -1)
	{
		parking_area.push(t);
		std::cout << "Rails are all occupied, train n " << t.nTrain << " sent to the parking area in station " << name << std::endl;
	}
	else
	{
		rails[p - 1] = t;
		std::cout << "Train stopped successfuly on rail n " << p << " in station " << name << std::endl;
		ntrains++;
	}
}

void LStation::approaching(Train& t)
{
	if (t.get_train_type() == 1)
	{
		std::cout << "Train n " << t.nTrain << " approaching (5km left) station " << name << ", maximum speed set to 80km/h. \n";
		if (t.get_from() == 0)
			t.set_speed(80);
		else
			t.set_speed(-80);
	}
}

void LStation::startTrain(Train& t)
{
	std::cout << "Train n " << t.nTrain << " starting from station " << name << ", speed set to 80km/h. \n";

	if (t.get_from() == 0)
		t.set_speed(80);
	else
		t.set_speed(-80);

	t.set_status(1);
	/*
	if (isParkAreaEmpty())
	{
		//rails[p - 1] = nullptr;
		ntrains--;
	}
	else
	{
		rails[p - 1] = parking_area.front();
		parking_area.pop();
	}*/
}
//Comunica se un certo binario è libero o meno
bool LStation::isRailFree(int p)			
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");

	if (p == 2 || p == 5)
		std::cout << "è un binario di transito \n";
		//VEDI DOPO
	return (false);
}