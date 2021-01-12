/*Gruppo 16:
/*Andrei Ovidiu Danciu - 1224263
/*Niccolò Castellan - 1227137
/*Giovanni Zago - 1226024

GitHub Repo link https

https://github.com/NonnoPinto/TrainSegnalationSystem.git

--------------------------------------------
Il progetto è così struttrato:
ReadTables.h: la classe per gli input. Si occupa di leggere i file e di passare i dati in modo coerente alle altre classi
Train.h: è la classe madre, con le funzioni virtuali e da cui tutti dipendono (come figli o come inclusione)
RTrain.h AVTrain.h AVSTrain.h : le classi figlie di train. Implementano le funzioni virtuali a seconda del tipo di treno
Station.h: classe madre delle stazioni. Dichiara le funzioni virtuali utili alla gestione delle fermate e del transito dei treni
LStation.h PStation.h : classi figlie delle stazioni. In base al loro tipo, implementano le funzioni puramente virtuali della classe base
Rails.h: una spece di intermediario tra classi e main. Unisce i treni e le stazioni e si occupa delle funzioni di comunicazione tra i due
	e, principalmente, delle situazioni di viaggio

Ovviamente i .cpp non sono che l'implementazione degli header
-------------------------------------------


L'elaborazione del sistema per la segnalazione dei treni ha richiesto alcune scelte progettuali che vanno oltre la consegna.
Il nostro progetto quindi, oltre a rispettare tutte le indicazioni date, ha le seguenti caratteristiche:

- la CMakeList.txt non funziona. Purtroppo non siamo riusciti ad importare i file con lei

- le timetables.txt di esempio sono tutte scritte col solo orario di partenza, per testare il calcolo dei tempi di arrivo di ReadTeables

- verifica i dati di ingresso, dando per scontato che le informazioni dei treni siano complete
  e che la prima e l'ultima stazione siano principali (tipo 0). In caso di assenza di dati, si assume che manchino le stazioni finali
  (ex: se ci sono 2 tempi di arrivo, si presume che siano delle prime due stazioni: i tempi mancanti vanno dalla terza fino all'ultima stazione)

- i cicli si basano sul minuto come tempo unitario, di conseguenza i km sono considerati anche nei loro decimali.
  Ogni distanza richiesta (i km delle stazioni, la distanza di sicurezza etc...) è quindi approssimata con un errore assoluto
  che tiene conto dei km percorribili dal treno in un minuto

- per i tempi di arrivo, invece, esegue la verifica solo delle stazioni "accettabili"
  e di queste verifica la correttezza secondo il seguente algoritmo:
	tempo_di_arrivo = (km_di_distanza - 10)/vel_max + 7.5 + 10
	Dove:
		-10 toglie i km attorno alla stazione con regole diverse
		+7.5 aggiunge i minuti necessari a percorrere quei 10km ai 80kmph
		+10 è il tempo di sicurezza richiesto

- per non creare casi troppo specifici, abbiamo preferito trattare la prima e l'ultima stazione esattamente come tutte le altre
