#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define tamanho_vetor 100

void print(int v[]){
    for (int i = 0; i < tamanho_vetor; i++)
        printf("%d ", v[i]);
    printf("\n");
}


void swap(int v[], int i, int j){
    int aux;
    aux = v[i], v[i] = v[j], v[j] = aux;
}

void quickSort(int v[],int left, int right){
  if (left < right){
    int i=left,j=right,index,pivot;
    index = (right+left)/2;
    pivot = v[index];
    while(i<j){
      while (v[i] != pivot && v[i] < pivot) {i++;};
      while (v[j] != pivot && v[j] > pivot) {j--;};
      printf("To aqui [i: %d j: %d]\n",i,j);
      if (i<j){
        swap(v,i,j);
      }
    }
    quickSort(v,left,i-1);
    quickSort(v,i+1,right);
  }
}


int main(){
  int v[tamanho_vetor];
  for (int l = 0;l < 10;l++) {
    for (int i = 0; i < tamanho_vetor; i++){
            v[i] = (int) rand()%10000;
    }
  // print(v);
  quickSort(v,0,tamanho_vetor-1);
  // print(v);

  // bool ok = true;
  // for (int i = 0; i < tamanho_vetor-1; i++){
  //   if (v[i] > v[i+1]){
  //       ok = false;
  //       break;
  //   }
  // }
  // printf("%s\n\n\n", ok ? "ok" : "error");
    
  }
  

  
  return 0;
}
