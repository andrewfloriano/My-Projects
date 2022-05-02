#include "rodas_pernas.h"


rodas_pernas::rodas_pernas(void)
{
}


rodas_pernas::~rodas_pernas(void)
{
}

void rodas_pernas::setNomeRodas_pernas(string rp)
{
	NomeRodas_pernas=rp;
}

string rodas_pernas::getNomeRoda_pernas()
{
	return NomeRodas_pernas;
}

void rodas_pernas::setNro_quadros(int nq)
{
	nro_quadros=nq;
}

int rodas_pernas::getNro_quadros()
{
	return nro_quadros;
}