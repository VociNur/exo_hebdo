#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct noeud {
  int a;
  int b;
  struct noeud* suiv;
} noeud;

typedef noeud* liste;

liste creer_liste(int **aretes, int m){
  liste l = NULL;
  for(int i = 0; i < m; i++){
    noeud* pn = (noeud*) malloc(sizeof(noeud));
    pn->a = aretes[i][0];
    pn->b = aretes[i][1];
    pn->suiv = l;
    l = pn;
  }
  return l;
}

void filtrer_liste(liste* pl, int a, int b){
  while(*pl != NULL){
    
    if((*pl)->a == a || (*pl)->a == b || (*pl)->b == a || (*pl)->b == b){
      liste aux = ((*pl)->suiv);
      free(*pl);
      *pl = aux;
    }else{
      pl=&((*pl)->suiv);
    }
  }
}

void free_liste(liste pl){
  while(pl != NULL){
    liste aux = pl->suiv;
    free(pl);
    pl = aux;
  }
}

void afficher_liste(liste l){
  while(l!= NULL){
    printf("%d lié à %d\n", l->a, l->b);
    l = l->suiv;
  }
}

bool est_vide_liste(liste l){
  return l==NULL;
}



void test_liste(int **aretes, int m){
  liste l = creer_liste(aretes, m);
  afficher_liste(l);
  filtrer_liste(&l, 3, 9);
  printf("test2\n");
  afficher_liste(l);
  printf("%d\n", est_vide_liste(l));
  free_liste(l);
}


int *approximation(int n, int **aretes, int m, int *nbr_sommets_pris){
  //aretes donnée sous liste d'aretes (liste de couple (a, b) )
  //n le nombre de sommets
  //m le nombre d'arêtes
  //on en fait une liste chainée, pour filtrer plus efficacement
  *nbr_sommets_pris = 0;
  int *sommets_pris = (int *)malloc(n * sizeof(int));
  
  liste l = creer_liste(aretes, m);

  while(!est_vide_liste(l)){
    int a = l->a;
    int b = l->b;
    l = l->suiv;
    filtrer_liste(&l, a, b);

    //printf("rajout\n");
    sommets_pris[*nbr_sommets_pris] = a;
    *nbr_sommets_pris = *nbr_sommets_pris +1;
    sommets_pris[*nbr_sommets_pris] = b;
    *nbr_sommets_pris = *nbr_sommets_pris +1;
    
  }
  
  free_liste(l);
  return sommets_pris;
}


int main(void){
  int n = 10;
  int m = 5;
  int **aretes = (int **)malloc(m * sizeof(int *));
  for(int i = 0; i < m; i++){
    aretes[i] = (int *)malloc(2 * sizeof(int));
  }

  aretes[0][0] = 1;
  aretes[0][1] = 2;
  aretes[1][0] = 3;
  aretes[1][1] = 4;
  aretes[2][0] = 1;
  aretes[2][1] = 3;
  aretes[3][0] = 8;
  aretes[3][1] = 9;
  aretes[4][0] = 7;
  aretes[4][1] = 9;
  test_liste(aretes, m);
  int nbr_sommets_pris = 0;
  int *tab = approximation(n, aretes, m, &nbr_sommets_pris);

  printf("Rés[%d]: \n", nbr_sommets_pris);
  for(int i = 0; i < nbr_sommets_pris; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");

  free(tab);
  return 0;
}
   
