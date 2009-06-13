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

void escreve_pag(FILE *destino,int endereco,pagina pag);
/*
  escreve no encedereco "endereco" a pagina "pag"
*/     
pagina le_pag(FILE *destino,int endereco);
/*
  le, do endereco "endereco" uma pagina e a retorna
*/
void pre_tree(entrada,destino,desprezados,ind_chave,campo,n_campos);
/*
  eh dentro desta funcao que chamaremos a busca pelo noh e, depois a adiciona_na_tree
*/
