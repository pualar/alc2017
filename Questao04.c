#include <stdio.h>
#include <math.h>

#define h 0.001

//12 5 4 9 7

void show_polinomio(int grau, double coef[grau]){
   int exp;
   double raiz;
   
   for(exp = grau; exp >= 0; exp--){

      if(coef[exp] == 0){
         printf(" ");
      }
      else if(coef[exp] > 0){
         printf("+%.lf ", coef[exp]);
      }

      else if(exp == 0){
         printf("%.lf ", coef[exp]);
      }

      else {
         printf("%.lfx^%d ", coef[exp], exp);
      }
   }

   printf("\n");
}

void show_derivada(int grau, double coef[grau]){
   int exp,
      newExp;

   double newCoef[grau];

   for(exp = grau; exp >= 0; exp--){
      
      newCoef[exp] = coef[exp] * exp;
      
      if(newCoef[exp] == 0){
         printf(" ");
      }
      

      else{
         printf("%.lfx^%d ", newCoef[exp], exp-1);
      }
      

   }

   printf("\n");

   
}

double funcao(double x, int grau, double coef[grau]){
   double raiz = 0;
   int exp;

   for(exp = grau; exp >= 0; exp--){
      raiz += coef[exp] * pow(x, exp);
      // printf("coeficiente %lf  * x %lf", coef[exp], x);
   }

   // printf("\n\n\n%lf\n",raiz);


   return raiz;
}

double derivada(double x, int grau, double coef[grau]){
   double deriv = 0;

   deriv = (funcao(x+h, grau, coef) - funcao(x, grau, coef))/h;

   return deriv;
}

int main(int argc, char const *argv[])
{
   int grau, 
       i,
       interacoes;

   
   printf("\nGrau do polinomio: ");
   scanf("%d", &grau);

   double coef[grau], 
          fx,
          deriv, 
          erro;   

   printf("\nCoeficientes do polinomio: ");
   for(i = grau; i >= 0; i--){
      scanf("%lf", &coef[i]);
   }


   printf("\nPolinomio(x): ");
   show_polinomio(grau, coef);

   printf("\nDerivada de p(x): ");
   show_derivada(grau, coef);

   double x1;

   printf("\nInsira um numero maximo de interações: ");
   scanf("%d", &interacoes);

   printf("\nInsira o valor x1: ");
   scanf("%lf", &x1);
   printf("\n");

   for(i = 0; i < interacoes; i++){
      
      fx = funcao(x1, grau, coef);
      deriv = derivada(x1, grau, coef);
      erro = (fx/deriv);
      x1 -= erro;

      printf("f(x%d) vale: %lf\n", i+1, fx);
      printf("f'(x%d) vale: %lf\n", i+1, deriv);
      printf("Erro fa função: %lf\n", erro);
      printf("x%d vale: %lf\n", i+1, x1);

      printf("\n\n");

   }

   printf("p(0): %lf\n", funcao(0, grau, coef));
   printf("p(1): %lf\n", funcao(1, grau, coef));


   
   return 0;
}