#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct{
    int largeur;
    int hauteur;
    int *data;
    int *r,*v,*b;
} STRUCTURE;


typedef struct elem_pile elem_pile;
struct elem_pile {
    int coord_x;
    int coord_y;
    elem_pile *precedent;
} ;

typedef struct pile pile;
struct pile {
    elem_pile *premier;
    elem_pile *dernier;
} ;
typedef struct points points;
struct points{
    int x;
    int y;
    points *suivant;
} ; 
typedef struct files files;
struct files {
    points *premier;
    points *dernier;
} ;

files creer_file(){
    files *f = malloc(sizeof(*f));
    f->dernier = NULL;
    f->premier = NULL;
    points *elem = malloc(sizeof(*elem));
    if(f == NULL && elem == NULL){
        exit(EXIT_FAILURE);
    }
    return *f;
}

int file_vide(files f){
    if ( &f == NULL){
        return 1;
    }
    return 0;
}

void enfile(files *f, int x, int y){
    points *new = malloc(sizeof(*new));
    if (f == NULL && new == NULL){
        printf("Nope");
        exit(EXIT_FAILURE);
    }
    new->x = x;
    new->y = y;
    new->suivant = NULL;
    //printf("%p\n", new);
    //printf("%p\n", new->suivant);
    if (f->dernier == NULL && f->premier == NULL){
        f->premier = new;
    }
    else{
        f->dernier->suivant = new;
        }
    f->dernier = new;
    
   
    //printf("%p\n", f->premier);
    //printf("%p\n", f->dernier);
}

void tete(files f, int *x, int *y){
    int a = file_vide(f);
    if (a == 1){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    points *prems = f.premier;
     *x = prems->x;
     *y = prems->y;
}

void defile(files *f){
    points *suppr = f->premier;
    f->premier = f->premier->suivant;
    free(suppr);
}


pile creer_pile(){
    pile *p =malloc(sizeof(*p));
    p->dernier = NULL;
    p->premier = NULL;
    elem_pile *elem_pile = malloc(sizeof(*elem_pile));
    if(p == NULL && elem_pile == NULL){
        exit(EXIT_FAILURE);
    }
    return *p;
}

int pile_vide(pile p){
    if (&p == NULL){
        return 1;
    }
    return 0;
}

void empile(pile *p, int x, int y){
    int a = pile_vide(*p);
    if (a == 1){
        exit(EXIT_FAILURE);
    }
    elem_pile *nouv = malloc(sizeof(*nouv));
    nouv->coord_x = x;
    nouv->coord_y = y;
    nouv->precedent = p->premier;
    if (p->premier == NULL && p->dernier == NULL){
        p->dernier = nouv;
    }
    p->premier = nouv;
}

void sommet(pile p, int *x, int *y){
    int a = pile_vide(p);
    if (a == 1){
        exit(EXIT_FAILURE); 
    }
    elem_pile *premier = p.premier;
    *x = premier->coord_x;
    *y = premier->coord_y;

}

void depile(pile *p){  
    int a = pile_vide(*p);
    if (a == 1){
        exit(EXIT_FAILURE);
    }   
    elem_pile *suppr = p->premier;
    p->premier = p->premier->precedent;
    free(suppr); 
}



void init(STRUCTURE *s){
    s->data= (int *)malloc(3* s->hauteur * s->largeur * sizeof(int));
    s->r= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    s->v= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    s->b= (int *)malloc(s->hauteur * s->largeur * sizeof(int));
    for(int i = 0;i<s->hauteur*s->largeur;i++){
        s->r[i] = 0;
        s->b[i] = 0;
        s->v[i] = 0;
    }
}



void trace_triangle_joli(STRUCTURE *s, int x0, int y0, int x1, int y1,int x2, int y2,int r0, int r1, int r2, int b0, int b1, int b2, int v0, int v1, int v2){
    for(int y=0; y < s->hauteur; y++){
        for(int x = 0; x < s->largeur; s++){
            double detT = (y1 - y2)*(x0-x2) + (x2 - x1)*(y0 - y2);
            double alpha = ((y1 - y2)*(x - x2) + (x2 - x1)*(y - y2))/detT;
            double beta = ((y2 - y0)*(x - x2) + (x0 - x2)*(y - y2))/detT;
            double gamma = 1 - beta - alpha;
            printf("%d %d %d %d\n", detT, alpha,beta,gamma);
            if(alpha >=0 && gamma >=0 && beta >=0){
                double red = alpha * r0 + beta*r1 + gamma*r2;
                double green = alpha * v0 + beta*v1 + gamma*v2;
                double blue = alpha * b0 + beta*b1 + gamma*b2;
                
                int pos = y*s->hauteur + x;
                s->r[pos] = red;
                s->v[pos] = green;
                s->b[pos] = blue;
            }   
        }
    }
}


void rebord_anti_pb(STRUCTURE *s){
    for(int i = 0;i< s->largeur;i++){
        s->r[i] = 1;
        s->r[i + (s->hauteur-1)*(s->hauteur)] = 1;
    }
    for(int j = 0;j< s->hauteur;j++){
        s->r[s->hauteur*j] = 1;
        s->r[s->hauteur*j + (s->largeur-1)]=1;
    }
}


void trace_ligne(STRUCTURE *s,double x1,double y1,double x2,double y2, int couleur_r, int couleur_v,int couleur_b){
    double ix,iy,dx,dy;
    dx = x2 - x1;
    dy = y2 - y1;
    double  a,b;
    if(dx>dy){
        a = dy/dx;
        b = y1 - a* x1; 
        double y;
        if(x1<x2){
        for(double x = x1; x < x2; x = x + 0.1){
            y = a * x + b ;
            int x_b = x;
            int y_b = y;
            s->r[x_b + y_b*s->hauteur] = couleur_r;
            s->v[x_b+ y_b*s->hauteur] = couleur_v;
            s->b[x_b + y_b*s->hauteur] = couleur_b;
        }}
        else{
            for(double x = x2; x < x1; x=x+0.1){
            y = a * x + b ;
            int x_b = x;
            int y_b = y;
            s->r[x_b + y_b*s->hauteur] = couleur_r;
            s->v[x_b+ y_b*s->hauteur] = couleur_v;
            s->b[x_b + y_b*s->hauteur] = couleur_b;
        }
    }
    }
    else{
        a = dx/dy;
        b = x1 - a*y1;
        if(y1 < y2){
        for(double y = y1;y<y2;y=y+0.1){
            int x = a * y + b;
            int y_b = y;
            s->r[x + y_b*s->hauteur] = couleur_r;
            s->v[x + y_b*s->hauteur] = couleur_v;
            s->b[x + y_b*s->hauteur] = couleur_b;

        }}
        else{
            for(double y = y2 ; y<y1;y=y+0.1){
            int x = a * y + b;
            int y_b = y;
            s->r[x + y_b*s->hauteur] = couleur_r;
            s->v[x + y_b*s->hauteur] = couleur_v;
            s->b[x + y_b*s->hauteur] = couleur_b;
            }
        }
    }
}
void trace_triangle_vide(STRUCTURE *s,int x1, int y1,int x2,int y2,int x3,int y3, int couleur_r,int couleur_v,int couleur_b){
    trace_ligne(s,x1,y1,x2,y2,couleur_r,couleur_v,couleur_b);
    trace_ligne(s,x1,y1,x3,y3,couleur_r,couleur_v,couleur_b);
    trace_ligne(s,x2,y2,x3,y3,couleur_r,couleur_v,couleur_b);

}

void trace_rectangle_vide(STRUCTURE *s,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int couleur_r,int couleur_v, int couleur_b){
    trace_ligne(s,x1,y1,x2,y2,couleur_r,couleur_v,couleur_b);
    trace_ligne(s,x1,y1,x3,y3,couleur_r,couleur_v,couleur_b);
    trace_ligne(s,x2,y2,x4,y4,couleur_r,couleur_v,couleur_b);
    trace_ligne(s,x3,y3,x4,y4,couleur_r,couleur_v,couleur_b);
}


void remplir(STRUCTURE *s,int x,int y,int couleur_r,int couleur_v,int couleur_b){
    pile p = creer_pile();
    empile(&p,x,y);
    int x_act,y_act;
        while(p.premier != NULL){
            sommet(p,&x_act,&y_act);
            depile(&p);
            s->r[x_act + y_act*s->largeur] = couleur_r;
            s->v[x_act + y_act*s->largeur] = couleur_v;
            s->b[x_act + y_act*s->largeur] = couleur_b;
            int dy[] = {-1,1,0,0};
            int dx[] = {0,0,-1,1};
            for(int i =0;i < 4; i++){
                int x_nouv = x_act + dx[i];
                int y_nouv = y_act + dy[i];
                if(s->r[x_nouv + y_nouv*s->largeur] != couleur_r || s->v[x_nouv + y_nouv*s->largeur] != couleur_v || s->b[x_nouv + y_nouv*s->largeur] != couleur_b ){
                    empile(&p,x_nouv,y_nouv);
            }
       }
    }
}



void degrade_blanc_bas(STRUCTURE *s,int x_min, int y_min,int x_max,int y_max,int n,int couleur_r,int couleur_v,int couleur_b){
    //x_min,x_max,y_min et y max servent à ce que l'on fasse un balayage sur une pas trop grande zone
    //n correspond au nombre de pixels dont on veut le dégradé 
    int facteur_ammortissement = 2;
    for(int i = x_min;i<x_max;i++){
        int temp;
        for(int j =y_min; j< y_max;j++){
            if(s->r[j*s->largeur + i] == couleur_r && s->v[j*s->largeur + i] == couleur_v && s->b[j*s->largeur + i] == couleur_b ){
                temp = j;
                }
            }
        int rouge = (255-couleur_r)/n;
        int vert = (255-couleur_v)/n;
        int bleu = (255-couleur_b)/n;
        for(int k = 0;k<n;k++){
            if(s->r[(temp-k)*s->largeur + i] == couleur_r && s->v[(temp-k)*s->largeur + i] == couleur_v && s->b[(temp-k)*s->largeur + i] == couleur_b ){
            s->r[i + (temp-k)*s->largeur] =  s->r[i + (temp-k)*s->largeur] + rouge*(n-k)/facteur_ammortissement;
            s->v[i + (temp-k)*s->largeur] =  s->v[i + (temp-k)*s->largeur] + vert*(n-k)/facteur_ammortissement;
            s->b[i + (temp-k)*s->largeur] =  s->b[i + (temp-k)*s->largeur] + bleu*(n-k)/facteur_ammortissement;
            }
        } 
    }
}

void trace_courbe_para(STRUCTURE *s,int x0,int y0,int x1, int y1,int x2,int y2,int x3,int y3, int couleur_r,int couleur_v,int couleur_b ){
    for(double k =0;k<1; k = k + 0.001){
        int x = (1-k)*(1-k)*(1-k)* x0 + 3 * k * (1-k) * (1-k) * x1 + 3 * (1-k) * k * k * x2 + k*k*k*x3;
        int y = (1-k)*(1-k)*(1-k)* y0 + 3 * k * (1-k) * (1-k) * y1 + 3 * (1-k) * k * k * y2 + k*k*k*y3;
        s->r[y*s->largeur + x] = couleur_r;
        s->v[y*s->largeur + x] = couleur_v;
        s->b[y*s->largeur + x] = couleur_b;

    }
}

int CapValue(int n, int c, int d){
    if(n<c){return c;}
    if(n>d){return d;}
    return n;
}


void trace_cercle_vide(STRUCTURE *s,int centre_x,int centre_y,int r, int couleur_r,int couleur_v,int couleur_b){
    int cx = centre_x;
    int cy = centre_y;
    for(int y=0;y<s->hauteur;y++){
        for(int x=0;x<s->largeur;x++){
            int k = x + s->largeur*y;
            int tot = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));  
            if(tot == r){
        s->r[k] = couleur_r;
        s->v[k] = couleur_v;
        s->b[k] = couleur_b;
            }
        }
    }
}


void Bezier_taille_n(STRUCTURE *s, files *f,int n,int couleur_r,int couleur_v,int couleur_b){
            int x_tab,y_tab;
            int *x = (int *)malloc(n*sizeof(int));
            int *y = (int *)malloc(n*sizeof(int));
            for(int k=0;k<n;k++){
                tete(*f,&(x_tab),&(y_tab));
                x[k] = x_tab;
                y[k] = y_tab;
                defile(f);
            }
            int *tot = (int *)malloc(n*sizeof(int));
            tot[0] = 1;
            int b;
            for(int i=1;i<n;i++){
              tot[i] = tot[i-1] * ((n-1)-i+1)/i;
        }
            double t;
            for(double t=0;t<1;t+=0.0000001){
                int x_fonction = 0,y_fonction = 0;
                for(int k =0;k<n;k++){
                    x_fonction += tot[k]*pow(t,k)*pow(1-t,n-k-1)*x[k];
                    y_fonction += tot[k]*pow(t,k)*pow(1-t,n-k-1)*y[k];
                }
                s->r[x_fonction + y_fonction*s->largeur] = couleur_r;
                s->v[x_fonction + y_fonction*s->largeur] = couleur_v;
                s->b[x_fonction + y_fonction*s->largeur] = couleur_b;
            }
            t = 1;
            int x_fonction = 0,y_fonction = 0;
            for(int k =0;k<n;k++){
                    x_fonction += tot[k]*pow(t,k)*pow(1-t,n-k-1)*x[k];
                    y_fonction += tot[k]*pow(t,k)*pow(1-t,n-k-1)*y[k];
                    }
                s->r[x_fonction + y_fonction*s->largeur] = couleur_r;
                s->v[x_fonction + y_fonction*s->largeur] = couleur_v;
                s->b[x_fonction + y_fonction*s->largeur] = couleur_b;
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
    s.largeur = 500;
    s.hauteur = 500;
    init(&s);
    files f = creer_file();
    enfile(&f,0,250);
    enfile(&f,50,350);
    enfile(&f,150,370);
    enfile(&f,200,300);
    enfile(&f,210,310);
    enfile(&f,499,170);
    FILE *sortie = fopen("Shenron.ppm", "w");
    rebord_anti_pb(&s);
    //trace_rectangle_vide(&s,0,0,0,200,499,0,499,200,30,30,240);
    //remplir(&s,30,30,30,30,240);
    //trace_cercle_vide(&s,250,200,150,240,30,0);
    //remplir(&s,250,200,240,30,0);
    //trace_rectangle_vide(&s,0,140,0,370,499,140,499,370,100,100,255);
    //remplir(&s,2,141,100,100,255);
    //Bezier_taille_n(&s,&f,6,255,255,0);
    //trace_ligne(&s,0,250,0,500,255,255,0);
    trace_ligne(&s,0,500,499,500,255,255,0);
    //trace_ligne(&s,499,170,499,500,255,255,0);
    faire_img(&s,sortie);
    free(s.b);
    free(s.r);
    free(s.v);
    return 0;
}
