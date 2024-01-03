#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Fila{
    char nome[20];
    struct Fila *next;
}Fila;

void add(Fila **head,Fila **last,char nome[]){
    Fila *element = malloc(sizeof(Fila));
    strcpy(element->nome,nome);
    if (*head == NULL) {
        element->next = *head;
        *head = element;
    }
    else{
        (*last)->next = element;
    }
    *last = element;
}

void remov(Fila **head){
    if (*head == NULL) {
        printf("Lista vazia!\n");
    }
    else{
        Fila *aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}


void show(Fila **head){
    if (*head == NULL) {
        printf("Lista vazia!\n");
    }
    else{
        printf("\n%s\n\n",(*head)->nome);
    }
}


int main() {
    Fila *head = NULL;
    Fila *last = NULL;
    char string[20];
    int opcao = 0;
    while (opcao != 4){
        printf("Digite a opção desejada\n[1]=Adcionar\n[2]=Remover\n[3]=Exibir\n[4]=Sair\nOpção: ");
        scanf("%d",&opcao);

        switch (opcao){
        case 1:
            printf("Digite o nome de quem você quer adcionar a fila:\n");
            scanf("%s",&string);
            add(&head,&last,string);
            break;
        case 2:
            printf("Removendo...\n");
            remov(&head);
            break;
        case 3:
            show(&head);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Vocẽ digitou uma opção invalida\n");
        }
    }
    
    return 0;
}


