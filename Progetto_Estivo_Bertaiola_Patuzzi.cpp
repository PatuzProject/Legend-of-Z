/*
------- VALORI FONDANTI -------
- IL GIOCO E' OPENSOURCE
- IL GIOCO E' FATTO E CREATO PER ESSERE GIOCATO COME SI VUOLE
- IL GIOCO E' FATTO PER ESSERE ESPANSO E MIGLIORATO DA CHIUNQUE VOGLIA FARLO
- IL GIOCO E' FATTO PER ESSERE DIVERTENTE, NON PER ESSERE PERFETTO
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

#define LVLMAX_SALUTE 20
#define LVLMAX_AGILITA 20
#define LVLMAX_FORTUNA 25
#define LVLMAX_FORZA 3
#define LVLMAX_SPIRITUALITA 14
#define LVLMAX_PLAYER LVLMAX_SALUTE + LVLMAX_FORZA + LVLMAX_AGILITA + LVLMAX_FORTUNA + LVLMAX_SPIRITUALITA

const string FILE_SALVATAGGIO_DEAFULT = "salvataggio.json";
const string FILE_CONFIG_DEAFULT = "config.json";
json DATA_CARICAMENTO;
json DATA_CONFIGURAZIONI;

//https://en.wikipedia.org/wiki/ANSI_escape_code
void errore(string s){
	cout << "\033[31m" << s << "\033[0m" << endl;
}
void info(string s){
	cout << "\033[43;1m" << s << "\033[0m" << endl;
}
void titolo(string s){
	cout << "\033[3;4m" << s << "\033[0m" << endl;
}
void racconto(string s){
	cout << "\033[0m" << s << endl;
}

class Oggetto {
	protected:
		string nome;
		unsigned short prezzo_ferro;
		unsigned short prezzo_oro;
		unsigned short prezzo_diamante;
		unsigned short prezzo_monete;
	public:
		void setNome(string nomeO){
			nome = nomeO;
		}
		string getNome(){
			return nome;
		}

		void setPrezzoFerro(unsigned short prezzo_ferroO){
			prezzo_ferro = prezzo_ferroO;
		}
		unsigned short getPrezzoFerro(){
			return prezzo_ferro;
		}

		void setPrezzoOro(unsigned short prezzo_oroO){
			prezzo_oro = prezzo_oroO;
		}
		unsigned short getPrezzoOro(){
			return prezzo_oro;
		}

		void setPrezzoDiamante(unsigned short prezzo_diamanteO){
			prezzo_diamante = prezzo_diamanteO;
		}
		unsigned short getPrezzoDiamante(){
			return prezzo_diamante;
		}

		void setPrezzoMonete(unsigned short prezzo_moneteO){
			prezzo_monete = prezzo_moneteO;
		}
		unsigned short getPrezzoMonete(){
			return prezzo_monete;
		}

		void toString(){
			/// TODO: completare il toString()
		}

		Oggetto(){
			nome = "";
			prezzo_ferro = 0;
			prezzo_oro = 0;
			prezzo_diamante = 0;
			prezzo_monete = 0;
		}

		Oggetto(string nomeO, unsigned short prezzo_ferroO,unsigned short prezzo_oroO,
				unsigned short prezzo_diamanteO, unsigned short prezzo_moneteO){
			nome = nomeO;
			prezzo_ferro = prezzo_ferroO;
			prezzo_oro = prezzo_oroO;
			prezzo_diamante = prezzo_diamanteO;
			prezzo_monete = prezzo_moneteO;
		}

};

class Armatura: public Oggetto {
	protected:
		unsigned short difesa;

	public:
		void setDifesa(unsigned short difesaA){
			difesa = difesaA;
		}
		unsigned short getDifesa(){
			return difesa;
		}

		void toString(){
			/// TODO: completare il toString()
		}

		Armatura(){
			nome = "";
			prezzo_ferro = 0;
			prezzo_oro = 0;
			prezzo_diamante = 0;
			prezzo_monete = 0;

			difesa = 0;
		}

		Armatura(string nomeA, unsigned short prezzo_ferroA,unsigned short prezzo_oroA,
				unsigned short prezzo_diamanteA, unsigned short prezzo_moneteA, unsigned short difesaA){
			nome = nomeA;
			prezzo_ferro = prezzo_ferroA;
			prezzo_oro = prezzo_oroA;
			prezzo_diamante = prezzo_diamanteA;
			prezzo_monete = prezzo_moneteA;

			difesa = difesaA;
		}
};

class Arma: public Oggetto {
	protected:
		unsigned short attacco;

	public:
		void setAttacco(unsigned short attaccoA){
			attacco = attaccoA;
		}
		unsigned short getAttacco(){
			return attacco;
		}

		void toString(){
			/// TODO: completare il toString()
		}

		Arma(){
			nome = "Spada moscia";
			prezzo_ferro = 0;
			prezzo_oro = 0;
			prezzo_diamante = 0;
			prezzo_monete = 0;

			attacco = 0;
		}

		Arma(string nomeA, unsigned short prezzo_ferroA,unsigned short prezzo_oroA,
				unsigned short prezzo_diamanteA, unsigned short prezzo_moneteA, unsigned short attaccoA){
			nome = nomeA;
			prezzo_ferro = prezzo_ferroA;
			prezzo_oro = prezzo_oroA;
			prezzo_diamante = prezzo_diamanteA;
			prezzo_monete = prezzo_moneteA;

			attacco = attaccoA;
		}
};

class Consumabile: public Oggetto {
	protected:
		unsigned short quantita;

	public:
		void setQuantita(unsigned short quantitaC){
			quantita = quantitaC;
		}
		unsigned short getQuantita(){
			return quantita;
		}

		void toString(){
			/// TODO: completare il toString()
		}

		Consumabile(){
			nome = "";
			prezzo_ferro = 0;
			prezzo_oro = 0;
			prezzo_diamante = 0;
			prezzo_monete = 0;

			quantita = 0;
		}

		Consumabile(string nomeC, unsigned short prezzo_ferroC,unsigned short prezzo_oroC,
				unsigned short prezzo_diamanteC, unsigned short prezzo_moneteC, unsigned short quantitaC){
			nome = nomeC;
			prezzo_ferro = prezzo_ferroC;
			prezzo_oro = prezzo_oroC;
			prezzo_diamante = prezzo_diamanteC;
			prezzo_monete = prezzo_moneteC;

			quantita = quantitaC;
		}
};

enum tipo_pozione {
	CURA,
	DIFESA,
	FORTUNA
};
class Pozione: public Consumabile{
	protected:
		unsigned short efficacia; //efficacia in %, utilizza spiritualita come moltiplicatore
		tipo_pozione tipoPoz;
		
	public:
		void setEfficacia(unsigned short efficaciaA){
			efficacia = efficaciaA;
		}
		unsigned short getEfficacia(){
			return efficacia;
		}

		void setTipoPozione(tipo_pozione tipoPozP){
			tipoPoz = tipoPozP;
		}
		tipo_pozione getTipoPozione(){
			return tipoPoz;
		}

		void toString(){
			/// TODO: completare il toString()
		}

		Pozione(){
			nome = "";
			prezzo_ferro = 0;
			prezzo_oro = 0;
			prezzo_diamante = 0;
			prezzo_monete = 0;
			quantita = 0;

			efficacia = 0;
			enum tipo_pozione tipoPoz = CURA;
		}

		Pozione(string nomeC, unsigned short prezzo_FerroC,unsigned short prezzo_oroC,
				unsigned short prezzo_diamanteC, unsigned short prezzo_moneteC, unsigned short quantitaC,
				unsigned short efficaciaC, enum tipo_pozione tipoPozC){
			nome = nomeC;
			prezzo_ferro = prezzo_FerroC;
			prezzo_oro = prezzo_oroC;
			prezzo_diamante = prezzo_diamanteC;
			prezzo_monete = prezzo_moneteC;
			quantita = quantitaC;

			efficacia = efficaciaC;
			enum tipo_pozione tipoPoz = tipoPozC;
		}
};

class PersonaggioBase {
	protected:
		string nome;
		unsigned int salute;
		unsigned int agilita; 
		unsigned int fortuna; // Utilizzato da Player e Nemico, aumenta prob. del critico
		
		unsigned int ferro;
		unsigned int oro;
		unsigned int diamante;
		unsigned int monete;

	public:
		PersonaggioBase(){
			nome = "Personaggio1";
			salute = 10;
			agilita = 5;
			fortuna = 5;

			ferro = 0;
			oro = 0;
			diamante = 0;
			monete = 0;
		}

		PersonaggioBase(string nomeP, int saluteP, int agilitaP, int fortunaP, int ferroP, int oroP, int diamanteP, int moneteP){
			nome = nomeP;
			salute = saluteP;
			agilita = agilitaP;
			fortuna = fortunaP;

			ferro = ferroP;
			oro = oroP;
			diamante = diamanteP;
			monete = moneteP;
		}

		//void setNome(string s){
		//	if (s != ""){
		//		nome = s;
		//	} else {
		//		// errore("Errore, nome personaggio vuoto");
		//	}
		//}
		string getNome(){
			return nome;
		}

		virtual void setSalute(unsigned int i){
			if(i > 0){
				salute = i;
			} else {
				salute = 10; //DEFAULT
			}
		}
		unsigned int getSalute(){
			return salute;
		}

		virtual void setAgilita(unsigned int i){
			if(i > 0){
				agilita = i;
			} else {
				agilita = 5; //DEFAULT
			}
		}
		unsigned int getAgilita(){
			return agilita;
		}

		virtual void setFortuna(unsigned int i){
			if(i > 0){
				fortuna = i;
			} else {
				fortuna = 5; //DEFAULT
			}
		}
		unsigned int getFortuna(){
			return fortuna;
		}

		void setFerro(unsigned int  i){
			if(i > 0){
				ferro = i;
			} else {
				ferro = 0; //DEFAULT
			}
		}
		unsigned int getFerro(){
			return ferro;
		}

		void setOro(unsigned int i){
			if(i > 0){
				oro = i;
			} else {
				oro = 0; //DEFAULT
			}
		}
		unsigned int getOro(){
			return oro;
		}

		void setDiamante(unsigned int i){
			if(i > 0){
				diamante = i;
			} else {
				diamante = 0; //DEFAULT
			}
		}
		unsigned int getDiamante(){
			return diamante;
		}

		void setMonete(unsigned int i){
			if(i > 0){
				monete = i;
			} else {
				monete = 0; //DEFAULT
			}
		}
		unsigned int getMonete(){
			return monete;
		}

		bool isAlive(){
			return salute > 0;
		}
};

//statistiche del nemico 
struct nemico {
	string name;
	unsigned int danno = 100;
	unsigned int vita = 100;
	unsigned int cure = 1;
	unsigned int agilita = 100;
	unsigned int fortuna = 100;

	unsigned int ferro = 0;
	unsigned int oro = 0;
	unsigned int diamante = 0;
	unsigned int monete = 0;
};

//struct che contiene tutte le informazioni sul giocatore
struct recPlayer{
	string nome = "";

	//statistiche
	int maxsalute = 10; //max 20
	int salute = 10; //max 20
	int forza = 1; //max 3
	int agilita = 5; //max 20

	//modificatori 
	int fortuna = 5; //max 25  possibilita' di ricevere monete doppie
	int spiritualita = 0; //max 14 utilizzo per tenere armi di un certo livello 
	int livello = maxsalute + forza + agilita + fortuna + spiritualita;
	int xp = 0;
	//item
	string nome_spada = "spada arruginita"; // le spade aumentano i danni
	int danno_spada = 0;
	string nome_armatura = "armatura in pelle";
	int difesa_armatura = 0;
	int pozione_curativa = 0;
	string zona = "dungeon_boss";
	
	//item quest
	int ferro = 0;
	int oro = 0;
	int diamante = 0;
	int monete = 0;
	
	//interazione npc
	int	minatore_frase = 1;
	int vescovo_frase = 1;
	int fabbro_frase = 1;
	
	int numero_segreto = 0;
	int numero_vescovo = 0;
	int numero_minatore = 0;
	int numero_fabbro = 0;
	bool gioco_finito = false;
};

class Quest {
	protected:
		unsigned short id;
		string descrizione;
		unsigned short ferro;
		unsigned short oro;
		unsigned short diamante;
		unsigned short moneta;
		string* discorso;

	public:
		Quest(unsigned short idQ,
			string descrizioneQ,
			unsigned short ferroQ,
			unsigned short oroQ,
			unsigned short diamanteQ,
			unsigned short monetaQ,
			string* discorsoQ){
				id = idQ;
				descrizione = descrizioneQ;
				ferro = ferroQ;
				oro = oroQ;
				diamante = diamanteQ;
				moneta = monetaQ;
				discorso = discorsoQ;
		}

		void setId(unsigned short idQ){
			id = idQ;
		}
		unsigned short getId(){
			return id;
		}

		void setFerro(unsigned short ferroQ){
			ferro = ferroQ;
		}
		unsigned short getFerro(){
			return ferro;
		}

		void setOro(unsigned short oroQ){
			oro = oroQ;
		}
		unsigned short getOro(){
			return oro;
		}

		void setDiamante(unsigned short diamanteQ){
			diamante = diamanteQ;
		}
		unsigned short getDiamante(){
			return diamante;
		}

		void setMoneta(unsigned short monetaQ){
			moneta = monetaQ;
		}
		unsigned short getMoneta(){
			return moneta;
		}

		//void setDiscorso(string* discorsoQ){
		//	discorso = discorsoQ;
		//}
		string* getDiscorso(){
			return discorso;
		}
};

class NPC: public PersonaggioBase{
	protected:
		string id;
		string nome;
		vector<Quest> listaQuest;
		
	public:
		NPC(string idN, string nomeN, vector<Quest> listaQuestN){
			id = idN;
			nome = nomeN;
			listaQuest = listaQuestN;
		}

		void setId(string idN){
			id = idN;
		}
		string getId(){
			return id;
		}

		void setNome(string nomeN){
			nome = nomeN;
		}
		string getNome(){
			return nome;
		}

		void addQuest(const Quest& questZ) {
			listaQuest.push_back(questZ);
		}
		Quest& getParent(size_t index) {
			if (index >= listaQuest.size()) {
				throw out_of_range("listaQuest::get: index out of range");
			}
			return listaQuest[index];
    	}
		vector<Quest>& getAllParent() {
			return listaQuest;
		}

};

class Zona {
	protected:
		string nome; //nome univoco, usato come 'id'
		string descrizione;
		vector<NPC> npc;
		unsigned short difficolta; // indice di difficolta
		
		vector<Zona> children; // lista delle destinazioni possibili da quella zona
		vector<Zona> parent; // lista dei possibili padri
		
	public:
		void setNome(string nomeZ){
			nome = nomeZ;
		}
		string getNome(){
			return nome;
		}

		void setDescrizione(string descrizioneZ){
			descrizione = descrizioneZ;
		}
		string getDescrizione(){
			return descrizione;
		}

		void addNPC(const NPC& npcZ) {
			npc.push_back(npcZ);
		}
		NPC& getNPC(size_t index) {
			if (index >= npc.size()) {
				throw out_of_range("npc::get: index out of range");
			}
			return npc[index];
    	}
		vector<NPC>& getAllNPC() {
			return npc;
		}

		void setDifficolta(unsigned short difficoltaZ){
			difficolta = difficoltaZ;
		}
		unsigned short getDifficolta(){
			return difficolta;
		}

		void addChildren(const Zona& childrenZ) {
			children.push_back(childrenZ);
		}
		Zona& getChildred(size_t index) {
			if (index >= children.size()) {
				throw out_of_range("children::get: index out of range");
			}
			return children[index];
    	}
		vector<Zona>& getAllChildren() {
			return children;
		}
		
		void addParent(const Zona& parentZ) {
			parent.push_back(parentZ);
		}
		Zona& getParent(size_t index) {
			if (index >= parent.size()) {
				throw out_of_range("parent::get: index out of range");
			}
			return parent[index];
    	}
		vector<Zona>& getAllParent() {
			return parent;
		}

		Zona(){}
		Zona(string nomeZ, string descrizioneZ, vector<NPC> npcZ, unsigned short difficoltaZ,
				vector<Zona> childrenZ, vector<Zona> parentZ){
			nome = nomeZ;
			descrizione = descrizioneZ;
			npc = npcZ;
			difficolta = difficoltaZ;
			children = childrenZ;
			parent = parentZ;
		}
};

class Nemico: public PersonaggioBase{
	protected:
		unsigned int danno; //danno base
		unsigned int cure; //num pozioni nel inventario
	
	public:
		Nemico(){
			nome = "Cattivone";
			salute = 100;
			agilita = 100;
			fortuna = 0;
			ferro = 0;
			oro = 0;
			diamante = 0;
			monete = 0;
			danno = 100;
			cure = 1;
		}

		Nemico(unsigned int difficolta){
			/// TODO: Implentare nemico secondo la zona, usare json
		}

		Nemico(string nomeN,
				unsigned int saluteN,
				unsigned int agilitaN, 
				unsigned int fortunaN,
				unsigned int ferroN,
				unsigned int oroN, 
				unsigned int diamanteN,
				unsigned int moneteN,
				unsigned int dannoN,
				unsigned int cureN){
			nome = nomeN;
			salute = saluteN;
			agilita = agilitaN;
			fortuna = fortunaN;

			ferro = ferroN;
			oro = oroN;
			diamante = diamanteN;
			monete = moneteN;
			danno = dannoN;
			cure = cureN;
		}

		void setDanno(unsigned int i){
			if(i > 0){
				danno = i;
			} else {
				danno = 100; //DEFAULT
			}
		}
		unsigned int getDanno(){
			return danno;
		}

		void setCure(unsigned int i){
			if(i > 0){
				cure = i;
			} else {
				cure = 1; //DEFAULT
			}
		}
		unsigned int getCure(){
			return cure;
		}

		json toJson(){
			return {
				{"nome", getNome() },
				{"salute", getSalute() },
				{"agilita", getAgilita() },
				{"fortuna", getFortuna() },
				{"ferro", getFerro() },
				{"oro", getOro() },
				{"diamanti", getDiamante() },
				{"monete", getMonete() },
				{"danno", getDanno() },
				{"cure", getCure() }
			};
		}
};

class RecPlayer: public PersonaggioBase {
	private:
		unsigned short numero_segreto;
		unsigned short numero_minatore;
		unsigned short numero_vescovo;
		unsigned short numero_fabbro;

		void setNumeriSegreti(){
			srand(time(NULL));
			numero_segreto = (rand()%899)+100;
			/// TODO: valutare di salvare solo il numero segreto e 'giocarci'
			///			(magari unire con il nome in binario) per avere anche gli altri numeri
			numero_vescovo = numero_segreto %10;// numero prima posizione
			numero_minatore = ((numero_segreto - numero_vescovo)%100);//numero seconda posizione
			numero_fabbro = (numero_segreto - (numero_minatore + numero_vescovo ));//numero terzo posizione
		}

		void setNumeroSegreto(unsigned int num){
			if (num > 0){
				numero_segreto = num;
			}
		}
		void setNumeroMinatore(unsigned int num){
			if (num > 0){
				numero_minatore = num;
			}
		}
		void setNumeroVescovo(unsigned int num){
			if (num > 0){
				numero_vescovo = num;
			}
		}
		void setNumeroFabbro(unsigned int num){
			if (num > 0){
				numero_fabbro = num;
			}
		}
	protected:
		unsigned int maxsalute; //max 20
		unsigned int forza; //max 3
		unsigned int spiritualita; //max 14 utilizzo per tenere armi di un certo livello 

		/// TODO: FARLE PROPRIETA livello PRIVATO MAGARI?
		unsigned int livello;
		unsigned int xp;

		string nome_spada; // le spade aumentano i danni
		unsigned int danno_spada;
		/// TODO: implementare class/struct spada
		//Arma armaEquipaggiata;

		string nome_armatura;
		unsigned int difesa_armatura;
		/// TODO: implementare class/struct armatura
		//Armatura armaturaEquipaggiata;

		/// TODO: implementare class/struct pozioni
		unsigned int pozione_curativa;
		//vector <Pozione> pozioni_disponibili;
		/// TODO: implementare zone da poter espandere
		string zona;
		unsigned short minatore_frase;	//interazione minatore
		unsigned short vescovo_frase;	//interazione vescovo
		unsigned short fabbro_frase;	//interazione fabbro
		
		bool gioco_finito;

	public:
		RecPlayer(){
			nome = "IlSalvatore";
			maxsalute = 10;
			salute = 10;
			forza = 1;
			agilita = 5;
			fortuna = 5;
			spiritualita = 0;
			ferro = 0;
			oro = 0;
			diamante = 0;
			monete = 0;
			aggiornaLivello();
			xp = 0;
			nome_spada = "spada arruginita";
			danno_spada = 0;
			//armaEquipaggiata = *(new Arma());
			nome_armatura = "armatura in pelle";
			difesa_armatura = 0;
			//armaturaEquipaggiata = *(new Armatura());
			//pozione_curativa = 0;
			zona = "dungeon_boss";
			minatore_frase = 1;
			vescovo_frase = 1;
			fabbro_frase = 1;
			setNumeriSegreti();
			gioco_finito = false;
		}

		RecPlayer(string nomeR){
			nome = nomeR;
			maxsalute = 10;
			salute = 10;
			forza = 1;
			agilita = 5;
			fortuna = 5;
			spiritualita = 0;
			ferro = 0;
			oro = 0;
			diamante = 0;
			monete = 0;
			aggiornaLivello();
			xp = 0;
			nome_spada = "spada arruginita";
			danno_spada = 0;
			//armaEquipaggiata = *(new Arma());
			nome_armatura = "armatura in pelle";
			difesa_armatura = 0;
			//armaturaEquipaggiata = *(new Armatura());
			//pozione_curativa = 0;
			zona = "dungeon_boss";
			minatore_frase = 1;
			vescovo_frase = 1;
			fabbro_frase = 1;
			setNumeriSegreti();
			gioco_finito = false;
		}

		RecPlayer(string nomeR,
				unsigned int saluteR,
				unsigned int agilitaR,
				unsigned int fortunaR,
				unsigned int ferroR,
				unsigned int oroR, 
				unsigned int diamanteR,
				unsigned int moneteR,
				unsigned int maxsaluteR,
				unsigned int forzaR, 
				unsigned int spriritualitaR,
				unsigned int xpR,
				////// DA CAMBIARE QUA SOTTO
				string nome_spadaR,
				unsigned int danno_spadaR,
				string nome_armaturaR,
				unsigned int difesa_armaturaR,
				unsigned int pozione_curativaR,
				string zonaR,
				////
				unsigned short minatore_fraseR,
				unsigned short vescovo_fraseR, 
				unsigned short fabbro_fraseR){
			nome = nomeR;
			salute = saluteR;
			agilita = agilitaR;
			fortuna = fortunaR;
			ferro = ferroR;
			oro = oroR;
			diamante = diamanteR;
			monete = moneteR;
			forza = forzaR;
			spiritualita = spriritualitaR;
			maxsalute = maxsaluteR;
			aggiornaLivello();
			xp = xpR;

			nome_spada = nome_spadaR;
			danno_spada = danno_spadaR;
			//armaEquipaggiata = *(new Arma());

			nome_armatura = nome_armaturaR;
			difesa_armatura = difesa_armaturaR;
			//armaturaEquipaggiata = *(new Armatura());

			pozione_curativa = pozione_curativaR;
			zona = zonaR;


			minatore_frase = minatore_fraseR;
			vescovo_frase = vescovo_fraseR;
			fabbro_frase = fabbro_fraseR;
			setNumeriSegreti();
			gioco_finito = false;
		}

		// OVERRIDE
		void setMaxSalute(unsigned int i){
			if(i > 0 && i <= LVLMAX_SALUTE){
				salute = i;
			} else {
				salute = 10; //DEFAULT
			}
		}
		unsigned int getMaxSalute(){
			return maxsalute;
		}

		void setAgilita(unsigned int i){
			if(i > 0 && i <= LVLMAX_AGILITA){
				agilita = i;
			} else {
				agilita = 5; //DEFAULT
			}
		}

		void setFortuna(unsigned int i){
			if(i > 0 && i <= LVLMAX_FORTUNA){
				fortuna = i;
			} else {
				fortuna = 5; //DEFAULT
			}
		}

		// SPECIFICI
		void setForza(unsigned int i){
			if(i > 0 && i <= LVLMAX_FORZA){
				forza = i;
			} else {
				forza = 1; //DEFAULT
			}
		}
		unsigned int getForza(){
			return forza;
		}

		void setSpiritualita(unsigned int i){
			if(i > 0 && i <= LVLMAX_SPIRITUALITA ){
				spiritualita = i;
			} else {
				spiritualita = 1; //DEFAULT
			}
		}
		unsigned int getSpiritualita(){
			return spiritualita;
		}

		void aggiornaLivello(){
			unsigned int temp = maxsalute + forza + agilita + fortuna + spiritualita;
			if(temp <= LVLMAX_PLAYER ){
				livello = temp;
			}
		}
		int getLivello(){
			return livello;
		}

		void setXP(unsigned int i){
			if(i > 0){
				xp = i;
			} else {
				xp = 1; //DEFAULT
			}
		}
		unsigned int getXP(){
			return xp;
		}
		
		void setNomeSpada(string s){
			if (s != ""){
				nome_spada = s;
			} else {
				errore("Errore, nome spada vuoto");
			}
		}
		string getNomeSpada(){
			return nome_spada;
		}

		void setDannoSpada(unsigned int i){
			if(i >= 0){
				danno_spada = i;
			} else {
				i = 0;
			}
		}
		unsigned int getDannoSpada(){
			return danno_spada;
		}

		void setNomeArmatura(string s){
			if (s != ""){
				nome_armatura = s;
			} else {
				errore("Errore, nome armatura vuoto");
			}
		}
		string getNomeArmatura(){
			return nome_armatura;
		}

		void setDifesaArmatura(unsigned int i){
			if(i >= 0){
				difesa_armatura = i;
			} else {
				i = 0;
			}
		}
		unsigned int getDifesaArmatura(){
			return difesa_armatura;
		}

		void setPozioneCurativa(unsigned int i){
			if(i >= 0){
				pozione_curativa = i;
			} else {
				i = 0;
			}
		}
		unsigned int getPozioneCurativa(){
			return pozione_curativa;
		}

		void setZona(string s){
			if (s != ""){
				zona = s;
			} else {
				errore("Errore, nome zona vuoto");
			}
		}
		string getZona(){
			return zona;
		}

		void setMinatoreFrase(unsigned short i){
			if(i > 0){
				minatore_frase = i;
			} else {
				i = 1;
			}
		}
		unsigned short getMinatoreFrase(){
			return minatore_frase;
		}

		void setVescovoFrase(unsigned short i){
			if(i > 0){
				vescovo_frase = i;
			} else {
				i = 1;
			}
		}
		unsigned short getVescovoFrase(){
			return vescovo_frase;
		}

		void setFabbroFrase(unsigned short i){
			if(i > 0){
				fabbro_frase = i;
			} else {
				i = 1;
			}
		}
		unsigned short getFabbroFrase(){
			return fabbro_frase;
		}

		unsigned short getNumeroSegreto(){
			return numero_segreto;
		}
		unsigned short getNumeroVescovo(){
			return numero_vescovo;
		}
		unsigned short getNumeroMinatore(){
			return numero_minatore;
		}
		unsigned short getNumeroFabbro(){
			return numero_fabbro;
		}

		bool isGiocoFinito(){
			return gioco_finito;
		}
		void setGiocoFinito(){
			gioco_finito = true;
		}

		//stampa statistiche personaggio
		void infoPersonaggio(){
			titolo("Presentati agli ospiti...");
			racconto("Nome: "+nome);
			racconto("Salute disponibile: " + to_string(salute));
			racconto("Salute massima: " + to_string(maxsalute));
			racconto("Forza: " + to_string(forza));
			racconto("Livello: " + to_string(livello));
			racconto("XP: " + to_string(xp));
			racconto("\t*Modificatori*");
			racconto("Agilita: " + to_string(agilita));
			racconto("Fortuna: " + to_string(fortuna));
			racconto("Spiritualita: " + to_string(spiritualita));
			racconto("\t*Equipaggiamento*");
			racconto(nome_spada + " che aumenta i danni di " + to_string(danno_spada));
			racconto(nome_armatura + " che riduce i danni di " + to_string(difesa_armatura));
			racconto("Pozione Curativa: " + to_string(pozione_curativa));
			racconto("\t*Item*");
			racconto("Ferro :" + to_string(ferro));
			racconto("Oro :" + to_string(oro));
			racconto("Diamante :" + to_string(diamante));
			racconto("Monete : " + to_string(monete));
		}

		json toJson(){
			return {
				{"id", getNumeroSegreto() },
				{"idM", getNumeroMinatore() },
				{"idV", getNumeroVescovo() },
				{"idF", getNumeroFabbro() },
				{"nome", getNome() },
				{"salute", getSalute() },
				{"maxsalute", getMaxSalute() },
				{"agilita", getAgilita() },
				{"fortuna", getFortuna() },
				{"ferro", getFerro() },
				{"oro", getOro() },
				{"diamanti", getDiamante() },
				{"monete", getMonete() },
				{"forza", getForza() },
				{"spiritualita", getSpiritualita() },
				{"livello", getLivello() },
				{"xp", getXP() },
				{"spada", {
					{"nome", getNomeSpada() },
					{"danno", getDannoSpada() }
				}},
				{"armatura", {
					{"nome", getNomeArmatura() },
					{"difesa", getDifesaArmatura() }
				}},
				{"pozione_curativa", getPozioneCurativa() },
				{"zona", getZona() },
				{"minatore_frase", getMinatoreFrase() },
				{"vescovo_frase", getVescovoFrase() },
				{"fabbo_frase", getFabbroFrase() },
				{"fine", isGiocoFinito() }
			};
		}
};

/*menu*/
int menu_scelte(nemico &enemy, recPlayer &player);
int open_menu(nemico &enemy, recPlayer &player);
void salva_account(char nome, int eta);
void info_personaggio_output(recPlayer player);

/*carico e scarico*/
void caricamento(recPlayer &player);
void salvataggio(recPlayer player);

/* zone e vari movimenti*/
int spostarsi(int scelta, recPlayer &player);
void viaggia(nemico &enemy, recPlayer &player);
void miniera(nemico &enemy, recPlayer &player, bool &esci_dal_gioco);
void arena(nemico &enemy, recPlayer &player, bool &esci_dal_gioco);
void villaggio(nemico &enemy, recPlayer &player, bool &esci_dal_gioco);
void mercato(nemico &enemy, recPlayer &player, bool &esci_dal_gioco);
void casa(nemico &enemy, recPlayer &player, bool &esci_dal_gioco);

/*interazioni con gli npc*/
void npc_parla(string nome_npc, int &qn_frase);
void quest_minatore(recPlayer &player);
void quest_vescovo(recPlayer &player);
void quest_fabbro(recPlayer &player);
void acquista_funzioni(recPlayer &player);

/*combattimento*/
void dungeon(nemico &enemy, recPlayer &player);
void selezione_mostro(int difficolta_dungeon,string zona,nemico &enemy);
void salita_di_livello(recPlayer &player);

bool schivata(nemico &enemy, recPlayer &player,int scelta);
void statistiche_combattimento(nemico &enemy, recPlayer &player, int &flag_ripeti);
int colpo_critico_player(recPlayer &player);

void attacco_player(nemico &enemy, recPlayer &player);
void pozioni_player(recPlayer &player, int &flag_ripeti);
void fuga_player(recPlayer &player, int &fuga, int difficolta_dungeon);
void turno_player(nemico &enemy, recPlayer &player,int &fuga,int difficolta_dungeon);
int colpo_critico_nemico(nemico &enemy);
void attacco_nemico(nemico &enemy, recPlayer &player);
void cura_nemico(nemico &enemy, recPlayer &player);
void turno_nemico(nemico &enemy, recPlayer &player, int difficolta_dungeon,int fuga);
void combattimento(nemico &enemy, recPlayer &player, int difficolta_dungeon);


class Combattimento {
	protected:
		RecPlayer personaggio;
		Nemico nemico;
		bool fuga;
		bool ripeti;

	public:
		Combattimento(RecPlayer playerC, Nemico nemicoC){
			personaggio = playerC;
			nemico = nemicoC;
			fuga = false;
			ripeti = false;
		};

		void iniziaCombattimento(){
			while(personaggio.isAlive() && nemico.isAlive()){
				if(firstTurn()){
					/// TODO: Implementare il turno del player 
				} else {
					/// TODO: Implementare il turno del player 
				}
				stampaStatistiche(nemico, personaggio);
			}
		}

		bool firstTurn(){
			return personaggio.getAgilita() >= nemico.getAgilita();
		}

		void stampaStatistiche(Nemico enemy, RecPlayer player){
			titolo("\t\t\tStatistiche combattimento");
			racconto(player.getNome() +"\t\t"+ enemy.getNome());
			racconto("sSalute: " + to_string(player.getSalute()) + "\tSalute: " + to_string(enemy.getSalute()));
			racconto("Danno: " + player.getForza() + to_string(player.getDannoSpada()) + "\tDanno: " + to_string(enemy.getDanno()));
			racconto("Difesa: " + player.getDifesaArmatura());
			racconto("Agilita': " + to_string(player.getAgilita()) + "\tAgilita': " + to_string(enemy.getAgilita()));
			racconto("Fortuna: " + to_string(player.getFortuna()) + "\tFortuna: " + to_string(enemy.getFortuna()));
			racconto("Arma: " + player.getNomeSpada());
			racconto("Armatura " + player.getNomeArmatura());
		}
};







int menu_scelte(nemico &enemy, recPlayer &player){
	int scelta=0;//variabile che determina le scelte al interno del menu
	int zona=0;//variabile che determina la zona in cui andare
	bool chiudi=false;//bool che serve per la chiusura del gioco
	//menu iniziale
	cout<<"inserisci nome utente:"<<endl;
	cin>>player.nome;
	system("CLS");
	do{
		scelta=open_menu(enemy, player);//funzione che determina la scelta
		switch (scelta){
			case 1:
				viaggia(enemy,player);//premendo 1 inizia il gioco e si va a scegliere la prima zona in cui andare
				system("CLS");//serve per pulire il/la terminale/console 
				break;
			case 2:
				system("CLS");
				salvataggio(player);//premendo 2 Si salva la partita in salvataggio.txt che viene generato nella funzione 
				cout<<"stiamo salvando la partita...";
				system("pause");//serve a interrompere il programma e farlo ripartire solo dopo che si preme il tasto invio
				break;	
			case 3:
				system("CLS");
				caricamento(player);//premendo 3 si carica il salvataggio
				break;
			case 4:
				chiudi=true;//premendo 4 il bool diventa true e il gioco si chiude 
				cout<<endl<<"arrivederci"<<endl;
				break;
		} 
	}while(!chiudi);
}

int open_menu(nemico &enemy, recPlayer &player){//funzione che gestisce gli input dati nel menu
	int scelta;
	do{//gioca da fare
	cout<<"[1] Gioca"<<endl<<"[2] Salva account"<<endl<<"[3] Carica account"<<endl<<"[4] Esci dal gioco"<<endl;//innformare 
		cin>>scelta;
		if(scelta<1&&scelta>5){
			cout<<"inserire un numero valido"<<endl;
			system("pause");
			system("CLS");
		}
	}while(scelta<1&&scelta>6);
	system("CLS");
	return scelta;	
}

void caricamento(recPlayer &player){//funzione che gestisce il cariamento del account 
    cout<<"stiamo caricando i file..."<<endl;//per bellezza e informare l'utente
    system("pause");
	ifstream MyReadFile("salvataggio.txt");//apriamo il file in lettura 
	if (!MyReadFile.is_open()) {//se il file non si apre informiamo l'utente
        cout<< "Non e' stato possibile aprire - 'salvataggio.txt'" << endl;
    }else{//passiamo tutte le cose dal file alla struct palyer 
		//prendo le statistiche
		getline(MyReadFile,player.nome);//nome		//tutti i dati del file sono messi uno sotto l'altro e li passiamo passo passo nella struct
		getline(MyReadFile,player.nome_spada);
		getline(MyReadFile,player.nome_armatura);
		getline(MyReadFile, player.zona);
		
		MyReadFile>>player.maxsalute;
		
		MyReadFile>>player.salute;
		
		MyReadFile>>player.forza;
		
		MyReadFile>>player.agilita;
		
		MyReadFile>>player.fortuna;
		
		MyReadFile>>player.spiritualita;
		
		player.livello=player.maxsalute+player.forza+player.agilita+player.fortuna+player.spiritualita;
		MyReadFile>>player.xp;
	
		MyReadFile>>player.danno_spada;
		
		MyReadFile>>player.difesa_armatura;
		MyReadFile>>player.pozione_curativa;

		//item
		MyReadFile>>player.ferro;
		
		MyReadFile>>player.oro;
	
		MyReadFile>>player.diamante;
		
		MyReadFile>>player.monete;

		//iterazioni npc
		MyReadFile>>player.minatore_frase;
		MyReadFile>>player.vescovo_frase;
		MyReadFile>>player.fabbro_frase;
		MyReadFile>>player.numero_segreto;
		player.numero_vescovo=player.numero_segreto %10;// numero prima posizione
		player.numero_minatore=((player.numero_segreto - player.numero_vescovo)%100);//numero seconda posizione
		player.numero_fabbro=(player.numero_segreto - (player.numero_minatore+player.numero_vescovo ));
		MyReadFile>>player.gioco_finito;
	// chiude il file
	}
	MyReadFile.close();
}

void salvataggio(recPlayer player){//passiamo la struct player per mettre tutti i dati della partita che sta venendo giocata nel file
    ofstream FileSalvataggio("salvataggio.txt");//apriamo salvataggio in scrittura
    //statistiche
    FileSalvataggio<<player.nome<<endl; //stesso passaggio del caricamento ma i dati si passano dalla struct al file
    FileSalvataggio<<player.nome_spada<<endl;
    FileSalvataggio<<player.nome_armatura<<endl;
    FileSalvataggio<<player.zona<<endl;
    FileSalvataggio<<player.maxsalute<<endl;
    FileSalvataggio<<player.salute<<endl;
    FileSalvataggio<<player.forza<<endl;
    FileSalvataggio<<player.agilita<<endl;
    //modificatori
    FileSalvataggio<<player.fortuna<<endl;
    FileSalvataggio<<player.spiritualita<<endl;
    FileSalvataggio<<player.xp<<endl;
    //item
    FileSalvataggio<<player.danno_spada<<endl;
    FileSalvataggio<<player.difesa_armatura<<endl;
    FileSalvataggio<<player.pozione_curativa<<endl;
    
    //item quest
    FileSalvataggio<<player.ferro<<endl;
    FileSalvataggio<<player.oro<<endl;
    FileSalvataggio<<player.diamante<<endl;
    FileSalvataggio<<player.monete<<endl;
    //interazione npc
    FileSalvataggio<<player.minatore_frase<<endl;
    FileSalvataggio<<player.vescovo_frase<<endl;
    FileSalvataggio<<player.fabbro_frase<<endl;
    FileSalvataggio<<player.numero_segreto<<endl;
    //gioco finito?
    FileSalvataggio<<player.gioco_finito<<endl;
}
// Carica i dati in DATA_CARICAMENTO usando il path della variabile FILE_SALVATAGGIO_DEAFULT
// ritornando true o false se e' riuscito a caricarli o meno
bool caricamentoJSON(){
	info("Carico la partita...");
	system("pause");
	///TODO: valutare se richiedere il nome del file da caricare
	ifstream File(FILE_SALVATAGGIO_DEAFULT);
	if (!File.is_open()) {
        errore("Non e' stato possibile trovare il file '" + FILE_SALVATAGGIO_DEAFULT + "'");
		return false;
    } else {
		DATA_CARICAMENTO = json::parse(File);
		return true;
	}
}

// Salva i dati in DATA_CARICAMENTO usando il path della variabile FILE_SALVATAGGIO_DEAFULT
// ritornando true o false se e' riuscito a salvarli o meno
bool salvataggioJSON(){
	info("Stiamo salvando la partita...");
	ofstream FileSalvataggio(FILE_SALVATAGGIO_DEAFULT);
	FileSalvataggio << setw(4) << DATA_CARICAMENTO << endl;
	FileSalvataggio.close();
	if(!FileSalvataggio) {
		errore("Errore salvataggio partita!");
		return false;
	} else {
		info("Salvataggio partita concluso con successo.");
		return true;
	}
}

void info_personaggio_output(recPlayer player){//serve per quando l'utente seleziona informazioni personaggio dal minatore,
	system("CLS");
	cout<<"Nome: "<<player.nome <<endl;
	cout<<"Salute disponibile: "<<player.salute<<endl;
	cout<<"Salute massima: "<<player.maxsalute<<endl;
	cout<<"Forza: "<<player.forza<<endl;
	cout<<"Livello: "<<player.livello<<endl;
	cout<<"XP: "<<player.xp<<endl;
	cout<<endl<<"\t *Modificatori*"<<endl;
	cout<<"Agilita: "<<player.agilita<<endl;
	cout<<"Fortuna: "<<player.fortuna<<endl;
	cout<<"Spiritualita: "<<player.spiritualita<<endl;
	cout<<endl<<"\t *Equipaggiamento*"<<endl;
	cout<<player.nome_spada <<" che aumenta i danni di "<<player.danno_spada<<endl;
	cout<<player.nome_armatura <<" che riduce i danni di "<<player.difesa_armatura <<endl;
	cout<<"Pozione Curativa: "<<player.pozione_curativa<<endl;
	cout<<endl<<"\t *Item*"<<endl;
	cout<<"Ferro :"<<player.ferro<<endl;
	cout<<"Oro :"<<player.oro<<endl;
	cout<<"Diamante :"<<player.diamante<<endl;
	cout<<"Monete : "<<player.monete<<endl;
	
	system("pause");
	system("CLS");
	return;
}

void viaggia(nemico &enemy, recPlayer &player){//gestione del viaggio
	int zona=0;
	bool esci_dal_gioco=false;
	do{
		system("CLS");
		zona=spostarsi(zona,player);
		switch(zona){
			case 1:
				player.zona="Miniera";
				miniera(enemy, player, esci_dal_gioco);
				break;
			case 2:
				player.zona="Casa";
				casa(enemy, player, esci_dal_gioco);
				break;
			case 3:
				player.zona="Villaggio";
				villaggio(enemy,player, esci_dal_gioco);
				break;
			case 4:
				player.zona="Mercato";
				mercato(enemy,player, esci_dal_gioco);
				break;
			case 5:
				player.zona="Arena";
				arena(enemy,player, esci_dal_gioco);
				break;
			case 20022005:
				player.gioco_finito=true;
				cout<<endl<<"BRAVO HAI ATTIVATO L'EASTEREGG E HAI FINTIO IL GIOCO"<<endl;
				system("pause");
				break;			
			
		}
		if(player.numero_segreto==zona){//se il player su viaggia inserisce il numero segreto composto tramite le quest si accede al combattimento
			player.zona="dungeon_boss";
			dungeon(enemy,player);//si accede al combvattimento con il boss nel suo dungeon
		}
	}while(!(esci_dal_gioco||player.gioco_finito));//fino a quando il gioco non e' finito e' posssibile spostarsi 
}

int spostarsi(int scelta,recPlayer &player){
    //scegli tra miniera, casa,villaggio e mercato
	do{
		cout<<"Scegli dove andare"<<endl<<"[1] Miniera"<<endl<<"[2] Casa"<<endl<<"[3] Villaggio"<<endl<<"[4] Mercato"<<endl<<"[5] Arena"<<endl;//si propongono le zone al utente
    	cin>>scelta;
    	if((scelta>5&&scelta<1)&&scelta!= player.numero_segreto){//se la scelta e' diversa dalle 4 o dal numero per accedere al boss si fa rifare
    		system("CLS");
		}
    }while((scelta>5&&scelta<1&&scelta!=20022005)&&scelta!= player.numero_segreto);
    system("CLS");
    return scelta;
}

void miniera(nemico &enemy, recPlayer &player, bool &esci_dal_gioco){
    system("CLS");
    int parla;
    bool lascia_zona = false;
    cout<<"sei arrivato in miniera..."<<endl<<endl;
    system("pause");
    system("CLS");
    cout<<endl<<"seduto su un masso affianco al muro c'e' un minatore..."<<endl;
    system("pause");
    system("CLS");
    do{
	    do{//cose da fare con il minaore
	        cout<<"[1] Parla con il minatore"<<endl<<"[2] Dungeon"<<endl<<"[3] Viaggia"<<endl<<"[4] Esci dal gioco"<<endl<<"[5] Info personaggio"<<endl; //vorrei fare un torna alla scelta ma non so come fare
	        cin>>parla;
	    }while (parla>5 ||parla<0);
	    switch (parla){
	    	case 1:
	    		quest_minatore(player);//porta alla funzione che ti da la quest da fare per il minatore
		    	break;
	    	case 2:
	    		dungeon(enemy, player);//porta al dungeon del minaore per raccogliere le cose che chiede
	    		break;
	    	case 3:
	    		lascia_zona=true;//serve a lasciare la zona tornare indietro e andare in altri dungeon per prendere altri materiali,monet,ecc
	    		break;
	    	case 4:
	    		esci_dal_gioco=true;	//esci dal gioco e SALVA quando esci dal gioco se no quando il giorno dopo apri il gioco paingi che hai perso tutto "ESPERIENZA PERSONALE"
				break;
			case 5:
				info_personaggio_output(player);// ti da le informazioni sul personaggio TUTTE ma proprio TUTTE 
				break;
		}
	}while(!(esci_dal_gioco||lascia_zona));// si fa fino a quando non si ha lascia zona o esci dal gioco
}

void arena(nemico &enemy, recPlayer &player, bool &esci_dal_gioco){
    system("CLS");
    int parla;
    bool lascia_zona = false;
    cout<<"sei arrivato nell'arena"<<endl<<endl;
    system("pause");
    system("CLS");
    cout<<"un enorme colosseo dove e' possibile combattere e ottenere piu' xp"<<endl;
    system("pause");
    system("CLS");
    do{
	    do{//cose da fare nell'arena
	        cout<<"[1] Dungeon"<<endl<<"[2] Viaggia"<<endl<<"[3] Esci dal gioco"<<endl<<"[4] Info personaggio"<<endl; //vorrei fare un torna alla scelta ma non so come fare
	        cin>>parla;
	    }while (parla>4 ||parla<0);
	    switch (parla){
	    	case 1:
	    		dungeon(enemy, player);//porta al dungeon del minaore per raccogliere le cose che chiede
	    		break;
	    	case 2:
	    		lascia_zona=true;//serve a lasciare la zona tornare indietro e andare in altri dungeon per prendere altri materiali,monet,ecc
	    		break;
	    	case 3:
	    		esci_dal_gioco=true;	//esci dal gioco e SALVA quando esci dal gioco se no quando il giorno dopo apri il gioco paingi che hai perso tutto "ESPERIENZA PERSONALE"
				break;
			case 4:
				info_personaggio_output(player);// ti da le informazioni sul personaggio TUTTE ma proprio TUTTE 
				break;
		}
	}while(!(esci_dal_gioco||lascia_zona));// si fa fino a quando non si ha lascia zona o esci dal gioco
}

void villaggio(nemico &enemy, recPlayer &player, bool &esci_dal_gioco){//cose da fare al villagigo
	system("CLS");
	int parla;
	bool lascia_zona=false;
	cout<<"sei arrivato al villaggio..."<<endl;
	system("pause");
	system("CLS");
	cout<<"fuori dalla chiesa il vescovo che ti sta guardando..."<<endl;
	system("pause");
	system("CLS");
	do{
		do{//cose scelta delle cose da fare con il vescovo
	        cout<<"[1] Parla con il vescovo"<<endl<<"[2] Dungeon"<<endl<<"[3] Viaggia"<<endl<<"[4] Esci dal gioco"<<endl<<"[5] Info personaggio"<<endl; //vorrei fare un torna alla scelta ma non so come fare
	        cin>>parla;
	    }while (parla>5 || parla<0);
	    switch (parla){
	    	case 1:
	    		quest_vescovo(player);//scopri e compi la quest del vescovo
		    	break;
	    	case 2:
	    		dungeon(enemy, player);//fai il dungeon del vescovo per guadagnare altre cose
	    		break;
	    	case 3:
	    		lascia_zona=true;//lascia la zona
	    		break;
	    	case 4:
	    		esci_dal_gioco=true;//esci dal gioco e vale il consiglio dato sopra
				break;	
			case 5:
				info_personaggio_output(player);// ti da le informazioni sul personaggio TUTTE ma proprio TUTTE 
				break;
		}
	}while(!(esci_dal_gioco||lascia_zona));// si fa fino a quando non si ha lascia zona o esci dal gioco
}

//
void mercato(nemico &enemy, recPlayer &player,bool &esci_dal_gioco){//cose da fare al mercato
    system("CLS");
    int parla;
    bool lascia_zona=false;
	cout<<"sei arrivato al mercato..."<<endl;
    system("pause");
    system("CLS");
    cout<<"davanti alla forgia c'e il fabbro e su un lato c'e' una bancarella con un mercante ..."<<endl;
    system("pause");
    system("CLS");
    do{
		do{//cose da fare con il fabbro 
			cout<<"[1] Parla con il fabbro"<<endl<<"[2] Acquista"<<endl<<"[3] Viaggia"<<endl<<"[4] Esci dal gioco"<<endl<<"[5] Info personaggio"<<endl;
	    	cin>>parla;
		}while (parla>5 || parla<0);
	    switch (parla){
			case 1:
		   		quest_fabbro(player);//fare le quest del fabbro
		    	break;
		    case 2:
		    	acquista_funzioni(player);
		    	break;
	    	case 3:
	    		lascia_zona=true;//lasci la zona
	    		break;
	    	case 4:
	    		esci_dal_gioco=true;	//esci dal gico
				break;
			case 5:
				info_personaggio_output(player);// ti da le informazioni sul personaggio TUTTE ma proprio TUTTE 
				break;
		}
	}while(!(esci_dal_gioco||lascia_zona));// si fa fino a quando non si ha lascia zona o esci dal gioco
    } 


void casa(nemico &enemy, recPlayer &player, bool &esci_dal_gioco){
    system("CLS");
    int parla;
    bool lascia_zona =false;
    cout<<"sei arrivato a casa..."<<endl;
    system("pause");
    system("CLS");
    cout<<"a casa ti puoi riposare per rigenerarti"<<endl;
    system("pause");
	do{//cose da fare a casa
	    do{
	        cout<<"[1] Riposa"<<endl<<"[2] Viaggia"<<endl<<"[3] Esci dal gioco"<<endl;
	        cin>>parla;
	  	}while (parla>2 &&parla<0);
	    switch (parla){
			case 1:
				cout<<endl<<"ti sdrai nel letto e riposi"<<endl;
				system("pause");
				system("CLS");
				cout<<"hai rigenerato tutta la tua salute"<<endl<<endl;
				player.salute=player.maxsalute; //riposarsi rigenera la vita 
		    	break;
	    	case 2:
	    		lascia_zona=true;
	    		break;
	    	case 3:
	    		esci_dal_gioco=true;	
				break;	
		}
	}while(!(esci_dal_gioco||lascia_zona));
}//
void npc_parla(string nome_npc, int &qn_frase){
	//si prende il nome del npc e il numero della frase
	string frase=""; 
	string file_nome_npc=nome_npc+".txt";//si aggiunge .txt al nome del ncp cosi che si apra il file giusto
	
	char apertura_file[file_nome_npc.length()]="";//imposta la lunghezza del char necessaria per contenenre npc.txt
    int i=0;
    for (i = 0; i < file_nome_npc.length(); i++) {
        apertura_file[i] = file_nome_npc[i];//si passa la stringa nel char
    }
	ifstream MyReadFile(apertura_file);//si apre il file in lettura
	if(!MyReadFile.is_open()){
		//error("Non ho trovato il file");
	}
	for (int i =0; i<qn_frase; i++){
		getline(MyReadFile, frase);//si passa ogni riga fino ad arrivare alla frase che serve che e' la variabiel qn_frase
	}
	cout <<endl<< frase<<endl<<endl;//dopo che la si ha la si stampa
	
	// chiude il file
	MyReadFile.close();
	
}

void quest_minatore(recPlayer &player){//quest del minatore
	string nome_npc="minatore";//ci si segna il nome del npc cosi da sapere dopo che file apire
	int risposta=1;
	system("CLS");
	if(player.minatore_frase ==1){
		for( ; player.minatore_frase<5; player.minatore_frase++){//sono 5 le frasi da dire
			npc_parla(nome_npc, player.minatore_frase);// si fanno dire tutte le frasi del minatore
		}
		player.minatore_frase--;
		
	}else if(player.minatore_frase ==4){//dopo che sono state dette le frasi da dire si fa fare la prima quest
		npc_parla(nome_npc, player.minatore_frase);//si fa ripetere l'ultima frse cosi da ripetere la quest
		do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] vai via"<<endl;//ecco a te gli dai i materiali= quest fatta //vai via per andare al dungeon e fare la quest
			cin>>risposta;
		}while(risposta<1||risposta>2);
		if(risposta==1){
			system("CLS");
			if(player.ferro >=7){
				player.ferro-=7;// si rimuovono i materiali richiesti dal inventario 
				player.minatore_frase++;//incrementiamo la frase
					
				for(int i=player.minatore_frase ; player.minatore_frase < i+4; player.minatore_frase ++){
					npc_parla(nome_npc, player.minatore_frase);//mini dialogo
				}
				player.minatore_frase--;//a fine dialogo c'e' una quest e bisogna ripetere l'ultima frase
			}else if(player.ferro <7){
				cout<<endl<<"dove e' il mio ferro????"<<endl;//se dice ecco a te e non si ha abbastanza ferro
			}//chiudiamo il dialogo con l'else if e quindi si rifa'
		}
	}else if(player.minatore_frase ==8){//seconda quest
		npc_parla(nome_npc, player.minatore_frase);
		do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] vai via"<<endl;//UGUALE A SOPRA PERO' FRASI DIVERSE E CON L'ORO
			cin>>risposta;
		}while(risposta<1||risposta>2);
		if(risposta==1){
			system("CLS");
			if(player.oro >=5){
				player.oro-=5;
				player.minatore_frase++;
					
				for(int i=player.minatore_frase ; player.minatore_frase < i+5; player.minatore_frase ++){
					npc_parla(nome_npc, player.minatore_frase);
				}
				player.minatore_frase--;
			}else if(player.oro <5){
				cout<<endl<<"dove e' il mio oro????"<<endl;
			}
		}
	}else if(player.minatore_frase ==13){//ultima quest
		npc_parla(nome_npc, player.minatore_frase);
		do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] vai via"<<endl;//UGUALE A SOPRA PERO' FRASI DIVERSE E CON I DIAMANTI
			cin>>risposta;
		}while(risposta<1||risposta>2);
		if(risposta==1){
			system("CLS");
			if(player.diamante >=2){
				player.diamante-=2;
				player.minatore_frase++;
				for(int i=player.minatore_frase ; player.minatore_frase < i+2; player.minatore_frase ++){
					npc_parla(nome_npc, player.minatore_frase);
				}
				cout<<"numero:"<<player.numero_minatore/10<<endl;//ridiamo la seconda cifra del numero 
			}else if(player.diamante <2){
				cout<<endl<<"dove sono i miei diamanti????"<<endl;
			}
		}
	}else if(player.minatore_frase ==16){
		npc_parla(nome_npc, player.minatore_frase);
		cout<<"numero:"<<player.numero_minatore/10<<endl;//diamo la seconda cifra del numero segreto
	}else{ //in caso di bug
		errore("Errore generico");
	}
}

void quest_vescovo(recPlayer &player){
	int risposta=1;
	string nome_npc="Vescovo";
	if(player.spiritualita<10){//per parlare con il vescovo bisogna avere tot spiritualita' che si fa con il level up che si fa con dentro il dungeon
		cout<<endl<<"scusa non posso parlare con te ora, torna quando la dea Hylia ti sorrider�"<<endl;
	}else{
		if(player.vescovo_frase==1){
			for(int i=player.vescovo_frase ; player.vescovo_frase < i+2; player.vescovo_frase ++){//stessa cosa del minatore
				npc_parla(nome_npc, player.vescovo_frase);
			}
			player.vescovo_frase--;
		}else if(player.vescovo_frase==2){
			npc_parla(nome_npc, player.vescovo_frase);
			do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] via via"<<endl;
			cin>>risposta;
			}while(risposta<1||risposta>2);
			if(risposta==1){
				system("CLS");
				if(player.oro >=7&&player.monete >= 10){
					player.oro-=7;
					player.monete-=10;
					for(int i=player.vescovo_frase ; player.vescovo_frase < i+5; player.vescovo_frase ++){
						npc_parla(nome_npc, player.vescovo_frase);
					}	
					player.vescovo_frase--;
					cout<<"numero: "<<player.numero_vescovo<<endl;
				}
			}
		}else if(player.vescovo_frase==6){
			npc_parla(nome_npc, player.vescovo_frase);
			cout<<"numero: "<<player.numero_vescovo<<endl;
		}else{
			errore("Errore generico");
		}
	}
}

void quest_fabbro(recPlayer &player){//STESSA COSA DEL MINATORE PERO' HA 2 QUEST E MODIFICA L'EQUIPAGGIAMENTO
	int risposta=1;
	string nome_npc="fabbro";
	if(player.fabbro_frase ==1){
		for(int i=player.fabbro_frase ; player.fabbro_frase < i+2; player.fabbro_frase ++){
			npc_parla(nome_npc, player.fabbro_frase);
		}
		player.fabbro_frase--;
	}else if(player.fabbro_frase==2){
		npc_parla(nome_npc, player.fabbro_frase);
		do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] vai via"<<endl;
			cin>>risposta;
		}while(risposta<1||risposta>2);
		if(risposta==1){
			system("CLS");
			if(player.ferro >=5&&player.monete >= 7){// fare la quest da una ricompensa in equipaggiamento
				player.ferro-=5;
				player.monete-=7;
				player.nome_armatura ="armatura in ferro";
				player.difesa_armatura = 1;
				player.nome_spada = "spada in ferro";
				player.danno_spada = 1;
				player.fabbro_frase++;
				for(int i=player.fabbro_frase ; player.fabbro_frase < i+3; player.fabbro_frase ++){
					npc_parla(nome_npc, player.fabbro_frase);
				}	
				player.fabbro_frase--;
			}else{
				cout<<endl<<"Fabbro: mancano dei materiali a quanto pare per completare la forgiatura"<<endl;
			}
		}
	}else if(player.fabbro_frase==5){
		npc_parla(nome_npc, player.fabbro_frase);
		do{
			cout<<endl<<"[1] ecco a te"<<endl<<"[2] vai via"<<endl;
			cin>>risposta;
		}while(risposta<1||risposta>2);
		if(risposta==1){
			system("CLS");
			if(player.ferro >=5&&player.monete >= 20&&player.oro>=10&&player.diamante>=3){
				player.ferro-=5;
				player.monete-=20;
				player.oro-=10;
				player.diamante-=3;
				player.nome_armatura ="armatura scarlatta";
				player.difesa_armatura = 2;
				player.nome_spada = "spada di exaliburger";
				player.danno_spada = 2;
				player.fabbro_frase++;
				for(int i=player.fabbro_frase ; player.fabbro_frase < i+3; player.fabbro_frase ++){
					npc_parla(nome_npc, player.fabbro_frase);
				}
				cout<<"numero: "<<player.numero_fabbro/100<<endl;//diamo un altra parte del numero segreto
				player.fabbro_frase--;
			}else if(player.fabbro_frase ==7){
				npc_parla(nome_npc, player.fabbro_frase);
				cout<<"numero: "<<player.numero_fabbro<<endl;
			}else{
				cout<<endl<<"Fabbro: mancano dei materiali a quanto pare per completare la forgiatura"<<endl;
			}
		}
	}
}

void acquista_funzioni(recPlayer &player){
	int quantita=0;//quantita' di pozioni che si vogliono acquistare 
	if(player.monete>=5){
		do{
			system("CLS");
			cout<<"quante pozioni da 5 monete vuoi acquistare?: "<<endl;
			cin>>quantita;
		}while(quantita<0||quantita*5>player.monete);//si chiede fino a quando non chiede 0 oppure un numero di pozioni che ti puoi permettere con le tue monete
		system("CLS");
		if(quantita>0){
			player.monete-=5*quantita;
			player.pozione_curativa=quantita;
			cout<<"hai acquistato "<<quantita<<" pozioni curative"<<" per "<<quantita*5<<" monete"<<endl;
			system("pause");
		}
	}else{
		cout<<"non hai abbastanza monete";
		system("pause");
		system("cls");
		return;
	}
}

void dungeon(nemico &enemy, recPlayer &player){
	int difficolta_dungeon=4;//difficolta' del boss
	if(player.zona!="dungeon_boss"){
		do{//se non e' il dungeon boss scegliere una difficolta' da 1 a 3
			cout<<endl<<"inserisci la difficolta' che vuoi affrontare"<<endl;
			cin>>difficolta_dungeon;
		}while(difficolta_dungeon<1 || difficolta_dungeon>3);
	}
	combattimento(enemy,player,difficolta_dungeon);//funzione del combattimento 
}

void selezione_mostro(int difficolta_dungeon,string zona,nemico &enemy){//funzione che sceglie i paramentri del mostro che affronterai nel dungeon
	// in base alla difficolta' i mostri hanno paramentri diversi
	if(difficolta_dungeon==1){//mostri pi� scarsi
		//in base alla zona si trovano mostri diversi
		if(zona=="miniera"){ 
			enemy.name="blob";
			enemy.vita=7;
			enemy.danno=1;
			enemy.agilita=(rand()%10)+1;
			enemy.fortuna=1+(rand()%10)+1;
			enemy.cure=1;
			enemy.ferro=(rand()%10)+1;
			if(enemy.ferro>=5){
				enemy.ferro=0;
			}
			enemy.oro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
		else if(zona=="villaggio"){
			enemy.name="ladro";
			enemy.vita=7;
			enemy.danno=1;
			enemy.agilita=(rand()%15)+1;
			enemy.fortuna=5+(rand()%5)+1;
			enemy.monete = (rand()%3)+1;
			enemy.cure=2;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
		}
		else if(zona=="arena"){
			enemy.name="boblin";
			enemy.vita=9;
			enemy.danno=2;
			enemy.agilita=(rand()%7)+1;
			enemy.fortuna=5+(rand()%11)+1;
			enemy.cure=1;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
		else{
			cout<<"errore creazione del mostro";
		}
	}else if(difficolta_dungeon==2){//media difficolt�
		
		if(zona=="miniera"){
			enemy.name="minatore infuriato";
			enemy.vita=8;
			enemy.danno=2;
			enemy.agilita=(rand()%15)+1;
			enemy.fortuna=5+(rand()%19)+1;
			enemy.cure=2;
			enemy.oro=(rand()%20)+1;
			if(enemy.oro>2){
				enemy.oro=0;
			}
			enemy.ferro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
		else if(zona=="villaggio"){
			enemy.name="scagnozzo";
			enemy.vita=7;
			enemy.danno=2;
			enemy.agilita=(rand()%30)+1;
			enemy.fortuna=5+(rand()%20)+1;
			enemy.cure=1;
			enemy.monete = 1+(rand()%6)+1;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
		}
		else if(zona=="arena"){
			enemy.name="lizalfos";
			enemy.vita=12;
			enemy.danno=2;
			enemy.agilita=(rand()%20)+1;
			enemy.fortuna=5+(rand()%10)+1;
			enemy.cure=1;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
		else{
			cout<<"errore creazione del mostro";
		}
	}else if(difficolta_dungeon==3){//difficolt� alta
		
		if(zona=="miniera"){
			enemy.name="sassorock";
			enemy.vita=19;
			enemy.danno=3;
			enemy.agilita=(rand()%20)+1;
			enemy.fortuna=5+(rand()%20)+1;
			enemy.cure=1;
			enemy.diamante=(rand()%25)+1;
			if(enemy.diamante>1){
				enemy.diamante=0;
			}
			enemy.ferro=0;
			enemy.oro=0;
			enemy.monete=0;
		}
		else if(zona=="villaggio"){
			enemy.name="boss mafioso";
			enemy.vita=18;
			enemy.danno=3;
			enemy.agilita=(rand()%18)+1;
			enemy.fortuna=5+(rand()%23)+1;
			enemy.monete = 10+(rand()%10);
			enemy.cure=3;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
		}
		else if(zona=="arena"){
			enemy.name="moblin";
			enemy.vita=20;
			enemy.danno=4;
			enemy.agilita=(rand()%10)+1;
			enemy.fortuna=5+(rand()%30)+1;
			enemy.cure=1;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
		else{
			cout<<"errore creazione del mostro";
		}
	}else if(difficolta_dungeon==4){//boss finale
		if(zona=="dungeon_boss"){
			enemy.name="GANON";
			enemy.vita=25;
			enemy.danno=5;
			enemy.agilita=(rand()%30)+1;
			enemy.fortuna=5+(rand()%30)+1;
			enemy.cure=1;
			enemy.ferro=0;
			enemy.oro=0;
			enemy.diamante=0;
			enemy.monete=0;
		}
	}
}
 
void salita_di_livello(recPlayer &player){
	bool flag = false;//se voglio upgrediare una cosa gia' al massimo la flag diventa true e allora richiede un altra cosa da potenziare
	int n_potenziamento = 0;
	if(player.livello<LVLMAX_PLAYER&&player.xp>=100){//controllo che il player non abbia gi� raggiunto il livello manssimo e abbia 100xp per livellare
		
		cout<<"ottimo guerriero hai ottenuto una benedizone ora puoi potenziare una delle tue abilita'"<<endl;
		do{
			
			if(flag==true){//false di base cosi' al primo giro non si vede
				cout<<endl<<"l'abilita' e' gia' stata migliorata al massimo"<<endl;
			}
			flag=false;
			cout<<endl<<"[1] salute "<<player.maxsalute<<"/"<<LVLMAX_SALUTE<<endl<<"[2] forza "<<player.forza<<"/"<<LVLMAX_FORZA<<endl<<"[3] agilita' "<<player.agilita<<"/"<<LVLMAX_AGILITA<<endl<<"[4] fortuna "<<player.fortuna<<"/"<<LVLMAX_FORTUNA<<endl<<"[5] spiritualita' "<<player.spiritualita<<"/"<<LVLMAX_SPIRITUALITA<<endl<<endl;	 //menu level-up
			cout<<"inserisci il numero del potenziamento: ";
			cin>>n_potenziamento;
			while(n_potenziamento<1 || n_potenziamento>5){//in caso di inserimento errato richiede
				cout<<endl<<"numero errato"<<endl;
				cout<<endl<<"[1] salute "<<player.maxsalute<<"/"<<LVLMAX_SALUTE<<endl<<"[2] forza "<<player.forza<<"/"<<LVLMAX_FORZA<<endl<<"[3] agilit� "<<player.agilita<<"/"<<LVLMAX_AGILITA<<endl<<"[4]fortuna "<<player.fortuna<<"/"<<LVLMAX_FORTUNA<<endl<<"[5] spiritualita' "<<player.spiritualita<<"/"<<LVLMAX_SPIRITUALITA<<endl<<endl;	
				//si dice quanto si ha della statistica e quanto e' il massimo 
				cout<<"inserisci il numero del potenziamento: ";
				cin>>n_potenziamento;
			}
			//potenziamento della cosa richiesta
			if(n_potenziamento == 1){//potenziamento della salute
				if(player.maxsalute < LVLMAX_SALUTE ){
					player.salute+=1;
					player.maxsalute+=1;
					cout<<endl<<"salute massima del personaggio aumentata a "<<player.maxsalute<<" punti ferita"<<endl;
				}else{
					flag = true;
				}
			}else if(n_potenziamento == 2){//potenziamento della forza
				if(player.forza < LVLMAX_FORZA ){
					player.forza+=1;
					cout<<endl<<"i danni del personaggio aumentano a "<<player.forza<<" per colpo"<<endl;
				}else{
					flag = true;
				}
			}else if(n_potenziamento == 3){//potenziamento agilit�
				if(player.agilita < LVLMAX_AGILITA ){
					player.agilita+=1;
					cout<<endl<<"l'agilit� del personaggio aumenta a "<<player.agilita<<endl;
				}else{
					flag = true;
				}
			}else if(n_potenziamento == 4){//poteziamento fortuna 
				if(player.fortuna < LVLMAX_FORTUNA ){
					player.fortuna+=1;
					cout<<endl<<"fortuna del personaggio aumenta a "<<player.fortuna<<endl;
				}else{
					flag = true;
				}
			}else if(n_potenziamento == 5){//potenziamento spiritualit�
				if(player.spiritualita < LVLMAX_SPIRITUALITA ){
					player.spiritualita+=1;
					cout<<endl<<"spiritualita' del personaggio aumenta a "<<player.spiritualita<<endl;
				}else{
					flag = true;
				}
				//se l'upgrade e' andato a bun fine la flag rimane false e si esce dalla zona levelup
			}else{
				flag = true;
			}
			
		}while(flag);//se la flag � tru singinifica che c'� stato un errore oppure le abilit� che si voleva poteziare � gi� al massimo
		player.livello+=1;
		player.xp-=100;
	}else if(player.livello==LVLMAX_PLAYER){//se e' tutto al massimo non si fa nessun upgrade
		cout<<"il personaggio ha raggiunto il livello massimo di tutte le abilita'"<<endl;
		system("pause");
	}
	
}
/*
!-!-!-!-!-!-!-!-!-!-!-!-!-!-!
INIZIO SEZIONE COMBATTIMENTO
!-!-!-!-!-!-!-!-!-!-!-!-!-!-!
*/
bool schivata(nemico &enemy, recPlayer &player,int scelta){ //SCELTA SERVE per indicare se � il nemico o il player a eseguire la scivata   [1] player    [2] nemico
	int probabilita=0;
	probabilita = (rand()%100)+1;//randomico
	if (scelta == 1){
		if(player.agilita >=  probabilita){//se l'agilit' e' maggiore della probabitlit' si schiva
			return true;//schivata del player riuscita
		}else{//altrimenti te la prendi
			return false;
		}
	}else{//stessa cosa pero' e' il mostro a schivare
		if(enemy.agilita >=  probabilita){
			return true; //scivata dell'avversario riuscita
		}else{
			return false;
		}
	}
}

void statistiche_combattimento(nemico &enemy, recPlayer &player, int &flag_ripeti){ //stampa semplicemete le statistiche su richiesta
	flag_ripeti=1;//non essendo un azione di combattimento non si spreca la mossa e si puo' rifare
	cout<<endl<<"  **statistiche combattimento**"<<endl;
	cout<<endl<<player.nome<<"\t\t"<<enemy.name;
	cout<<endl<<"salute: "<<player.salute<<"\t"<<"salute: "<<enemy.vita ;
	cout<<endl<<"danno: "<<player.forza + player.danno_spada <<"\t"<<"danno: "<<enemy.danno;
	cout<<endl<<"difesa: "<<player.difesa_armatura<<"\t"<<"difesa: "<<0;
	cout<<endl<<"agilita': "<<player.agilita <<"\t"<<"agilita': "<<enemy.agilita;
	cout<<endl<<"fortuna: "<<player.fortuna<<"\t"<<"fortuna: "<<enemy.fortuna<<endl;
	cout<<endl<<"arma: "<<player.nome_spada;
	cout<<endl<<"armatura "<<player.nome_armatura<<endl<<endl;
}

/*
!!!!!!!!!!!!!!!!!
AZIONI COMPIUTE DAL PLAYER	
!!!!!!!!!!!!!!!!!
*/
int colpo_critico_player(recPlayer &player){//per critttare 
	int probabilita=0;
	probabilita = (rand()%100)+1;
		if(player.fortuna >=  probabilita){//stessa cosa della schivata pero' lo puo' fare solo il player e si usa la fortuna e non l'agilit'
			cout<<endl<<"WOW COLPO CRITICO!!!"<<endl;
			return 2;//retunra 2 perche' il colpo critico e' il valore per il quale viene moltiplicato l'attacco *2
		}else{
			return 1;//*1
		}
}

void attacco_player(nemico &enemy, recPlayer &player){
	int danno=0;
	if(!schivata(enemy, player,2)){//se il nemico non schiva
		danno=(player.forza+player.danno_spada)*colpo_critico_player(player);//vinene calcolato il danno tramite la soma del danno del player e quello della spada e viene moltiplicato per il colpo critico
		enemy.vita=enemy.vita-danno;
		if(enemy.vita>0){//controllo se il menico � ancora in vita a fine attacco
			cout<<endl<<"il tua attacco infligge un danno di "<<danno<<" ora il nemico ha "<<enemy.vita<<"hp"<<endl;
		}else{
			cout<<endl<<"il tua attacco infligge un danno di "<<danno<<" ora il nemico e' ko"<<endl;
		}
	}else{
		cout<<endl<<enemy.name<<" ha scivato il tua attacco "<<endl;//se schiva buon per lui
	}

}

void pozioni_player(recPlayer &player, int &flag_ripeti){//per le pozzioni
	if(player.salute == player.maxsalute ){//se la salute non sia gi� al massimo
		cout<<endl<<"la tua salute e' gia' al massimo"<<endl<<endl;
		flag_ripeti=1;//attiva la flag che fa ripetere il turno del player
	}else if(player.pozione_curativa >0){//se non e' al massimo controllo di avere delle pozioni 
		player.pozione_curativa = player.pozione_curativa -1;//tolgo una pozione dal conteggio
		player.salute +=5;//curo il player di 5hp
		if(player.salute > player.maxsalute){ //se la salute del player � magggiore di quella massima la riadeguo
			player.salute = player.maxsalute ;
		}
		cout<<endl<<"la pozione ha un effetto di cura, ora il tuo personaggio ha "<<player.salute <<"hp"<<endl;// si informa l'utente della salute che si ha 
	}else{//se nono ho pozioni riffaccio il turno
		cout<<endl<<"hai finito le pozioni quindi"<<endl;
		flag_ripeti=1;//riesesguo il turno
	}
}


void fuga_player(recPlayer &player, int &fuga, int difficolta_dungeon){//sacappare dal combattimento da parte del player
	int probabilita=0;
	probabilita = (rand()%100)+1;//calcolo la probalbilit� di fuga 
	cout<<endl<<"hai tentato la fuga e..."<<endl;
		if(player.agilita >=  probabilita&&difficolta_dungeon<4){ //controllo che non sia contro un boss perch� altrimenti non si scappa per la citta' di Z
			//si scappa solo se la agilita' e maggiore della probabilita'
			cout<<endl<<"sei riuscito a scappare con successo"<<endl;
			fuga=1;
		}else{
			cout<<endl<<"i tuoi tentativi di scappare sono falliti"<<endl;
			fuga=0;
		}
}

void turno_player (nemico &enemy, recPlayer &player,int &fuga,int difficolta_dungeon){
	if(fuga !=1 &&enemy.vita >0 && player.salute >0){//controllo che ci siano tutti i requisiti per giocare un turno
		int scelta_azione=0;
		int flag_ripeti=0;
		cout<<"e' il tuo turno "<<endl;
		do{
			flag_ripeti=0;
			cout<<"scegli l'azione da compiere:"<<endl;
	
			do{
				cout<<"[1] attacca"<<endl<<"[2] usa pozione"<<endl<<"[3] fuggi"<<endl<<"[4] analizza combattimento"<<endl;//si sceglie che cosa fare
				cin>>scelta_azione;
			}while(scelta_azione <1 || scelta_azione>4);
			system("CLS");
			cout<<"Il TUO turno"<<endl;
			switch (scelta_azione){//qui si scelgono le varie azioni da fare
				case 1:
					attacco_player(enemy,player);
					break;
				case 2:
					pozioni_player(player, flag_ripeti);//gli si passa il flag ripeti
					break;
				case 3:
					fuga_player(player, fuga,difficolta_dungeon);
					break;
				case 4:
					statistiche_combattimento(enemy, player, flag_ripeti);//gli si passa il flag ripeti
					break;
				default:
					cout<<endl<<"errore"<<endl;
					
			}
		}while(flag_ripeti==1);//si fa fino a quando non si fa una cosa inutile
	}
}

/*
!!!!!!!!!
Azioni intraprese dal nemico
!!!!!!!!!!
*/
int colpo_critico_nemico(nemico &enemy){//stessa cosa ma la fa il nemico
	int probabilita=0;
	probabilita = (rand()%100)+1;
		if(enemy.fortuna >=  probabilita){
			cout<<endl<<"WOW COLPO CRITICO DEL NEMICO!!"<<endl;
			return 2;
		}else{
			return 1;
		}
}

void attacco_nemico(nemico &enemy, recPlayer &player){//stessa cosa ma la fa il nemico
	int danno=0;
	if(!schivata(enemy, player,1)){
		danno=enemy.danno*colpo_critico_nemico(enemy);
		danno-=player.difesa_armatura;
		if(danno<=0){
			danno=1;
		}
		player.salute -=danno;
		if(player.salute>0){
			cout<<endl<<"il nemico infligge un danno di "<<danno<<" ora hai "<<player.salute<<"hp"<<endl;
		}else{
			cout<<endl<<"il nemico infligge un danno di "<<danno<<" ora sei KO"<<endl;
		}
	}else{
		cout<<endl<<"WOW hai schivato l'attacco del nemico "<<endl;
	}
}

void cura_nemico(nemico &enemy, recPlayer &player){//si puo' over curare 
	if(enemy.cure >0){
		enemy.cure -=1;
		enemy.vita +=5;
		cout<<endl<<"il nemico usa una pozione arcana e recupera 5hp. Ora la sua vita e' di "<<enemy.vita<<endl;
	}else{
		attacco_nemico(enemy , player);
	}
}

void turno_nemico(nemico &enemy, recPlayer &player, int difficolta_dungeon,int fuga){
	if(fuga !=1 &&enemy.vita >0 && player.salute >0){//se il personaggio e il nemico sono vivi e non e' scappato 
		int scelta=(rand()%10)+1;
		cout<<endl<<"Il turno del NEMICO"<<endl;
		if(scelta ==1){
			cura_nemico(enemy, player);
		}else{
			attacco_nemico(enemy, player);
		}
	}
}

void ricompense_vittoria(nemico &enemy, recPlayer &player, int difficolta_dungeon){
		int xp=0;
		xp=((rand()%30)+1)*difficolta_dungeon;//numero random da 1 a 30 moltiplicato per la difficolta' dungeon
		if(player.zona=="arena"){//DLC che svilupperemo
			xp*=2;
		}
		player.xp += xp;
		cout<<endl<<"ottieni "<<xp<<" xp. Ora hai "<<player.xp<<"xp "<<endl;// ti fa vedere quanto xp hai e quanto ne hai ottenuto 
		//si prendono le risorse che aveva il nemico 
		if(enemy.ferro >0){
			player.ferro += enemy.ferro;
			cout<<endl<<"hai ottenuto "<<enemy.ferro<<" ferro"<<endl;
		}
		if(enemy.oro >0){
			player.oro += enemy.oro; 
			cout<<endl<<"hai ottenuto "<<enemy.oro<<" oro"<<endl;
		}
		if(enemy.diamante >0){
			player.diamante += enemy.diamante; 
			cout<<endl<<"hai ottenuto "<<enemy.diamante<<" diamante"<<endl;
		}
		if(enemy.monete >0){
			player.monete += enemy.monete; 
			cout<<endl<<"hai ottenuto "<<enemy.monete<<" monete"<<endl;
		}
		if(difficolta_dungeon==4){
			cout<<endl<<"HAI SALVATO LA CITTA' DI Z DALLA CALAMITA', BRAVO"<<endl;
			player.gioco_finito=true;
			system("pause");
			system("CLS");
		}
}

void combattimento(nemico &enemy, recPlayer &player, int difficolta_dungeon){
	selezione_mostro(difficolta_dungeon,player.zona,enemy);//scelta del mostro che e' sopra
	int fuga=0;
	//si printano le statistiche del mostro
	cout<<endl<<"e' apparso un mostro"<<endl
	<<"statistiche"<<endl
	<<"\tnome: "<<enemy.name<<endl
	<<"\tvita: "<<enemy.vita<<endl
	<<"\tdanno: "<<enemy.danno<<endl
	<<"\tagilita': "<<enemy.agilita<<endl
	<<"\tfortuna: "<<enemy.fortuna<<endl;
	
	if(player.agilita > enemy.agilita){//il turno lo inizia chi ha l'agilita' piu' alta
		while(!(fuga ==1 || enemy.vita <=0 || player.salute <=0)){//servono a vedere se le persono non sono morte e se non sei fuggito 
			turno_player(enemy, player, fuga, difficolta_dungeon);
			turno_nemico(enemy, player, difficolta_dungeon, fuga);
		}
	}else{
		while(!(fuga ==1 || enemy.vita <=0 || player.salute <=0)){
			turno_nemico(enemy, player, difficolta_dungeon, fuga);
			turno_player(enemy, player, fuga, difficolta_dungeon);
		}	
	}
	if(!(fuga==1||player.salute<=0)){//vittoria player
		ricompense_vittoria(enemy,player, difficolta_dungeon);
	}else if(player.salute<=0){//sconfitta player
		cout<<endl<<"!!!HAI PERSO!!!"<<endl;
		player.salute = player.maxsalute;
		if(player.monete > 0){
			player.monete -= 1;
		}
	}
	system("pause");
	salita_di_livello(player);
	
}

//OLD MAIN
//int main(){
//	nemico enemy;
//	recPlayer player;
//	srand(time(NULL));
//	player.numero_segreto=(rand()%899)+100;
//	player.numero_vescovo=player.numero_segreto %10;// numero prima posizione
//	player.numero_minatore=((player.numero_segreto - player.numero_vescovo)%100);//numero seconda posizione
//	player.numero_fabbro=(player.numero_segreto - (player.numero_minatore+player.numero_vescovo ));//numero terzo posizione
//	cout<<"start game"<<endl;
//	
//	menu_scelte(enemy, player);
//	
//	return 0;
//}

void istanziamentoPartita(RecPlayer* personaggio){
	// TODO: creazione e navigazione delle zone

}

//NEW MAIN
int main(){
	srand(time(NULL)); // non so se sia la giusta posizione
	// TODO: carica config
	//79 chars
    cout << "  _____                                        __              ___   ________   " << endl;
	cout << " |_   _|                                      |  ]           .' ..] |  __   _|  " << endl;
	cout << "   | |      .---.  .--./) .---.  _ .--.   .--.| |    .--.   _| |_   |_/  / /    " << endl;
	cout << "   | |   _ / /__\\\\/ /'`\\\\/ /__\\\\[ `.-. |/ /'`\\' |  / .'`\\ \\'-| |-'     .'.' _   " << endl;
	cout << "  _| |__/ || \\__.,\\ \\._//| \\__., | | | || \\__/  |  | \\__. |  | |     _/ /__/ |  " << endl;
	cout << " |________| '.__.'.',__`  '.__.'[___||__]'.__.;__]  '.__.'  [___]   |________|  " << endl;
	cout << "                 ( ( __))                                                       " << endl;
	cout << endl << endl;
	cout << "┌────────────────────────────────────────────────────────────────────────────────┐"<<endl;
	cout << "│                                                                                │"<<endl;
	cout << "│  1 - Nuova partita                                                             │"<<endl;
	cout << "│  2 - Carica partita                                                            │"<<endl;
	//cout << "│  3 - Impostazioni                                                              │"<<endl;
	cout << "│  4 - Esci                                                                      │"<<endl;
	cout << "│                                                                                │"<<endl;
	cout << "└────────────────────────────────────────────────────────────────────────────────┘"<<endl;

	unsigned short scelta = 0;
	string nomeProtagonista = "";
	RecPlayer* protagonista;

	while (scelta < 1 || scelta > 4){
		cout << "Seleziona: ";
		
		///TODO: sanificare scelta
		cin >> scelta;
		
		switch(scelta){
			case 1:
				// Nuova partita
				system("CLS");
				cout << "Inserisci nome protagonista: ";
				cin >> nomeProtagonista;
				protagonista = new RecPlayer(nomeProtagonista);
				istanziamentoPartita(protagonista);
				break;
			case 2:
				// Carica partita
				system("CLS");
				if (caricamentoJSON()){
					/// TODO: creare protagonista basato sui dati di DATA_CARICAMENTO
					//protagonista = new RecPlayer();
				} else {
					return 0;
				}
				break;
			case 3:
				//impostazioni
				info("Non esiste come opzione!");
				info("Perche non ascolti? Ora son offeso.");
				return 0;
				break;
			case 4:
				return 0;
			default:
				return 0;
		}
	}
}
