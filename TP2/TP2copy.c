#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


// Menu Thomas ICY

typedef struct {
    short h, m;
    double s;
} Heure;

typedef struct {
    short j, m, a;
    Heure h;
} Date;

typedef struct {
    short j, m, a;
    short n;
    Heure *h;   
} Date2;



//Exo 1

int saisie_heure(Heure *h){
    printf("Indique l'heure actuelle\n");
    scanf("%hd%hd%lf",&(h->h),&(h->m),&(h->s) );
    if(h->h > 24){return 0;}
    else if (h->m > 60) {return 0;}
    else if (h->s>60.00){return 0;}    
    else if (floor((h->s * 100 )) != h->s * 100) {return 0;}
    return 1; 
}

//Exo 2



int est_bissextile(short a){
    if(a%4 == 0 ||a%100 == 0 ||a%400 == 0){return 1;}
    return 0;
}
int saisie_date(Date *d){
    printf("Indiquez une date\n");
    scanf("%hd%hd%hd",&(d->j),&(d->m),&(d->a));
    if(d->j>31){return 0;}
    else if (d->j == 31){
        if(d->m == 2 || d->m == 4 || d->m == 6 || d->m == 9 || d->m == 11) {return 0;}
    }
    else if(d->j>28 && d->m == 2){
        short a= d->a;
        int b = est_bissextile(a);
        if(b == 0){return 0;}
    }
    else if(d->m>12){return 0;}
    saisie_heure(&d->h);
    return 1;
}

//Exo 3

Date *alloue(int n){
    Date *t = (Date *)malloc(n*sizeof(Date));
    if(&t == NULL){return 0;}
    for(int k=0;k<n;k++){
        int verif = saisie_date(t+k);
        if (verif == 0){return 0;}
    }
}

//Exo 4 

int difference_heure(Heure *h,Heure h1,Heure h2){
        if(h2.h-h1.h<0){
            h->h = -1;
            h->m = -1;
            h->s = -1;
            return 0;
        }
        else if(h2.h-h1.h == 0 && h2.m-h1.m<0){
            h->h = -1;
            h->m = -1;
            h->s = -1;
            return 0;

        }
        else if(h2.h-h1.h == 0 && h2.m-h1.m == 0 && h2.s-h1.s <0){
            h->h = -1;
            h->m = -1;
            h->s = -1;
            return 0;            
        }
        else{
            h->h = h2.h - h1.h;
            if(h2.m-h1.m<0){
                h->m =(h2.m-h1.m)+60;
            }
            else{
                h->m = h2.m-h1.m;
            }
            if(h2.s-h1.s<0){
                h->s =h2.s-h1.s + 60.00;
            }
            else{
                h->s = h2.s-h1.s;
            }
        }
    return 1;
}


//Exo 5


int difference_date(Date d1,Date d2){
    int d_nonbiss[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int d_biss[12] = {31,23,31,30,31,30,31,31,30,31,30,31};
    int nm_jour_a = 0;
    int nm_jour_pass_1 = d1.j;
    int nm_jour_pass_2 = d2.j;
    if(d2.a<d1.a){return -1;}
    else if(d2.a ==d1.a && d2.m<d1.m){return -1;}
    else if(d2.a ==d1.a && d2.m == d1.m && d2.j<d1.j){return -1;}
    else if(d2.a == d1.a && d2.m == d1.m && d2.j == d1.j){return 0;}
    else{ 
        int a = d1.m;
        if(est_bissextile(d1.a) == 1){
            
            for(int k=0;k<a;k++){
                nm_jour_pass_1 = nm_jour_pass_1 + d_biss[k];
            }
        }
        else{
            for(int k=0;k<a;k++){
                nm_jour_pass_1 = nm_jour_pass_1 + d_nonbiss[k];
        }
    }   
        int b = d2.m;
        if(est_bissextile(d2.a) == 1){
         
            for(int k=0;k<b;k++){
                nm_jour_pass_2 = nm_jour_pass_2 + d_biss[k];
            }   
        }
        else{

            for(int k=0;k<a;k++){
                nm_jour_pass_2 = nm_jour_pass_2 + d_nonbiss[k];
        }
    }
    if(d1.a == d2.a){
       if (nm_jour_pass_2-nm_jour_pass_1<0){
        return("%d",nm_jour_pass_2-nm_jour_pass_1 + 365); 
       }
       else{
        return(nm_jour_pass_2-nm_jour_pass_1);
       }
    }
    else{
        int c = d1.a;
        int d = d2.a;
        
        for(int i=c;i<d;i++){
            int check = est_bissextile(i);
            nm_jour_a = nm_jour_a + 365 + check;
            
        }
    }
}
    int tot;
    tot = nm_jour_a;
    if (nm_jour_pass_2-nm_jour_pass_1<0){
        tot = tot + nm_jour_pass_2 - nm_jour_pass_1 + 365;
        printf("%d",tot);
        return tot; 
       }
       else{
        tot = tot + nm_jour_pass_2 - nm_jour_pass_1;
        printf("%d",tot);
        return tot;
       }
    return tot;
}

//Exo 6

Date *annee(Date *t,int n, int a, int *m){
    Date *d = (Date *)malloc(n*sizeof(Date));

    for(int k=0;k<n;k++){
        if( ((t+k)->a) == a){
            (d+*m)->a =  (t+k)->a;
            (d+*m)->j =  (t+k)->j;
            (d+*m)->m = (t+k)->m; 
            (d+*m)->h = (t+k)->h;
            *m = *m + 1;  
        }
    }
}

//Exo 7

void permuter(Date d1,Date d2){
    int tampon1,tampon2,tampon3;
    Heure tampon4;
    tampon1 = d1.a;
    tampon2 = d1.m;
    tampon3 = d1.j;
    tampon4 = d1.h;
    d1.a = d2.a ;
    d1.m = d2.m ;
    d1.j = d2.j ;
    d1.h = d2.h;
    d2.a = tampon1;
    d2.m = tampon2;
    d2.j = tampon3;
    d2.h = tampon4;
}

Date *fusion(Date *t,int n,Date *u, int m){
    Heure *h;
    Date *s = (Date *)malloc(n*m*sizeof(Date));
    for(int k =0;k<n;k++){
        (s+k)->a = (t + k)->a;
        (s+k)->j = (t + k)->j;
        (s+k)->m = (t + k)->m;
        (s+k)->h = (t + k)->h;
                }
       for(int k = n+1;k<n+m;k++){
        (s+k)->a = (u + k)->a;
        (s+k)->j = (u + k)->j;
        (s+k)->m = (u + k)->m;
        (s+k)->h = (u + k)->h;   
    }
    int permutation = 0;
    while(permutation == 1){
        permutation = 0;
        for(int k =0;k<n-1;k++){
            if(difference_date(*(s+k),*(s+k+1)) != -1 || (difference_date(*(s+k),*(s+k+1)) == 0 && difference_heure(h,(s+k)->h,(s+k+1)->h) != -1)){
                permuter(*(s+k),*(s+k+1));
                permutation = 1;

            }
        }
    }
    permutation = 0;
    while(permutation == 1){
        permutation = 0;
        for(int k =n;k<n+m-1;k++){
            if(difference_date(*(s+k),*(s+k+1)) != -1 || (difference_date(*(s+k),*(s+k+1)) == 0 && difference_heure(h,(s+k)->h,(s+k+1)->h) != -1)){
                permuter(*(s+k),*(s+k+1));
                permutation = 1;

            }
        }
    }
}


//Exo 8

Date2 *chargement(char *nom, int *n){
}


int main(){
    Heure h;
    Date d;
    Date2 t;
    
    /* int a;
    a = saisie_heure(&h);
    printf("%d",a); 
    int a;
    a = saisie_date(&d);
    printf("%d",a);*/
    
    /*
    Date d1;
    Date d2;
    int a = saisie_date(&d1);
    if (a == 0){
        return 0;
    }
    a = saisie_date(&d2);
    if (a == 0){    
        return 0;
    }

    difference_date(d1,d2);
    */

    return 0;
}