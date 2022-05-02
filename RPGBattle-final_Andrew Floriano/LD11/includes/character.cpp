#include "character.hpp"
#include <fstream>

Character::Character()
{
	//set up values
	level=1;
	hp=20;
	mp=5;
	strength=10;
	defense=10;
	exp=0;
	expToNext=10;
	magicPower=1;
	maxHP=hp;
	maxMP=mp;
	potions=5;
	showValue=0;
	surDmgToHero = NULL;
	surDmgToMonster = NULL;
}

Character::~Character()
{
	//delete values
	SDL_FreeSurface(surDmgToHero);
    SDL_FreeSurface(surDmgToMonster);
}

void Character::update(actions action, Monster * monster)
{
	int dmgToMonster=0;
	int dmgToHero=0;
	int healed=0;
	//update
	dmgToHero=monster->calculateAttack(defense);
	switch(action)
	{
		case attack:
			dmgToMonster=monster->calculatePhysicalDmg(strength);
			if((rand()%100)<=50)
			{
				Mix_PlayChannel(-1, SE[0], 0);
			} else {
				Mix_PlayChannel(-1, SE[1], 0);
			}
			break;
		case atkMagic:
			if((mp<=0) || ((mp-magicPower)<0))
			{
				return;
			} else {
				dmgToMonster=monster->calculateMagicDmg(magicPower);
				Mix_PlayChannel(-1, SE[3], 0);
				mp-=magicPower;
			}
			break;
		case heal:
			if((mp<=0) || ((mp-magicPower)<0))
			{
				return;
			} else {
				//magic heal formula
				healed=magicPower+(level*2)+rand()%10;
				Mix_PlayChannel(-1, SE[2], 0);
				if((hp+healed)>maxHP)
				{
					healed=maxHP-hp;
				}
				dmgToHero=-healed;
				mp-=magicPower;
			}
			break;
		case potion:
			if(potions==0)
			{
				return;
			} else {
				mp=maxMP;
				potions--;
				Mix_PlayChannel(-1, SE[2], 0);
			}
	}
	char buffer[8];
	showValue=1;
	hp=hp-dmgToHero;
	
	if(dmgToMonster>0)
	{
		sprintf(buffer, "%d", -dmgToMonster);
		surDmgToMonster=show_text(buffer);
	} else {
		SDL_FreeSurface(surDmgToMonster);
	}
	
	sprintf(buffer, "%d", -dmgToHero);
	surDmgToHero=show_text(buffer);
}

void Character::show(unsigned int x, unsigned int y)
{
	//show
	char stats[20];

	sprintf(stats, "%2d/%-5d%d/%d",hp, maxHP, mp, maxMP);
	textSurface=show_text(stats);
	apply_surface(60, 10, textSurface, text);
	SDL_FreeSurface(textSurface);
	
	sprintf(stats, "%-6d%d",strength, defense);
	textSurface=show_text(stats);
	apply_surface(60, 50, textSurface, text);
	SDL_FreeSurface(textSurface);
	
	sprintf(stats, "%d %d", magicPower, magicPower);
	textSurface=show_text(stats);
	apply_surface(340, 90, textSurface, text);
	SDL_FreeSurface(textSurface);
	
	sprintf(stats, "%d/%d", exp, expToNext);
	textSurface=show_text(stats);
	apply_surface(120, 90, textSurface, text);
	SDL_FreeSurface(textSurface);
	
	sprintf(stats, "%d", potions);
	textSurface=show_text(stats);
	apply_surface(460, 50, textSurface, text);
	SDL_FreeSurface(textSurface);
	
	if(showValue>0)
	{
		apply_surface(40, (320-showValue), surDmgToHero, camera);
		if(surDmgToMonster!=NULL)
		{
			apply_surface(x+50, (y-showValue-20), surDmgToMonster, camera);
		}
		showValue++;
		if(showValue>20)
		{
			showValue=0;
			SDL_FreeSurface(surDmgToHero);
		}
	}
}

bool Character::changePower(int change)
{
	if(((change+magicPower)<1) || ((change+magicPower)>level) || ((change+magicPower)>9))
	{
		return false;
	}
	magicPower+=change;
	return true;
}

void Character::win(Monster * monster)
{
	//you won!
	exp+=monster->getEXP();
	Mix_PlayChannel(-1, SE[4], 0);
	Mix_PlayChannel(-1, SE[5], 0);
	if(exp>=expToNext)
	{
		levelUp();
	}
	if(rand()%100<10)
	{
		potions++;
	}
}

int Character::getLevel()
{
	return level;
}

int Character::getHP()
{
	return hp;
}

void Character::levelUp()
{
	level++;
	int hpUp=level+rand()%10;
	int mpUp=level+rand()%5;
	hp+=hpUp;
	mp+=mpUp;
	strength+=level+(level-1);
	defense+=level+(level-1);
	expToNext+=level^2+20*level;
	maxHP+=hpUp;
	maxMP+=mpUp;
}

void Character::save()
{
	ofstream file;
	file.open("character.sav");
	file<<level<<" "<<hp<<" "<<mp<<" "<<strength<<" "<<defense<<endl;
	file<<exp<<" "<<expToNext<<" "<<maxHP<<" "<<maxMP<<" "<<potions;
	file.close();
}
	
void Character::load()
{
	ifstream file;
	file.open("character.sav");
	file>>level>>hp>>mp>>strength>>defense;
	file>>exp>>expToNext>>maxHP>>maxMP>>potions;
	file.close();
}
