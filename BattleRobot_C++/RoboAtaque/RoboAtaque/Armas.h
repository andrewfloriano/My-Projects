#pragma once
#include <string>
#include <iostream>
using namespace std;
class Arma
{
public:
	Arma(void);
	~Arma(void);
	void setNomeArma(string n);
	string getNomeArma();
	void setBonus_ataque(int extra);
	int getBonus_ataque();
	void setAlcance(int al);
	int getAlcance();
	void setNro_disparo(int disp);
	int getNro_disparo();
protected:
	string nomeArma;
	int bonus_ataque;
	int alcance;
	int nro_disparo;
};

