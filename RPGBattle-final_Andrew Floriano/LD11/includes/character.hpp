#ifndef CHARACTER_H
#define CHARACTER_H

#include "headers.h"
#include "monster.hpp"

class Character
{
	private:
		int level, hp, mp, strength, defense;
		unsigned int magicPower, exp, expToNext, maxHP, maxMP, potions, showValue;

		void levelUp();
		
		SDL_Surface *surDmgToHero;
		SDL_Surface *surDmgToMonster;
	public:
		Character();
		~Character();
		void update(actions, Monster *);
		void show(unsigned int, unsigned int);
		
		bool changePower(int);
		void win(Monster *);
		int getLevel();
		int getHP();
		
		void save();
		void load();
};

#endif
