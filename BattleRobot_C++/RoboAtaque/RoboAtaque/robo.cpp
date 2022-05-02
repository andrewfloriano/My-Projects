#include "robo.h"


robo::robo(void)
{
	inicializaRobo();
}

robo::~robo(void)
{

}

void robo::setNome(string n)
{
	nome=n;
	
}

string robo::getNome()
{
	return nome;
}

void robo::setArmaRobo(Arma ar)
{
	armaRobo=ar;
}

Arma robo::getArmaRobo()
{
	return armaRobo;
}

void robo::setArmaduraRobo(armadura arm)
{
	armaduraRobo=arm;
}

armadura robo::getArmaduraRobo()
{
	return armaduraRobo;
}

void robo::setRodaPernaRobo(rodas_pernas rp)
{
	rodaPernasRobo=rp;
}

rodas_pernas robo::getRodaPernaRobo()
{
	return rodaPernasRobo;
}


void robo::setHP(int hp)
{
	if(hp<0)
	{
		HP=0;
	}
	else
	{
		HP=hp;
	}
}

int robo::getHP()
{
	return HP;
}

void robo::setDAM(int dam)
{
	DAM=dam;
}

int robo::getDAM()
{
	return DAM;
}

void robo::setPA(int pa)
{
	PA=pa;
}

int robo::getPA()
{
	return PA;
}

void robo::setDEF(int def)
{
	DEF=def;
}

int robo::getDEF()
{
	return DEF;
}

void robo::setPosMapCol(int posCol)
{
	posMapcol=posCol;
}

int robo::getPosMapCol()
{
	return posMapcol;
}

void robo::setPosMapLin(int posLin)
{
	posMapLin=posLin;
}

int robo::getPosMapLin()
{
	return posMapLin;
}

void robo::inicializaRobo()
{
	setPA(1);
	setDAM(1);
	setDEF(1);	
	setHP(30);
	setPosMapCol(0);
	setPosMapLin(0);
}