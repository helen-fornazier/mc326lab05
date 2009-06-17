#ifndef LIB_TREE
#define LIB_TREE

#ifndef STRUCT_CAMPO
#define STRUCT_CAMPO
typedef struct campos {
       int chave;
       char *nome;
       int pi;
       int pf;
       char tipo;
       char obrigatorio;
}campos;
#endif  /*STRUCT_CAMPO*/

typedef struct noh{
        /*eh uma dupla de uma chave e o endereco do registro referente à chave no arq de entrada*/
        int valor;
        long int end_noh;
}noh;

typedef struct pagina{
        /*pagina eh um conjunto de 9 noh*/
        long int ap_pai;
        noh n[9];
        long int f[10];
}pagina;

void adiciona_na_tree(FILE *destino,long int end_noh, noh reg,long int *raiz);
/*
  adiciona no noh de endereco busc_noh.endereco o conjunto reg (chave+end do 
  registro no arq de entrada).
  Deve alterar o valor da variavel raiz, caso seja criado uma nova raiz.
  Deve-se colocar -1 para os ponteiros das paginas q nao tenham filhos
*/
noh busca_na_pag(pagina pag,noh reg,int ord);
/*
  Busca na pagina o valor de reg.valor. 
  Se encontrar, retorna 1 / end_noh do noh com chave=reg.valor.
  Se nao encontrar, retorna 0 / endereco do filho onde buscar
*/
noh busca_noh(FILE *destino,noh reg,long int end,int ord);
/*
  verifica se reg.valor esta na tree.
  busca noh na arvore, se não encontrar retorna 0,endereco do noh; se encontrar 
  retorna 1, endereco do registro. Se a arvore estiver vazia, retorna 0,0 
  (endereco do primeiro noh na arvore)
*/
void escreve_pag(FILE *f,long int ad,pagina pag);
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
noh le_chave(FILE *entrada, char *reg_completo, campos *campo, int n_campos);
/*
  le no arquivo de entrada o próximo registro, retirando sua chave e endereco.
  Alem disso, copia o registro na integra para o &reg_completo
*/
pagina le_pag(FILE *f,long int ad);
/*
  le, do endereco "endereco" uma pagina e a retorna
*/
void pre_tree(FILE *entrada,FILE *destino,FILE *desprezados,int ind_chave,campos *campo,int n_campos,int ord);
/*
  eh dentro desta funcao que chamaremos a busca pelo noh e, depois a adiciona_na_tree
*/
void graph_tree(FILE *entrada, FILE *destino, int ord, long int root);
/*
  Descrição: Lê a árvore de FILE *entrada e escreve de forma fácil de ser montada
   à mão em FILE *Destino
   FILE *entrada ==>  Arquivo de índice/árvore onde estão armazenados as páginas da árvore
    Obs: Seta o descritor de destino no início do arquivo
   FILE *destino ==>  Arquivo onde será escrito a árvore de forma fácil de ser montada
    Obs: Escreve apartir de onde o descritor de destino esteja setado
   int ord ==> ordem da árvore
   long int root ==> endereço da raíz no arquivo de índice/árvore
*/

#endif   /*LIB_TREE*/

