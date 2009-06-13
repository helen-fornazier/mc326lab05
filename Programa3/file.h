#ifndef LIB_FILE
#define LIB_FILE
typedef struct campos {
       int chave;
       char *nome;
       int pi;
       int pf;
       char tipo;
       char obrigatorio;
}campos;


int count_caractere(char *texto, char c);
/*
  Funcao que retorna a quantidade de vezes que o caractere C aparece em texto 
*/
char *extrai_arq(FILE *fp);
/*
  Funcao que extrai o conteudo de um arquivo texto para uma string
*/

char **extrai_msg(char *texto_mensagens);
/*
  Transforme a string de mensagens em um vetor de mensagens
*/
char *ret_arg(char **texto, char *separadores);
/*
  Retorna sempre o primeiro argumento de TEXTO. 
  Altera TEXTO.
  Se TEXTO comecar por um separador, retorna NULL
*/

char *retorna_seq(char **texto, char *separadores);
/*
  Recebe um texto e um conjunto de separadores no formato de char* e retorna 
  um ponteiro p/uma string formada pela 1a sequencia de caracteres de TEXTO 
  diferentes de SEPARADORES. 
*/

int tam_arq(FILE *fd);
/*
  Funcao que retorna o tamanho do arquivo
*/

#endif /*LIB_FILE*/
