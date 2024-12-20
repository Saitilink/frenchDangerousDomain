#include <stdio.h>
#define l 5
#define MAXL 15
#define MAXC 10



int decal(int t[l],int m){
    int p[l];
    for(int k = 0; k<l-m;k++){
        p[k] = t[k+m];
    }
    for(int k = l-m; k<l;k++){
        p[k] = t[l-k-1];
    }
    for(int k=0; k<l; k++){
       t[k] = p[k];
       printf("%d",t[k]);   
    }
}

//Exo 2 

void sommes(int t[MAXL][MAXC], int n, int m, int sl[MAXL], int sc[MAXC]){
    for(int k =0;k<n;k++){
        int sommel = 0;
        for(int i = 0; i<m; i++){
            sommel = sommel + t[k][i];
              ;
        }
    sl[k] = sommel;
    }  
    for(int k =0;k<m;k++){
        int sommec = 0;
        for(int i = 0; i<n; i++){
            sommec = sommec + t[i][k];   
        } 
    sc[k] = sommec;
    } 
}

void tri_tabl(int t[MAXL][MAXC], int n, int m, int sl[MAXL], int sc[MAXC]){
    sommes(t,3,3,sl,sc);
    int permutation = 1;
    int tampon = 0;
    int tampon2;
    while (permutation == 1) {
        permutation = 0;
        for(int k =0; k<n-1; k++){
            if(sl[k]<sl[k+1]){
                permutation = 1;
                tampon = sl[k];
                sl[k] = sl[k+1];
                sl[k+1] = tampon;
                
                for(int i = 0; i<m-1 ;i++){
                tampon2 = t[k][i];
                t[k][i] = t[k+1][i];
                t[k+1][i] = tampon2;
            

            }
    } 
}  
} 
for(int k=0;k<n;k++){
    printf("%d %d %d\n", t[k][0], t[k][1],t[k][2]);

}
}

//q3
/* les booleens existent pas, faut retourner 1 ou -1*/

int main(){
    //int t[5] = {1,2,3,4,5};
    //decal(t,4);

int t[MAXL][MAXC] = {{4,7,5},{2,8,4},{5,7,5}};
int sl[MAXL];
int sc[MAXC];
tri_tabl(t,3,3,sl,sc);

}