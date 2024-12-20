#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define hauteur 1000
#define largeur 1000


typedef struct {
    int *data;
} surface;
typedef struct {
    int centre_x,centre_y,r,v,b;
    int rayon;
}cercle;
typedef struct{
    int x0,y0,x1,y1,x2,y2,x3,y3;
}courbe;
typedef struct{
    int x0,x1,y0,y1,x2,y2;
}cercle_para;
typedef struct{
    int x0,y0,x1,y1,x2,y2;
    int r0,b0,v0;
    int r1,b1,v1;
    int r2,b2,v2;
} triangle ;

void init(surface *s){
    s->data= (int *)malloc(3* hauteur * largeur * sizeof(int));
    for(int i=0;i<largeur*hauteur;i++){
        s->data[i]=0;
    }
}

void trace_cercle_plein(surface *s,cercle *c){
    int x;
    int y;
    int cx = c->centre_x;
    int cy = c->centre_y;
    int r = c->rayon;
    for(int y=0;y<hauteur;y++){
        for(int x=0;x<largeur;x++){
            int k = x + largeur*y;
            int tot = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));  
            if(tot <= r){   
        s->data[3*k ] = c->r;
        s->data[3*k + 1] = c->v;
        s->data[3*k + 2] = c->b;
            }
        }
    }
}

void trace_cercle_vide(surface *s,cercle *c){
    int x;
    int y;
    int cx = c->centre_x;
    int cy = c->centre_y;
    int r = c->rayon;
    for(int y=0;y<hauteur;y++){
        for(int x=0;x<largeur;x++){
            int k = x + largeur*y;
            int tot = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));  
            if(tot == r){
        s->data[3*k ] = c->r;
        s->data[3*k + 1] = c->v;
        s->data[3*k + 2] = c->b;
            }
        }
    }
}


void trace_courbe_para(surface *s, courbe *b){
    for(double k =0;k<1; k = k + 0.001){
        int x = (1-k)*(1-k)*(1-k)* b->x0 + 3 * k * (1-k) * (1-k) * b->x1 + 3 * (1-k) * k * k * b->x2 + k*k*k*b->x3;
        int y = (1-k)*(1-k)*(1-k)* b->y0 + 3 * k * (1-k) * (1-k) * b->y1 + 3 * (1-k) * k * k * b->y2 + k*k*k*b->y3;
        int a = 3*y*largeur + 3*x;
        s->data[3*y*largeur + 3*x] = 255;
        s->data[3*y*largeur + 3*x +1] = 255;
        s->data[3*y*largeur + 3*x +2] = 255;

    }
}

void trace_courbe_para_deg2(surface *s,cercle_para *p){
    for(double k =0;k<1; k = k + 0.001){
        int x = (1-k)*(1-k)*p->x0 + (1-k) * k * p->x1 + k * k * p->x2; 
        int y = (1-k)*(1-k)*p->y0 + (1-k) * k * p->y1 + k * k * p->y2; 
        int a = 3*y*largeur + 3*x;
        s->data[3*y*largeur + 3*x] = 255;
        s->data[3*y*largeur + 3*x +1] = 255;
        s->data[3*y*largeur + 3*x +2] = 255;
    }
}


void trace_cercle_courbe_para(surface *s,int x, int y, int r,cercle_para *p){
    int a = x+r, b =x-r,c = y+r,d = y-r;
    p->x0 = x + r;
    p->y0 = y;
    p->x2 = x-r;
    p->y2 = y;
    p->x1 = x;
    p->y1 = y-r;
    trace_courbe_para_deg2(s,p);
}

void trace_triganle_joli(surface *s,triangle t){
    for(int y = 0; y < hauteur;y++){
        for(int x = 0;x < largeur;x++){
            double detT = (t.y1 - t.y2)*(t.x0-t.x2) + (t.x2 - t.x1)*(t.y0 - t.y2);
            double alpha = ((t.y1 - t.y2)*(x - t.x2) + (t.x2 - t.x1)*(y - t.y2))/detT;
            double beta = ((t.y2 - t.y0)*(x - t.x2) + (t.x0 - t.x2)*(y - t.y2))/detT;
            double gamma = 1 - beta - alpha;
            if(alpha >=0 && gamma >=0 && beta >=0){
                double red = alpha * t.r0 + beta*t.r1 + gamma*t.r2;
                double green = alpha * t.v0 + beta*t.v1 + gamma*t.v2;
                double blue = alpha * t.b0 + beta*t.b1 + gamma*t.b2;
            s->data[3*y*largeur + 3*x] = red;
            s->data[3*y*largeur + 3*x + 1] = green;
            s->data[3*y*largeur + 3*x + 2] = blue;
            }
}
}}

int CapValue(int n, int c, int d){
    if(n<c){return c;}
    if(n>d){return d;}
    return n;
}

int faire_img(surface *s, FILE *f){
    
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n",largeur, hauteur,255);
    for (int i =0 ; i < largeur*hauteur;i++) {
        count = count + fprintf(f, "%d %d %d ",CapValue(s->data[3*i],0,255),CapValue(s->data[3*i+1],0,255), CapValue(s->data[3*i+2],0,255));
       
    }

    return count;
}  


int main(){
    FILE *sortie = fopen("Cercle.ppm", "w");
    surface s;
    init(&s);
    cercle c;
    courbe b;
    /*c.r = 255;
    c.b = 34;
    c.v = 140;
    c.centre_x = 30;
    c.centre_y = 20;
    c.rayon = 15;
    trace_cercle_plein(&s,&c);
    c.centre_x = 70;
    c.centre_y = 50;
    c.rayon = 20;
    trace_cercle_vide(&s,&c);*/
    b.x0 = 500;
    b.y0 = 500;
    b.x1 = 300;
    b.y1 = 500;
    b.x2 = 300;
    b.y2 = 700;
    b.x3 = 500;
    b.y3 = 700;
    trace_courbe_para(&s,&b);
    cercle_para p;
    /*trace_cercle_courbe_para(&s, 500,500,40,&p);
    triangle t;
    t.x0 = 100;
    t.y0 = 900;
    t.x1 = 800;
    t.y1 = 200;
    t.x2 = 100;
    t.y2 = 20;

    t.r0 = 0;
    t.v0 = 0;
    t.b0 = 255;

    t.r1 = 0;
    t.v1 = 255;
    t.b1 = 0;

    t.r2 = 255;
    t.v2 = 0;
    t.b2 = 0;

    trace_triganle_joli(&s,t); */


    faire_img(&s,sortie);
    free(s.data);
    return 0;
}
