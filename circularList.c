#include <stdio.h>
#include <stdlib.h>


typedef struct node{
  int numero;
  struct node* next;
}Node;

void add (Node **head,Node **last,int n){
  Node *element = malloc(sizeof(Node));
  element->numero = n;
  if (*head == NULL) {
    *head = element;
  }
  else {
    Node *aux = *head;
    while(aux->next != *head){
      aux = aux->next;
    }
    aux->next = element;
  }
  element->next=*head;
  
}

int main() {
  Node *head = NULL;
  Node *last = NULL;//Fazendo lista cirular, NÃO USAR.
  add(&head,&last,10);
  add(&head,&last,20);
  add(&head,&last,30);
  add(&head,&last,40);
  
  return 0;
}