#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int num;
  int charge;
  struct No *dad;
  struct No *left;
  struct No *right;
} No;

typedef struct Tree {
  No *root;
  int size;
} Tree;

void in_ordem(No *No, int v[], int b[], int *index) {
  if (No) {
    in_ordem(No->left, v, b, index);
    v[*index] = No->num;
    b[*index] = No->charge;
    (*index)++;
    in_ordem(No->right, v, b, index);
  }
}

void printTree(Tree *T) {
  int v[T->size];
  int b[T->size];
  int index = 0;
  in_ordem(T->root, v, b, &index);
  for (int i = 0; i < T->size; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
  for (int i = 0; i < T->size; i++) {
    if (b[i] < 0) {
      printf("%d ", b[i]);
    } else if (v[i] >= 10) {
      printf("%d  ", b[i]);
    } else
      printf("%d ", b[i]);
  }
  printf("\n");
}

void simple_right_rotation(No *dad, Tree *T) {
  No *son = dad->left;
  if (!(dad)->dad) {
    (T)->root = son;
    son->dad = NULL;
  } else if (dad->dad->left == dad) {
    dad->dad->left = son;
  } else {
    dad->dad->right = son;
  }
  // Fator carga
  dad->charge = 0;
  if (!son->right) {
    if (dad->right && son->charge == -1) {
      son->charge = +1;
    } else {
      son->charge = 0;
    }
    if (dad->right) {
      dad->charge++;
    }
  } else {
    if (!dad->right && son->charge == 0) {
      dad->charge--;
    }
    if (dad->right && son->right && son->charge == -2) {
      son->charge = 0;
      dad->charge--;
    } else {
      son->charge++;
    }
  }
  // Troca de pais
  son->dad = dad->dad;
  dad->dad = son;
  if (son->right) {
    son->right->dad = dad;
  }
  // Troca de lados
  dad->left = son->right;
  son->right = dad;

}
void simples_left_rotation(No *dad, Tree *T) {
  No *son = dad->right;
  if (!(dad)->dad) {
    (T)->root = son;
    son->dad = NULL;
  } else if (dad->dad->left == dad) {
    dad->dad->left = son;
  } else {
    dad->dad->right = son;
  }
  // Fator carga
  dad->charge = 0;
  if (!son->left) {
    if (dad->left && son->charge == +1) {
      son->charge = -1;
    } else {
      son->charge = 0;
    }
    if (dad->left) {
      dad->charge--;
    }
  } else {
    if (!dad->left && son->charge == 0) {
      dad->charge++;
    }
    if (dad->left && son->left && son->charge == 2) {
      son->charge = 0;
      dad->charge--;
    } else {
      son->charge--;
    }
  }
  // Troca de pais
  son->dad = dad->dad;
  dad->dad = son;
  if (son->left) {
    son->left->dad = dad;
  }
  // Troca de lados
  dad->right = son->left;
  son->left = dad;

  printf("--L--\n");
  printTree(T);
  printf("--L--\n");
}

void balacing(No **dad, Tree *T) {
  if ((*dad)->charge == -2 && (*dad)->left->charge <= 0) {
    simple_right_rotation(*dad, T);
  } else if ((*dad)->charge == 2 && (*dad)->right->charge >= 0) {
    simples_left_rotation(*dad, T);
  } else if ((*dad)->charge == 2 && (*dad)->right->charge <= 0) {
    simple_right_rotation((*dad)->right, T);
    simples_left_rotation((*dad), T);
  } else if ((*dad)->charge == -2 && (*dad)->left->charge >= 0) {
    simples_left_rotation((*dad)->left, T);
    simple_right_rotation((*dad), T);
  }
}

void loadFactorInsert(No **element, Tree *T) {
  No *aux = *element;
  do {
    if (aux->dad->left == aux) {
      aux->dad->charge--;
    } else {
      aux->dad->charge++;
    }
    aux = aux->dad;
  } while (aux && aux->dad && aux->charge % 2 != 0);

  if (abs(aux->charge) == 2) {
    printTree(T);
    balacing(&aux, T);
    printTree(T);
  }
}

void loadFactorDelete(No **element, Tree *T) {
  No *aux = *element;
  No *previous = NULL;
  do {
    previous = aux;
    if (aux->dad->left == aux) { /////////////////
      aux->charge--;             // TRABALHAR NISSO AMANHA
    } else {
      aux->charge++;
    }
    aux = aux->dad;
  } while (aux && previous->charge == 0);
  if (abs(previous->charge) == 2) {
    printTree(T);
    balacing(&previous, T);
    printTree(T);
  }
}

void add(Tree **T, int i) {
  No *element = malloc(sizeof(No));
  element->num = i;
  element->right = NULL;
  element->left = NULL;
  element->dad = NULL;
  element->charge = 0;
  if (!(*T)->root) {
    (*T)->root = element;
    (*T)->size++;
  } else {
    No *aux = (*T)->root;
    No *previous = NULL;
    while (aux) {
      previous = aux;
      if (aux->num >= i) {
        aux = aux->left;
      } else {
        aux = aux->right;
      }
    }
    element->dad = previous;
    if (previous->num >= i) {
      previous->left = element;
    } else {
      previous->right = element;
    }
    (*T)->size++;
    loadFactorInsert(&element, *T);
  }
}

No *searchNo(Tree *T, int key) {
  No *element = T->root;
  while (element && element->num != key) {
    if (key > element->num) {
      element = element->right;
    } else {
      element = element->left;
    }
  }
  if (!element) {
    return element;
  }
  return element;
}

void delete (Tree **T, int key) {
  No *element = searchNo(*T, key);
  No *auxLoad = NULL;
  if (element) {
    No *aux = element->left;
    while (aux && aux->right) {
      aux = aux->right;
    }
    if (!aux && element->right) {
      aux = element->right;
    } else if (element->dad) {
      auxLoad = element->dad;
    }

    if (!element->dad) {
      (*T)->root = aux;
    } // Alterando a raiz da arvore

    if (aux) {
      auxLoad = aux->dad;
      if (aux && aux->dad && aux->dad->right && aux->dad->right == aux) {
        aux->dad->right = NULL;
      }
      if (aux) {
        aux->dad = element->dad;
      }

      if (element->right && element->right != aux) {
        aux->right = element->right;
        element->right->dad = aux;
      }

      if (element->left && element->left != aux) {
        aux->left = element->left;
        element->left->dad = aux;
      }
    }
    if (element->dad && element->dad->right == element) {
      element->dad->right = aux;
    } else if (element->dad) {
      element->dad->left = aux;
    }

    if (auxLoad) {
      loadFactorDelete(&auxLoad, *T);
    } // TEM PROBLEMAS NESSE FATOR EM ALGUNS CASOS AINDA..
    free(element);
    (*T)->size--;
  } else {
    printf("Elemento não encontrado para ser removido!\n");
  }
}

int main() {
  Tree *arv = malloc(sizeof(Tree));
  arv->root = NULL;
  arv->size = 0;

  add(&arv, 1);
  add(&arv, 2);
  add(&arv, 3);
  add(&arv, 4);
  add(&arv, 5);
  add(&arv, 6);
  add(&arv, 7);
  add(&arv, 8);
  add(&arv, 10);
  add(&arv, 15);
  add(&arv, 16);
  add(&arv, 17);
  add(&arv, 18);
  add(&arv, 20);
  add(&arv, 30);
  add(&arv, 29);
  add(&arv, 28);
  add(&arv, 27);
  add(&arv, 9);
  add(&arv, 12);
  add(&arv, 11);
  add(&arv, 14);
  add(&arv, 13);
  printTree(arv);
  delete (&arv, 6);
  printf("Depois do delete\n");
  printTree(arv);
  delete (&arv, 5);
  printf("Depois do delete2\n");
  printTree(arv);
  delete (&arv, 3);
  printf("Depois do delete2\n");
  printTree(arv);
  delete (&arv, 2);
  printf("Depois do delete2\n");
  printTree(arv);
  return 0;
}
