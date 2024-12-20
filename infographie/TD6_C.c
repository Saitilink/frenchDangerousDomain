#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Exo 1

void saisie(int *a,int *b,int *c,int *d){
    printf("Donnez moi 4 valeurs entières\n");
    scanf("%d%d%d%d",a,b,c,d);
}

void pointage(int *t[4],int *a,int *b, int *c,int *d){
    t[0] = a;   
    t[1] = b;
    t[2] = c;
    t[3] = d;
}

typedef struct Livre Livre;
struct Livre{
    long id;
    char *titre;
    double prix; 
} ;

void init(Livre *l){
    char temp[128];
    char t;
    printf("Titre du livre ? ");
    fgets(temp,128,stdin);
    printf("Id du livre ? ");
    scanf("%ld", &(l->id));
    printf("Prix ? ");
    scanf("%f",&(l->prix));
    scanf("%c",&t); // On recup l'\n laissé dans le buffer
    l->titre = (char*)malloc(sizeof(char)*128);
    if(l->titre != NULL){
        strcpy(l->titre,temp);
    }
}

Livre *alloue(int n){
    int i;
    Livre *t = NULL;
    t = (Livre *)malloc(n*sizeof(Livre));
    if(t != NULL){
        for(i = 0;i<n;i++){
            init(&t[i]);
        }
    }
    return t;
}

void libere(Livre *t,int n){
    int i;
    for(i =0;i<n;i++){
        free(t[i].titre);
    }
    free(t);
}

typedef struct cell{
    double v;
    struct cell *suiv;
} Cellule ;

int combien(Cellule *l){
    int compteur =0;
    while(l->suiv !=NULL){
        compteur++;
        l = l->suiv;
    }
    return compteur;
}

Cellule *ajout(Cellule *l, double v){
    Cellule *temp = malloc(sizeof(*temp));
    temp->v = v;
    temp->suiv = NULL;
}





int main()
{
   /* int a,b,c,d;
    int *t[4] = {NULL,NULL,NULL,NULL};
    saisie(&a,&b,&c,&d);
    pointage(t,&a,&b,&c,&d);
    printf("[%p %d %p %d]",&a,a,t[0],*t[0]);
    */
    Livre l;
    init(&l);
    init(&l);
    return 0;
}
