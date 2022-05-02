#pragma once
#include <string>
#include <iostream>
using namespace std;
class rodas_pernas
{
public:
	rodas_pernas(void);
	~rodas_pernas(void);
	void setNomeRodas_pernas(string rp);
	string getNomeRoda_pernas();
	void setNro_quadros(int nq);
	int getNro_quadros();
protected:
	string NomeRodas_pernas;
	int nro_quadros;
};

