#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void myprint(int **tab) {
  int i,j;
  for(i=0;i<4;i++) {
    for(j=0;j<4;j++) {
       printf("|");
       printf("%d", tab[i][j]);
       printf("|");
    }
    printf("\n");
  } 
 


}


int main(int argc, char *argv[]) {

  ;
  int **tab;
  tab = malloc(sizeof(int *) * 4);
  int i,j;
  for(i=0;i<4;i++) {
   tab[i] = malloc(sizeof(int)*4);
  }

    for(i=0;i<4;i++) {
      for(j=0;j<4;j++) {
        tab[i][j] = i+j;
      }
    }

   myprint(tab);

  free(tab);
  
  return (EXIT_SUCCESS);
}
