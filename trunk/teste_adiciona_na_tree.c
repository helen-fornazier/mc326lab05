#include <stdio.h>
#include <stdlib.h>
#include "trees.h"

int main(int argc, char *argv[])
{
    FILE *fpag = fopen ("pagina.txt", "w+");
	escreve_pag(fpag, 0, new_page());

    int ord = 3;
    pagina pag;
	pagina pag2;
	long int root = 0;
	
	pag=new_page();
	pag2=new_page();
 	


    pag.n[1].valor=91624;
    pag.n[0].valor=718472;
    pag.n[0].end_noh=-1;
    pag.n[1].end_noh=-1;
    pag.f[0] = TAM_PAG+1;
    pag.f[1]=-1;
    pag.f[2]=-1;
    pag.ap_pai=-1;

    pag2.n[0].valor=61624;
    pag2.n[1].valor=518472;
    pag2.n[0].end_noh=-1;
    pag2.n[1].end_noh=-1;
    pag2.f[0] = -1;
    pag2.f[1]=-1;
    pag2.f[2]=-1;
    pag2.ap_pai=-1;

	adiciona_na_tree(fpag, &root, pag.n[0], ord-1);
	adiciona_na_tree(fpag, &root, pag.n[1], ord-1);
	adiciona_na_tree(fpag, &root, pag2.n[0], ord-1);
//	adiciona_na_tree(fpag, &root, pag2.n[1], ord-1);
    
    //escreve_pag(fpag, 0, pag);
	fseek(fpag, 0, SEEK_END);

    //escreve_pag(fpag, ftell(fpag), pag);
    
    pag2 = le_pag (fpag, 204);
    
    printf("%d, %d\n", pag2.n[0].valor, pag2.n[1].valor);
    

  
 // system("PAUSE");	
  return 0;
}
