#include "LStation.h"
/*
//Restituisce il numero del binario su cui passare in base al segnale (transito o fermata), verso del treno (dato dalla velocità)
//e condizione dei binari (se sono liberi o meno)
int LStation::signalResponse(bool stopping, int v, Train<L>& t)
{
	std::cout << "Signal received from station " << name << " by the train n " << t.getntrain() << std::endl;
	if (!stopping)
	{
		std::cout << "Confirmed train n" << t.getntrain() << " is just passing through -> ";
		if (v > 0)
		{
			std::cout "Sent to Rail number 3" << std::endl;
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
		std::cout << "Confirmed train n" << t.getntrain() << " is stopping at station " << name << " -> ";
		if (isFull())
		{
			std::cout << "All rails are occupied -> Sent to parking area" << std::endl;
			return 0;
		}
		else
		{
			if (v > 0) //Origine -> Fine
			{
				if (isFree(0))
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
				if (isFree(3))
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

void LStation::parkTrain(int p, Train<L>& t)
{
	if (p < 0 || p>6)
		throw std::invalid_argument("Position out of bounds");
	t.setpos(p);
	if (p == -1)
	{
		parking_area.push(t);
		cout << "Rails are all occupied, train n " << t.getntrain() << " sent to the parking area in station " << name << std::endl;
	}
	else
	{
		rails[p - 1] = t;
		std::cout << "Train stopped successfuly on rail n " << p << " in station " << name << std::endl;
		ntrains++;
	}
}

void LStation::approaching(Traint<L>& t)
{
	if (t.train_type == 1)
	{
		cout << "Train n " << t.getntrain() << " approaching (5km left) station " << name << ", maximum speed set to 80km/h. \n";
		if (t.from == 0)
			t.setspeed(80);
		else
			t.setspeed(-80);
	}
}

void LStation::startTrain(int p)
{
	cout << "Train n " << rails[p - 1].getntrain() << " starting from station " << name << ", speed set to 80km/h. \n";

	if (rails[p - 1].from == 0)
		rails[p - 1].setspeed(80);
	else
		rails[p - 1].setspeed(-80);

	rails[p - 1].setpos(-1);

	if (isParkAreaEmpty())
	{
		rails[p - 1] = nullptr;
		ntrains--;
	}
	else
	{
		rails[p - 1] = parking_area.front();
		parking_area.pop();
	}
}
//Comunica se un certo binario è libero o meno
bool LStation::isRailFree(int p)			
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");

	if (p == 2 || p == 5)
		std::cout << "è un binario di transito \n";

	return (rails[p] == nullptr);
}*/