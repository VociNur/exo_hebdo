#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

int max(int a, int b){
  return a<b?b:a;
}

void parcours(int **gt, bool* vu, int* degrees, int n, int s){
  if(s<0 || s > 2*n+1 || vu[s]){
    return;
  }
  printf("%d\n", s);
  vu[s] = true;
  for(int j=0; j<3;j++){
    int pere = gt[s][j];
    printf("pree %d\n", pere);
    /*on suppose le parcours pour l'attracteur de j2*/
    if(1<pere && pere<=n){
      degrees[pere] = degrees[pere] - 1;
      if(degrees[pere] ==0){
	parcours(gt, vu, degrees, n, pere);
      }
    }else{
      
    
      parcours(gt, vu, degrees, n, pere);
    }
  }

}

  
int main(void){
  int n;
  printf("Nombre d'allumettes\n");
  scanf("%d", &n);
  
  
  printf("%d\n", n);
  assert(n<1000); /*on évite les tableaux trop grand*/

  /*déjà faire le graphe transposé*/
  /*chaque sommet à au plus 3 «fils», on préfère donc une implémentation par liste d'adjacence*/
  

  /*on va donc faire un tableau 2n+2 cases de tableau de 3 cases -1 correspond à pas de fils*/
  /*découpé de 0 à n, puis de n+1 à 2n+1*/
   
  int **adj = (int **)malloc(2*(n+1)*sizeof(int *));
  for(int i = 0; i <= n; i++){
    adj[i] = (int *)malloc(3*sizeof(int));
    for(int j = 1; j < 4; j ++){
      if(i+j<=n){
	adj[i][j-1] = n+1+i+j; //dans le jeu, on peut se déplacer en n+i-j, c'est à dire jouer en retirant j allumette et donner le tour à l'adversaire, donc en remontant, on peut rajouter 1 à 3 arêtes
      }else{
	adj[i][j-1] = -1;
      }
    }
  }
  for(int i = 0; i <= n; i++){
    adj[i+n+1] = (int *)malloc(3*sizeof(int));
    for(int j = 1; j < 4; j ++){
      if(i+j<=n){
	adj[i+n+1][j-1] = i+j; 
      }else{
	adj[i+n+1][j-1] = -1;
      }
    }
  }

  for(int i = 0; i < 2*(n+1); i++){
    for(int j =0; j < 3; j++){
      printf("%d %d pere %d\n", i, j, adj[i][j]);
      
    }
  }
  //états gagnants: 0 : j2 a pris la dernière arête, j2 gagne
  //n: j1 l'a prise, j1 gagne

  

  //calcul de l'attracteur pour j2
  //degré dans l'arbre du jeu
  int *degrees = (int *)malloc((n+1)*sizeof(int));
  for(int i = 0; i <=n; i++){
    
    degrees[i] = i>=3?3:i;
  }
  bool* vu = (bool *)malloc(2*(n+1)*sizeof(bool));
  for(int i =0; i < 2*(n+1); i++){
    vu[i] = false;
  }

  //on part des états gagnants par j2 = 0
  parcours(adj, vu, degrees, n, 0);

  for(int i =0;i <2*(n+1); i++){
    printf("%d", vu[i]);

  }
  printf("\nRésultat:\n");
  /*on suppose que chaque position est gagnante pour un joueur*/
  for(int i =1;i < (n+1); i++){
    if(vu[i]){
      printf("nbr d'allumettes restantes: %d, J2 gagne\n", i);
    }
    else{
      printf("nbr d'allumettes restante: %d,  J1 gagne\n", i);
    }
  }
  return 0;
}
