#include "game.h"

game::game(void)
{
	topoInventario=0;
}

void game::sorteia_robo()
{
	int sorteio;
	int i=0;
	bool existe;
	int sort;
	srand(time(NULL));
	do
	{
		sorteio=rand()%20;
		existe=false;
		for(int n=0;n<i;n++)//teste para não sortear o mesmo robo
		{
			if(carregar[sorteio].getNome()==selecao[n].getNome())
			{
				existe=true;
				n=i;
			}
			
		}
		if(existe==false)
		{
		selecao[i]=carregar[sorteio];//selecao recebe carregar na posicao de sorteio
		selecao[i].simbolo='#';
			if(i<3)
			{
				selecao[i].setArmaRobo(armas[rand()%3]);//0 à 2
				selecao[i].setArmaduraRobo(armaduras[rand()%3]);//0 à 2
				selecao[i].setRodaPernaRobo(rodasPernas[rand()%2]);//0 e 1
			}
			else if(i>=3&&i<=5)
			{
				
				selecao[i].setArmaRobo(armas[rand()%3+3]);//3 à 5
				selecao[i].setArmaduraRobo(armaduras[rand()%3+3]);//3 à 5
				selecao[i].setRodaPernaRobo(rodasPernas[rand()%2+1]);//1 e 2
			}
			else
			{
				selecao[i].setArmaRobo(armas[rand()%3+6]);//6 à 8
				selecao[i].setArmaduraRobo(armaduras[rand()%3+6]);//6 à 8
				selecao[i].setRodaPernaRobo(rodasPernas[rand()%2+3]);//3 e 4
			}
			
		//------------------------------------------------------------------
		i++;
		}
	}while(i<8);
	selecao[8]=carregar[20];
	selecao[8].setArmaRobo(armas[9]);
		selecao[8].setArmaduraRobo(armaduras[9]);
		selecao[8].setRodaPernaRobo(rodasPernas[4]);
		//-------------------------------------------------------
}

int game::combate(bool lg)
{
	arena inf_jogador;
	system("cls");
	srand(time(NULL));
	int ganhaItem;
	string mostraItemGanho;
	char turno='a';// a = vez do jogador / b = vez do inimigo
	if(lg==false)
	{
	inicializarBatalha();
	}
	do               
	{
		inf_jogador.imprime_interface(jogador,inimigo,rod);
		if(turno=='a')
		{
			jogada(&jogador,&inimigo);//rodada do jogador 
			turno='b';
		}
		else
		{
			jogada(&inimigo,&jogador);//jogada do inimigo
			turno='a';
		}
		if(fimDeJogo==true)
		{
			return 0;
		}
	}while(jogador.getHP()>0&&inimigo.getHP()>0);
	if(jogador.getHP()<=0)
	{
		cout<<"GAME OVER";
	return 0;
	}
	else
	{
		if(topoInventario>9)
		{
			topoInventario=0;
		}
		ganhaItem=rand()%3;
		switch(ganhaItem)
		{
		case 0://inventario recebe arma
			invetarioJogador[topoInventario].setInventArma(inimigo.getArmaRobo());
			invetarioJogador[topoInventario].setTipoItem(0);
			mostraItemGanho="ARMA: " + invetarioJogador[topoInventario].getInventArma().getNomeArma();
			break;
		case 1://inventario recebe armadura
			invetarioJogador[topoInventario].setInventArmadura(inimigo.getArmaduraRobo());
			invetarioJogador[topoInventario].setTipoItem(1);
			mostraItemGanho="ARMADURA: " + invetarioJogador[topoInventario].getInventArmadura().getNomeArmadura(); 
			break;
		case 2://inventario recebe roda pernas
			invetarioJogador[topoInventario].setInventRodas_pernas(inimigo.getRodaPernaRobo());
			invetarioJogador[topoInventario].setTipoItem(2);
			mostraItemGanho="RODAS/PERNAS: " + invetarioJogador[topoInventario].getInventRodas_pernas().getNomeRoda_pernas();
			break;
		}
	topoInventario++;
	cout<<"PARABÉNS! VOCE GANHOU "<<mostraItemGanho<<endl;

	system("pause");
	return 1;
	}
}

void game::creditos()
{
	system("cls");
	cout<<"DSENVOLVEDOR:\n Andrew Floriano\n "; 
	system("pause");
}

void game::carrega_armas(int i,ifstream *arq)
{
	string str_Arma;//arma
	int ba;//bonus ataque
	int al;//alcance
	int nd;//numero de disparo
	if(i<9)
	{
		i++;
		*arq>>str_Arma>>ba>>al>>nd;
		armas[i].setNomeArma(str_Arma);
		armas[i].setBonus_ataque(ba);
		armas[i].setAlcance(al);
		armas[i].setNro_disparo(nd);
		carrega_armas(i,arq);
	}
}

void game::carrega_armaduras(int i,ifstream *arq)
{
	string str_arm;
	int bd;
	if(i<9)
	{
		i++;
		*arq>>str_arm>>bd;
		armaduras[i].setNomeArmadura(str_arm);
		armaduras[i].setBonus_defesa(bd);
		carrega_armaduras(i,arq);
		
	}
}

void game::carrega_rodaPerna(int i,ifstream *arq)
{
	string str_rp;
	int nq;
	if(i<4)
	{
		i++;
		*arq>>str_rp>>nq;
		rodasPernas[i].setNomeRodas_pernas(str_rp);
		rodasPernas[i].setNro_quadros(nq);
		carrega_rodaPerna(i,arq);
	}
}

void game::carrega_robo(int i,ifstream *arq)
{
	string str_Nome;//nome

	
	if(i<20)
	{
		i++;
		*arq>>str_Nome;
		carregar[i].setNome(str_Nome);
		carrega_robo(i,arq);
	}
	
}

void game::inicializarBatalha()
{

	jogador.inicializaRobo();
	//if(rod<3)
	//{
	//	jogador.setArmaRobo(armas[rand()%3]);
	//	jogador.setArmaduraRobo(armaduras[rand()%3]);
	//	jogador.setRodaPernaRobo(rodasPernas[rand()%2]);
	//}
	//else if(rod>=3&&rod<=5)
	//{
	//	jogador.setArmaRobo(armas[rand()%3+3]);
	//	jogador.setArmaduraRobo(armaduras[rand()%3+3]);
	//	jogador.setRodaPernaRobo(rodasPernas[rand()%2+1]);
	//}
	//else
	//{
	//	jogador.setArmaRobo(armas[rand()%3+6]);
	//	jogador.setArmaduraRobo(armaduras[rand()%3+6]);
	//	jogador.setRodaPernaRobo(rodasPernas[rand()%2+3]);
	//}


	jogador.setPA(jogador.getPA()+jogador.getArmaRobo().getBonus_ataque());//poder de ataque recebe bonus de ataque
	jogador.setDEF(jogador.getDEF()+jogador.getArmaduraRobo().getBonus_defesa());//defesa recebe bonus defesa
	jogador.setHP(30);
	jogador.setPosMapCol(4);//padrão jogador recebe a cada rodada a posiçao 4x5
	jogador.setPosMapLin(5);

	inimigo=selecao[rod];
	inimigo.setPA(inimigo.getPA()+inimigo.getArmaRobo().getBonus_ataque());
	inimigo.setDEF(inimigo.getDEF()+inimigo.getArmaduraRobo().getBonus_defesa());
	inimigo.setHP(30);
	inimigo.setPosMapCol(6);
	inimigo.setPosMapLin(5);
}

void game::jogada(robo *A,robo *B)//A=jogador da rodada / B = jogador oponente / mov = movimento da rodada
{
	int paAux;
	int defAux;
	int damAux;
	int slotsave;
	char save_S_N;

	//calcula linha inicial e final NÃO MOVE JOGADOR, somente calcula as linhas permitidas de movimento
	int l_ini,l_fim,cord_x,cord_y;

	l_ini=A->getPosMapLin() - A->getRodaPernaRobo().getNro_quadros();//diminui os quadros da pos linha atual
	if(l_ini<1)
	{
		l_ini=1;
	}
	l_fim=A->getPosMapLin() + A->getRodaPernaRobo().getNro_quadros();//diminui os quadros da pos linha atual
	if(l_fim>10)
	{
		l_fim=10;
	}

	int c_ini,c_fim;
	c_ini=A->getPosMapCol() - A->getRodaPernaRobo().getNro_quadros();//diminui os quadros da pos linha atual
	if(c_ini<1)
	{
		c_ini=1;
	}
	c_fim=A->getPosMapCol() + A->getRodaPernaRobo().getNro_quadros();//diminui os quadros da pos linha atual
	if(c_fim>10)
	{
		c_fim=10;
	}
	cout<<"INFORME COORDENADAS DO ROBO "<<A->getNome()<<" OU '0' PARA SAIR DO JOGO "<<endl;
	bool pos_invalida=false;//para jogador não ficar na mesma posiçao que inimigo
	do
	{
		do
		{
		cout<<"   LINHA ("<<l_ini<<".."<<l_fim<<")";
		cin>>cord_x;
		}while((cord_x<l_ini||cord_x>l_fim)&&cord_x!=0);//testa se movimento é possivel
		if(cord_x==0)
		{
			cout<<"DESEJA SALVAR JOGO (S/N)";
			cin>>save_S_N;
			if(save_S_N=='S'||save_S_N=='s')
			{
				do
				{
				cout<<"ESCOLHA SLOTE A SER SALVO (1),(2) OU (3):"<<endl;
				cin>>slotsave;
				}while(slotsave<1||slotsave>3);
				saveGame(slotsave);
				cout<<"JOGO SALVO!"<<endl;
			}
			
			fimDeJogo=true;
			return;//sai do jogo

		}
		
		do
		{
		cout<<"   COLUNA ("<<c_ini<<".."<<c_fim<<")";
		cin>>cord_y;
		}while((cord_y<c_ini||cord_y>c_fim)&&cord_y!=0);//testa se movimento é possivel
		if(cord_y==0)
		{
			cout<<"DESEJA SALVAR JOGO (S/N)";
			cin>>save_S_N;
			if(save_S_N=='S'||save_S_N=='s')
			{
				do
				{
				cout<<"ESCOLHA SLOTE A SER SALVO (1),(2) OU (3):"<<endl;
				cin>>slotsave;
				}while(slotsave<1||slotsave>3);
				saveGame(slotsave);
				cout<<"JOGO SALVO!"<<endl;
			}
			
			fimDeJogo=true;
			return;//sai do jogo
		}
		if(cord_x==B->getPosMapLin()&&cord_y==B->getPosMapCol())
		{
			pos_invalida=true;
			cout<<"ESTA POSIÇAO JÁ ESTÁ OCUPADA PELO ADVERSÁRIO"<<endl;
			cout<<"DIGITE OUTRA POSIÇÃO"<<endl;
			system("pause");
		}
		else
		{
			pos_invalida=false;
		}
	}while(pos_invalida==true);

	A->setPosMapLin(cord_x);//coloca cord na pos de mapa
	A->setPosMapCol(cord_y);
	
	l_ini=A->getPosMapLin() - A->getArmaRobo().getAlcance();
	if(l_ini<1)
	{
		l_ini=1;
	}
	l_fim=A->getPosMapLin() + A->getArmaRobo().getAlcance();
	if(l_fim>10)
	{
		l_fim=10;
	}

	c_ini=A->getPosMapCol() - A->getArmaRobo().getAlcance();
	if(c_ini<1)
	{
		c_ini=1;
	}
	c_fim=A->getPosMapCol() + A->getArmaRobo().getAlcance();
	if(c_fim>10)
	{
		c_fim=10;
	}
	srand(time(NULL));
	if(B->getPosMapLin()>=l_ini&&B->getPosMapLin()<=l_fim&&B->getPosMapCol()>=c_ini&&B->getPosMapCol()<=c_fim)//testa se jogador A rodada esta no alcance de jogadr B 
	{
		int contDisparo=0;
		do
		{
			
		paAux=rand()%A->getPA()+1;//sorteia Poder de ataque
		defAux=rand()%B->getDEF()+1;// sorteia poder de defesa
		if(paAux>defAux)// teste se o ataque for maior que defesa
			{
				B->setDAM(paAux-defAux);//dano recebe ataque menos a defesa 
				damAux=rand()%B->getDAM()+1;//sorteia dano
				B->setHP(B->getHP()-damAux);//HP RECEBE HP MENOS O DANO
				cout<<"ROBO "<<B->getNome()<<" FOI ATINGIDO"<<endl;
				
			}
		else
		{
			cout<<"ROBO "<<A->getNome()<<" ERROU O ATAQUE"<<endl;
		}

		contDisparo++;
		if(A->getArmaRobo().getNro_disparo()>contDisparo)
		{
			cout<<"Robo "<<A->getNome()<<" TEM DIREITO A MAIS UM DISPARO"<<endl;
		}
		system("pause");
		}while(A->getArmaRobo().getNro_disparo()>contDisparo);
		
	}
	else
	{
		cout<<"ROBO "<<A->getNome()<<" ERROU O ATAQUE"<<endl;
		system("pause");
	}
}
void game::NovoJogo()
{
	system("cls");
	contpartidas=0;
	fimDeJogo=false;
	rod=0;
	string nome;
	cout<<" NOME ->";
		cin>>nome;
	jogador.setNome(nome);
	jogador.simbolo='@';
	if(inicializaJogodor()==false)
	{
		return;
	}
	partida(false);
	
}

bool game::inicializaJogodor()
{
	char op;
	int opArma;
	int opArmadura;
	int opRp;
	bool selArma=false,selArmadura=false,selRp=false;
	do
	{
	system("cls");
	if(selArma&&selArmadura&&selRp)//se todas bool forem verdadeiras faz
	{
		cout<<"[1]SELECIONAR ARMAS\n[2]SELECIONAR ARMADURAS\n[3]SELECIONAR RODAS\PERNAS\n[4]INICIAR JOGO\n[0]VOLTA PARA MENU PRINCIPAL\n\n";
	}
	else
	{
		cout<<"[1]SELECIONAR ARMAS\n[2]SELECIONAR ARMADURAS\n[3]SELECIONAR RODAS\PERNAS\n[0]VOLTA PARA MENU PRINCIPAL\n\n";
	}
	cout<<"DIGITE A OPCAO DESEJADA: ";
	cin >> op;
		switch(op)
		{
		case '1':
			do
			{
			system("cls");
			cout<<"SELECIONAR ARMAS: "<<endl<<endl;
			cout<<"CODIGO NOME          BONUS DE ATAQUE ALCANCE NUMERO DE DISPARO\n";
			cout<<setfill('-')<<setw(7)<<right<<" "<<setw(14)<<" "<<setw(16)<<" "<<setw(8)<<" "<<setw(18)<<"\n";
			
			for(int i=0;i<3;i++)
			{
				cout<<setfill(' ')<<setw(6)<<left<<i+1<<" "<<setw(13)<<armas[i].getNomeArma()<<" "<<setw(15)<<armas[i].getBonus_ataque()<<" "<<setw(7)<<armas[i].getAlcance()<<" "<<setw(17)<<armas[i].getNro_disparo()<<endl;

			}
			cout<<"\nDIGITE O CODIGO DA ARMA DESEJADA: ";
			cin>>opArma;
			}while(opArma<1||opArma>3);
			invetarioJogador[0].setInventArma(armas[opArma-1]);
			invetarioJogador[0].setTipoItem(0);
			jogador.setArmaRobo(armas[opArma-1]);//atribui pro jogador
			selArma=true;
			break;
		case '2':	
			do
			{
			system("cls");
			cout<<"SELECIONAR ARMADURA: "<<endl<<endl;
			cout<<"CODIGO NOME               BONUS DE DEFESA\n";
			cout<<setfill('-')<<setw(7)<<right<<" "<<setw(19)<<" "<<setw(16)<<"\n";
			for(int i=0;i<3;i++)
			{
				cout<<setfill(' ')<<setw(6)<<left<<i+1<<" "<<setw(18)<<armaduras[i].getNomeArmadura()<<" "<<setw(15)<<armaduras[i].getBonus_defesa()<<endl;

			}
			cout<<"\nDIGITE O CODIGO DA ARMADURA DESEJADA: ";
			cin>>opArmadura;
			}while(opArmadura<1||opArmadura>3);
			invetarioJogador[1].setInventArmadura(armaduras[opArmadura-1]);
			invetarioJogador[1].setTipoItem(1);
			jogador.setArmaduraRobo(armaduras[opArmadura-1]);
			selArmadura=true;
			break;
		case '3':	
			do
			{
			system("cls");
			cout<<"SELECIONAR RODA/PERNA: "<<endl<<endl;
			cout<<"CODIGO NOME           NUMERO DE QUADROS\n";
			cout<<setfill('-')<<setw(7)<<right<<" "<<setw(15)<<" "<<setw(18)<<endl;
			
			for(int i=0;i<2;i++)
			{
				cout<<setfill(' ')<<setw(6)<<left<<i+1<<" "<<setw(14)<<rodasPernas[i].getNomeRoda_pernas()<<" "<<setw(17)<<rodasPernas[i].getNro_quadros()<<endl;

			}
			cout<<"\nDIGITE O CODIGO DA RODA/PERNA DESEJADA: ";
			cin>>opRp;
			}while(opRp<1||opRp>2);
			invetarioJogador[2].setInventRodas_pernas(rodasPernas[opRp-1]);
			invetarioJogador[2].setTipoItem(2);
			jogador.setRodaPernaRobo(rodasPernas[opRp-1]);
			selRp=true;
			break;
		case '4':
			if(selArma&&selArmadura&&selRp)//se todas bool forem verdadeiras inicia o jogo
			{
				op='0';
				topoInventario=3;
			}
			else
			{
				op='9';
			}
			break;
		case '0':/*sair*/return false ;break;
		default:cout<<"OPCAO INVALIDA"<<endl;system("pause");
		}
	}while(op !='0');
}
void game::saveGame(int slot)  // ARQUIVOS
{
	string nomeArq;
	ofstream save;
	switch(slot)
	{
	case 1:nomeArq="Save Game01.txt";break;
	case 2:nomeArq="Save Game02.txt";break;
	case 3:nomeArq="Save Game03.txt";break;
	default:nomeArq="Save Game.txt";
	}
	save.open(nomeArq);
	for(int i=0;i<9;i++)
	{
		save<<selecao[i].getNome()<<" ";
		save<<selecao[i].getArmaduraRobo().getNomeArmadura()<<" ";
		save<<selecao[i].getArmaduraRobo().getBonus_defesa()<<" ";
		save<<selecao[i].getArmaRobo().getNomeArma()<<" ";
		save<<selecao[i].getArmaRobo().getBonus_ataque()<<" ";
		save<<selecao[i].getArmaRobo().getAlcance()<<" ";
		save<<selecao[i].getArmaRobo().getNro_disparo()<<" ";
		save<<selecao[i].getRodaPernaRobo().getNomeRoda_pernas()<<" ";
		save<<selecao[i].getRodaPernaRobo().getNro_quadros()<<endl;
		save<<selecao[i].simbolo<<endl;
	
	}
	
	save<<jogador.getNome()<<endl;
	save<<jogador.getArmaRobo().getNomeArma()<<endl;
	save<<jogador.getArmaRobo().getBonus_ataque()<<endl;
	save<<jogador.getArmaRobo().getAlcance()<<endl;
	save<<jogador.getArmaRobo().getNro_disparo()<<endl;
	save<<jogador.getArmaduraRobo().getNomeArmadura()<<endl;
	save<<jogador.getArmaduraRobo().getBonus_defesa()<<endl;
	save<<jogador.getRodaPernaRobo().getNomeRoda_pernas()<<endl;
	save<<jogador.getRodaPernaRobo().getNro_quadros()<<endl;
	save<<jogador.getHP()<<endl;
	save<<jogador.getPosMapCol()<<endl;
	save<<jogador.getPosMapLin()<<endl;
	save<<inimigo.getHP()<<endl;
	save<<inimigo.getPosMapCol()<<endl;
	save<<inimigo.getPosMapLin()<<endl;
	save<<rod<<endl;
	save<<contpartidas;
	save.close();
}

bool game::loadGame(int slot) // LOAD
{
	ifstream load;
	string str_RoboNome;
	string str_NomeArm;
	int bd;
	armadura Armadura;
	string str_NomeAr;
	int ba;
	int al;
	int nd;
	Arma arma;
	string str_NomeRodasPernas;
	int nq;
	rodas_pernas RodaPernas;
	int Hp_jogador;
	int	Hp_Inimigo;
	int poslin;
	int poscol;
	robo jogadorAux;
	string nomeArq;
	char simb;
	switch(slot)
	{
	case 1:nomeArq="Save Game01.txt";break;
	case 2:nomeArq="Save Game02.txt";break;
	case 3:nomeArq="Save Game03.txt";break;
	default:nomeArq="Save Game.txt";
	}
	load.open(nomeArq);
	if(!load)
	{
		cout<<"ARQUIVO NÃO PODE SER ENCONTRDO"<<endl;
		system("pause");
		return false;
	}
	else
	for(int i=0;i<9;i++)
	{
		load>>str_RoboNome;
		selecao[i].setNome(str_RoboNome);
		load>>str_NomeArm>>bd;
		Armadura.setNomeArmadura(str_NomeArm);
		Armadura.setBonus_defesa(bd);
		selecao[i].setArmaduraRobo(Armadura);
		load>>str_NomeAr>>ba>>al>>nd;
		arma.setNomeArma(str_NomeAr);
		arma.setBonus_ataque(ba);
		arma.setAlcance(al);
		arma.setNro_disparo(nd);
		selecao[i].setArmaRobo(arma);
		load>>str_NomeRodasPernas>>nq;
		RodaPernas.setNomeRodas_pernas(str_NomeRodasPernas);
		RodaPernas.setNro_quadros(nq);
		selecao[i].setRodaPernaRobo(RodaPernas);
		load>>simb;
		selecao[i].simbolo=simb;
	}
	load>>str_RoboNome;
	jogadorAux.setNome(str_RoboNome);
	load>>str_NomeAr>>bd>>al>>nd;
	arma.setNomeArma(str_NomeAr);
	arma.setBonus_ataque(bd);
	arma.setAlcance(al);
	arma.setNro_disparo(nd);
	jogadorAux.setArmaRobo(arma);
	load>>str_NomeArm>>bd;
	Armadura.setNomeArmadura(str_NomeArm);
	Armadura.setBonus_defesa(bd);
	jogadorAux.setArmaduraRobo(Armadura);
	load>>str_NomeRodasPernas>>nq;
	RodaPernas.setNomeRodas_pernas(str_NomeRodasPernas);
	RodaPernas.setNro_quadros(nq);
	jogadorAux.setRodaPernaRobo(RodaPernas);
	load>>Hp_jogador>>poscol>>poslin;
	jogadorAux.setHP(Hp_jogador);
	jogadorAux.setPosMapCol(poscol);
	jogadorAux.setPosMapLin(poslin);
	load>>Hp_Inimigo>>poscol>>poslin;
	load>>rod;
	load>>contpartidas;
	inimigo=selecao[rod];
	inimigo.setHP(Hp_Inimigo);
	inimigo.setPosMapCol(poscol);
	inimigo.setPosMapLin(poslin);
	load.close();
	jogadorAux.simbolo='@';
	jogadorAux.setPA(jogadorAux.getPA()+jogadorAux.getArmaRobo().getBonus_ataque());//poder de ataque recebe bonus de ataque
	jogadorAux.setDEF(jogadorAux.getDEF()+jogadorAux.getArmaduraRobo().getBonus_defesa());
	jogador=jogadorAux;
	inimigo.setPA(inimigo.getPA()+inimigo.getArmaRobo().getBonus_ataque());
	inimigo.setDEF(inimigo.getDEF()+inimigo.getArmaduraRobo().getBonus_defesa());
	return true;
}
void game::partida(bool lg)//lg  se bolena vem de load game
{
	bool lgAux=lg;
	char invent_S_N;
	do
	{
		if(rod>0)
		{
			cout<<"ABRIR INVENTARIO (S/N)? "<<endl;
			cin>>invent_S_N;
			if(invent_S_N=='s'||invent_S_N=='S')
			{
				buscaItensDoInventario();
			}
		}
		rod=rod+combate(lgAux);
		lgAux=false;
		if(fimDeJogo==true)
		{
			return;
		}
		contpartidas++;
	}while(rod<9);
}

void game::buscaItensDoInventario()
{
	system("cls");
	int seleciona;
	int cont=0;
	cout<<"INVENTARIO"<<endl<<endl;
	for(int i=0;i<10;i++)
	{
		if(invetarioJogador[i].gettipoItem()==0)
		{
			mostraArmas(invetarioJogador[i].getInventArma(),i+1);
			cont++;
		}
		else if(invetarioJogador[i].gettipoItem()==1)
		{
			mostraArmadura(invetarioJogador[i].getInventArmadura(),i+1);
			cont++;
		}
		else if(invetarioJogador[i].gettipoItem()==2)
		{
			mostraRodasPernas(invetarioJogador[i].getInventRodas_pernas(),i+1);
			cont++;
		}
	}
	do
	{
	cout<<"DIGITE O NUMERO DO ITEM DESEJADO OU (0) PARA SAIR"<<endl;
	cin>>seleciona;
	}while(seleciona<0||seleciona>cont);
	if(seleciona>0)
	{
		cout<<"VOCE SELECIONOU O ITEM"<<endl<<endl;
		seleciona--;
		if(invetarioJogador[seleciona].gettipoItem()==0)
		{
			jogador.setArmaRobo(invetarioJogador[seleciona].getInventArma());
			mostraArmas(jogador.getArmaRobo(),seleciona+1);
			system("pause");
		}
		else if(invetarioJogador[seleciona].gettipoItem()==1)
		{
			jogador.setArmaduraRobo(invetarioJogador[seleciona].getInventArmadura());
			mostraArmadura(jogador.getArmaduraRobo(),seleciona+1);
			system("pause");
		}
		else if(invetarioJogador[seleciona].gettipoItem()==2)
		{
			jogador.setRodaPernaRobo(invetarioJogador[seleciona].getInventRodas_pernas());
			mostraRodasPernas(jogador.getRodaPernaRobo(),seleciona+1);
			system("pause");
		}
	}
}

void game::mostraArmas(Arma ar,int indice)
{
	cout<< indice<<") ARMA:"<<endl;
	cout<<"    Nome.............: "<<ar.getNomeArma()<<endl;
	cout<<"    Bonus Ataque.....: "<<ar.getBonus_ataque()<<endl;
	cout<<"    Alcance..........: "<<ar.getAlcance()<<endl;
	cout<<"    Numero de Disparo: "<<ar.getNro_disparo()<<endl<<endl;
}

void game::mostraArmadura(armadura arm,int indice)
{
	cout<< indice<<") ARMADURA:"<<endl;
	cout<<"    Nome.............: "<<arm.getNomeArmadura()<<endl;
	cout<<"    Bonus Defesa.....: "<<arm.getBonus_defesa()<<endl<<endl;
}

void game::mostraRodasPernas(rodas_pernas rp,int indice)
{
	cout<< indice<<") RODA/PERNAS:"<<endl;
	cout<<"    Nome.............: "<<rp.getNomeRoda_pernas()<<endl;
	cout<<"    Numero de Quadros: "<<rp.getNro_quadros()<<endl<<endl;
}
game::~game(void)
{
}
