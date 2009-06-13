#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "trees.h"
#include "file.h"
#include "save_arq.h"
#include "read_arq.h"

void pre_tree(FILE *entrada,FILE *destino,FILE *desprezados,int ind_chave,campos *campo,int n_campos){
     /*no caso de construir a arvore*/
    noh busc_noh; 
    noh *reg;
    char *reg_completo = malloc(sizeof(char)*ftam(campo,n_campos));
    
    /*abertura abertura */
    
    
    fgetc(entrada);
    while(! eof(entrada)){
            fseek(entrada,-1,SEEK_CUR);
            /*MIRIA E RUBENS: le_chave*/  
            reg = le_chave(entrada,reg_completo,campo,n_campos); 
            /*MIRIA E RUBENS: busca_noh*/  
            busc_noh = busca_noh(destino,reg); 
    
            /*HELEN E PEDRO: adiciona_na_tree*/
            if(busc_noh.valor == 0) adiciona_na_tree(destino,busc_noh.end_noh,reg);
                
                 /*MIRIA E RUBENS: grava_reg_desp*/            
            else grava_reg_desp(desprezados,reg_completo);
                  /*grava o registro reg_completo no arquivo de desprezados*/
         
         
         fgetc(entrada);
         }         
}
pagina le_pag(FILE *destino,int endereco){
       pagina pag;
       int i;
       fseek(destino,endereco,SEEK_SET);
       fscanf(destino,"%d", &pag.ap_pai);
       for(i=0;i<9;i++) fscanf(destino,"%d %d", &pag.n[i].valor,&pag.n[i].end_noh);
       for(i=0;i<10;i++) fscanf(destino,"%d", &pag.f[i]);       
       return pag;
}
pagina le_pag_seq(FILE *destino){
       pagina pag;
       int i;
       fscanf(destino,"%d", &pag.ap_pai);
       for(i=0;i<9;i++) fscanf(destino,"%d %d", &pag.n[i].valor,&pag.n[i].end_noh);
       for(i=0;i<10;i++) fscanf(destino,"%d", &pag.f[i]);       
       return pag;
}
void escreve_pag(FILE *destino,int endereco,pagina pag){
       int i;
       fseek(destino,endereco,SEEK_SET);
       fprintf(destino,"%d ",pag.ap_pai);
       for(i=0;i<9;i++) fprintf(destino,"%d %d", pag.n[i].valor,pag.n[i].end_noh);
       for(i=0;i<10;i++) fprintf(destino," %d", pag.f[i]);       
}
int ftam(campos *campo,int n_campos){
    int tam = campo[n_campos-1].pf;
    return tam;
}
noh busca_noh(FILE *destino,noh *reg){
   
}
noh *le_chave(FILE *entrada, char *reg_completo, campos *campo, int n_campos){
    noh *novos_dados;
//    int tam = ftam(campos *campo,int n_campos);
    int tam = ftam(campo,n_campos);
//    int ind = ret_indice_chave(campos *campo,int n_campos);
    int ind = ret_indice_chave(campo,n_campos);
    int chave_tam = campo[ind-1].pf - campo[ind-1].pi + 1;
    char *chave = (char*) malloc (sizeof(char)*(chave_tam+1));
    /*gravação do valor do inicio do registro na variável a ser retornada*/
//    novos_dados.end_noh = ftell (entrada);
    novos_dados->end_noh = ftell (entrada);
    /*gravação do registro completo em reg_completo*/
//    fread (reg_completo,sizeof(char),tam,fileptr);
    fread (reg_completo,sizeof(char),tam,entrada);
    reg_completo[tam] = '\0';
    /*reposicionamento do ponteiro de arquivo no inicio do registro*/
    fseek (entrada, -tam, SEEK_CUR);
    fseek (entrada, campo[ind-1].pi, SEEK_CUR);
    /*gravação do valor da chave na variável a ser retornada*/
//  fread (chave,sizeof(char),chave_tam,fileptr);
    fread (chave,sizeof(char),chave_tam,entrada);
    chave[chave_tam] = '\0';
//  novos_dados.valor = atoi (chave);
    novos_dados->valor = atoi (chave);
    return novos_dados;
}

void grava_reg_desp(FILE *desprezados,char *reg_completo){
     
