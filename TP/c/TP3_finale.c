#include <stdio.h>
#include <stdlib.h> 


// MENU THOMAS ICY
// Dans ce problème, les coordonnées du laybrinthe seront traité comme ceci
//      axe x
// axe  0 1 0
//      1 1 0
//  y   1 0 0 
//Ainsi, pour acceder à la case (x,y), on recherche de cette manière dans le tableau : t[y*largeur +x]
//avec x et y allant de 0 à taille-1


typedef struct{
    int taille;
    int *t;
} Laby ; 

Laby charge_laby(char *nom){
    Laby l;
    int b;
    FILE *f = fopen(nom,"r");
    if( f == NULL) { 
		printf("Failed to open the input file.\n");
        return l;
	}
    fscanf(f,"%d", &(l.taille));
    (l.t) = ( int *)malloc( l.taille * l.taille * sizeof(int));
    if (l.t == NULL){
        printf("Failed to create t");
        return l;
    }
    for(int k = 0;k < l.taille*l.taille;k++){
        int a;
        fscanf(f,"%d ",&a);
        l.t[k] = a;
    }
    fclose(f);
    return l;
}

//Exo 3

int dans_laby(Laby l,int x, int y){
    if(l.t[y*l.taille + x] == 0 || l.t[y*l.taille + x] == 1 || l.t[y*l.taille + x] == 2 || l.t[y*l.taille + x] == 3 ||l.t[y*l.taille + x] == 4){
        return 1;
    }
    return 0;
}

//Exo 4

int accessible(Laby l,int x, int y){
    int a = dans_laby(l,x,y);
    if(a == 0){
        return 0;
    }
    int b = l.t[y*(l.taille) + x]; 
    if(l.t[y*(l.taille) + x] == 1 || l.t[y*(l.taille) + x] == 4){
        return 1;
            }
    return 0;
}

//Exo 5
//Pour simplifier la fin du problème, on considère que 3, étant donné que l'on est dans une impasse, est vu comme un mur.

int impasse(Laby l, int x, int y){
    int a = accessible(l,x,y);
    if(x == l.taille-1 && l.taille-1){
        return 1;
    }
    if( x == 0 || y == 0 || x == l.taille -1 || y == l.taille - 1){
    
    if( a == 0){
        return 0;}
    if (x == 0 && y == 0){
        return 1;
    }
    if ((x == 0 && y == l.taille -1 && l.t[(y-1)*l.taille]==0) || (x == 0 && y == l.taille -1 && l.t[y * l.taille + 1]==0) || (x == 0 && y == l.taille -1 && l.t[(y-1)*l.taille]== 3) || (x == 0 && y == l.taille -1 && l.t[y * l.taille + 1]==3)){
        return 0;
    }
    if (( y == 0 && x == l.taille-1 && l.t[x-1] == 0) || (y == 0 && x == l.taille-1 && l.t[x + l.taille] == 0) || ( y == 0 && x == l.taille-1 && l.t[x-1] == 3) || (y == 0 && x == l.taille-1 && l.t[x + l.taille] == 3)){
        return 0;
    }
    if( x == 0){
        int compteur = 0;
        if(l.t[(y-1)*l.taille] == 0 || l.t[(y-1) * l.taille] == 3 ){
            compteur++;
        } 
        if(l.t[(y+1) * l.taille] == 0 || l.t[(y+1) * l.taille] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + 1] == 0 || l.t[y*l.taille + 1] == 3){
            compteur++;
        }
        if(compteur >=2){
            return 0;
        }
    
    }
    if(x == l.taille-1){
        int compteur = 0;
        if(l.t[(y-1)*l.taille] == 0 || l.t[(y-1) * l.taille] == 3 ){
            compteur++;
        } 
        if(l.t[(y+1) * l.taille] == 0 || l.t[(y+1) * l.taille] == 3){
            compteur++;
        }
        if(l.t[y*l.taille - 1] == 0 || l.t[y*l.taille - 1] == 3){
            compteur++;
        }
        if(compteur >=2){
            return 0;
        }
    }
    if(y == 0){
        int compteur = 0;
        if(l.t[(y+1)*l.taille + x] == 0 || l.t[(y+1)*l.taille + x] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + x + 1 ] == 0 || l.t[y*l.taille + x + 1 ] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + x - 1 ] == 0 || l.t[y*l.taille + x - 1 ] == 3){
            compteur++;
        }
        if (compteur >= 2){
            return 0;
        }
    }
    if(y == l.taille-1){
        int compteur = 0;
        if(l.t[(y-1)*l.taille + x] == 0 || l.t[(y+1)*l.taille + x] == 3){
        compteur++;
        }
        if(l.t[y*l.taille + x + 1 ] == 0 || l.t[y*l.taille + x + 1 ] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + x - 1 ] == 0 || l.t[y*l.taille + x - 1 ] == 3){
            compteur++;
        }
        if (compteur >= 2){
            return 0;
        }
    }
    }
    else {
        //A.K.A on est pas sur les bords
        int compteur = 0;
        if(l.t[(y-1)*l.taille + x] == 0 || l.t[(y-1)*l.taille + x] == 3){
            compteur++;
        }
        if(l.t[(y+1)*l.taille + x] == 0 || l.t[(y+1)*l.taille + x] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + (x-1)] == 0 || l.t[y*l.taille + (x-1)] == 3){
            compteur++;
        }
        if(l.t[y*l.taille + (x+1)] == 0 || l.t[y*l.taille + (x+1)] == 3){
            compteur++;
        }
        if(compteur >= 3){
            return 0;
        }
    }
    return 1;
}


typedef struct elem elem;
struct elem{
    int value_x,value_y;
    elem *suivant;
};

typedef struct file file;
struct file{
    elem *premier;
    elem *dernier;
};



file creer_file(){
    file *f = malloc(sizeof(*f));
    f->dernier = NULL;
    f->premier = NULL;
    elem *elem = malloc(sizeof(*elem));
    if(f == NULL && elem == NULL){
        exit(EXIT_FAILURE);
    }
    return *f;
}

int file_vide(file f){
    if ( &f == NULL){
        return 1;
    }
    return 0;
}

void enfile(file *f, int x, int y){
    elem *new = malloc(sizeof(*new));
    if (f == NULL && new == NULL){
        printf("Nope");
        exit(EXIT_FAILURE);
    }
    new->value_x = x;
    new->value_y = y;
    new->suivant = NULL;
    //printf("%p\n", new);
    //printf("%p\n", new->suivant);
    if (f->dernier == NULL && f->premier == NULL){
        f->premier = new;
    }
    else{
        f->dernier->suivant = new;}
    f->dernier = new;
    
   
    //printf("%p\n", f->premier);
    //printf("%p\n", f->dernier);
}

void tete(file f, int *x, int *y){
    int a = file_vide(f);
    if (a == 1){
        printf("Error");
        return;
    }
    //printf("%p\n",f.premier);
    elem *prems = f.premier;
     *x = prems->value_x;
     *y = prems->value_y;
}

void defile(file *f){
    elem *suppr = f->premier;
    //printf("%p\n", suppr);
    //printf("%p\n", f->premier->suivant);
    f->premier = f->premier->suivant;
    free(suppr);
    //printf("%p\n", f->premier);
}

void largeur(Laby l){
    int taille = l.taille;
    file f = creer_file();
    enfile(&f,0,0);
    int x,y;
    tete(f,&x,&y);
    while(x != (taille -1) || y != taille -1){
        if (x != 0 && x != taille -1 && y !=0 && y != taille-1){
            l.t[y * taille + x] = 4;
            int a = accessible(l,x-1,y);
            if (a == 1){
                enfile(&f,x-1,y);
            }
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                enfile(&f,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                enfile(&f,x,y+1);
            }
        }
        else if(x ==0 && y != 0 && y != taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                enfile(&f,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                enfile(&f,x,y+1);
            }

        }
        else if(x == taille -1 && y != 0 && y != taille-1){
            int a = accessible(l,x-1,y);
            if (a == 1){
                enfile(&f,x-1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                enfile(&f,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                enfile(&f,x,y+1);
            }
        }
        else if (x == taille -1 && y ==0){
            int a = accessible(l,x-1,y);
            if (a == 1){
                enfile(&f,x-1,y);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                enfile(&f,x,y+1);   
            }
        }
        else if(x == 0 && y == taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
            int d = accessible(l,x,y-1);
            if (d == 1){
                enfile(&f,x,y-1);
            }
        }
                else if (x == taille -1 && y ==0){
            int a = accessible(l,x-1,y);
            if (a == 1){
                enfile(&f,x-1,y);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                enfile(&f,x,y+1);   
            }
        }
        else if(x == 0 && y == taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
            int d = accessible(l,x,y-1);
            if (d == 1){
                enfile(&f,x,y-1);
            }
        }
        else if(y == l.taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
            int d = accessible(l,x,y-1);
            if (d == 1){
                enfile(&f,x,y-1);
            }
            int c = accessible(l,x-1,y);
            if (c == 1){
                enfile(&f,x-1,y);
            }  
        }
        else if( x == l.taille -1 && y != 0 && y !=taille -1){
            int a = accessible(l,x-1,y);
            if (a == 1){
                enfile(&f,x-1,y);
            }
            int b = accessible(l,x,y+1);
            if (b == 0){
                enfile(&f,x,y+1);
            }
            int c = accessible(l,x,y-1);
            if (c == 0){
                enfile(&f,x,y-1);
        }
        }
        //ce dernier cas si dessous ne sers que pour l'adresse 0,0
        else{
            int a = accessible(l,x,y+1);
            if (a==1){
                enfile(&f,x,y+1);
            }
            int b = accessible(l,x+1,y);
            if (b == 1){
                enfile(&f,x+1,y);
            }
        }
        l.t[x + y*taille] = 2;
        defile(&f);
        int comptage = 0;
        tete(f,&x,&y);
        while(comptage == 0){
        int traque = accessible(l,x,y);
        if(traque == 0){
                defile(&f);
                tete(f,&x,&y);
            }
        else{
            int traque2 = impasse(l,x,y);
            if(traque2 == 0){
                l.t[x + y*taille] = 3;
                defile(&f);
                tete(f,&x,&y);
                int vide = file_vide(f);
                if (vide == 1){
                    printf("Y'a pas de solutions possible");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                l.t[x + y*taille] = 4;
                comptage++;
            }
        }
        }
        for(int k = 0; k< taille; k++){
            for(int i =0; i < taille;i++){
                printf("%d ",l.t[i + k*taille]);
            }
            printf("\n");
        }
        printf("____________\n");

    }
    printf("Chemin possible !\n");

}

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


//Exo 11;
pile *creer_pile(){
    pile *p =malloc(sizeof(*p));
    p->dernier = NULL;
    p->premier = NULL;
    elem_pile *elem_pile = malloc(sizeof(*elem_pile));
    if(p == NULL && elem_pile == NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}

int pile_vide(pile *p){
    if (&p == NULL){
        return 1;
    }
    return 0;
}

void empile(pile **p, int x, int y){
    int a = pile_vide(*p);
    if (a == 1){
        exit(EXIT_FAILURE);
    }
    elem_pile *nouv = malloc(sizeof(*nouv));
    nouv->coord_x = x;
    nouv->coord_y = y;
    nouv->precedent = (*p)->premier;
    if ((*p)->premier == NULL && (*p)->dernier == NULL){
        (*p)->dernier = nouv;
    }
    (*p)->premier = nouv;
}

void sommet(pile *p, int *x, int *y){
    int a = pile_vide(p);
    if (a == 1){
        exit(EXIT_FAILURE); 
    }
    elem_pile *premier = (*p).premier;
    *x = premier->coord_x;
    *y = premier->coord_y;

}

void depile(pile **p){  
    int a = pile_vide(*p);
    if (a == 1){
        exit(EXIT_FAILURE);
    }   
    elem_pile *suppr = (*p)->premier;
    (*p)->premier = (*p)->premier->precedent;
    free(suppr); 
}

void profondeur(Laby l){
    int taille = l.taille;
    pile *p = creer_pile();
    empile(&p,0,0);
    int x,y;
    sommet(p,&x,&y);
        while(x != taille -1 || y != taille -1){
        if (x != 0 && x != taille -1 && y !=0 && y != taille-1){
            l.t[y * taille + x] = 4;
            int a = accessible(l,x-1,y);
            if (a == 1){
                empile(&p,x-1,y);
            }
            int b = accessible(l,x+1,y);
            if (b == 1){
                empile(&p,x+1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                empile(&p,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                empile(&p,x,y+1);
            }
        }
        else if(x ==0 && y != 0 && y != taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                empile(&p,x+1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                empile(&p,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                empile(&p,x,y+1);
            }

        }
        else if(x == taille -1 && y != 0 && y != taille-1){
            int a = accessible(l,x-1,y);
            if (a == 1){
                empile(&p,x-1,y);
            }
            int c = accessible(l,x,y-1);
            if( c == 1){
                empile(&p,x,y-1);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                empile(&p,x,y+1);
            }
        }
        else if (x == taille -1 && y ==0){
            int a = accessible(l,x-1,y);
            if (a == 1){
                empile(&p,x-1,y);
            }
            int d = accessible(l,x,y+1);
            if(d==1){
                empile(&p,x,y+1);   
            }
        }
        else if(x == 0 && y == taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                empile(&p,x+1,y);
            }
            int d = accessible(l,x,y-1);
            if (d == 1){
                empile(&p,x,y-1);
            }
        }
        else if(y == l.taille-1){
            int b = accessible(l,x+1,y);
            if (b == 1){
                empile(&p,x+1,y);
            }
            int d = accessible(l,x,y-1);
            if (d == 1){
                empile(&p,x,y-1);
            }
            int c = accessible(l,x-1,y);
            if (c == 1){
                empile(&p,x-1,y);
            }  
        }
        else if( x == l.taille -1 && y != 0 && y !=taille -1){
            int a = accessible(l,x-1,y);
            if (a == 1){
                empile(&p,x-1,y);
            }
            int b = accessible(l,x,y+1);
            if (b == 0){
                empile(&p,x,y+1);
            }
            int c = accessible(l,x,y-1);
            if (c == 0){
                empile(&p,x,y-1);
            }
        }

        //ce dernier cas si dessous ne sers que pour l'adresse 0,0
        else{
            int a = accessible(l,x,y+1);
            if (a==1){
                empile(&p,x,y+1);
            }
            int b = accessible(l,x+1,y);
            if (b == 1){
                empile(&p,x+1,y);
            }
        }
        l.t[x + y*taille] = 2;
        int comptage = 0;
        sommet(p,&x,&y);
        while(comptage == 0){
            printf("%d %d\n",x,y);
            int traque = accessible(l,x,y);
            if(traque == 0){
                    depile(&p);
                    sommet(p,&x,&y);
                }
            else{
                int traque2 = impasse(l,x,y);
                if(traque2 == 0){
                    l.t[x + y*taille] = 3;
                    depile(&p);
                    sommet(p,&x,&y);
                    int vide = pile_vide(p);
                    if (vide == 1){
                        printf("Y'a pas de solutions possible");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    l.t[x + y*taille] = 4;
                    comptage++;
                }
            }
        }
        for(int k = 0; k< taille; k++){
            for(int i =0; i < taille;i++){
                printf("%d ",l.t[i + k*taille]);
            }
            printf("\n");
        }
        printf("____________\n");
    }
    printf("Chemin possible !\n");
    free(p);

}



//Exo 13
//La fonction largeur peut ne pas completer les impasses correctement si le labyrinthe est organisé d'une certaine manière
//Si on ne retourne pas à une certaine position par exemple
//Tandis que la fonction profondeur trouvera un chemin, sans passer par tous 






int main()
{
    Laby l;
    char Laby[] = "Laby.txt";
    l = charge_laby(Laby);
    /*elem m;
    file f = creer_file();  
    char Laby[] = "Laby.txt";
    l = charge_laby(Laby);
    int a = impasse(l,8,1);
    // printf("%d",a);
    largeur(l);*/

    /*
    pile *p = creer_pile();
    empile(&p,0,0);
    int x,y;
    sommet(p,&x,&y);
    printf("%d %d\n", x,y);
    empile(&p,1,0);
    sommet(p,&x,&y);
    printf("%d %d\n", x,y);
    depile(&p);
    sommet(p,&x,&y);
    printf("%d %d", x,y);
    free(l.t); */
    //largeur(l);
    //profondeur(l);

    return 0;   
}
