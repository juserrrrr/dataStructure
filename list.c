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


//=====================================

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// typedef struct Fila{
//     char numero;
//     struct Fila *next;
// }Fila;

// void add(Fila **head,Fila **last,int num){
//     Fila *element = malloc(sizeof(Fila));
//     element->numero = num;
//     element->next = NULL;
//     if (*head == NULL) {
//         *head = element;
//     }
//     else{
//         (*last)->next = element;
//     }
//     *last = element;
// }

// void remov(Fila **head){
//     if (*head == NULL) {
//         printf("Lista vazia!\n");
//     }
//     else{
//         Fila *aux = *head;
//         *head = (*head)->next;
//         free(aux);
//     }
// }

// void end(Fila **head,Fila **last){
//     Fila *aux = *head;
//     *head = (*head)->next;
//     (*last)->next = aux;
//     aux->next = NULL;
//     (*last) = aux;
// }


// void show(Fila **last){
//     if (*last == NULL) {
//         printf("Lista vazia!\n");
//     }
//     else{
//         printf("\n%d\n\n",(*last)->numero);
//     }
// }


// int main() {
//     Fila *head = NULL;
//     Fila *last = NULL;
//     char string[20];
//     int tamanho = 0;
//     scanf("%d",&tamanho);
//     for (int i = 1;i<=tamanho;i++){
//         add(&head,&last,i);
//     }
//     while (tamanho >= 2){
//         remov(&head);
//         end(&head,&last);
//         tamanho --;
//     }
//     show(&last);
        
//     return 0;
// }

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Fila{
    char numero;
    struct Fila *next;
}Fila;

void add(Fila **head,Fila **last,int num){
    Fila *element = malloc(sizeof(Fila));
    element->numero = num;
    element->next = NULL;
    if (*head == NULL) {
        *head = element;
    }
    else{
        (*last)->next = element;
    }
    *last = element;
}

int remov(Fila **head){
    if (*head == NULL) {
        printf("Lista vazia!\n");
    }
    else{
        Fila *aux = *head;
        int val_delete = aux->numero;
        *head = (*head)->next;
        free(aux);
        return val_delete;
    }
}

void end(Fila **head,Fila **last){
    Fila *aux = *head;
    *head = (*head)->next;
    (*last)->next = aux;
    aux->next = NULL;
    (*last) = aux;
}


void show(Fila **last){
    if (*last == NULL) {
        printf("Lista vazia!\n");
    }
    else{
        printf("\nRemaining card: %d\n",(*last)->numero);
    }
}


int main() {
    Fila *head = NULL;
    Fila *last = NULL;
    char string[20];
    int tamanho = 0;
    int valor_deletado = 0;
    scanf("%d",&tamanho);
    for (int i = 1;i<=tamanho;i++){
        add(&head,&last,i);
    }
    printf("Discarded cards:");
    while (tamanho >= 2){
        valor_deletado = remov(&head);
        tamanho --;
        
        if (tamanho > 1) {
            end(&head,&last);
            printf(" %d,",valor_deletado);
        }  
        else {
            printf(" %d",valor_deletado);
        }
    }
    show(&last);
        
    return 0;
}