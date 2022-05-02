#pragma once
#include"armadura.h"
#include"Armas.h"
#include"rodas_pernas.h"
#include "robo.h"
class inventario //: armadura,Arma,rodas_pernas
{
public:
	inventario(void);
	~inventario(void);
	void setInventArma(Arma ar);
	Arma getInventArma();
	void setInventArmadura(armadura arm);
	armadura getInventArmadura();
	void setInventRodas_pernas(rodas_pernas rp);
	rodas_pernas getInventRodas_pernas();
	void setTipoItem(int item);
	int gettipoItem();
protected:
	int tipoItem;//0 = arma, 1=armadura, 2=rodas/pernas
	Arma inventArma;
	armadura inventArmadura;
	rodas_pernas inventRodas_pernas;

};

