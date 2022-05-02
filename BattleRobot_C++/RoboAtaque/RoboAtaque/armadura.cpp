#include "armadura.h"


armadura::armadura(void)
{
}


armadura::~armadura(void)
{
}

void armadura::setNomeArmadura(string arm)
{
	NomeArmadura=arm;
}

string armadura::getNomeArmadura()
{
	return NomeArmadura;
}

void armadura::setBonus_defesa(int extra)
{
	Bonus_defesa=extra;
}

int armadura::getBonus_defesa()
{
	return Bonus_defesa;
}