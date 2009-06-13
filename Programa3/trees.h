#ifndef STR_CAMPOS
#define STR_CAMPOS
typedef struct campos {
       int chave;
       char *nome;
       int pi;
       int pf;
       char tipo;
       char obrigatorio;
}campos;
#endif /*fim da redefinicao de STR_CAMPOS*/

typedef struct noh{
        /*eh uma dupla de uma chave e o endereco do registro referente à chave no arq de entrada*/
        int valor;
        int end_noh;
}noh;

typedef struct pagina{
        /*pagina eh um conjunto de 9 noh*/
        int ap_pai;
        noh n[9];
        int f[10];
}pagina;

void adiciona_na_tree(FILE *destino,int end_noh, noh *reg);
/*
  adiciona no noh de endereco busc_noh.endereco o conjunto reg (chave+end do 
  registro no arq de entrada).
*/
noh busca_noh(FILE *destino,noh *reg);
/*
  verifica se reg.valor esta na tree.
  busca noh na arvore, se não encontrar retorna 0,endereco do noh; se encontrar 
  retorna 1, endereco do registro. Se a arvore estiver vazia, retorna 0,0 
  (endereco do primeiro noh na arvore)
*/
void escreve_pag(FILE *destino,int endereco,pagina pag);
/*
  escreve no encedereco "endereco" a pagina "pag"
*/   
int ftam(campos *campo,int n_campos);
/*
  retorna o tamanho dos registros. Nota: Os registros tem tamanho fixo
*/
void grava_reg_desp(FILE *desprezados,char *reg_completo);
/*
  grava reg_completo no arquivo de desprezados
*/
noh *le_chave(FILE *entrada, char *reg_completo, campos *campo, int n_campos);
/*
  le no arquivo de entrada o próximo registro, retirando sua chave e endereco.
  Alem disso, copia o registro na integra para o &reg_completo
*/
pagina le_pag(FILE *destino,int endereco);
/*
  le, do endereco "endereco" uma pagina e a retorna
*/
pagina le_pag_seq(FILE *destino);
/*
  le o proximo registro do arquivo DESTINO
*/
void pre_tree(FILE *entrada,FILE *destino,FILE *desprezados,int ind_chave,campos *campo,int n_campos);
/*
  eh dentro desta funcao que chamaremos a busca pelo noh e, depois a adiciona_na_tree
*/
