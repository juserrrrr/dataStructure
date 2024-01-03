#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilha{
    char nome[15];
    struct Pilha *down;
}Pilha;



void remove_p(Pilha **topo){
    if (*topo == NULL) {
        printf("Pilha vazia!!!\n");
    }
    else {
        Pilha *aux = *topo;
        *topo = (*topo)->down;
        free(aux);
    }
}

void add(Pilha **topo,char nome[]){
    Pilha *element = malloc(sizeof(Pilha));
    strcpy(element->nome,nome);
    element->down = *topo;
    *topo = element;
}

void viewTop(Pilha **topo){
    printf("%s\n",(*topo)->nome);
}


int main() {
    char nome[15];
    int opcao;
    Pilha *topo = NULL;
    while (opcao != 4){
        printf("Digite a opção [1] - Add [2] - Show [3] - Remove [4] - Sair\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("Digite o nome a ser add.\n");
                scanf("%s",nome);
                add(&topo,nome);
            break;
            case 2:
                printf("Topo:\n");
                viewTop(&topo);
            break;
            case 3:
                printf("Removendo...:\n");
                remove_p(&topo);
            break;
            case 4:
                printf("Saindo...");
            break;
            default:
                printf("Você digitou uma opção invalida!\n");
        }
    }
    return 0;
}