/* author: Andrei Ovidiu Danciu - 1224263
 * File cpp della classe madre "Station"*/

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

//Funzione ausiliaria per stampare se i binari di una stazione sono occupati o meno (utilizzata in fase di test)
void Station::printRailStatus()
{
	std::cout << "STATION " << name << "\n";
	for (int i = 0; i < nrails; i++)
	{
		std::cout << "Rail n. " << i << "IsFree: ";
		if (isRailFree(i))
			std::cout << "Yes \n";
		else
			std::cout << "No \n";
	}

	if (isParkAreaEmpty())
		std::cout << "\n" << " PARCHEGGIO VUOTO " << "\n";
	else
		std::cout << "\n" << " PARCHEGGIO NON VUOTO  " << "\n";
}