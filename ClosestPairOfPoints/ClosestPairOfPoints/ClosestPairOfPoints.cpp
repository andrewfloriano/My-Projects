#include "pch.h"
#include <iostream> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h>
using namespace std;

class Point
{
public:
	float x, y;
};

Point pontoA;
Point pontoB;


//distancia entre 2 pontos
float dist(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y)
	);
}

//funcção pra ordenar em X
int compareX(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x - p2->x);
}

//em Y
int compareY(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y - p2->y);
}

//distancia pra poucos pontos
float DistanciaPontos(Point P[], int n)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (dist(P[i], P[j]) < min) {
				min = dist(P[i], P[j]);
				pontoA = P[i];
				pontoB = P[j];
			}
		}
	}
	return min;
}


float min(float x, float y)
{
	return (x < y) ? x : y;
}

float DistanciaParte(Point parte[], int size, float d)
{
	float min = d;

	

	//função c++ pra ordenar usando a função Y
	qsort(parte, size, sizeof(Point), compareY);

	//achar a distancia dos pontos salvar dist e pontos
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size && (parte[j].y - parte[i].y) < min; ++j) {
			if (dist(parte[i], parte[j]) < min) {
				min = dist(parte[i], parte[j]);
				pontoA = parte[i];
				pontoB = parte[j];
			}
		}
	}

	return min;
}

float ClosestPoints(Point P[], int n)
{
	//não divide mais o array e acha distancia direto
	if (n <= 3)
		return DistanciaPontos(P, n);

	int PN = n / 2;
	Point PM = P[PN];

	//duas partes dividas no meio do array P
	float dl = ClosestPoints(P, PN);
	float dr = ClosestPoints(P + PN, n - PN);

	
	float d = min(dl, dr);

	//metade do array
	Point* parte = new Point[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(P[i].x - PM.x) < d)
			parte[j] = P[i], j++;

	

	//Point* points = ClosestPoints(parte, j, d);
	return min(d, DistanciaParte(parte, j, d));
}

void closest(Point P[], int n)
{
	qsort(P, n, sizeof(Point), compareX);
	ClosestPoints(P, n);
}







int main()
{
	Point P[] = { {-13, 0.5}, {-10.5, -11.5}, {-10, 9}, {-4.5, -2}, {-1, 8.5}, {0.5, 6}, {0.5, -12}, {2, 12.5}, {3.5, 11}, {5.5, 3}, {5.5, -7 }, {5,11.5}, {6.5, 3.2}, {7, -10},{9, -5 }, { 11.5, -4 } };
	int n = sizeof(P) / sizeof(P[0]);
	closest(P, n);
	cout << "Pontos mais próximos: " << "Ponto A:" << endl
		<< "X: " << pontoA.x << endl
		<< "Y: " << pontoA.y << endl
		<< "Ponto B:" << endl
		<< "X: " << pontoB.x << endl
		<< "Y: " << pontoB.y << endl;

	return 0;
}
