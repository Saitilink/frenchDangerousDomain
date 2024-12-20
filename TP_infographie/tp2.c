#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    int largeur;
    int hauteur;
    int *r,*v,*b;
} STRUCTURE;

void init(STRUCTURE *s){
    s->r= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    s->v= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    s->b= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    for(int i =0;i< s->hauteur*s->largeur;i++){
        s->r[i] = 0;
         s->v[i] = 0;
          s->b[i] = 0;
    }
}

void trace_triangle_joli(STRUCTURE *s, int x0, int y0, int x1, int y1,int x2, int y2,int r0, int r1, int r2, int b0, int b1, int b2, int v0, int v1, int v2){
    for(int y=0; y < s->hauteur; y++){
        for(int x = 0; x < s->largeur; x++){
            double detT = (y1 - y2)*(x0-x2) + (x2 - x1)*(y0 - y2);
            double alpha = ((y1 - y2)*(x - x2) + (x2 - x1)*(y - y2))/detT;
            double beta = ((y2 - y0)*(x - x2) + (x0 - x2)*(y - y2))/detT;
            double gamma = 1 - beta - alpha;
            if(alpha >=0 && gamma >=0 && beta >=0){
                double red = alpha * r0 + beta*r1 + gamma*r2;
                double green = alpha * v0 + beta*v1 + gamma*v2;
                double blue = alpha * b0 + beta*b1 + gamma*b2;
                int pos = y*s->largeur + x;
                s->r[pos] = red;
                s->v[pos] = green;
                s->b[pos] = blue;
            }   
        }
    }
}
int CapValue(int n, int c, int d){
    if(n<c){return c;}
    if(n>d){return d;}
    return n;
}

void flou(STRUCTURE *s){
    for(int i = 0; i< s->hauteur*s->largeur - s->hauteur -1;i++){
        s->r[i] = (s->r[i+1] +s->r[i + s->largeur] + s->r[i])/3;
        s->v[i] = (s->r[i+1] +s->v[i + s->largeur] + s->v[i])/3;
        s->b[i] = (s->b[i+1] +s->b[i + s->largeur] + s->b[i])/3; 
    }
}

void tracer_ligne(STRUCTURE *s,int x1, int y1, int x2, int y2){
    double a, b;
    double ix,iy,dx,dy;
    dx = x2 - x1;
    dy = y2 - y1;
    if(dx>dy){
        a = dy/dx;
        b = y1 - a* x1; 
        int y;
        for(int x = x1; x < x2; x++){
            y = a * x + b ;
    
            s->r[y*s->largeur + x] = 255;
            s->v[y*s->largeur + x] = 255;
            s->b[y*s->largeur + x] = 255;
        }
    }
    else{
        a = dx/dy;
        b = x1 - a*y1;
        for(int y = y1;y<y2;y++){
            int x = a * y + b;

            s->r[y*s->largeur + x] = 255;
            s->v[y*s->largeur + x] = 255;
            s->b[y*s->largeur + x] = 255;
        }
    }
}    

void trace_rectangle_droit(STRUCTURE *s){
    tracer_ligne(s,3,3,3,s->largeur-4);
    tracer_ligne(s,3,3,s->hauteur-4,3);
    tracer_ligne(s,s->hauteur-4,3,s->hauteur-4,s->largeur-4);
    tracer_ligne(s,3,s->largeur-4,s->largeur-4,s->hauteur-4);
}

void trace_ligne_alea_sur_tri(STRUCTURE *s,int n){
    for(int k = 0;k<n;k++){
    int a = rand()% 3;
    int b = rand() % 3;
    if(a == 0 && b == 0){
        tracer_ligne(s,3,rand() % (s->hauteur -1), s->largeur-1, rand() % (s->hauteur -1));
    }
    else if(a == 0 && b != 0){
        if (b == 1){
            tracer_ligne(s,3,rand() % (s->hauteur -4),rand() % (s->hauteur -4), s->largeur-4);
        }
        else{
            tracer_ligne(s,3,rand() % (s->hauteur -4),rand() % (s->hauteur -4), 3);
        }
    }
    else if(a != 0 && b == 0){
        if(b == 1){
            tracer_ligne(s,rand() % (s->hauteur -4),s->largeur-4,s->largeur-4,rand() % (s->largeur-4));
        }
        else{
            tracer_ligne(s,rand() % (s->hauteur -4),3,rand() % (s->largeur -4),s->largeur-4);
        }
    }
    else{
        tracer_ligne(s,rand() % (s->hauteur -4),3,rand() % (s->largeur -4),s->largeur-4);
    }   
}
}

int faire_img(STRUCTURE *s, FILE *f){
    
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n",s->largeur, s->hauteur,255);
    for (int i =0 ; i < s->largeur*s->hauteur;i++) {
        count = count + fprintf(f, "%d %d %d ",CapValue(s->r[i],0,255),CapValue(s->v[i],0,255), CapValue(s->b[i],0,255));
       
    }

    return count;
}  
int main()
{
    STRUCTURE s;
    s.hauteur = 1000;
    s.largeur = 1000;
    srand(time(NULL));
    init(&s);
    FILE *sortie = fopen("Zamasu.ppm", "w");
    //trace_triangle_joli(&s,50,50,450,50,234,235,255,0,0,0,255,0,0,0,255);
    //flou(&s);
    //tracer_ligne(&s,40,40,100,340);
    trace_rectangle_droit(&s);
    trace_ligne_alea_sur_tri(&s,100);
    faire_img(&s,sortie);
    return 0;
}
