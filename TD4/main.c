#include <stdio.h>
#define MAX 10
//Exo 1

void exo(char s[]){
    int i,t;
    //Ici on a l'adresse du tableau , donc sizeof(s) = taille du POINTEUR, et ça dépend, kek
    t = sizeof(s)/sizeof(s[0]);
    printf("%d\n",t);
    for(i = 0; i<t; ++i){
        printf("%c ", s[i]);
    }
}

void affiche(double t[MAX], int n){
    double *p = t+n;
    for(; t != p ; t++){
        printf("[%p %lf]",t,*t );
    }
}


// EXO 3
// Q1 : plante
// 
// Q2 : On veut return l'adresse de la variable a mais la valeur est reset (donc l'emplacement de a sera vide)
// 
// Q3 bah la ça marche



//Exo 4 


int main()
{
    /*int t;
    char s[4] = {'a','b', 'c', 'd'};
    t = sizeof(s)/sizeof(s[0]);
    printf("%d\n", t);
    exo(s);*/
    double t[MAX] = {5.3, 4,6,8,45.9};
    affiche(t,4);

    return 0;
}
