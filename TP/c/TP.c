#include <stdio.h>
#include <string.h>
#define MAX 10
#define MAXI 1000


typedef struct {
    double taille,poids;
    int age;
    char cp[6];
} Personne;

//Exo 1

Personne saisie_p(){
    Personne p;
    printf("donne, dans l'ordre, la taille en cm, le poids en kg, l'age et le code postal d'une personne\n");
    scanf("%lf%lf%d%s",&p.taille,&p.poids,&p.age,&p.cp);
    return p;
}

//Exo 2

void saisie_p2(Personne *p){
    printf("donne, dans l'ordre, la taille en cm, le poids en kg, l'age et le code postal d'une personne\n");
    scanf("%lf%lf%d%s",&(p->taille),&(p->poids),&(p->age),&(p->cp));
}

//Exo 3

void affiche_p(Personne p){
    printf("Taille: %lf, Poids: %lf, Age: %d, Code Postal: %s\n", p.taille, p.poids, p.age, p.cp);
}

//Exo 4

int plus_grand(Personne *p1,Personne *p2){
   printf("pour la premiere personne, ");
   saisie_p2(p1);
   printf("pour la seconde personne, ");
   saisie_p2(p2);
   double a = p1->taille, b = p2->taille;
   if (a>b){
    printf("1");
    return 1;}
   else if (a<b) {
    printf("-1");
    return -1;}
   else {
    printf("0");
    return 0;}
   // je suis passé par int plus_grand(Personne *p1, Personne *p2) car on lis la valeur via le pointeur, et on peut donc modifier celle ci
}

//Exo 6

int saisie_tp(Personne t[MAX], int n){
        if(n>MAX){
            printf("nt");
            return -1;
        }
        else{
        for(int k=0;k<n;++k){
        t[k] = saisie_p();
        }
        }
    return n;
}

//Exo 7

double taille_moy(Personne t[MAX], int n){
    saisie_tp(t,n);
    double tot = 0;
    for(int k =0;k<n;++k){
        tot = tot + t[k].taille;

    }
    tot /=n;
    printf("Le poids moyen est de %lf",tot);
    return tot;
}

//Exo 9

int chargement(Personne t[MAXI], char nom_fichier[50]){
    FILE *f;
    int a =0;
    f = fopen(nom_fichier, "r");
    if (f == NULL){
        return -1;
    }
    int n;
    if (fscanf(f,"%d",&n) != 1){return -1;}
    if (n>MAXI) {return -1;}
    
    for(int k =0; k<n;k++){
        fscanf(f,"%s%d%lf%lf",&t[k].cp, &t[k].age, &t[k].taille, &t[k].poids);
        a = k+1;
    }
    fclose(f);
    return a;
}

//Exo 10

int trouve(Personne t[MAX],int n, char cp[50]){
    int compteur =0;
    
    char test[50] = "test.txt"; 
    chargement(t,test);
    for(int i =0; i<n;i++){
        if (strcmp(t[i].cp,cp)==0){
            compteur +=1;}
    }
    printf("Il y a %d personne(s) qui ont ce code postal",compteur);
    return compteur;
}

//Exo 11

int tri(Personne t[MAXI],int n,int *p){
    char test[100] = "test.txt"; 
    chargement(t,test);
    
    int permutation = 1;

    while(permutation == 1){
        int iter = 0;
        Personne tampon;
        int compteur =0;
        p = &compteur;
        permutation = 0;
        for(int i = 0;i < n-1; i++){
            
            if (t[i].age>t[i+1].age) {
               permutation = 1;   
               tampon = t[i+1];
               ;   
               t[i+1] = t[i];
                 
               t[i] = tampon;
               
               *p = *p + 1;
            }
            else if(t[i].age == t[i+1].age){
                if(t[i].poids < t[i+1].poids){
                    tampon = t[i+1];
                    t[i] = t[i+1];
                    t[i+1] = tampon;
                    *p = *p + 1;
                    permutation = 1;

                }
                else if (t[i].poids == t[i+1].poids) {
                    if (t[i].taille > t[i+1].taille){
                    tampon = t[i+1];
                    t[i] = t[i+1];
                    t[i+1] = tampon;
                    *p = *p + 1;
                    permutation = 1;

                }
                else if (t[i].taille == t[i+1].taille){
                if(strcmp(t[i].cp,t[i+1].cp) >= 1){
                    tampon = t[i+1];
                    t[i] = t[i+1];
                    t[i+1] = tampon;
                    *p = *p + 1;
                    permutation = 1;

                }
            }
          }
        }
        
      } 
      
      

    }    
    return *p;
}

//Exo 12

int direction(Personne *p1,Personne *p2){
    int compteur = 0;
    
    if(p1->age == p2->age && p1->poids ==p2->poids && p1->taille == p2->taille && strcmp(p1->cp,p2->cp)) {return 0;}
    if(p1->age > p2->age){compteur +=1;}
    if(p1->age < p2->age){compteur -=1;}
    if(p1->taille < p2->taille){compteur +=1;}
    if(p1->taille > p2->taille){compteur -=1;}
    if(p1->poids > p2->poids){compteur +=1;}
    if(p1->poids < p2->poids){compteur -=1;}
    if(strcmp(p1->cp,p2->cp)>=1){compteur +=1;}
    if(strcmp(p1->cp,p2->cp)<=-1){compteur -=1;}    
    if(compteur >0){return 1;}
    return-1;
} 

//Exo 13

int trouve_p2(Personne t[MAXI],int n, Personne *p, int *inter){
    int m = 0;
    tri(t,n,&m);
    int zone_rch = n/2;
    int tampon;
    int compteur =0;
    int borne_inf = 0;
    int borne_sup = n;
    printf("Saisissez les info de la personne recherche");
    saisie_p2(p);
    while (compteur<n/2){
        tampon = t[zone_rch].age;
        if(tampon < p->age){ 
            borne_sup = zone_rch;
            zone_rch = (borne_inf+zone_rch)/2;
            }
        else if (tampon > p->age){
            borne_inf = zone_rch;
            zone_rch = (borne_sup+zone_rch)/2;
        }
        else if (p->taille == t[zone_rch].taille && p->poids==t[zone_rch].poids && strcmp(p->cp,t[zone_rch].cp)){
            return 1;
        }
        
    }
    return -1;
}

//Exo 14

typedef struct {
    int n;
    double stat[7][MAXI];
    int nc[7];
    double imcc[7];
} IMC ;




void remplie_stat(Personne t[MAXI], int n, IMC *I){
    char test[100] = "test.txt";
    chargement(t,test); 
    if(n> chargement(t,test)){
        n = chargement(t,test);
        printf("Tu as voulu evaluer plus de\npersonne que ce qu'il y avait dans\n le tableau, j'ai donc\nchange ta requete\n");
    }
    double IMC;
    I->n = n;
    for(int i =0 ; i<7 ; i++){   
        I->nc[i] = 0;
        I->imcc[i] = 0.0;
        I->stat[i][0] = 0;
        
    }
    for(int k = 0;  k < n ; k++ ){

        IMC = t[k].poids / (t[k].taille * t[k].taille); 
        
        if (t[k].age >= 70){ 
            I->stat[6][I->nc[6]] = IMC;
            I->nc[6]++;
        }
        else if (t[k].age >= 60 && t[k].age < 70){ 
            I->stat[5][I->nc[5]] = IMC;
            I->nc[5]++;
        }
         else if (t[k].age >= 50 && t[k].age < 60){ 
            I->stat[4][I->nc[4]] = IMC;
            I->nc[4]++;
        }
         else if (t[k].age >= 40 && t[k].age < 50){ 
            I->stat[3][I->nc[3]] = IMC;
            I->nc[3]++;
        }
         else if (t[k].age >= 30 && t[k].age < 40){ 
            I->stat[2][I->nc[2]] = IMC;
            I->nc[2]++;
        }
         else if (t[k].age >= 20 && t[k].age < 30){ 
            I->stat[1][I->nc[1]] = IMC;
            I->nc[1]++;
        }
         else if (t[k].age >= 18 && t[k].age < 20){ 
            I->stat[0][I->nc[0]] = IMC;
            I->nc[0]++;
        }

    }


}


//Exo 15 

void affiche_stat(IMC *I){
    
    double Moyenne[7] ;
    for(int k = 0; k < 7; k++ ){
        for(int i = 0; i < I->nc[k]; i++){
            Moyenne[k] = Moyenne[k] + I->stat[k][i];
            
        }
        if(I->nc[k] == 0){
            Moyenne[k] = 0;
        }
        else {
        Moyenne[k] = Moyenne[k] / I->nc[k];
        }

    }
    printf("[18 - 20[: %d %lf\n", I->nc[0], Moyenne[0]);
    printf("[20 - 30[: %d %lf\n", I->nc[1], Moyenne[1]);
    printf("[30 - 40[: %d %lf\n", I->nc[2], Moyenne[2]);
    printf("[40 - 50[: %d %lf\n", I->nc[3], Moyenne[3]);
    printf("[50 - 60[: %d %lf\n", I->nc[4], Moyenne[4]);
    printf("[60 - 70[: %d %lf\n", I->nc[5], Moyenne[5]);
    printf("[70 - [: %d %lf", I->nc[6], Moyenne[6]);
}

int main(){
    /*Personne p1;
    Personne p2;
    saisie_p();
    plus_grand(&p1,&p2);
    return 0;
   
   int n;
   printf("Chosi un n");
   scanf("%d",&n);
   Personne t[MAX];
   taille_moy(t, n);
   
    int p =  0;
    Personne t[MAXI];
    char test[50] = "test.txt";    
    char cp[6] = "59000";
    tri(t,4,&p);
    
   Personne t[MAXI];
   int *p = 0;
   tri(t,5,p);
    
    */
   Personne t[MAXI];
   IMC I;
   int n = 0;
   printf("Choisissez un nb de personnes a evaluer pour l'IMC\n");
   scanf("%d", &n);
   remplie_stat(t,n,&I);
   affiche_stat(&I);
    
}

