#include "inventario.h"


inventario::inventario(void)
{
}


inventario::~inventario(void)
{
}

void inventario::setInventArma(Arma ar)
{
	inventArma=ar;
}

Arma inventario::getInventArma()
{
	return inventArma;
}

void inventario::setInventArmadura(armadura arm)
{
	inventArmadura=arm;
}

armadura inventario::getInventArmadura()
{
	return inventArmadura;
}

void inventario::setInventRodas_pernas(rodas_pernas rp)
{
	inventRodas_pernas=rp;
}

rodas_pernas inventario::getInventRodas_pernas()
{
	return inventRodas_pernas;
}

void inventario::setTipoItem(int item)
{
	tipoItem=item;
}

int inventario::gettipoItem()
{
	return tipoItem;
}