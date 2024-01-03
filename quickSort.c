#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
void quicksort_A(int a[], int p, int r) {
   int t;
   if (p < r) {
      // sorteia numero entre p e r e utiliza como pivo
      int v = (rand()%(r-p))+p;
      int pivo = a[v];
      a[v] = a[r];
      a[r] = pivo;

      int i = p-1;
      int j = r;
      do {
          // move i e j
          do { i ++; } while (a[i] < pivo);
          do { j --; } while ((a[j] > pivo) && (j > p));

          // se i ainda for menor que j, troca i com j
          if (i < j) {
             t = a[i], a[i] = a[j], a[j] = t;
          }
      } while (i<j);  // termina se i ultrapassar com j

      // devolve o pivo a sua posicao original
      a[r] = a[i];
      a[i] = pivo;

      // recursivamente ordena a[p..i-1] e a[i+1..r]
      quicksort_A(a, p, i-1);
      quicksort_A(a, i+1, r);
   }
}

int main (void) {
   // ponteiros para criacao de dois arranjos a serem ordenados
   int *A, *B;
   A = (int *)malloc(sizeof(int)*MAX);
   B = (int *)malloc(sizeof(int)*MAX);

   int i;
   // Execucao da versao A do quicksort
   printf("\nQuicksort A com arranjo aleatorio de %dM inteiros",MAX/1000000);
   // geracao de numeros aleatorios dos arranjos A e B
   printf("\n...gerando arranjo aleatorio...");
   for (i=0; i<MAX; i++) {
     A[i] = (int)rand()%10000;
     B[i] = A[i];
   }

   quicksort_A(A,0,MAX-1);

   return 0;
}