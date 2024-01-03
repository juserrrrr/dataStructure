#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
  char nome[50];
  int matricula;
} Pessoa;

typedef struct Node {
  Pessoa pessoa;
  struct Node *next;
} Node;

typedef struct Hash {
  Node **itens;
  int tamanho, quantidade;
} Hash;

void createHash(Hash **ha, int size) {
  (*ha)->tamanho = size;
  (*ha)->itens = malloc(size * sizeof((*ha)->itens));
  (*ha)->quantidade = 0;
  for (int i = 0; i < (*ha)->tamanho; i++) {
    (*ha)->itens[i] = NULL;
  }
}

int hashing(Hash *ha, int num) { return num % ha->tamanho; }

int validateSizeMaxHash(Hash *ha) { return ha->quantidade >= ha->tamanho * 0.7; }

void rehashing(Hash **ha);

void insert(Hash **ha, int num, char* name) {
  int index = hashing(*ha, num);
  Node *element = malloc(sizeof(Node));
  Pessoa pessoa;

  pessoa.matricula = num;
  strcpy(pessoa.nome, name);

  element->next = NULL;
  element->pessoa = pessoa;

  if (!(*ha)->itens[index]) {
    (*ha)->itens[index] = element;
  } else {
    Node *aux = (*ha)->itens[index];
    while (aux && aux->next) {
      aux = aux->next;
    }
    aux->next = element;
  }
  (*ha)->quantidade++;
  
  if (validateSizeMaxHash(*ha)) {
    rehashing(&*ha);
  }
}

void rehashing(Hash **ha) {
  int size = (*ha)->tamanho * 2;
  Hash *newHash = malloc(sizeof(Hash));
  Hash *aux;
  Node *element;

  createHash(&newHash, size);

  for (int i = 0; i < (*ha)->tamanho; i++) {
    element = (*ha)->itens[i];
    while (element) {
      insert(&newHash, element->pessoa.matricula, element->pessoa.nome);
      element = element->next;
    }
  }
  aux = *ha;
  *ha = newHash;
  free(aux);
}

void remover(Hash **ha, int key){
  int index = hashing(*ha, key);
  Node *element = (*ha)->itens[index];
  Node* previous = NULL;
  while(element && element->pessoa.matricula != key){
    previous = element;
    element = element->next;
  }
  if(element){
    if(element == (*ha)->itens[index]){
      (*ha)->itens[index] = element->next;
    }
    else if(element->next){
      previous->next = element->next;
    }
    else{
      previous->next = NULL;
    }
    char name[50];
    strcpy(name,element->pessoa.nome);
    printf("%s removed!\n", name);
    free(element);
    (*ha)->quantidade--;
  }
  else{
    printf("Matrícula not found!\n");
  }
}

void print(Hash **ha){
  Node *element;
  for (int i = 0; i < (*ha)->tamanho; i++) {
    element = (*ha)->itens[i];
    while (element) {
      printf("Matrícula: %d Name: %s\n",element->pessoa.matricula, element->pessoa.nome);
      element = element->next;
    }
  }
}

void search(Hash **ha, int key){
  int index = hashing(*ha, key);
  Node *element = (*ha)->itens[index];
  while(element && element->pessoa.matricula != key){
    element = element->next;
  }
  printf("Name: %s\n", element->pessoa.nome);
}

int main(void) {
  Hash *ha = malloc(sizeof(Hash));
  createHash(&ha, 10);
  int option, matricula;
  char name[50];
  do{
    printf("-----HASH TABLE-----\n");
    printf("1 - Insert\n");
    printf("2 - Remove\n");
    printf("3 - Search\n");
    printf("4 - Print all elements\n");
    printf("5 - Exit\n");
    printf("--------------------\n");
    printf("Option: ");
    scanf("%d", &option);
    setbuf(stdin, NULL);
    
    switch(option){
      case 1:
        printf("Name: ");
        scanf("%[^\n]", name);
        setbuf(stdin, NULL);
        printf("Matricula: ");
        scanf("%d", &matricula);
        setbuf(stdin, NULL);
        insert(&ha, matricula, name);
        break;
      case 2:
        printf("Matricula: ");
        scanf("%d", &matricula);
        setbuf(stdin, NULL);
        remover(&ha, matricula);
        break;
      case 3:
        printf("Matricula: ");
        scanf("%d", &matricula);
        setbuf(stdin, NULL);
        search(&ha, matricula);
        break;
      case 4:
        print(&ha);
        break;
      case 5:
        exit(0);
      default:
        printf("Invalid option!\n");
    }
  }while(1);
  return 0;
}