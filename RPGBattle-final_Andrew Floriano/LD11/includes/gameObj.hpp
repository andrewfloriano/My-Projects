#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "character.hpp"
#include "monster.hpp"

//singleton
class Game
{
	private:
		int cursor;
		bool introOn;
		Character * hero;
		Monster * monster;
		actions action;
		
		SDL_Surface * intro, *cursorSurface;
		
		unsigned int x, y;
	protected:
		Game();
		Game(const Game&);
		Game& operator=(const Game&);
	public:
		~Game();
		static Game * Instance();
		
		void handle_events(bool &);
		bool logic(bool &);
		void show();
		
		void reset();
};

#endif
