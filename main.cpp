#include "ReadTables.h"
#include "RTrain.h"
#include "AVTrain.h"
#include "AVSTrain.h"

using namespace std;

int main(){
	
	ReadTables TS;
	
	//dare degli output alla train station!
	TS.read_inputs();
	
	vector<vector<int>> timeTable = TS.get_timeTable();
	
	vector<vector<string>> lineDescription = TS.get_lineDescription();
	
	vector<string> myLineDescription;
	
	for(int i = 0; i<lineDescription.size(); i++)
		myLineDescription.push_back(lineDescription[i][2]);
	
	vector<Train> trains;
	
	for(int i = 0; i < timeTable.size(); i++){
		int x = timeTable[i][2];
		
		//vettore con i soli orari, senza variaibli di controllo
		vector<int> tmp (timeTable[i].begin()+3,timeTable[i].end());
		
		switch(x){
		case 1: //RTrain constructor
			trains.push_back(RTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		case 2: //AVTrain constructor
			trains.push_back(AVTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		case 3: //AVSTrain constructor
			trains.push_back(AVSTrain(timeTable[i][0], timeTable[i][1], tmp, myLineDescription));
			break;
		}
	}
	
	/*double myKM = 0;
	for (int i = 0 ; i< 30; i++){
		trains[2].set_status(1);
		trains[2].set_speed(-300);
		cout << trains[2].status << " ";
		myKM = trains[2].update_pos();
	}
	int myDaltay = trains[2].myDelay(36);
	
	cout << "\nKm fatti = " << myKM <<endl;
	*/
	cout << endl;
	
return 0;
}