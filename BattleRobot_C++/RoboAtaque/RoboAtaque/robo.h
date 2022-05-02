#pragma once
#include <fstream>
#include"Armas.h"
#include "armadura.h"
#include <iostream>
#include <string>
#include <time.h>
#include"rodas_pernas.h"
#include "inventario.h"
using namespace std;
class robo
{
public:
	robo(void);
	~robo(void);
	void setNome(string n);
	string getNome();
	void setArmaRobo(Arma ar);
	Arma getArmaRobo();
	void setArmaduraRobo(armadura arm);
	armadura getArmaduraRobo();
	void setRodaPernaRobo(rodas_pernas rp);
	rodas_pernas getRodaPernaRobo();
	void setHP(int hp);
	int getHP();
	void setDAM(int dam);
	int getDAM();
	void setPA(int pa);
	int getPA();
	void setDEF(int def);
	int getDEF();
	void setPosMapLin(int posLin);
	int getPosMapLin();
	void setPosMapCol(int posCol);
	int getPosMapCol();
	void inicializaRobo();
	char simbolo;
protected:
	string nome;
	Arma armaRobo;
	armadura armaduraRobo;
	rodas_pernas rodaPernasRobo;
	int HP;
	int DAM;
	int PA;
	int DEF;
	int posMapLin;
	int posMapcol;
};

