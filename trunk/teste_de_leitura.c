#include <stdio.h>
#include <stdlib.h>
#include "trees.h"

int main(int argc, char *argv[])
{
    FILE *fpag = fopen ("pagina.txt", "r+");
    int ord = 3;
    pagina pag, pag2;
    
    pag.n[0].valor=1;
    pag.n[1].valor=2;
    pag.n[0].end_noh=-1;
    pag.n[1].end_noh=-1;
    pag.f[0] = -1;
    pag.f[1]=-1;
    pag.f[2]=-1;
    pag.ap_pai=-1;
    
    escreve_pag(fpag, 0, pag);
    
    pag2 = le_pag (fpag, 0);
    
    printf("%d, %d\n", pag2.n[0], pag2.n[1]);
    

  
  system("PAUSE");	
  return 0;
}
