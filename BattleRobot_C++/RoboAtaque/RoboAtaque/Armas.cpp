#include "Armas.h"


Arma::Arma(void)
{
}


Arma::~Arma(void)
{
}

void Arma::setNomeArma(string n)
{
	nomeArma=n;
	
}

string Arma::getNomeArma()
{
	return nomeArma;
}

void Arma::setBonus_ataque(int extra)
{
	bonus_ataque=extra;
}

int Arma::getBonus_ataque()
{
	return bonus_ataque;
}

void Arma::setAlcance(int al)
{
	alcance=al;
}

int Arma::getAlcance()
{
	return alcance;
}

void Arma::setNro_disparo(int disp)
{
	nro_disparo=disp;
}

int Arma::getNro_disparo()
{
	return nro_disparo;
}

