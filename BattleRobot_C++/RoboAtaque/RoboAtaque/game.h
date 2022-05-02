#pragma once
#include <iomanip>
#include "robo.h"
#include "arena.h"
#include <locale.h>
using namespace std;
class game
{
public:
	game(void);
	void creditos();
	void sorteia_robo();
	void carrega_armas(int i,ifstream *arq);
	void carrega_armaduras(int i,ifstream *arq);
	void carrega_robo(int i,ifstream *arq);
	void carrega_rodaPerna(int i,ifstream *arq);
	int combate(bool lg);
	void inicializarBatalha();
	void jogada(robo *A,robo *B);
	void NovoJogo();
	void saveGame(int slot);
	bool loadGame(int slot);
	bool inicializaJogodor();
	void partida(bool lg);
	bool fimDeJogo;
	int topoInventario;
	int contpartidas;
	void buscaItensDoInventario();
	void mostraArmas(Arma ar,int indice);
	void mostraArmadura(armadura arm,int indice);
	void mostraRodasPernas(rodas_pernas rp,int indice);
	~game(void);
protected:
	robo carregar[21];
	Arma armas[10];
	armadura armaduras[10];
	inventario invetarioJogador[10];
	rodas_pernas rodasPernas[10];
	robo selecao[9];
	robo jogador;
	robo inimigo;
	int rod;
	
};

