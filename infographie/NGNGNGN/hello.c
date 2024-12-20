#include <stdio.h>
#include <math.h>

int main(void) {
  int i ;
  do {printf("Choisi un numéro entre 1 et 15\n");
  scanf("%d", &i);} while(i<1 || i> 15);
  long int Nb = 0;
  long int Nb_tot = 0;
  for(int k =1 ;k <=i ; k++){
    printf("%ld\n",Nb);
    Nb = Nb + 5*pow(10,k-1);
    Nb_tot = Nb_tot + Nb;
  }
   while (Nb_tot > 1000000000000000) {
    Nb_tot = Nb_tot/10;
     ;} 
  
  printf("%ld",Nb_tot);
  return 0;
}
