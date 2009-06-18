#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "trees.h"
#include "file.h"
#include "save_arq.h"
#include "read_arq.h"

/*Retorna a raíz*/
long int pre_tree(FILE *entrada,FILE *destino,FILE *desprezados,int ind_chave,campos *campo,int n_campos,int ord){
     /*no caso de construir a arvore*/
    noh busc_noh; 
    noh reg;
    int i=0;
    long int raiz=0;               /*possui o endereco da pagina raiz*/
    char *reg_completo = malloc(sizeof(char)*(ftam(campo,n_campos)+1));
    fgetc(entrada);
    while(!feof(entrada)){
            fseek(entrada,-1,SEEK_CUR); 
            reg = le_chave(entrada,reg_completo,campo,n_campos); 
            //printf("reg.valor = %d, reg.end_noh = %ld, contador = %d\n",reg.valor, reg.end_noh, ++i);
            /*MIRIA E RUBENS: busca_noh*/  
            busc_noh = busca_noh(destino,reg,raiz,ord); 
            //printf("reg.valor = %d, reg.end_noh = %ld\n", busc_noh.valor, busc_noh.end_noh);
            /*HELEN E PEDRO: adiciona_na_tree*/
            if(busc_noh.valor == 0) adiciona_na_tree(destino,&raiz,reg, ord-1);
                
                 /*MIRIA E RUBENS: grava_reg_desp*/            
            else grava_reg_desp(desprezados,reg_completo);
                  /*grava o registro reg_completo no arquivo de desprezados*/
         
         fgetc(entrada);
         }
	free(reg_completo);
	return raiz;
}

/*Funcão adiciona um noh em uma página, parametros
 * f-> o arquivo
 * *root-> ponteiro para o endereço da raiz
 * reg-> o nó a ser adicionado
 * ord - a ordem da árvore
 * ad - o endereço da pagina
 * adright - o endereço da página que fica a direira do reg*/

void add_node(FILE *f, long int *root, noh reg, int ord, long int ad, long int adright){
	pagina pag;
	pag = new_page();
	noh tempnoh, tempnoh2;
	int i, j, tempint=0;
	long int templint;
	
	pag=le_pag(f,ad);
	for(i=0;i<ord;i++)
		if(pag.n[i].valor==-1) tempint=1;
	
/* se tiver espaço, apenas insere o noh */
	if(tempint){
		for(i=0;i<ord;i++){
			if(reg.valor<pag.n[i].valor || pag.n[i].valor==-1){
				tempnoh=pag.n[i];
				pag.n[i]=reg;
				reg=tempnoh;
				templint=pag.f[i+1];
				pag.f[i+1]=adright;
				adright=templint;
			}
		}
		escreve_pag(f,ad,pag);
	}

/*caso contrário*/
	else{
/*Se a página não tem pai, cria ele*/
		pagina newpag;
		if(pag.ap_pai==-1){
			newpag=new_page();
			newpag.f[0]=ad;
			*root=newpagespace(f);
			escreve_pag(f,*root,newpag);
			pag.ap_pai=*root;
		}
		
/* divide a página em duas e vê onde fica o novo nó */		
		tempint=(ord/2);
		newpag=new_page();
		for(i=0,j=0;i<ord;i++){
			if(reg.valor<pag.n[i].valor){
				tempnoh=pag.n[i];
				pag.n[i]=reg;
				reg=tempnoh;
				templint=pag.f[i+1];
				pag.f[i+1]=adright;
				adright=templint;
			}
			if(i==tempint){ 
				tempnoh2=pag.n[i];
				pag.n[i].valor=-1;
				pag.n[i].end_noh=-1;
			}
			if(i>tempint){
				newpag.n[j]=pag.n[i];
				newpag.f[j]=pag.f[i];
				j++;

				pag.n[i].valor=-1;
				pag.n[i].end_noh=-1;
				pag.f[i]=-1;
			}
		}
		escreve_pag(f,ad,pag);
		newpag.n[j]=reg;
		newpag.f[j]=pag.f[i];
		pag.f[i]=-1;	
		newpag.ap_pai=pag.ap_pai;
	
/* escreve o novo nó */
		templint=newpagespace(f);
		escreve_pag(f,templint,newpag);

/*modifica o pai de todos os filhos do novo nó*/
		for(i=0;newpag.f[i]!=-1;i++){
			pag=le_pag(f,newpag.f[i]);
			pag.ap_pai=templint;
			escreve_pag(f,newpag.f[i],pag);
		}

/* insere o elemento que subiu na página pai */
		add_node(f,root,tempnoh2,ord,newpag.ap_pai,templint);
	
	}

}

/* insere um nó na arvore */
void adiciona_na_tree(FILE *f, long int *root, noh reg, int ord){
	noh temp;

	temp=busca_noh(f,reg,*root,ord+1);
	if(temp.valor) return;

	add_node(f,root,reg,ord,temp.end_noh,-1);

}

/*Funcao acha espaco no final de arquivo, devolve endereco*/
long int newpagespace(FILE *f){
	fseek(f,0,SEEK_END);
	return ftell(f);
}

pagina new_page(){
	int i;
	pagina pag;
	pag.ap_pai=-1;
	for(i=0;i<9;i++){
		pag.n[i].valor=-1;
		pag.n[i].end_noh=-1;
		pag.f[i]=-1;
	}
	pag.f[9]=-1;
	return pag;
}

pagina le_pag(FILE *destino,long int endereco){
       pagina pag;
	   pag = new_page();
       int i;
       fseek(destino,endereco,SEEK_SET);
       fscanf(destino,"%ld", &pag.ap_pai);
       for(i=0;i<9;i++){ 
		   	fscanf(destino,"%d", &pag.n[i].valor);
			fscanf(destino,"%ld",&pag.n[i].end_noh);
	   }
       for(i=0;i<10;i++) fscanf(destino,"%ld", &pag.f[i]);       
       return pag;
}
void escreve_pag(FILE *destino,long int endereco,pagina pag){
       int i;
       fseek(destino,endereco,SEEK_SET);
       fprintf(destino,"%6ld ",pag.ap_pai);
       for(i=0;i<9;i++){ 
		   fprintf(destino,"%6d ",pag.n[i].valor);
		   fprintf(destino,"%6ld ", pag.n[i].end_noh);
	   }
       for(i=0;i<10;i++) fprintf(destino,"%6ld ", pag.f[i]);       
	   fprintf(destino, "\n");
}


int ftam(campos *campo,int n_campos){
    int tam = campo[n_campos-1].pf;
    return tam;
}
noh busca_noh(FILE *destino,noh reg,long int end,int ord){
    noh res; res.valor = 0; res.end_noh = 0;  /*retorna o resultado da busca na pagina*/
    char c;
    if((c = fgetc(destino)) == EOF) return res;
    pagina pag = le_pag(destino,end);
    res = busca_na_pag(pag,reg,ord);
    if(res.valor == 1) return res;
    if(res.valor == 0 && res.end_noh == -1)
      {res.end_noh = end; return res;}
    return busca_noh(destino,reg,res.end_noh,ord);  
}

noh busca_na_pag(pagina pag,noh reg,int ord){
    int i = 0, nkey = 0;
    noh ret;
    for(i=0;i<ord-1;i++) {
       if(reg.valor == pag.n[i].valor) 
         {ret.valor = 1; ret.end_noh = pag.n[i].end_noh; return ret;}
       if(reg.valor < pag.n[i].valor) 
         {ret.valor = 0; ret.end_noh = pag.f[i]; return ret;}
	   if (pag.n[i].valor!=-1){	   nkey++;}
    }
    ret.valor = 0; ret.end_noh = pag.f[nkey]; return ret; 
}

noh le_chave(FILE *entrada, char *reg_completo, campos *campo, int n_campos){
    noh novos_dados;
    int tam = ftam(campo,n_campos);
    int ind = ret_indice_chave(campo,n_campos);
    int chave_tam = campo[ind-1].pf - campo[ind-1].pi;
    char *chave = (char*) malloc (sizeof(char)*(chave_tam+1));
    //reg_completo = (char*)malloc((sizeof(char))*(tam + 1));   não precisa malocar, pois já é mallocado fora, e aqui não é alterado fora da função
    /*gravação do valor do inicio do registro na variável a ser retornada*/
    novos_dados.end_noh = ftell (entrada);
    /*gravação do valor da chave na variável a ser retornada*/
    fseek (entrada, campo[ind-1].pi - 1, SEEK_CUR);
    fread (chave,sizeof(char), chave_tam, entrada);
    chave[chave_tam] = '\0';
    novos_dados.valor = atoi (chave);
    /*reposicionamento do ponteiro de arquivo no inicio do registro*/
    fseek (entrada, -campo[ind-1].pf +1, SEEK_CUR);
    /*gravação do registro completo em reg_completo*/
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
     fseek(entrada, 0, SEEK_SET);     /*Seta o arquivo entrada no seu início*/
     
	 long int addr = 0;     /*addr será a variável do endereço do nó que representará este*/
     pagina pag, pag2;           /*pagina que será lida linearmente do arquivo de entrada*/
     int i = 0, nkey = 0;  /*Contador da órdem da árvore, e contador de quantas chaves uma página contém*/
     
     fprintf(destino, "RAÍZ: nó %6ld\n", root);         /*informa qual é o nó raíz*/
	 pag = le_pag (entrada, addr);
     while(!feof(entrada)){
                fprintf(destino, "nó: %6ld\t", addr);
                for(i=0; i<ord-1;i++){
                         if(pag.n[i].valor!=-1){  /*se a chave existir*/
                                   fprintf(destino, "(%ld,%d),", pag.f[i], pag.n[i].valor);
                                   nkey++;          /*incrementa o valor de chaves existentes*/
                         }
                }
                if(nkey!=0){
                         fprintf(destino, "(%ld)\t", pag.f[nkey]);
                         fprintf(destino, "Total Chaves = %d\t Nó Pai: %ld\n", nkey, pag.ap_pai);
                         nkey = 0;
                }
                addr=addr+1+TAM_PAG;
                pag2 = le_pag(entrada, addr);
				if(pag2.n[0].valor == pag.n[0].valor) break;
				pag = pag2;
     }
}

