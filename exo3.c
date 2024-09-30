#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int val;
    struct node* left;
    struct node* right;
} node;

typedef struct node* tree;


node *create_pnode(int val){
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}


//Fonction d'insertion dans l'ABR
void insert(tree *pt, int val){
    if(*pt == NULL){
        *pt = create_pnode(val);
        return;
    }
    tree t = *pt;
    if(val == t->val){
        //Si la valeur est déjà dans l'arbre, on rajoute la même valeur dans le sous arbre gauche du noeud *t
        tree aux = t->left;
        t->left = create_pnode(val);
        t->left->left = aux;
        return;
    }
    if(val < t->val){
        //On insérer dans l'arbre de gauche
        insert(&(t->left), val);
    }else{
        //on insère dans l'arbre de droite
        insert(&(t->right), val);
    }
}


//Fonction qui permet de vérifier si une valeur est dans l'ABR
bool contains(tree t, int val){
    if(t==NULL){
        return false;
    }
    if(t->val == val){
        return true;
    }
    if(t->val > val){
        return contains(t->left, val);
    }
    if(t->val < val){
        return contains(t->right, val);
    }
    return false;
}


//Deux fonctions qui permettent l'affichage d'un arbre
void show_tree_a(tree t){
    if(t==NULL){
        return;
    }
    show_tree_a(t->left);
    printf("%d\n", t->val);
    show_tree_a(t->right);

}

void show_tree(tree t){
    printf("-----------\n");
    show_tree_a(t);
    printf("-----------\n");
}


int main(void){
    tree t = NULL;    
    insert(&t, 5);
    insert(&t, 10);
    insert(&t, 8);
    show_tree(t);//montre l'arbre avec un parcours infixe (donc liste triée des élements de l'arbre)
    printf("%d", contains(t, 2)); //le premier n'est pas trouvé
    printf("%d", contains(t, 5)); //ceux d'après si 
    printf("%d", contains(t, 8));
    return 0;
}