/*#include <math.h>
#include <fstream>
#include <sstream>

//DA CANCELLARE
using namespace std;
//************************++

#include "TrainStation.h"


void TrainStation::read_timetable() {

	std::ifstream file_in("TimeTable.txt");

	std::string line;

	while (getline(file_in, line)) {

		std::istringstream ss(line);

		std::vector<int> new_vec;

		int v;

		while (ss >> v)
			new_vec.push_back(v);
			
		vec.push_back(new_vec);
	}
}

void TrainStation::read_linedescription() {

	std::ifstream file_in2("line_description.txt");

	std::string line2;

	while (getline(file_in2, line2)) {

		istringstream ss2(line2);

		vector<std::string> new_vec2;

		string in;

		while (ss2 >> in)
			new_vec2.push_back(in);

		vec2.push_back(new_vec2);
	}
}

void TrainStation::strin_conc() {

	for (int i = 0; i < vec2.size(); i++) {
		if ((vec2[i][1]).size() > 1) {

			string ins = vec2[i][0] + " " + vec2[i][1];

			vec2[i].erase(vec2[i].begin() + 1);

			vec2[i][0] = ins;
		}
	}
}

void TrainStation::fill_matrix() {
	
	//variabili ausiliarie
	std::vector<int> dist(vec2.size(), 0);
	
	size_t sz_prec;
		
	size_t sz_succ;
		
	string s_prec;
		
	string s_succ;
	
	//creo un array di dimensione (stazioni-1) con le distanze tra le stazioni
	for(int i = 0; i<vec2.size()-1; i++){
		s_prec = vec2[i][2];
		
		s_succ = vec2[i+1][2];
		
		int km_tmp = stoi(s_succ, &sz_succ) - stoi(s_prec, &sz_prec) - 10; //tolgo 10 per le zone
																	//ai 80km/h
		dist[i+1] = km_tmp;
	}
	
	//velocità massima del i-esimo treno
	double v;
	
	//indice treno
	for (int i=0; i<vec.size(); i++){
		
		if (vec[i][2] == 1)
			v = 160;
		else if (vec[i][2] == 2)
			v = 240;
		else
			v = 300;
		
		//indice tempo di arrivo alla stazione k-esima
		for(int k = 4; k < vec[i].size(); k++){
			
			if(v!=160 && vec2[k-3][1].compare("1") == 0) //se treno AV o AVS
				vec[i][k] = -2;							//imposto segnale di controllo
			
			else{
				int km = 0;
				int tmp=k-1;
				while((vec[i][tmp])==-2){ //sommo tutte le non fermate, tranne la prima
					tmp--;
					km += dist[tmp-2] + 10; //sommo 10 perchè non si è fermato
				}
				
				//cout << "km " << km << " + " << dist[k-3] << endl;
				
				//calcolo tempo ipotetico minimo di percorrenza alla vel massima
				double h = ((dist[k-3]+km)/v)*60 + vec[i][tmp];//dist[tmp-3] == i km alla prima stazione senza fermata
												//km == i km da dist[tmp-3] fino alla prox fermata
												//-10 == i km percorsi agli 80 all'ora
				
				//cast
				int intH = round((h+0.5) + 7.5); //7.5 == minuto per fare 10 km ai 80 km/h
				
				if (vec[i][k] < intH)
					vec[i][k] = intH;
			}
		}
	}
}

void TrainStation::check_trainstime() {

	for (int i = 1; i < vec2.size(); i++) {

		size_t sz;

		string s = vec2[i][2];

		int km = stoi(s, &sz);

		double v;

		for (int j = 0; j < vec.size(); j++) {

			int idx = 4;

			for (int n = 0; n < vec2[j].size(); n++) {
				if (vec[j][2] == 1)
					v = 160;
				else if (vec[j][2] == 2)
					v = 240;
				else
					v = 300;

				double h = double(km / v);

				int conf = (h * 60);

				//cout << " " << conf << " ";

				//cout << " " << vec[j][idx] << " ";

				if (idx > vec2.size())
					break;
				if (conf > vec[j][idx]) {

					vec[j][idx] = conf;

					idx++;
				}
			}
		}
	}
}

void TrainStation::print_lined() {
	
	cout << "L";
	
	for (int i = 0; i < vec2.size(); i++) {
		for (int j = 0; j < vec2[i].size(); j++)
			cout << vec2[i][j] << " ";
		cout << endl;
	}

}

void TrainStation::print_timet() {

	cout << "L";
	
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++)
			cout << vec[i][j] << " ";
		cout << endl;
	}
}

void TrainStation::check_dist() {

	int n = 4;
	
	for (int i = 0; i < vec2.size() - 2; i++) {

		string::size_type sz;

		string t1 = vec2[i][2];

		int comp1 = stoi(t1, &sz);

		string t2 = vec2[i + 1][2];

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
	string::size_type sz;

	string t1 = vec2[vec2.size() - 2][2];

	int comp1 = stoi(t1, &sz);

	string t2 = vec2[vec2.size() - 1][2];

	int comp2 = stoi(t2, &sz);

	if (comp2 < comp1 + 20) {
		vec2.erase(vec2.begin() + (vec2.size() - 2));
		for (int i = 0; i < vec.size(); i++)
			vec[i][vec[i].size() - 2] = -1;
	}
}

void TrainStation::filler(){
	//funzione che inserisce nella matrice il tipo della stazione principale e il km (fissato a 0)
	//Serve per poter successivamente effettuare confronti tra le distanze delle stazioni
	string type_o = "0";
	vec2[0].push_back(type_o);
	string km_o = "0";
	vec2[0].push_back(km_o);
}

void TrainStation::eraseStations(){
	for (int i = 0; i<vec.size(); i++)
		for (int j = 0; j<vec[i].size(); j++)
			if (vec[i][j] == -1)
				vec[i].erase(vec[i].begin()+j);
}

void TrainStation::read_inputs(){
	
	read_timetable();
	
	read_linedescription();
	
	strin_conc();
	
	filler();
	
	//check_trainstime();
	
	check_dist();
	
	eraseStations();
	
	fill_matrix();
	
	print_lined();
	
	print_timet();
}*/

