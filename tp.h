#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vertice{
	int x, y;
}vert;

typedef struct precedencia{
	int a, b;
}pred;

void troca(int vetor[], int i, int j);

void permuta(int vetor[], int inf, int sup, pred p[], float **distancia, int np, float *caminho,int *rep);
