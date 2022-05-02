#pragma once
#include <string>
#include <iostream>
using namespace std;
class armadura
{
public:
	armadura(void);
	~armadura(void);
	void setNomeArmadura(string arm);
	string getNomeArmadura();
	void setBonus_defesa(int extra);
	int getBonus_defesa();
protected:
	string NomeArmadura;
	int Bonus_defesa;
};

