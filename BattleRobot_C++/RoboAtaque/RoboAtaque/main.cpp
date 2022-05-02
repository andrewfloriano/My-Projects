#include <iostream>
#include "game.h"
using namespace std;

int main()
{
	setlocale(LC_ALL,"portuguese");
	game inf;
	int op=0;

	ifstream *arq = new ifstream;
	arq->open("Armadura.txt");//abre arquivo das armadura
	inf.carrega_armaduras(-1,arq);
	arq->close();

	arq->open("Armas.txt");//abre arquivo das armas
	inf.carrega_armas(-1,arq);
	arq->close();

	arq->open("RodasPernas.txt");//abre arquivo das rodas
	inf.carrega_rodaPerna(-1,arq);
	arq->close();

	
	int load;
	do
	{
	system("cls");
	cout<<"[1]NOVOJOGO\n[2]CARREGAR JOGO\n[3]RANKING\n[4]CREDITOS\n[5]SAIR\n";
	cin >> op;
		switch(op)
		{
		case 1:
			arq->open("Robo.txt");//abre arquivo com nome dos robos
			inf.carrega_robo(-1,arq);
			arq->close();
			inf.sorteia_robo();
			inf.NovoJogo();
			system("pause");
				break;
		case 2:
			do
			{
			cout<<"QUAL SLOT DESEJA CARREGAR (1),(2) OU (3)"<<endl;
				cin>>load;
			}while(load<1||load>3);
			if(inf.loadGame(load)==true)
			{
			inf.partida(true);system("pause");
			}
				break;
		case 3:inf.inicializaJogodor();system("pause");break;
		case 4:inf.creditos();break;
		case 5:/*SAIR*/break;
		default:cout<<"OPCAO INVALIDA"<<endl;system("pause");
		}
	}while(op !=5);
	return 0;
}