#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
  int nb_etats;
  int nb_lettres;
  bool* initial;
  bool* final;
  int*** delta;
} automate;

automate *random_auto(int nb_e,int nb_l){
  automate *pa = (automate *)malloc(sizeof(automate));
  pa->nb_etats = nb_e;
  pa->nb_lettres = nb_l;
  pa->initial = (bool *)malloc(nb_e * sizeof(bool));
  pa->final = (bool *)malloc(nb_e * sizeof(bool));
  for(int i =0; i < pa->nb_etats; i++){
    if(rand()%100 > 75){
      pa->initial[i] = true;
    }else{
      pa->initial[i] = false;
    }

    if(rand()%100 > 75){
      pa->final[i] = true;
    }else{
      pa->final[i] = false;
    }
  }

  pa->delta = (int ***)malloc(pa->nb_etats * sizeof(int **));
  
  for(int i = 0; i < pa->nb_etats; i ++){
    pa->delta[i] = (int **)malloc(pa->nb_lettres * sizeof(int *));
    for(int j=0; j < pa->nb_lettres; j++){
      int nbr_next = rand()%(pa->nb_etats);
      bool is_next[pa->nb_etats];
      int n_next = 0;
      for(int k = 0; k < pa->nb_etats; k++){
	if(rand()%100>90){
	  n_next = n_next+1;
	  //printf("%d lit %d, j'ajoute %d\n", i, j, k);
	  is_next[k] = true;
	}else{
	  is_next[k] = false;
	}
	
      }
      /*printf("next %d\n", n_next);*/
      pa->delta[i][j] = (int *) malloc((n_next+1) * sizeof(int));
      int init_next = 1;
      pa->delta[i][j][0] = n_next;
      for(int k=0; k < pa->nb_etats; k++){/*on fait tous les états; si il y en a un on l'ajoute*/
	if(is_next[k]){
	  pa->delta[i][j][init_next] = k;
	  init_next ++;
	}
      }
    }
  }
  
  return pa;
			   
}

void show_auto(automate a){
  printf("%d etats\n", a.nb_etats);
  printf("%d lettres\n", a.nb_lettres);
  printf("états initiaux\n");
  for(int i = 0; i < a.nb_etats;i ++){
    if(a.initial[i]){
      printf("%d ",i);
    }
  }
  printf("\n");
  printf("états finaux\n");
  
  for(int i = 0; i < a.nb_etats;i ++){
    if(a.final[i]){
      printf("%d ",i);
    }
  }
  printf("\n");

  for(int i =0; i<a.nb_etats; i++){
    for(int j=0; j < a.nb_lettres; j++){
      //printf("à lire : %d", a.delta[i][j][0]);
      printf("%d %d: ", i, j);
      for(int k=1; k < a.delta[i][j][0] +1; k++){
	printf("%d ", a.delta[i][j][k]);
      }
      printf("\n");
    }
  }
}

void show_current(bool *a, int n){
  for(int i = 0; i < n; i++){
    if(a[i]){
      printf("%d ", i);
    }
  }
  printf("\n");
}

void lire_lettre(automate a, int lettre, bool *current){
  bool next[a.nb_etats];
  for(int i = 0; i < a.nb_etats; i++){//init next to false
    next[i] = false; 
  }

  for(int i = 0; i < a.nb_etats; i++){ //update next with current
    if(current[i]){
      
      for(int j = 1; j < a.delta[i][lettre][0] + 1; j++){
	printf("%d lit la lettre %d et donne %d\n", i, lettre, a.delta[i][lettre][j]);
	next[a.delta[i][lettre][j]] = true;
      }
    }
  }
  for(int i = 0; i < a.nb_etats; i++){ //current = next
    current[i] = next[i];
  }
  //printf("show current\n");
  //show_current(next, a.nb_etats);
  //show_current(current, a.nb_etats);
  
   
}

bool intersection(bool *a, bool *b, int n){
  for(int i = 0; i < n; i++){
    if(a[i] && b[i]){
      return true;
    }
  }
  return false;
}
    

bool accepte(automate a, int *tab, int n){
  bool *current = (bool *)malloc(a.nb_etats * sizeof(bool));
  for(int i = 0; i < a.nb_etats; i++){
    current[i] = a.initial[i];
  }
  printf("init current\n");
  show_current(current, a.nb_etats);
  for(int i = 0; i < n; i++){
    int lettre = tab[i];
    lire_lettre(a, lettre, current);
    printf("current\n");
    show_current(current, a.nb_etats);
  }
  return intersection(current, a.final, a.nb_etats);
  
}

int *create_word(int n){
  int *w = (int *)malloc(n*sizeof(int));
  for(int i = 0; i < n;i++){
    w[i] = rand()%5;
  }
  return w;
}

void destroy_auto(automate *pa){
  free(pa->final);
  free(pa->initial);
  for(int i = 0; i < pa->nb_etats; i++){
    for(int j=0; j < pa->nb_lettres; j++){
      free(pa->delta[i][j]);
    }
    free(pa->delta[i]);
  }
  free(pa->delta);
  free(pa);
}

void print_word(int *w, int n){
  for(int i = 0; i < n; i++){
    printf("%d", w[i]);
  }
  printf("\n");
}

int main(void){
  srand(time(NULL));
  automate *pa = random_auto(10, 5);
  show_auto(*pa);
  int *w = create_word(4);
  printf("accepte %d\n", (int) accepte(*pa, w, 4));

  printf("le mot a lire est ");
  print_word(w, 4);
  
  free(w);
  destroy_auto(pa);
  return 0;
}
