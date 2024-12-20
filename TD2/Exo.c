#include <stdio.h>
#include <math.h>
#define MAX 20


int binaire(int n){
    int k =0, tab[30];
    while(n>0) {
        tab[k] = n%2;
        n = n/2;
        ++k;
    }
    for(int i = 0;i<k;++i){
    printf("%d",tab[k-i-1]);
    }
    return 0;
}


int chiffre_et_lettres(){
    int c, t[3] = {0,0,0};
    c = getchar();
    while (c != '\n'){
        if (c ==65 || c ==  69 || c == 73 ||c ==79|| c == 85||c ==89||c==97||c==101||c==105||c==111||c==117||c==121 ){
            t[0] += 1;}
        else if (c <=40 || (c >=91 && c <=96) || c >=123){
            t[2] +=1;
        }
        else{
            t[1] +=1;
        }
        c = getchar();
    }
    printf("Voyelle = %d, consonne = %d, autres = %d",t[0],t[1],t[2]);
    return 0;
}


int pos(int t[MAX],int n, int p[MAX]){
    if (n>20) {return -1;}
    else {int k = 0;
    for(int i=0;i<MAX;++i){
        if (t[i] < 0){
            p[k] = i;
            ++k;        
            }
    }
    printf("[");
    for(int y=0;y<k;++y){
        printf(" %d ",p[y]);
    }
    printf("]");
    return (k+1);
    }
}






int recursif(int n, int s){
    if (n<0){return s;}
    s= s*10 + s%10;
    return inverse(n/10, s);
    }

int inverse(int s, int n){
    int sacrifice = s;
    int compt =0;
    while(sacrifice>0){
        sacrifice /=10;
        ++compt;
    }
    int t[compt];
    for(int k=0;k < compt;++k){
        t[compt-k] = s%10;
        s = s/10;
    }
    
    int tampon;
    for(int k =0;k<n;++k){
        tampon = t[k];
        t[k] = t[n-k];
        t[n-k] = tampon;
    }
    return n/2;
}


int main(){
    /*int n;
    printf("Choisi un nb");
    scanf("%d",&n);
    binaire(n);

    chiffre_et_lettres();*/
    int n;
    int t[MAX] = {-5,5,9,4,2,-6,5,-7,4}, p[MAX];
    printf("Taille de n");
    scanf("%d",&n);
    pos(t,n,p);




    return 0; 
}


