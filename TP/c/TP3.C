#include <stdio.h>
#include <stdlib.h> 


// MENU THOMAS ICY


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
    if(l.t[y*(l.taille) + x] == 1){
        return 1;
            }
    return 0;
}

//Exo 5

int impasse(Laby l, int x, int y){
    int a = accessible(l,x,y);
    if( a == 0){
        return 0;
    }
    if((x == 0 && l.t[y*l.taille + x] == 1) || (x == l.taille && l.t[y * l.taille + x] == 1)){
        return 1;
    }
    else if((y == 0 && l.t[y*l.taille + x] == 1) || (y == l.taille && l.t[y * l.taille + x] == 1)){
    return 1;
}
    //Ici on regarde au bord du labyrinthe
    else {
        //A.K.A on est pas sur les bords
        int compteur = 0;
        if(l.t[(y-1)*l.taille + x] == 0){
            compteur++;
        }
        if(l.t[(y+1)*l.taille + x] == 0){
            compteur++;
        }
        if(l.t[y*l.taille + (x-1)] == 0){
            compteur++;
        }
        if(l.t[(y-1)*l.taille + (x+1)] == 0){
            compteur++;
        }
        if(compteur >= 3){
            return 0;
        }
    }
    return 1;
}

typedef struct file file;
struct file{
    int value_x,value_y;
    file *suivant,*precedent;
};



file creer_file(){
    file f;
    f.value_x = 0;
    f.value_y = 0;
    f.precedent = NULL;
    f.suivant = NULL;
    printf("%p", f.precedent);
    return f;
}

int file_vide(file f){
    if(f.suivant == NULL && f.precedent == NULL && f.value_x == NULL && f.value_y){
        return 0;
    }
    return 1;
}

void enfile(file *f, int x, int y){
    int a = file_vide(*f);
    if(a == 0){
        printf("Error");
        return;
    }

    file *current = f;
    while(current->suivant != NULL){
        current = current->suivant;
    }
    printf("%p",f);
    current->value_y= y;
    current->value_x = x;
    current->suivant = NULL;
    current->precedent = f;
    if( x == 0 && y == 0){
        current->precedent = NULL;
    }
    printf("%p ",f);
    printf("%d\n", current->precedent);
}

void tete(file f, int *x, int *y){
    int a = file_vide(f);
    if(a == 0){
        printf("Error");
        return;
    }
    file *current = &f;
    while(current->precedent != NULL){
        printf("%p", current->precedent);
        current = current->precedent;
    }
    *x = current->value_x;
    *y = current->value_y;
    
}

void defile(file *f){
    int a = file_vide(*f);
    if(a == 0){
        printf("Error");
        return;
    }
    int x,y;
    tete(*f,&x,&y);
    file *suppr = f;
    while(suppr->precedent != NULL){
        suppr = suppr->precedent;
    }
    file *tampon;
    tampon = suppr->suivant;
    free(suppr);
    tampon->precedent = NULL;
}

//Exo 8

void largeur(Laby l){
    int taille = l.taille;
    file f = creer_file();
    enfile(&f,0,0);
    int x,y;
    tete(f,&x,&y);
    while( x != (l.taille)-1 && y != (l.taille) - 1){
        l.t[ x * l.taille + y] = 4;
        if(x+1 < l.taille && x+1 >=0){
        enfile(&f,(x+1),y);
        }
        if(x-1 < l.taille && x-1 >=0){
        enfile(&f,(x-1),y);
        }
        if(y-1 < l.taille && y-1 >=0){
        enfile(&f,x,(y-1));
        }
        if(y+1 < l.taille && y+1 >= 0){
        enfile(&f,x,(y+1));
        }
        file *current = &f;
        while(current->precedent != NULL){
        current = current->precedent;
        }   
        current = current->suivant;
        x = current->value_x;
        y = current->value_y;
        if(l.t[x*l.taille + y] == 0){
            printf("OEeeeeeeeeee");
            return;
        }
    
    }
    return ;
}

int main()
{
    Laby l; 
    char Laby[] = "Laby.txt";
    l = charge_laby(Laby);
    /*int a =*/ impasse(l,8,1);
    // printf("%d",a);
    largeur(l);
    free(l.t);
    return 0;
}
