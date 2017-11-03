#include <stdio.h>
#include <math.h>

void printMatriz(int dim, double matriz[dim][dim]){
	int i, j;

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			printf("%.1lf ", matriz[i][j]);
		}

		printf("\n");
	}
}

void preencheMatriz(int dim, double matriz[dim][dim]){
	int i, j;

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			scanf("%lf", &matriz[i][j]);
		}
	}
}

double modulo(double numero){
	if(numero > 0)
		return numero;
	else
		return -(numero);
}

void matrizDiagonal(int dim, double matriz[dim][dim], double vetor[dim]){
	int i, j;

	for(i = 0; i < dim; i++){
		for(j = 0; j< dim; j++){
			if(i == j){
				matriz[i][j] = vetor[i];
			}
			else{
				matriz[i][j] = 0;
			}
		}
	}

	printMatriz(dim, matriz);
}

void determinanteDiagonal(int dim, double matriz[dim][dim]){
	int i, j;
	double det = 1;

	for(i = 0; i < dim; i++){
		for(j = 0; j< dim; j++){
			if(i == j){
				det *= matriz[i][j];
			}
			
		}
	}

	printf("\nDeterminante da matriz D: %.1lf\n", det);

}

void zeraVetor(int dim, double vetor[dim]){
	int i;

	for(i = 0; i < dim; i++){
		vetor[i] = 0;
	}
}

void printVetor(int dim, double vetor[dim]){
	int i;

	for(i = 0; i<dim; i++){
		printf("%.2lf ", vetor[i]);

	}
}

void matrizLaplaciana(int dim, double matriz[dim][dim], double matriz2[dim][dim]){
	int i, 
		j;

	double n;
	double matrizL[dim][dim];

	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			matrizL[i][j] = matriz[i][j] - matriz2[i][j];
		}
	}

	printf("\nMatriz Laplaciana:\n");
	printMatriz(dim, matrizL);
}


void normaInfinita(int dim, double matriz[dim][dim]){
	int i,
		j;

	double soma[dim];
	double maior = 0;

	zeraVetor(dim, soma);


	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			soma[i] += modulo(matriz[i][j]);
		}

		if(soma[i] > maior){
			maior = soma[i];
		}
	}

	printf("\nNorma infinita da matriz L: %.3lf\n", maior);
}

//√a² + b²..... dos vetores
double norma(int dim, double vetor[dim]){
   int i;
   double soma = 0, 
          result = 0;

   for(i = 0; i < dim; i++){
      soma += (pow(vetor[i], 2));
   }

   result = sqrt(soma);
   return result;
}

void angulo(int dim, double vetor1[dim], double vetor2[dim]){
	int i;
	double  arco,
			prod_interno = 0;

	//prod interno
	//<x,y>
	for(i = 0; i < dim; i++){
		prod_interno += vetor1[i] * vetor2[i];
	}

	//printf(">> Prod interno: %lf", prod_interno);


	double  normax = norma(dim, vetor1),
			normay = norma(dim, vetor2);

	//printf(">> Norma vetor 1: %lf\nNorma vetor 2: %lf\n", normax, normay);

	arco = (prod_interno)/((normax)*(normay));

	// return arco;

	printf("O angulo entre a 1ª e a 3ª coluna da matriz L é arccos(%.3lf)\n", arco);
}

int main(void){
	int erro = 0;
	int op;

	while(erro != 1){

		printf("******* Questao 06 prova de implementação 2017.2\n");
		int i,
			j,
			dim;

		printf("Insira a dimensão da matriz Adjacência: ");
		scanf("%d", &dim);

		double  matrizA[dim][dim],
				matrizD[dim][dim],
				matrizL[dim][dim],
				grafo[dim];

		printf("\nEntre com a matriz Adjacência:\n");
		preencheMatriz(dim, matrizA);

		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++){
				if(matrizA[i][i] != 0){
					erro = 1;
				}
			}
		}

		if(erro == 1){
			printf("Matriz incorreta.\n");
			break;
		}


		printf("\nGrau dos %d vetrices do grafo:\n", dim);
		for(i = 0; i < dim; i++){
			printf("Vertice %d: ", i+1);
			scanf("%lf", &grafo[i]);
		}
		
		printf("\nMatriz diagonal:\n");
		matrizDiagonal(dim, matrizD, grafo);

		determinanteDiagonal(dim, matrizD);

		matrizLaplaciana(dim, matrizD, matrizA);

		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++){
				matrizL[i][j] = matrizD[i][j] - matrizA[i][j];
			}
		}
	
		normaInfinita(dim, matrizL);
		
		double  vetorColuna1[dim],
				vetorColuna3[dim];

		printf("\nVetor coluna 1:\n");

		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++){
			vetorColuna1[j] = matrizL[j][0];
			}
		}	

		printVetor(dim, vetorColuna1);
			// printf("\n");

		printf("\nVetor coluna 3:\n");

		for(i = 0; i < dim; i++){
			for(j = 0; j < dim; j++){
			vetorColuna3[j] = matrizL[j][2];
			}
		}

		printVetor(dim, vetorColuna3);
		printf("\n");

		// printf("%s\n", );
		angulo(dim, vetorColuna1, vetorColuna3);

		return 0;
	}
}
