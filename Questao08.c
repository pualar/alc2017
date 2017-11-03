#include <stdio.h>
#include <math.h>

void preencheVetor(int dim, double vetor[dim]){
	int i;

	for(i = 0; i<dim; i++){
		scanf("%lf", &vetor[i]);
	}
}

int norma(int quantidade, int dimensao, double vetor[quantidade][dimensao]){
	double soma = 0, norma = 0;
	int i;


	for (int i = 0; i < quantidade; i++){
		printf("Norma vetor %d: ", i+1);
		for(int j = 0; j < dimensao; j++){
			soma += pow(vetor[i][j], 2);
		}

		norma += sqrt(soma);
		printf("%lf\n", norma);
		soma = 0;
		norma = 0;
	}

	if(norma == 1){
		printf("Vetor unitário.\n");
		return 0;
	}

	else{
		printf("Base não pode ser ortnonormal porque um dos vetores não é unitário.\n");
		return 1;
	}
		
}

void ortonormais(int quantidade, int dimensao, double vetor[quantidade][dimensao]){
	int i, j, erro = 0;
	double sum = 0;

	for(i = 0; i < quantidade; i++){
		for(j = 0; j < dimensao; j++){
			sum += vetor[i][j];
		}

		if(sum != 0){
			erro = 1;
		}

		sum = 0;
	}

	if(erro == 1){
		printf("Nao sao ortonormais.\n");
	}

}

int main(void){

	int n, m, i, j;
	printf("Entre com o numero de vetores: ");
	scanf("%d", &n);

	printf("Entre com a dimensao desse espaço: ");
	scanf("%d", &m);

	double vetor[n][m], aux[m];

	printf("\nEntre com os %d vetores\n", n);

	for(i = 0; i < n; i++){
		printf("Insira o %dº vetor: ", i+1);
		for (j = 0; j < m; j++){
			scanf("%lf", &vetor[i][j]);
		}	
	}

	printf("\n");
	norma(n, m, vetor);

	ortonormais(n, m, vetor);
	

	return 0;
}
