#ifndef LIB_READ_ARQ
#define LIB_READ_ARQ

#define FIM_DE_REGISTRO '#'
#define TAM_MAX_NOME 50
#define ARQ_REM '1'
#define ARQ_VAL '0'
#define STR_ARQ_VAL "0"

void busca_seq(FILE *destino,int ind_chave,char *chave,campos *campo, char **mensagens);
/*
  faz busca sequencial no arquivo DESTINO ateh encontrar o registro cuja chave 
  eh CHAVE. Imprime da tela o registro no mesmo formato que a funcao imprime_campo,
  imprimando cada campo por vez.
  Se n�o encontrar, imprime "ARQUIVO INEXISTENTE".
*/
int conta_campos(FILE *nome);
/*
  determina numero de campos
*/

char *le_arq (FILE *pointer, campos data);
/*
  le campo no arquivo conforme parametros passados
*/

void le_arq_var (FILE *pointer, campos *campo, char **mensagens);
/*
  le o proximo campo de acordo com as informacoes contidas no primeiro byte lido 
  do arquivo
*/

campos *vet_campos(FILE *nome,int n);
/*
  monta vetor de campos
*/

void imprime_arq(FILE *fileptr, campos *campo, int tam);
/*
  imprime da tela o arquivo de tamanho fico
*/

void imprime_arq_var(FILE *fileptr, campos *campo, char **mensagens);
/*
  imprime da tela o arquivo de tamanho variavel
*/

void imprime_campo(int indice,campos *campo, char *texto, char **mensagens);
/*
  imprime as informacoes acima, no seguinte formato:
  Tamanho do campo: tam Indice do campo: indice Campo: campo[indice] Conteudo: texto
*/

void imprime_reg(FILE *fileptr,campos *campo, char **mensagens);
/*
  imprime todos os campos de um registro a partir do endereco END
*/

void imprime_resumo(FILE *fileptr, char **mensagens);
/*
  Conta o numero de caracteres do arquivo de registros e imprime
  Conta o numero de registro do arquivo de registros e imprime
*/

void libera_campos(campos *vetor_campos, int num_campos);
/*
  Libera a memoria alocada para o vetor de campos
*/

int ret_indice_chave(campos *campo,int n_campos);
/*
  Retorna o indice do campo que for a chave
*/

void keys(FILE *fileptr, FILE *destino, int ind_chave, campos *campo);
/*
  Gera um arquivo com as chaves e os respectivos enderecos
*/

#endif         /*LIB_READ_ARQ*/