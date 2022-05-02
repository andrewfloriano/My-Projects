#include "arena.h"




arena::arena(void)
{
}


arena::~arena(void)
{
}

void arena::imprime_arena(robo player,robo enemy)
{
	string matriz[11][11];
	string vLetra[11]= {"  ","1","2","3","4","5","6","7","8","9","10"};
	string vNumero[11]={"  "," 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"};
	int numero=48;
	int letra=64;
	for(int i=0;i<11;i++)
	{
		cout<<"\t\t\t";
		for(int j=0;j<11;j++)
		{
			if(i==0)
			{
				matriz[i][j]=vLetra[j];	
			}
			else
			{
				if(j==0)
				{
					
					matriz[i][j]=vNumero[i];
				}
				else
				{
					matriz[i][j]="-";
				}
			}
			if(i==player.getPosMapLin()&&j==player.getPosMapCol())
			{
				matriz[i][j]=player.simbolo;
			}
			if(i==enemy.getPosMapLin()&&j==enemy.getPosMapCol())
			{
				matriz[i][j]=enemy.simbolo;
			}
			cout<< matriz[i][j]<<" ";
			
		}
		cout<<endl;
	}	
}

void arena::imprime_interface(robo player,robo enemy,int Nrod)
{
	system("cls");
	imprime_Dados(player,enemy,Nrod);
	imprime_arena(player,enemy);
}

void arena::imprime_Dados(robo player,robo enemy,int Nrod)
{
	cout<<"\tJOGADOR\t\t\t"<<"    "<<"|\t\t\tINIMIGO"<<endl;
	cout<<"-------------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t RODADA:"<<Nrod+1<<endl;
	cout<<"\tNOME:"<<player.getNome()<< "\t\t"<<"    "<<"|\t\t\tNOME:"<<enemy.getNome()<<endl;
	cout<<"\tDEFESA:"<<player.getDEF()<< "\t\t"<<"    "<<"|\t\t\tDEFESA:"<<enemy.getDEF()<<endl;
	cout<<"\tATAQUE:"<<player.getPA()<< "\t\t"<<"    "<<"|\t\t\tATAQUE:"<<enemy.getPA()<<endl;
	cout<<"\tALCANCE:"<<player.getArmaRobo().getAlcance()<< "\t\t"<<"    "<<"|\t\t\tALCANCE:"<<enemy.getArmaRobo().getAlcance()<<endl;
	cout<<"\tDISPARO:"<<player.getArmaRobo().getNro_disparo()<< "\t\t"<<"    "<<"|\t\t\tDISPARO:"<<enemy.getArmaRobo().getNro_disparo()<<endl;
	cout<<"\tMOVIMENTO:"<<player.getRodaPernaRobo().getNro_quadros()<< "\t\t"<<"    "<<"|\t\t\tMOVIMENTO:"<<enemy.getRodaPernaRobo().getNro_quadros()<<endl;
	cout<<"\t\t\t\t    |"<<endl;
	cout<<"\tVIDA:"<<player.getHP()<< "\t\t\t"<<"    "<<"|\t\t\tVIDA:"<<enemy.getHP()<<endl;
	cout<<endl<<endl;
}