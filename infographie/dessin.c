#include <stdio.h>
#include <stdlib.h>
#define TAILLE_IMG_LONG 1000
#define TAILLE_IMG_HAUT 1000


typedef struct{
    int longueur;
    int hauteur;
    int x_debut;
    int y_debut;
    int v,r,b;
    int *tab;
}   Surface ; 






unsigned appel(Surface *s){
    printf("Longueur et hauteur?\nValeur de la couleur en bleu, vert et rouge?\n");
    scanf("%d %d %d %d %d",&(s->longueur),&(s->hauteur),&(s->v),&(s->b),&(s->r));
    printf("Choisisez la position du début du rectangle, le x et le y\n");
    scanf("%d %d", &(s->x_debut), &(s->y_debut));
    if(TAILLE_IMG_LONG-s->longueur< s->x_debut) {
        printf("Il risque d'y avoir un souci, recommence\n\n\n");
        return appel(s);
}
}


void init(Surface *s){
    s->tab = malloc(3*TAILLE_IMG_HAUT*TAILLE_IMG_LONG*sizeof(int));

}

void draw_rect(Surface *s){
    int valeur_ajoute;
    for (int a= s->y_debut; a<=( s->y_debut + s->hauteur ); a++){
        for (int b =s->x_debut; b<=(s->x_debut + s->longueur); b++){
            int Aleatoire = rand();
            if(Aleatoire % 2 == 0){
                valeur_ajoute = 0;
            }
            else{
                valeur_ajoute = rand() % 50;
            }
            
            s->tab[3*(a*TAILLE_IMG_LONG+b)] = s->r + valeur_ajoute;
            // (s->r[xxx]);
            s->tab[3*(a*TAILLE_IMG_LONG+b)+1] = s->v+valeur_ajoute;
            // (s->vr[xxx]);
            s->tab [3*(a*TAILLE_IMG_LONG+b)+2]= s->b + valeur_ajoute;
            // (s->br[xxx]);

        }
    }
}

int CapValue(int n, int c, int d){
    if(n<c){return c;}
    if(n>d){return d;}
    return n;
}


int faire_img(Surface *s, FILE *f){
    
    int count = fprintf(f, "P3\n# writePGM\n%d %d\n%d\n",TAILLE_IMG_LONG, TAILLE_IMG_HAUT,255);
    for (int i =0 ; i < TAILLE_IMG_HAUT*TAILLE_IMG_LONG;i++) {
        count = count + fprintf(f, "%d %d %d ",CapValue(s->tab[3*i],0,255),CapValue(s->tab[3*i+1],0,255), CapValue(s->tab[3*i+2],0,255));
       
    }

    return count;
}  

int Nombre_rectangle(){
    int a;
    a = rand() % 40;
    return a;
}

int dessin_rect_alea(Surface *s){
    int n = rand() % 30;
    int valeur_ajoute = 0;
    int Surplus_x = 0;
    int Surplus_y = 0; 
    int plus_moins = 1;
    s->y_debut = 20 + rand() % 30;
    s->hauteur = 30 + rand() % 50;
    for (int k = 0;k<n;k++){
        s->x_debut =20 + rand()% 20 + Surplus_x;
        s->longueur = 60 + rand() % 20;
        if(s->longueur + s->x_debut > TAILLE_IMG_LONG){
            s->longueur = TAILLE_IMG_LONG - s->x_debut - 10;
        }

        s->y_debut = 20 + Surplus_y;
        int Alea = rand();
                if(Alea % 2 == 0){
                    plus_moins = -1;}
        s->r = rand() % 255;
        s->b = rand() % 255;
        s->v = rand() % 255;
        for (int a= (s->y_debut); a<=( s->y_debut+ s->hauteur ); a++){
            for (int b =s->x_debut; b<=(s->x_debut + s->longueur); b++){

                int Aleatoire = rand();
                if(Aleatoire % 2 == 0){
                    valeur_ajoute = 0;

                }
                else{
                    valeur_ajoute = rand() % 10;
                }
                s->tab[3*(a*TAILLE_IMG_LONG+b)] = s->r + valeur_ajoute;
                printf("%d\n",s->tab[3*(a*TAILLE_IMG_LONG+b)]);
                // (s->r[xxx]);
                s->tab[3*(a*TAILLE_IMG_LONG+b)+1] = s->v + valeur_ajoute;
                // (s->vr[xxx]);
                    // (s->br[xxx]);


       
            }
           
        }
 Surplus_x = Surplus_x + s->longueur + rand() %10 ; 
        
        if(s->x_debut + Surplus_x > TAILLE_IMG_LONG){
            Surplus_x = 0;
           
             
            Surplus_y = Surplus_y + s->hauteur +20;
            if(Surplus_y > TAILLE_IMG_HAUT){
                return 0;
        }
        }
    }
}



int plagiat(Surface *s){
    int valeur_ajoute;
    s->r = 255;
    s->b = 0;
    s->v = 0;
    for(int a = 30; a <= 970; a++){
        for (int b = 30; b <= 330; b++){
            int Aleatoire = rand();
            
            valeur_ajoute = rand() % 255;
       
            
            s->tab[3*(a*TAILLE_IMG_LONG+b)] = s->r - valeur_ajoute;
            // (s->r[xxx]);
            s->tab[3*(a*TAILLE_IMG_LONG+b)+1] = s->v - valeur_ajoute;
            // (s->vr[xxx]);
            s->tab [3*(a*TAILLE_IMG_LONG+b)+2]= s->b - valeur_ajoute;
            // (s->br[xxx]);
            
        }
    }
}

int main(int argc, char const *argv[])
{

   
    /* appel(&s);
    FILE *sortie = fopen("sortie.ppm", "w");
    if (sortie == NULL) {
        printf("Failed to open the output file.\n");
        return 3;}
    init(&s);
    draw_rect(&s);
    faire_img(&s,sortie);
    
    fclose(sortie);
    printf("Successfully written the image.\n"); 
    int n;
    Surface s;
    printf("Combien de rectangle voulez vous\n(pas trop non plus genre pas 656) ?\n");
    scanf("%d",&n); */


    Surface s;
    FILE *sortie = fopen("sortie.ppm","w");
    if (sortie == NULL) {
        printf("Failed to open the output file.\n");
        return 3;}
    init(&s);
    /* for(int i =0; i <n ; i++){
        appel(&s);
        draw_rect(&s);
        
    } */


    plagiat(&s);
    faire_img(&s,sortie);

    return 0;
}
