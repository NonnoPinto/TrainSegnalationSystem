#include <iostream>
#include <vector>
#include <string>

class ReadTables {
public:
	void read_timetable();

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

	std::vector<std::vector<int>> get_timeTable() { return vec; };

	std::vector<std::vector<std::string>> get_lineDescription() { return vec2; };

private:

	//vettore per raccogliere i dati della timetable
	std::vector<std::vector<int>> vec;

	//vettore per raccogliere i dati della line description
	std::vector<std::vector<std::string>> vec2;
};

