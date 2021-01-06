#include "PStation.h"

int PStation::signalResponse(bool stopping, int v, Train& t)
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

void PStation::parkTrain(int p, Train& t)
{
	if (p < 0 || p>4)
		throw std::invalid_argument("Position out of bounds");
	t.setpos(p);
	if (p == 0)
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

void PStation::approaching(Train& t)
{
	cout << "Train n " << t.getntrain() << " approaching (5km left) station " << name << ", maximum speed set to 80km/h. \n";
	if (t.from == 0)
		t.setspeed(80);
	else
		t.setspeed(-80);
}

void PStation::startTrain(int p)
{
	rails[p - 1].setspeed(80);
	if (isParkAreaEmpty())
		rails[p - 1] = nullptr;
	else
	{
		rails[p - 1] = parking_area.front();
		parking_area.pop();
	}
}

bool PStation::isRailFree(int p)				//Comunica se un certo binario è libero o meno
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");
		
	return (rails[p] == nullptr);
}