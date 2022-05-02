#ifndef MONSTER_H
#define MONSTER_H

#include "headers.h"

class Monster
{
	private:
		int level, hp, strength, defense;
		unsigned int exp, x, y, ID;

	public:
		Monster(int);
		~Monster();
		void update();
		void show();
		
		int calculatePhysicalDmg(int);
		int calculateMagicDmg(int);
		int calculateAttack(int);
		int getHP();
		int getEXP();
		
		unsigned int getX();
		unsigned int getY();
};

#endif
