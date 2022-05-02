#include "monster.hpp"

Monster::Monster(int levelIn)
{
	//set up values
	level=levelIn;
	hp=4*level+(5+rand()%10)*level;
	strength=7+level^2;
	defense=9+level^2;
	exp=rand()%10*level;
	x=10+rand()%450;
	y=130+rand()%70;
	if(rand()%100<50)
	{
		ID=0;
	} else {
		ID=1;
	}
}

Monster::~Monster()
{
	//delete values
}

void Monster::update()
{
	//update
}

void Monster::show()
{
	apply_surface(x, y, sprites[ID], camera);
}

int Monster::calculatePhysicalDmg(int heroAttack)
{
	int dmg=0;
	dmg=(heroAttack*2-defense)-rand()%10;
	if(dmg<=0)
	{
		dmg=1;
	}
	if(dmg>hp)
	{
		dmg=hp;
	}
	hp-=dmg;
	//calulate damage
	return dmg;
}

int Monster::calculateMagicDmg(int magicPower)
{
	//magic attack power
	int dmg=0;
	dmg=magicPower*10+rand()%10;
	if(dmg<=0)
	{
		dmg=1;
	}
	hp-=dmg;
	return dmg;
}

int Monster::calculateAttack(int heroDefense)
{
	int dmg=0;
	dmg=(strength*2-heroDefense)-rand()%10;
	if(dmg<=0)
	{
		dmg=1;
	}
	//calulate damage
	return dmg;
}

int Monster::getHP()
{
	return hp;
}

int Monster::getEXP()
{
	return exp;
}

unsigned int Monster::getX()
{
	return x;
}

unsigned int Monster::getY()
{
	return y;
}
