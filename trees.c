#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "trees.h"
#include "file.h"
#include "save_arq.h"
#include "read_arq.h"

void pre_tree(FILE *entrada,FILE *destino,FILE *desprezados,long int ind_chave,campos *campo,int n_campos,int ord){
     /*no caso de construir a arvore*/
    noh busc_noh; 
    noh reg;
    int i=0;
    int raiz=0;               /*possui o endereco da pagina raiz*/
    char *reg_completo = malloc(sizeof(char)*ftam(campo,n_campos));
    fgetc(entrada);
    while(!feof(entrada)){
            fseek(entrada,-1,SEEK_CUR); 
            reg = le_chave(entrada,reg_completo,campo,n_campos); 
            printf("reg.valor = %d, reg.end_noh = %d, contador = %d\n",reg.valor, reg.end_noh, ++i);
            /*MIRIA E RUBENS: busca_noh*/  
            busc_noh = busca_noh(destino,reg,raiz,ord); 
            printf("reg.valor = %d, reg.end_noh = %d\n", busc_noh.valor, busc_noh.end_noh);
            /*HELEN E PEDRO: adiciona_na_tree*/
            if(busc_noh.valor == 0) adiciona_na_tree(destino,busc_noh.end_noh,reg,&raiz);
                
                 /*MIRIA E RUBENS: grava_reg_desp*/            
            else grava_reg_desp(desprezados,reg_completo);
                  /*grava o registro reg_completo no arquivo de desprezados*/
         
         fgetc(entrada);
         }         
}
void adiciona_na_tree(FILE *destino,long int end_noh, noh reg,long int *raiz){
     /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
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
noh busca_noh(FILE *destino,noh reg,long int end,int ord){
    noh res; res.valor = 0; res.end_noh = 0;  /*retorna o resultado da busca na pagina*/
    char c;
    if(c = fgetc(destino) == EOF) return res;
    pagina pag = le_pag(destino,end);
    res = busca_na_pag(pag,reg,ord);
    if(res.valor == 1) return res;
    if(res.valor == 0 && res.end_noh == -1)
      {res.end_noh = end; return res;}
    busca_noh(destino,reg,res.end_noh,ord);  
}
noh busca_na_pag(pagina pag,noh reg,int ord){
    int i;
    noh ret;
    for(i=0;i<ord-1;i++) {
       if(reg.valor == pag.n[i].valor) 
         {ret.valor = 1; ret.end_noh = pag.n[i].end_noh; return ret;}
       if(reg.valor < pag.n[i].valor) 
         {ret.valor = 0; ret.end_noh = pag.f[i]; return ret;}
    }
    ret.valor = 0; ret.end_noh = pag.f[ord]; return ret; 
}
noh le_chave(FILE *entrada, char *reg_completo, campos *campo, int n_campos){
    noh novos_dados;
    int tam = ftam(campo,n_campos);
    int ind = ret_indice_chave(campo,n_campos);
    int chave_tam = campo[ind-1].pf - campo[ind-1].pi;
    char *chave = (char*) malloc (sizeof(char)*(chave_tam+1));
    reg_completo = (char*)malloc((sizeof(char))*(tam + 1));
    /*grava��o do valor do inicio do registro na vari�vel a ser retornada*/
    novos_dados.end_noh = ftell (entrada);
    /*grava��o do valor da chave na vari�vel a ser retornada*/
    fseek (entrada, campo[ind-1].pi - 1, SEEK_CUR);
    fread (chave,sizeof(char), chave_tam, entrada);
    chave[chave_tam] = '\0';
    novos_dados.valor = atoi (chave);
    /*reposicionamento do ponteiro de arquivo no inicio do registro*/
    fseek (entrada, -campo[ind-1].pf +1, SEEK_CUR);
    /*grava��o do registro completo em reg_completo*/
    fread (reg_completo,sizeof(char),tam,entrada);
    reg_completo[tam] = '\0';
    free (chave);
    return novos_dados;
}

void grava_reg_desp(FILE *desprezados,char *reg_completo){
     int tam = strlen(reg_completo);
     fseek (desprezados, 0, SEEK_END);
     fwrite(reg_completo,sizeof(char),tam,desprezados);
}

void graph_tree(FILE *entrada, FILE *destino, int ord, long int root){
     long int addr = 0;     /*addr ser� a vari�vel do endere�o do n� que representar� este*/
     pagina pag;           /*pagina que ser� lida linearmente do arquivo de entrada*/
     int i = 0, nkey = 0;  /*Contador da �rdem da �rvore, e contador de quantas chaves uma p�gina cont�m*/
     fseek(entrada, 0, SEEK_SET);     /*Seta o arquivo entrada no seu in�cio*/
     
     fprintf(destino, "RA�Z: n� %ld\n", root);         /*informa qual � o n� ra�z*/
     while(!feof(entrada)){
                addr = ftell(entrada);
                pag = le_pag(entrada, addr);
                fprintf(destino, "n�: %ld", addr);
                for(i=0; i<ord;i++){
                         if(pag.n[i].valor!=-1){  /*se a chave existir*/
                                   fprintf(destino, "(%ld,%d);", pag.f[i], pag.n[i].valor);
                                   nkey++;          /*incrementa o valor de chaves existentes*/
                         }
                }
                if(nkey!=0){
                         fprintf(destino, "(%ld)", pag.f[i]);
                         fprintf(destino, "Total Chaves = %d\n", nkey);
                         nkey = 0;
                }
     }
}
