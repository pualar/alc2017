#include <stdio.h>
#include <math.h>

void preencheMatriz(int dim, double matrizA[dim][dim])
{   
    int i, j;

	printf("Entre com os elementos da matriz: \n");
	
	for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            scanf("%lf", &matrizA[i][j]);
        }
    }
}

void imprimeMatriz(int dim, double matriz[dim][dim]){
	int i, j;
    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            printf("%lf  ", matriz[i][j]);
        }

        printf("\n");
    }
}

//soma dos elementos q nao estao na diagona/elemento da diagona <1
int criterioColunas(int dim, double matriz[dim][dim])
{	
	int i, j;
	double soma = 0.0;
	double result = 0.0;
	double result_td[dim];
	double maior = 0;


	for(j = 0; j < dim; j++)
	{
		for(i = 0; i < dim; i++)
		{
			if(matriz[i][j] < 0){
				matriz[i][j] *= -1;
			}
			soma += matriz[i][j];			
		}

		result = soma - matriz[j][j];
		result_td[j] = result/matriz[j][j];

		printf("Resultado: %.2lf\n", result_td[j]);

		soma = 0;
		result = 0;

		if(maior < result_td[j])
		{
			maior = result_td[j];
		}
	}

	printf("Maior resultado: %.2lf \n", maior);

	if(maior < 1){
		printf("Satisfaz o criterio das colunas.\n");
		return 0;
	} 
	else{
		printf("Não Satisfaz o criterio das colunas.\n");
		return 1;
	}	
}

//soma dos elementos q nao estao na diagona/elemento da diagona <1
int criterioLinhas(int dim, double matriz[dim][dim])
{	
	int i, j;
	double soma = 0.0;
	double result = 0.0;
	double result_td[dim];
	double maior = 0;


	for(i = 0; i < dim; i++)
	{
		for(j = 0; j< dim; j++)
		{
			if(matriz[i][j] < 0){
				matriz[i][j] *= -1;
			}
			soma += matriz[i][j];			
		}

		result = soma - matriz[i][i];
		result_td[i] = result/matriz[i][i];

		printf("Resultado: %.2lf\n", result_td[i]);

		soma = 0;
		result = 0;

		if(maior < result_td[i])
		{
			maior = result_td[i];
		}
	}

	printf("Maior resultado: %.2lf \n", maior);

	if(maior < 1){
		printf("Satisfaz o criterio das linhas.\n");
		return 0;
	} 
	else{
		printf("Não Satisfaz o criterio das linhas\n");
		return 1;
	}	
}

int main(void){
	
	int dim;

	printf("Insida a dimensao da matriz: ");
	scanf("%d", &dim);

	double matrizA[dim][dim];

	preencheMatriz(dim, matrizA);

	//imprimeMatriz(dim, matrizA);

	criterioLinhas(dim, matrizA);

	criterioColunas(dim, matrizA);




	return 0;
}