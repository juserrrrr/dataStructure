#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define MAX 10000

void print(int[]);
void Mergesort(int[], int, int);
void intercala(int[], int, int, int);

int main(void) {
        int vetor[5] = {3,2,4,5,1};
        print(vetor);
        Mergesort(vetor, 0, 4);
        print(vetor);
    return 0;
}

void Mergesort(int v[], int l, int r) {
     if (l < r) {
        int m = (l + r) / 2;
        Mergesort(v, l, m);
        Mergesort(v, m+1, r);
        intercala(v, l, m, r);
     }
}

void intercala(int v[], int l, int m, int r) {
    int i = 0, j = 0, k = l, n1, n2;

     // calculando tamanho dos subarranjos
    n1 = m - l +1;
    n2 = r - m;

     // declarando subarranjos que serão intercalados
    int sideL[n1], sideR[n2];

     // iniciando subarranjos a partir de v
    for (int i = 0 ; i < n1 ; i++) {
        sideL[i] = v[l+i];
    }

    for (int c = 0 ; c < n2 ; c++) {
        sideR[c] = v[m + 1 + c];
    }

     // intercalando arranjos
    while (i < n1 && j < n2){
        if (sideL[i] <= sideR[j]) {
            v[k] = sideL[i];
            i++;
        }
        else{
            v[k] = sideR[j];
            j++;
        }    
        k++;
    }
    while (i<n1){
        v[k] = sideL[i];
        i++;
        k++;
    }
    while(j < n2) {
        v[k] = sideR[j];
        j++;
        k++;
    }
}

void print(int v[]){
    for (int i = 0; i < 5; i++)
        printf("%d ", v[i]);
    printf("\n");
}
