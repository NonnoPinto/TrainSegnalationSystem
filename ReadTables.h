/*
* Author: Niccolò Castellan - 1227137
* Header : Classe base da cui vengono derivate le classi derivate Train,Station e Rails
* Contiene le funzioni necessarie alla lettura e elaborazione dei tile .txt
*/

#ifndef READTABLES_H
#define READTABLES_H

#include <iostream>
#include <vector>
#include <string>


class ReadTables {
public:

	//Funzione che legge,acquisice le informazioni della TimeTable e le memorizza in una matrice
	void read_timetable();

	//Funzione che legge,acquisice le informazioni della line_description e le memorizza in una matrice
	void read_linedescription();

	//Funzione che concatena in un unica stringa i nomi delle stazioni formati da due stringhe
	void strin_conc();

	//Funzione che inserisce nella matrice il tipo della stazione principale e il km (fissato a 0)
	//Serve per poter successivamente effettuare confronti tra le distanze delle stazioni
	void fill_matrix();

	//Stampa a schermo la matrice della linea ferroviaria
	void print_lined();

	//Stampa a schermo la matrice dei treni
	void print_timet();

	//funzione che imposta a -1 gli orari che corrispondono a stazioni piu vicine di 20km dalla precedente
	//se la stazione di capolinea dista < 20km dalla precedente viene settata a -1 la precedente
	void check_dist();

	//Completa la matrice dei treni (se incompleta) aggiungendo un valore compatibile con la velocità e i tempi del treno 
	void filler();

	//Elimina le stazioni che non rispettano il vincolo dei 20km di distanza
	void eraseStations();

	//Funzione che riassume tutte le operazioni di lettura e acquisizione delle tabelle
	void read_inputs();

	//Ritorna il vettore TimeTable
	std::vector<std::vector<int>> get_timeTable() { return vec; };

	//Ritorna il vettore line_description
	std::vector<std::vector<std::string>> get_lineDescription() { return vec2; };

private:

	//vettore per raccogliere i dati della timetable
	std::vector<std::vector<int>> vec;

	//vettore per raccogliere i dati della line description
	std::vector<std::vector<std::string>> vec2;
};

#endif
