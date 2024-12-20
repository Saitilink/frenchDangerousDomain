#include <stdio.h>




int Hanoi(int n, char A,char B, char C){
    int somme =0;
    somme ++;
    if(n == 1){
        return somme;
    }

    somme += Hanoi(n-1,A,C,B);
    somme += Hanoi(n-1,B,A,C);
    return somme;
}

int main()
{

    char A = 'A';
    char B = 'B';
    char C = 'C';
    for(int n =3;n<20;n++){
    int somme = 0;
    somme = Hanoi(n,A,B,C);
    printf("%d\n",somme);
    }
    return 0;
}
