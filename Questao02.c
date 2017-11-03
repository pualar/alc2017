#include <stdio.h>
#include <math.h>

void preencherMatriz(int dim, double matriz[dim][dim]){
	int i, j;

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			scanf("%lf", &matriz[i][j]);
		}
	}
}

void preencherVetor(int dim, double vetor[dim]){
	int i;

	for(i = 0; i < dim; i++){
		scanf("%lf", &vetor[i]);
	}
}

void imprimeVetor(int dim, double vetor[dim]){
	int i;

	for(i = 0; i < dim; i++){
		printf("%.2lf\n", vetor[i]);
	}
}

void imprimeMatriz(int dim, double matriz[dim][dim]){
	int i, j;

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			printf("%.2lf ", matriz[i][j]);
		}
		printf("\n");
	}	
}

void zerarMatriz(int dim, double matriz[dim][dim]){
	int i, j;
	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			matriz[i][j] = 0;
		}
	}
}

void fatorCholesky(int dim, double matrizA[dim][dim]){
	int i, j, n, l;

	for(i = 0; i < dim; i++){
		for(n = 0; n <= i-1; n++)
			matrizA[i][i] -= pow(matrizA[n][i], 2);

		if(matrizA[i][i] <= 0){
			printf("A matriz A nao é positiva definida.\n");
			
		}

		matrizA[i][i] = sqrt(matrizA[i][i]);

		for(j = i+1; j <= dim; j++){				
			for(n = 0;n <= i-1; n++)
				matrizA[i][j] -= (matrizA[n][i]*matrizA[n][j]); 

			matrizA[i][j] /= matrizA[i][i];
		}
		
		// l seria o j das colunas da matriz
		for (l = 0; l < dim; l++){
			if(i > l)
				matrizA[i][l] = 0;
		}
	}

	printf("\nFator cholesky:\n");
	imprimeMatriz(dim, matrizA);
}

int main(void){
	
	int dim, i, j, a = 0;
	
	printf("Entre com a dimensao da matriz A:\n");
	
	scanf("%d", &dim);
	
	double  matriz[dim][dim],
			vetorb[dim],
			Rt[dim][dim];
	
	printf("\nEntre com a matriz A:\n");
	preencherMatriz(dim, matriz);

	int op;

	printf("\n[1] Encontrar fator Cholesky.\n");
	printf("[2] Resolver o sistema por Cholesky.\n");

	printf("\nOpção: ");
	scanf("%d", &op);

	switch(op){
		case 1: fatorCholesky(dim, matriz);
			break;
		case 2:

		printf("\nEntre com o vetor b:\n");
		
		preencherVetor(dim, vetorb);
	
		//R transposta
		for(i = 0; i < dim; i++)
		{
			for(j = 0; j < dim; j++)
			{
				Rt[i][j] = matriz[j][i];
			}
		}
		
		//Rt*R*x = b;
		//R*x = y;
		//Rt*y = b;
		
		
		//SUBSTITUICAO PRA FRENTE: Rt*y = b;
		
		double y[dim];
		int contador = 0;
		
		for(i = 0; i < dim; i++)
		{	
			for(j = 0; j < i; j++)
			{
				if(i == 0 && j == 0){
					y[i] = vetorb[i]/Rt[i][j];
				}
				
				else{
					contador = contador + (Rt[i][j]*y[j]);
				}
				 			 
			}
			
			y[i] = (vetorb[i]-contador)/Rt[i][i];
			contador = 0;

		}
		
		//SUBSTITUICAO PRA TRAS: R*x = y
		double x[dim];
		
		contador = 0;
		
		for(i = 3; i >= 0; i--)
		{	
			for(j = 3; j > i; j--)
			{
				if(i == 3 && j == 3)
				{
					x[i] = y[i]/matriz[i][j];
				}
				
				else
				{
					contador = contador + (matriz[i][j]*x[j]);
				}	 			 
			}
			
			x[i] = (y[i]-contador)/matriz[i][i];
			contador = 0;

		}                                      

		 printf("\n");
		 printf("------Resultado por Cholesky-------\n");
		 printf("x: ");
		
		 for(i = 0; i < dim; i++)
		 {
		 	printf("%.2lf ", x[i]);
		 }

	}
	
	return 0;
}