#include <stdio.h>
int MAX = 10;
typedef struct {
    double taille, poids ;
    int age;
    char cp[6];
} Personne;

Personne saisie_p(){
    Personne p;
    printf("Taille ? \nPoids ? \nAge ? \nCode Postal ? \n");
    scanf("%lf%lf%d%s",&p.taille,&p.poids,&p.age,&p.cp);
    return p; 
}
void saisie_p2(Personne *p){
    printf("Taille ? \nPoids ? \nAge ? \nCode Postal ? \n");
    scanf("%lf%lf%d%s",&(p->taille),&(p->poids),&(p->age),p->cp);
}
void affiche_p(Personne p){
    printf("Taille: %lf, Poids: %lf, Age: %d, Code Postal: %s\n", p.taille, p.poids, p.age, p.cp); 
}
int plus_grand(Personne *p1,Personne *p2){

    saisie_p2(p1);
    saisie_p2(p2);
    double a = p1->taille, b = p2->taille;
    if (a>b){printf("%lf > %lf", a,b); return 1;}
    else if (a<b){printf("%lf < %lf", a,b); return -1;}
    else {printf("%lf = %lf", a,b); return 0;}
}
int main(){
    Personne p1;
    Personne p2;
    plus_grand(&p1,&p2);   

    saisie_tp(t,n);
    taille_moy(t,n);
    return 0;
}



int saisie_tp(Personne t[MAX],int n){
    if(n<MAX){
    for (int i =0 ;i <n; ++i){
        t[i] = saisie_p();
     }
    }
    else {
        printf("n est trop grand, du coup ton n vaudra %d me fait pas chier",MAX);     
    }
    return 0;
}

double taille_moy(Personne t[max], int n){
    saisie_tp(t ,n);*
    int tot_taile = 0;
    for(int i=0;i<n;i++){
        tot_taille = tot_taille + t[i].taille;
    }
    tot_taille = tot_taille/n;
}

