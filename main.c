#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tp.h"

void troca(int vetor[], int i, int j)
{
	int aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

void permuta(int vetor[], int inf, int sup, pred p[], float **distancia, int np, float *caminho,int *rep)
{
	int i=0,j=0;
	if(inf == sup)
	{
		pred cp[np];
		for(i=0;i<np;i++)
			cp[i] = p[i];
		int aux = 0, dt=0;
		if(vetor[0] == 0 && vetor[sup] == 0){
			i=0;
			while(i<=sup){
				int cont=0;
				for(cont=0;cont<np;cont++){
					if(vetor[i] == cp[cont].b){
						if(vetor[i] != 0)
							aux++;
					}
					if(vetor[i] == cp[cont].a){
						cp[cont].a = 0;
						cp[cont].b = 0;
					}
				}
				i++;
			}
			if(aux == 0){
				float dt= 0.f;
				for(i=1;i<=sup;i++){
					int c1=0,c2=0;
					c1=vetor[i];
					c2=vetor[i-1];
					dt = dt + distancia[c1][c2];
				}
				*rep += 1;
				if(*rep == 1)
					*caminho = dt;
				if(dt<(*caminho)){
					*caminho = dt;
				}
			}
		}
	}
	else
	{
		for(i = inf; i <= sup; i++)
		{
			troca(vetor, inf, i);
			permuta(vetor, inf + 1, sup, p, distancia, np, caminho, rep);
			troca(vetor, inf, i); 
		}
	}
}


int main(){
	int n=0;
	FILE* arquivo = fopen("arquivo.txt","r");
	fscanf(arquivo,"%d",&n);
	vert v[n];
	pred p[n];
	int m=n+1;
	int vetor[m];
	int i=0, np=0;
	char c;
	while(!feof(arquivo)){
		if(i<n)
			fscanf(arquivo,"%d %d",&v[i].x,&v[i].y);
		else{
			if(i==n)
				fscanf(arquivo,"%d",&np);
			else
				fscanf(arquivo,"%d %d",&p[np].a,&p[np].b);
			
		}
		i++;
	}
	fclose(arquivo);
	
	i=0;
	int j=0;
	int grafo[n][n];
	float **distancia;
	distancia = (float**) malloc (n*sizeof(float*));
	for ( j = 0; j < n; j++){
		distancia[j] = (float*) malloc (n*sizeof(float));
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)
			grafo[i][j]=0;
			else
			grafo[i][j]=1;
		}
		vetor[i]=i;
	}
	
	int dx=0,dy=0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)
			distancia[i][j]=0;
			else{
				dx=v[j].x - v[i].x;
				dy=v[j].y - v[i].y;
				dx*=dx;
				dy*=dy;
				distancia[i][j]=sqrt(dx+dy);
			}
		}
	}
	
	int d=0;
	for(i=0;i<np;i++){
		for(j=0;j<np;j++){
			if(p[i].a == p[j].b && p[i].b == p[j].a)
			d++;
		}
	}
	
	if(d>0){
		printf("Deadlock");
		return 0;
	}
	vetor[n]=0;
	
	float caminho=0.f;
	int rep=0;
	
	permuta(vetor,0,n,p,distancia,np,&caminho,&rep);
	
	printf("%.2f",caminho);
	
	for(i=0;i<n;i++){
		free(distancia[i]);
	}
	free(distancia);
	distancia=NULL;
	
	return 0;
}
