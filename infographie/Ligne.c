#include <stdio.h>
#include <stdlib.h>
#define Hauteur 1000
#define Longueur 300

typedef struct {
    int x_deb;
    int y_deb;
    int x_fin;
    int y_fin;
    int v,r,b;
    int *Surf;
} Ligne ;


int CapValue(int n, int c, int d){
    if(n<c){return c;}
    if(n>d){return d;}
    return n;
}



void calcul_ligne_droite(Ligne *l){
    l->x_deb = 20;
    l->x_fin = 80;
    l->y_deb = 50;
    l->Surf = malloc(3 * Hauteur * Longueur * sizeof(int));
    for(int i = 0;i< Hauteur*3*Longueur;i++){
        l->Surf[i] = 0;
    }
    for(int i = l->x_deb; i <l->x_fin;i++){
        l->Surf[3*i + 3*Hauteur * l->y_deb] = 200;
        l->Surf[3*i + 3*Hauteur * l->y_deb + 1] = 255;
        l->Surf[3*i + 3*Hauteur * l->y_deb + 2] = 234;
    }
    
}





void calcul_ligne_pas_droite(Ligne *l){
    l->Surf = malloc(3 * Hauteur * Longueur * sizeof(int));
        for(int i = 0;i< Hauteur*3*Longueur;i++){
        l->Surf[i] = 0;
    }
    l->x_deb = 300;
    l->x_fin = 300;
    l->y_deb = 200;
    l->y_fin = 200;  
    double a, b;
    int x1 = l->x_deb;
    int x2 = l->x_fin;
    int y1 = l->y_deb;
    int y2 = l->y_fin;
    double ix,iy,dx,dy;
    dx = x2 - x1;
    dy = y2 - y1;
    if(dx>dy){
        a = dy/dx;
        b = y1 - a* x1; 
        int y;
        for(int x = x1; x < x2; x++){
            y = a * x + b ;
            printf("%f\n",a);
            l->Surf[3*x + 3*Longueur * y] = 200;
            l->Surf[3*x + 3*Longueur* y + 1] = 255;
            l->Surf[3*x + 3*Longueur* y + 2] = 234;
        }
    }
    else{
        a = dx/dy;
        b = x1 - a*y1;
        for(int y = y1;y<y2;y++){
            int x = a * y + b;
             printf("%d\n",y);
        l->Surf[3*x + 3*Longueur * y] = 200;
        l->Surf[3*x + 3*Longueur* y + 1] = 0;
        l->Surf[3*x + 3*Longueur*y + 2] = 234;
        }
    }
}

int faire_img(Ligne *s, FILE *f){
    
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n",Longueur, Hauteur,255);
    for (int i =0 ; i < Longueur*Hauteur;i++) {
        count = count + fprintf(f, "%d %d %d ",CapValue(s->Surf[3*i],0,255),CapValue(s->Surf[3*i+1],0,255), CapValue(s->Surf[3*i+2],0,255));
       
    }

    return count;
}  






int main()
{
    Ligne l;
    FILE *sortie = fopen("Ningen.ppm", "w");
    calcul_ligne_pas_droite(&l);
    faire_img(&l,sortie);
    free(l.Surf);
    return 0;
}
