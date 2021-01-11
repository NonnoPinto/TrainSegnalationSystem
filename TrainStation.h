/* author: Niccolò Castellan - 1227137
* Header : Classe base da cui vengono derivate le classi derivate Train,Station e Rails
* Contiene le variabili ereditate dalle classi derivate (?)
*/

#ifndef TrainStation_h
#define TrainStation_h

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm> 

class TrainStation {

public:
	
	TrainStation() { clock = 0; };
	
	int update_clock() {return ++clock;};

	virtual double update_pos() { return 0; };
	
	virtual int myDelay(int clock_) { return 0; };
	
	virtual void set_timeTable(std::vector<int> &t) {};
	
	virtual void set_train_type(int x) {};
	
	virtual void set_vMax(int x) {};
	
	virtual void set_dist_max(int x) {};
	
	virtual void set_from(int x) {};

protected:
	virtual void set_speed (const int v) {};
	
	//vettore per raccogliere i dati della timetable
	std::vector<std::vector<int>> vec;
	
	//vettore per raccogliere i dati della line description
	std::vector<std::vector<std::string>> vec2;

	//orologio di sistema, viene aggiornato ad ogni passo che modifica lo stato del programma
	int clock = 0;
	
	/*virtual bool isParkAreaEmpty() = 0;
	
	virtual bool isRailFree(int p) = 0;
	
	virtual bool isFull() = 0;
	
	virtual void startTrain(int p) = 0;
	
	virtual bool runningIsFree() = 0;*/
	
	/* Funzione che legge i dati dalla timetable
	I dati vengono salvati in un vettore strutturato come una matrice che verrà poi restituito
	std::vector <std:: vector<int>> check_timetable();

	Funzione che legge i dati dalla "line_description"
	i dati vengono salvati in un vettore strutturato a matrice che verrà poi restituito
	std::vector <std::vector<std::string>> chack_line_description();

	//restituisce true se il treno è in transito, false se il treno deve ancora partire
	bool get_status() { return status; }

	//funzione che aggiorna l'orologio
	void set_clock();

	//funzione che ritorna l'orario corrente
	int get_time() { return clock; }*/


/*	void read_timetable();

	void read_linedescription();

	// Funzione che concatena in un unica stringa i nomi delle stazioni formati da due stringhe
	void strin_conc();

	//funzione che inserisce nella matrice il tipo della stazione principale e il km (fissato a 0)
	//Serve per poter successivamente effettuare confronti tra le distanze delle stazioni
	void fill_matrix();

	//funzione che confronta i tempi teorici con i limiti di velocità dei treni
	void check_trainstime();

	void print_lined();

	void print_timet();

	//funzione che imposta a -1 gli orari che corrispondono a stazioni piu vicine di 20km dalla precedente
	//se la stazione di capolinea dista < 20km dalla precedente viene settata a -1 la precedente
	void check_dist();
	
	void filler();
	
	void eraseStations();
	
	void read_inputs();
	
	std::vector<std::vector<int>> get_timeTable() {return vec;};
	
	std::vector<std::vector<std::string>> get_lineDescription() {return vec2;};*/
	
	//variabile che tiene conto dello stato di un treno(true = in transito, false = fermo)
	//bool status;

	//velocità corrente del treno
	//int speed;

	//posizione del treno
	//double pos;

	/*
	const int DIST_MAX = 10;

	int vMax;

	int vCrociera;

	const int train_type;

	int from;

	std::vector<int> time;

	int status;

	double pos;

	int delay;
	*/

};

#endif

/*
class Train : public TrainStation {
public:

	Train<L>();


private:

};

class Station : public TrainStation {
public:

	Station();

	//bool isFree();

	//Station next_station(Train t);

private:

};

class Rails : public TrainStation {
public:

	Rails();

	//funzione che rallenta il treno nel caso si trovi a 5 km di distanza da una stazione
	void slow_down(Train t, Station s);

	//funzione che porta il treno alla velocità di crociera una volta superati i 5 km antecedenti una stazione
	void speed_up(Train t, Station s);

	
	*funzione che controlla che due treni (uno in arrivo e uno fermano) non collidano
	*se il treno deve transitare e ci sono binari disponibili cambia binario
	*se il treno deve transitare e non ci sono binari liberi lo parcheggia
	*se il treno deve fermarsi e ci sono binari liberi per la fermata esegue quest'ultima azione
	*se il treno deve fermarsi e non ci sono binari liberi per la fermata lo parcheggia
	
	void check_smash(Train& t1, Train& t2);

	//funzione che imposta la velocità di un treno
	void set_speed(Train t);

	//funzione che ritorna la velocità del treno accettato come argomento
	int get_speed(Train t);
};*/
