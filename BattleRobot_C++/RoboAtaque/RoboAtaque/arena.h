#pragma once
#include <string>
#include<iostream>
#include "robo.h"
using namespace std;
class arena
{
public:
	arena(void);
	~arena(void);
	void imprime_arena(robo player,robo enemy);
	void imprime_interface(robo player,robo enemy,int Nrod);
	void imprime_Dados(robo player,robo enemy,int Nrod);
};

