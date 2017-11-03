#include <stdio.h>
#include <math.h>

void zeros_v(int dim, double mult[dim])
{
    int i;

    for(i = 0; i < dim; i++)
    {
        mult[i] = 0;
    }
}

double multiplicacaoMatrizVetor(int dim, double matriz[dim][dim], double vetor[dim])
{
    int i, j;
    double mult[dim];

    zeros_v(dim, mult);
    
    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            mult[i] += matriz[i][j]*vetor[j];
        }
    }
    
    return mult[i];
}

void ImprimeVetor(int dim, double vetor[dim])
{
    int i;

    for(i = 0; i < dim; i++)
    {
        printf("%lf\n", vetor[i]);
    }
}

void ImprimeMatriz(int dim, double matriz[dim][dim])
{
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

void substituicaofrente(int dim, double matrizA[dim][dim], double vetor_b[dim])
{

    int i, j; 
    double temp[dim];
     
    for(i = 0; i < dim; i++)
    {
        temp[i] = vetor_b[i]; 
    }
     
    for(i=0;i<dim;i++) 
    {
    	if (i > 0)
        {
           	for(j = 0; j <= (i-1); j++)
            {
               	temp[i] = temp[i] - matrizA[i][j] * temp[j];
            }
        }

        temp[i] = temp[i]/matrizA[i][i];
    }

    for(i = 0; i < dim; i++)
    {
        vetor_b[i] = temp[i];    
    }

}

void substituicaotras(int dim, double matrizA[dim][dim], double vetor_b[dim])
{
    int   i, j;
    double temp[dim];

    for(i = 0; i < dim; i++)
    {
        temp[i] = vetor_b[i]; 
    }

    for(i = dim-1; i >= 0; i--) 
    {
        for(j = dim-1; j >= i+1; j--)
        {
            temp[i] = temp[i] - matrizA[i][j] * temp[j];
        }
          
        temp[i] = temp[i]/matrizA[i][i];
    }

    for(i = 0; i < dim; i++)
    {
        vetor_b[i] = temp[i]; 
    }

}

void fatLU(int dim, double matrizA[dim][dim], double L[dim][dim], double U[dim][dim], double vetor_b[dim], double vetor_xLU[dim])
{
	int i, j, k;
    double y[dim], aux[dim];
 	
 	for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            if(j <= i)
            {
                U[j][i] = matrizA[j][i];

                for(k = 0; k <= j-1; k++)
                {
                    U[j][i] -= (L[j][k]*U[k][i]);
                }
                
                if(j == i)
                {
                    L[j][i]=1;
                }

                else
                {
                    L[j][i]=0;
                }
            }

            else
            {
                L[j][i] = matrizA[j][i];

                for(k = 0; k <= i-1; k++)
                {
                    L[j][i] -= L[j][k]*U[k][i];
                }

                L[j][i] /= U[i][i];

                U[j][i] = 0;
            }
        }
    }

    printf ("Matriz L:\n");
    ImprimeMatriz(dim, L);

    
    printf ("\nMatriz U:\n");
    ImprimeMatriz(dim, U);

    ///achando x
    printf("Fatoracao LU:\n");    
    for(i = 0; i < dim; i++)
    {
        y[i] = vetor_b[i];

        for(j = 0; j < i; j++)
        {
            y[i] -= L[i][j] * y[j];
        }
    }

    printf("\nVetor x:\n");

    for(i = dim; i >= 0; i--)
    {
        vetor_xLU[i] = y[i];

        for(j = i+1; j < dim; j++)
        {
            vetor_xLU[i] -= U[i][j] * vetor_xLU[j];
        }

        vetor_xLU[i] /= U[i][i];
        aux[i] = vetor_xLU[i];
    }

    for(i = 0; i < dim; i++)
    {
        printf("%lf\n", aux[i]);
    }

    substituicaofrente(dim, L, vetor_b);      
    substituicaotras(dim, U, vetor_b);
}

double norma2(int dim, double vetor_b[dim])
{
  	int i;
  	double s = 0;
  
    for(i = 0; i < dim; i++)
    {
		s += vetor_b[i] * vetor_b[i]; 
    }
  	
  	s = sqrt(s);
	
	return s;	  
}
	
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

void preencheVetor(int dim, double vetor_b[dim], double vetor_b1[dim])
{
    int i;
         
    for (i = 0; i < dim; i++)
    {
        scanf("%lf", &vetor_b[i]);	
        vetor_b1[i] = vetor_b[i];
    }
}

void GaussSeidel(int dim,int p, double matrizA[dim][dim], double vetor_xGS[dim], double tolerancia, double vetor_b[dim])
{
	int   i, j, flag;

	double R1, R2, sub1, sub2, T[dim];

    sub1 = 0;
    sub2 = 0;

	for(i = 0; i < dim; i++)
	    {
           for(j = 0; j < i; j++)
           {
			   sub1 += matrizA[i][j] * vetor_xGS[j];
           }
		
		   for(j = (i+1); j < dim; j++)
           {
			  sub2 += matrizA[i][j] * vetor_xGS[j];
           }
		
		    vetor_xGS[i] = (1-1)*vetor_xGS[i] + (1/matrizA[i][i]) * (vetor_b[i]-(sub1+sub2));
		    
		    sub1 = 0;
		    sub2 = 0;
		
	    }
	    
	    zeros_v(dim, T);
	
		for(i = 0; i < dim; i++)
        {
            for(j = 0; j < dim; j++)
            {
                T[i] += matrizA[i][j] * vetor_xGS[j];
            }
        }

        for(i = 0; i < dim; i++)
        {
            T[i] -= vetor_b[i];
        }
        
        R2 = norma2(dim, T);	
        
    do
    {
		R1 = R2;
	
	    for(i = 0; i < dim; i++)
	    {
           for(j = 0; j < i; j++)
           {
			   sub1 += matrizA[i][j] * vetor_xGS[j];
           }
		
		   for(j = (i+1); j < dim; j++)
           {
			  sub2 += matrizA[i][j] * vetor_xGS[j];
           }
		
		    vetor_xGS[i] = (1-1)*vetor_xGS[i] + (1/matrizA[i][i])*(vetor_b[i]-(sub1+sub2));
		    
		    sub1 = 0;
		    sub2 = 0;
		
	    }
	    
	    for(i = 0; i < dim; i++)
        {
		    T[i] = 0;
        }
	
		for(i = 0; i < dim; i++)
        {
            for(j = 0; j < dim; j++)
            {
                T[i] += matrizA[i][j] * vetor_xGS[j];
            }
        }
        
        for(i = 0; i < dim; i++)
        {
            T[i] -= vetor_b[i];
        }
        
        R2 = norma2(dim, T);

        if (R2 > R1);
        {
			flag = 0;
			break;
		}	
	}
    
    while((R2 > tolerancia));
    
    if(flag)
    {
    	printf("\nO sistema não converge para o metodo de Gauss-Seidel\n");
        p = 1;
	}

	else
	{
		printf("\nResultado do metodo de Gauss-Seidel\n");
	    ImprimeVetor(dim, vetor_xGS);
	}
	
}

void compara(int dim, int p, double vetor_xGS[dim], double vetor_xLU[dim], double vetor_b[dim], double matrizA[dim][dim])
{   
    int i, j;
    float s;
    double res1[dim], mult1[dim];
    double res2[dim], mult2[dim];

    //Ax
    for(i = 0; i < dim; i++)
    {
         for(j = 0; j < dim; j++)
         {
             mult1[i] += matrizA[i][j]* vetor_xGS[j];
         }
    }

    //b - Ax
    for(i = 0; i < dim; i++)
    {
        res1[i] = vetor_b[i] - mult1[i];
    }
   
   //||b-Ax||
    for(i = 0; i < dim; i++)
    {
       s += res1[i]*res1[i];
    }  
    
    s = sqrt(s);
       
    printf("\nNorma do residuo de Gauss:\n");
    printf("%f\n", s);
    
    s = 0;

    for(i = 0; i < dim; i++)
    {
         for(j = 0; j < dim; j++)
         {
             mult2[i] += matrizA[i][j]* vetor_xLU[j];
         }
    }

    //b - Ax
    for(i = 0; i < dim; i++)
    {
        res2[i] = vetor_b[i] - mult2[i];
    }
   
   //||b-Ax||
    for(i = 0; i < dim; i++)
    {
       s += res2[i]*res2[i];
    }  
    
    s = sqrt(s);
       
    printf("\nNorma do residuo de LU:\n");
    printf("%f\n", s);
}

void MatrizBanda(int dim,double matrizA[dim][dim])
{
    int i, j, matrizBanda = 0;

    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            if(i != j && i != j-1 && i != j+1)
            {
                if(matrizA[i][j] != 0)
                {
                    matrizBanda = 1;
                    break;
                }
            
                else
                {
                    matrizBanda = 0;
                }
            }
        }
    }

    if(matrizBanda)
    {
         printf("\nNão é uma matriz banda.\n");
    }

    else
    {
        printf("\nÉ uma matriz banda.\n");
    }
}

int main(void)
{
	int dim, p = 0;

	printf("Insira a dimensao da matriz: ");
	scanf("%d", &dim);

	double matrizA[dim][dim], L[dim][dim], U[dim][dim], vetor_b[dim], vetor_b1[dim], tolerancia, vetor_xLU[dim], vetor_xGS[dim];

    preencheMatriz(dim, matrizA);
    
    printf("\nInsira o vetor b:\n" ); 
    preencheVetor(dim, vetor_b, vetor_b1);
    
    fatLU(dim, matrizA, L, U, vetor_b, vetor_xLU);

    printf("\nInsira o valor da tolerancia: ");
    scanf("%lf", &tolerancia);
   
    GaussSeidel(dim, p, matrizA, vetor_xGS, tolerancia, vetor_b1);

    MatrizBanda(dim, matrizA);

    printf("\nComparacao:\n");
    compara(dim, p, vetor_xGS, vetor_xLU, vetor_b, matrizA);

    return 0;
}