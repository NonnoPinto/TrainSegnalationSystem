/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe "Station"*/

#include "Station.h"

 //Restituisce una stringa col tipo di treno
std::string Station::printTrainType(std::shared_ptr<Train> t)
{
	std::string s;
	if (t->train_type == 1)
		s = "Regional ";
	else if (t->train_type == 2)
		s = "High Speed ";
	else if (t->train_type == 3)
		s = "Super High Speed ";
	else
		std::cout << "TIPO TRENO:" << t->train_type;
	return s;
}

//Comunica se un dato binario è libero o meno
bool Station::isRailFree(int p)
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");
	return (rails[p] == nullptr);
}

//Comunica se un dato binario è prenotato o meno
bool Station::isRailSaved(int p)
{
	if (p<0 || p>nrails)
		throw std::invalid_argument("Position out of bounds");
	return (savedrails[p] == 0);
}

//Inizializza i binari in base a quanti sono (che dipende dal tipo di stazione)
void Station::set_rails(int n)
{
	rails.resize(n);
	for (int i = 0; i < n; i++)
	{
		rails[i] = nullptr;
		savedrails.push_back(0);
	}
}