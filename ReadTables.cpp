/*
* Author: Niccol� Castellan - 1227137
* Header : Classe base da cui vengono derivate le classi derivate Train,Station e Rails
* Implementazione delle funzioni della classe ReadTable
*/

#include <math.h>
#include <fstream>
#include <sstream>

#include "ReadTables.h"

//Funzione che legge,acquisice le informazioni della TimeTable e le memorizza in una matrice
void ReadTables::read_timetable() {

	std::ifstream file_in("timetables.txt");

	std::string line;

	while (std::getline(file_in, line)) {

		std::istringstream ss(line);

		std::vector<int> new_vec;

		int v;

		while (ss >> v)
			new_vec.push_back(v);

		vec.push_back(new_vec);
	}
}

//Funzione che legge,acquisice le informazioni della line_description e le memorizza in una matrice
void ReadTables::read_linedescription() {
	
	std::ifstream file_in2("line_description.txt");

	std::string line2;

	while (getline(file_in2, line2)) {

		std::istringstream ss2(line2);

		std::vector<std::string> new_vec2;

		std::string in;

		while (ss2 >> in)
			new_vec2.push_back(in);

		vec2.push_back(new_vec2);
	}
}

// Funzione che concatena in un unica stringa i nomi delle stazioni formati da due stringhe
void ReadTables::strin_conc() {

	for (int i = 0; i < vec2.size(); i++) {

		if ((vec2[i][1]).size() > 1) {

			std::string ins = vec2[i][0] + " " + vec2[i][1];

			vec2[i].erase(vec2[i].begin() + 1);

			vec2[i][0] = ins;
		}
	}
}

//Funzione che inserisce nella matrice il tipo della stazione principale e il km (fissato a 0)
//Serve per poter successivamente effettuare confronti tra le distanze delle stazioni
void ReadTables::fill_matrix() {

	//variabili ausiliarie
	std::vector<int> dist(vec2.size(), 0);

	size_t sz_prec;

	size_t sz_succ;

	std::string s_prec;

	std::string s_succ;


	//creo un array di dimensione (stazioni-1) con le distanze tra le stazioni
	for (int i = 0; i < vec2.size() - 1; i++) {
		s_prec = vec2[i][2];

		s_succ = vec2[i + 1][2];

		//tolgo 10 per le zone
		//ai 80km/h
		int km_tmp = std::stoi(s_succ, &sz_succ) - std::stoi(s_prec, &sz_prec) - 10;
																	
		dist[i + 1] = km_tmp;
	}

	//velocit� massima del i-esimo treno
	double v;

	//indice treno
	for (int i = 0; i < vec.size(); i++) {

		if (vec[i][2] == 1)
			v = 160;
		else if (vec[i][2] == 2)
			v = 240;
		else
			v = 300;

		if (vec[i][1] == 1) {
			std::vector<int> tmp;
			for (int k = 0; k < dist.size(); k++)
				tmp.push_back(dist[k]);
			for (int k = 0; k < dist.size(); k++)
				dist[dist.size() - 1 - k] = tmp[k];
		}
		//std::reverse(dist.begin(), dist.end());

		//indice tempo di arrivo alla stazione k-esima
		for (int k = 4; k < vec[i].size(); k++) {

			if (v != 160 && vec2[k - 3][1].compare("1") == 0)	//se treno AV o AVS
				vec[i][k] = -2;									//imposto segnale di controllo

			else {
				int km = 0;

				int tmp = k - 1;

				while ((vec[i][tmp]) == -2) {					//sommo tutte le non fermate, tranne la prima

					tmp--;

					km += dist[tmp - 2] + 10;					//sommo 10 perch� non si � fermato
				}

				//calcolo tempo ipotetico minimo di percorrenza alla vel massima
				double h = ((dist[k - 3] + km) / v) * 60 + vec[i][tmp];					/*dist[k-3] == i km alla prima stazione senza fermata
																						*km == i km da dist[k-3] fino alla prox fermata
																						*/

																						//cast
				int intH = round((h + 0.5) + 7.5 + 5);									//7.5 == minuto per fare 10 km ai 80 km/h
																						//5 == minuti per la fermata
																						 
				if (vec[i][k] < intH)
					vec[i][k] = intH;
			}
		}
	}
}

//Stampa a schermo la matrice della linea ferroviaria
void ReadTables::print_lined() {

	std::cout << "\n" << " ******TimeLine****** " << "\n";

	for (int i = 0; i < vec2.size(); i++) {
		for (int j = 0; j < vec2[i].size(); j++)
			std::cout << vec2[i][j] << " ";

		std::cout << std::endl;
	}

}

//Stampa a schermo la matrice dei treni
void ReadTables::print_timet() {

	std::cout << "\n" << " ******TimeTable****** " << "\n";

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++)
			std::cout << vec[i][j] << " ";

		std::cout << std::endl;
	}
}

//funzione che imposta a -1 gli orari che corrispondono a stazioni piu vicine di 20km dalla precedente
//se la stazione di capolinea dista < 20km dalla precedente viene settata a -1 la precedente
void ReadTables::check_dist() {

	int n = 4;

	for (int i = 0; i < vec2.size() - 2; i++) {

		std::string::size_type sz;

		std::string t1 = vec2[i][2];

		int comp1 = stoi(t1, &sz);

		std::string t2 = vec2[i + 1][2];

		int comp2 = stoi(t2, &sz);



		if (comp2 < comp1 + 20) {
			vec2.erase(vec2.begin() + (i + 1));

			for (int j = 0; j < vec.size(); j++) {
				vec[j][i + n] = -1;

			}
			i--;
			n++;
		}
	}
	std::string::size_type sz;

	std::string t1 = vec2[vec2.size() - 2][2];

	int comp1 = std::stoi(t1, &sz);

	std::string t2 = vec2[vec2.size() - 1][2];

	int comp2 = std::stoi(t2, &sz);

	if (comp2 < comp1 + 20) {
		vec2.erase(vec2.begin() + (vec2.size() - 2));
		for (int i = 0; i < vec.size(); i++)
			vec[i][vec[i].size() - 2] = -1;
	}
}

//Completa la matrice dei treni (se incompleta) aggiungendo un valore compatibile con la velocit� e i tempi del treno 
void ReadTables::filler() {

	std::string type_o = "0";

	vec2[0].push_back(type_o);

	std::string km_o = "0";

	vec2[0].push_back(km_o);

	//Aggiunge uno zero ad ogni matrice TimeTable che verr� successivamente sostituito con un'orario calcolato correttamente
	for (int i = 0; i < vec.size(); i++)                      
		for (int j = 3; j < vec[i].size(); j++)
			if (vec[i].size() - 3 < vec2.size())
				vec[i].push_back(0);

}

//Elimina le stazioni che non rispettano il vincolo dei 20km di distanza
void ReadTables::eraseStations() {

	for (int i = 0; i < vec.size(); i++)
		for (int j = 0; j < vec[i].size(); j++)
			if (vec[i][j] == -1)
				vec[i].erase(vec[i].begin() + j);

}

//Funzione che riassume tutte le operazioni di lettura e acquisizione delle tabelle
void ReadTables::read_inputs() {

	read_timetable();

	read_linedescription();

	strin_conc();

	filler();

	check_dist();

	eraseStations();

	fill_matrix();

	print_lined();

	print_timet();
}