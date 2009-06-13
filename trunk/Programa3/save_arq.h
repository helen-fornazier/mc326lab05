#ifndef LIB_SAVE_ARQ
#define LIB_SAVE_ARQ

int grava_arq (FILE *pointer, char *texto);
/*
  grava o texto no arquivo pointer, retornando a quantidade de caracteres gravada
*/

int grava_arq_nbin (FILE *destino, int n, int qtde);
/*
  grava em um bytes o valor binario de n, retornando a quantidade de caracteres gravada
*/

char *trata_nome(char *ent, char *extensao);
/*
  retorna um ponteiro para o nome do arquivo de saido
*/

#endif  /*LIB_SAVE_ARQ*/
