#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "erro.h"
#include "file.h"
#include "trees.h"
#include "read_arq.h"
#include "save_arq.h"

int main(int argc, char *argv[])
{
    char *texto_mensagens;    /*texto extra�do do arquivo de configura��o de mensagens*/  
    FILE *fileptr, *destino, *entrada, *desprezados, *desc_tree;
    char **vazio = NULL; 
    char **mensagens;         /*vetor de mensagens*/  
    int n_campos;             /*numero de campos*/
    campos *campo;
    int ind_chave;
    noh *busc_noh;
    int op = 1;
    int ord;                  /*ordem da arvore*/
    char *reg_completo;       /*alocado dinamicamente dentro da funcao le_chave()*/
    noh reg;
    int buscar;
    noh achou;
        
    /*Arquivo de erros*/
    fileptr = Fopen(ARQUIVO_DE_MENSAGENS,"r", vazio);
    texto_mensagens = extrai_arq(fileptr);
    Fclose(fileptr, mensagens);
  
    /*Construcao do vetor de erros*/
    mensagens = extrai_msg(texto_mensagens);
    free(texto_mensagens);
 
    /*erro no parametro de entrada*/
    erro_argumentos (argc , argv, mensagens);
      
   /*abre arquivo de campos- de configuracao*/
    fileptr = Fopen(ARQUIVO_DE_FORMATO,"r", mensagens); 
     
    /*determina numero de campos*/
    n_campos = conta_campos(fileptr);
      
    /*vetor de campos*/
    fseek (fileptr, 0, SEEK_SET);
    campo = vet_campos(fileptr,n_campos);   
    Fclose(fileptr, mensagens);
  
    /*ord recebe o valor da ordem da arvore dada pelo usuario*/
    ord = atoi(argv[1]);
    
    /*ABERTURA DOS ARQUIVOS*/
    /*abertura do arquivo de entrada*/
    entrada = Fopen(argv[2],"r", mensagens);
        
    /*abertura do arquivo da arvore*/
    destino = Fopen(argv[3],"w+", mensagens);
    
    /*abertura do arquivo de desprezados*/
    desprezados = Fopen(argv[4],"w+", mensagens);

    /*abertura do arquivo de descricao da arvore*/
    desc_tree = Fopen(argv[5],"w", mensagens);
        
    /*INICIO*/    
    /*gerar arvore*/
    while (op != 0){
          printf ("***********************************\n");
          printf ("0 = Sair\n1 = Gerar arvore-B de indices\n2 = Fazer busca por chave\n3 = Gerar \"desenho\" da arvore\n");
          printf ("***********************************\n");
          scanf (" %d", &op);
          switch (op){
                 case 0: 
                         break;
                 case 1:
                         ind_chave = ret_indice_chave(campo,n_campos);
                         pre_tree(entrada,destino,desprezados,ind_chave,campo,n_campos,ord);
                         sucesso (mensagens);
                         free (reg_completo);
                         break;
                 case 2:
                         reg.end_noh = 0;
                         printf ("Digite chave de busca (RA): ");
                         scanf ("%d", &reg.valor);
                         achou = busca_noh(destino,reg,0,ord);
                         printf("reg.valor = %d, reg.end_noh = %d\n", achou.valor, achou.end_noh);
                          /*busca por chave = aplicar fun��o utilizada dentro da construcao da arvore*/
                          break;
                 case 3:
                          /*desenhar a arvore*/
                          break;
                 default:
                          break;
          }
    }
 
    /*Libera memoria e fecha arquivos*/
    Fclose(entrada,mensagens);
    Fclose(destino,mensagens);
    Fclose(desprezados,mensagens);
    Fclose(desc_tree,mensagens);
    libera_erros(mensagens);
    libera_campos(campo, n_campos);
    system("pause");
    return 0;
}
    