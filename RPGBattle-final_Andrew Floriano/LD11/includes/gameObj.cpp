#include "gameObj.hpp"

Game::Game()
{
	cursor=300;

	hero=new Character();
	monster=new Monster(1);
	x=monster->getX();
	y=monster->getY();

	intro = load_image("resources\\images\\logo.png");
	apply_surface(120, 90, intro, screen);
	introOn=true;
	cursorSurface=show_text("?");
}

Game::~Game()
{
	delete hero;
	delete monster;
	SDL_FreeSurface(cursorSurface);
}

Game * Game::Instance()
{
	static Game inst;
	return &inst;
}

void Game::handle_events(bool & quit)
{
	//do stuff
	if(event.type == SDL_QUIT)
    {
        quit=true;
    } else if(event.type == SDL_KEYDOWN)
    {
		if(introOn)
		{
			if((event.key.keysym.sym!=SDLK_RSHIFT) && (event.key.keysym.sym!=SDLK_LSHIFT))
			{
				introOn=false;
			}
		} else {
			action=attack;
		}
        switch(event.key.keysym.sym)
 		{
			case SDLK_q:
				if(SDL_GetModState()&KMOD_SHIFT)
				{
					quit=true;
				}
				break;
			case SDLK_ESCAPE:
				quit=true;
				break;
			case SDLK_LEFT:
				cursor-=40;
				action=nothing;
				break;
			case SDLK_RIGHT:
				cursor+=40;
				action=nothing;
				break;
			case SDLK_UP:
				hero->changePower(1);
				action=nothing;
				break;
			case SDLK_DOWN:
				hero->changePower(-1);
				action=nothing;
				break;
			case SDLK_s:
				if(SDL_GetModState()&KMOD_SHIFT)
				{
					hero->save();
					action=nothing;
				}
				break;
			case SDLK_l:
				if(SDL_GetModState()&KMOD_SHIFT)
				{
					hero->load();
					action=nothing;
				}
				break;
			case SDLK_RSHIFT: SDLK_LSHIFT:
				action=nothing;
				break;
			case SDLK_1:
				cursor=300;
				action=nothing;
				break;
			case SDLK_2:
				cursor=340;
				action=nothing;
				break;
			case SDLK_3:
				cursor=380;
				action=nothing;
				break;
			case SDLK_4:
				cursor=420;
				action=nothing;
				break;
		}
	}
}

bool Game::logic(bool & lose)
{
	if(cursor<300)
	{
		cursor=420;
	} else if(cursor>420)
	{
		cursor=300;
	}
	if(action!=nothing)
	{
		x=monster->getX();
		y=monster->getY();
		switch(cursor)
		{
			case 300:
				action=attack;
				break;
			case 340:
				action=atkMagic;
				break;
			case 380:
				action=heal;
				break;
			case 420:
				action=potion;
				break;
			default:
				action=nothing;
				break;
		}
		hero->update(action, monster);
		if(monster->getHP()<=0)
		{
			hero->win(monster);
			delete monster;
			monster=new Monster(hero->getLevel());
		}
		if(hero->getHP()<=0)
		{
			delete monster;
			delete hero;
			lose=true;
			return true;
		}
	}
	
	action=nothing;
	return true;
}

void Game::show()
{
	if(!introOn)
	{
		if(intro!=NULL)
		{
			SDL_FreeSurface(intro);
		}
		apply_surface(0, 0, gui, text);
		apply_surface(cursor, 50, cursorSurface, text);
		apply_surface(0, 0, background, camera);

		hero->show(x, y);
		monster->show();
		apply_surface(0, 0, camera, screen);
		apply_surface(0, 350, text, screen);
	} else {
		apply_surface(120, 90, intro, screen);
	}
}

void Game::reset()
{
	cursor=300;

	hero=new Character();
	monster=new Monster(1);
	x=monster->getX();
	y=monster->getY();

	intro = load_image("resources\\images\\logo.png");
	apply_surface(120, 90, intro, screen);
	introOn=true;
}
