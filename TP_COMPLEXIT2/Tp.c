#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
void Hanoi(int n,char D,char A,char I){
    if(n==1){
        printf("Disque 1 de %c a %c \n", D , A );
    }
    else{
        Hanoi(n-1,D,I,A);
        printf("Disque %d de %c a %c \n", n , D , A );
        Hanoi(n-1,I,A,D);
    }
}



long long suite_itteratif(int n){
    int compteur = 0;
    long nb_1 = 0;
    compteur++;
    long nb_2 = 1;
    compteur++;
    if(n==1){
        compteur++;
        printf("%d ",compteur);
        return 1;
    }
    compteur++;
    for(int i=2;i<n;i++){
        if(nb_1 < nb_2){
            nb_1 = nb_1 + nb_2;
            compteur++;
        }
        else{
            nb_2 = nb_2 + nb_1;
            compteur++;
        }
    }
    return nb_1+nb_2;
}


int suite(int n){
    if(n <=1){
        return 1;
    }
    return(suite(n-1) - suite(n-2));
}



int *calculMatrice(int *m,int n){
    int *nouv = malloc(4 * sizeof(int));
    if ( n==0 ){
        nouv[0] = 1;
        nouv[1] = 0;
        nouv[2] = 0;
        nouv[3] = 1;
    }
    else if(n == 1){
        nouv[0] = m[0];
        nouv[1] = m[1];
        nouv[2] = m[2];
        nouv[3] = m[3];
    }
    else if(n%2 == 1){
        int *supp = calculMatrice(m,n-1);
        nouv[0] = m[0]*supp[0] + m[1]*supp[2];
        nouv[1] = m[0]*supp[1] + m[1]*supp[3];
        nouv[2] = m[2]*supp[0] + m[3]*supp[2];
        nouv[3] = m[2]*supp[1] + m[3]*supp[3];
        free(supp);
    }
    else{
        int *supp = calculMatrice(m,n/2);
        nouv[0] = m[0]*supp[0] + m[1]*supp[2];
        nouv[1] = m[0]*supp[1] + m[1]*supp[3];
        nouv[2] = m[2]*supp[0] + m[3]*supp[2];
        nouv[3] = m[2]*supp[1] + m[3]*supp[3];
        free(supp);
    }
    return nouv;
}
//Nb le programme est correct mais ne fonctionne pas, pour une certaine raison


int fibbo_logarythme(int n){
    int *m = malloc(4*sizeof(int));
    m[0] = 0;
    m[1] = 1;
    m[2] = 1;
    m[3] = 1;
    int *res = calculMatrice(m,n-1);
    int a = res[0] + res[1];
    int b = res[2] + res[3];
    int total =   a;
    printf("%d %d\n",a,b);
    return total;
    }

int eratosthène(int n){
    int compteur = 0;
    int *t = (int*)malloc(n*sizeof(int));
    compteur++;
    for(int i =0;i<n;i++){
        t[i] = 1;
        compteur++;
    } 
    for(int i = 2;i<=sqrt(n);i++ ){
        compteur++;
        if(t[i-1] == 0){
            compteur++;
            continue;
        }
        else{
        compteur++;
        for(int j = i+1;j<=n;j++){
            compteur++;
            if((j%i) == 0){
                t[j-1] = 0;
                compteur++;
            }}}}
    for(int i=1;i<n;i++){
        if(t[i-1] == 1){
            printf("%d ",i);
        }
    }
    return compteur;
}




int main()
{
    /*
    char A = 'D';
    char B = 'A';
    char C = 'I';
    clock_t start,end;
    
    for(int n =3;n<40;n++){
    start = time(NULL);
    Hanoi(n,A,B,C);
    end = time(NULL);
    double temps = (end - start);
    printf("Pour n = %d, on a un temps de calcul de %lf secondes\n",n,temps);
    }
    
    clock_t start,end;
    for(int i = 2;i<50;i++){
        start = time(NULL);
        long n = suite(i);
        end = time(NULL);
        double temps = (end - start);
        printf("Pour n = %d, on a un temps de calcul de %lf secondes\n",i,temps);
    
    }
    int a = eratosthène(10);
    int b = eratosthène(100);
    int c = eratosthène(1000);
    printf("\n\n%d %d %d",a,b,c);
    */
    for(int i = 1;i<10;i++){
        int a = fibbo_logarythme(i);
    }
    return 0;

}
