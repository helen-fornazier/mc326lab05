#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "file.h"
#include "save_arq.h"
#include "read_arq.h"

int count_caractere(char *texto, char c){
    char *aux;
    int count=0;
    
    aux =texto;
    
    while ((aux = memchr(aux,c,strlen(aux))) != NULL){
        count++;
	aux++;
    }
    free(aux);
    return (count);
}
char *extrai_arq(FILE *fp){
     char c;
     int count = tam_arq(fp);
     char *p = (char*) malloc (sizeof(char) * (count+1));
     count = 0;
     while ((c=fgetc(fp))!=EOF) p[count++]=c;
     p[count]=FIM_STRING;
     return(p);
}
char *retorna_seq(char **texto, char *separadores){  
     int tam = strcspn(*texto,separadores);
     char *p = malloc(sizeof(char)*(tam+1));
     p = strncpy(p,*texto,tam);
     p[tam] = '\0';
     *texto = *texto+(tam+1); 
     return p;
}

char *ret_arg(char **texto, char *separadores){
     char *p;

     if(count_caractere(separadores,texto[0][0]) != 0) {
        (*texto)++;                                                                                             
        return "\0";
     } /*else*/
     p = retorna_seq(texto,separadores);      
     return p;
}

int tam_arq(FILE *fp){
     int i=0;
     char c;
     while ((c=fgetc(fp))!=EOF)
         i++;
     fseek(fp,0,SEEK_SET);
     return (i);
}

char **extrai_msg(char *texto_mensagens){
     int i;
     char *lida;
     char **mensagens = (char**) malloc (sizeof(char*)*NUMERO_DE_MENSAGENS);
	 for (i=0;i<NUMERO_DE_MENSAGENS;i++){
	 	  lida = ret_arg(&texto_mensagens, SEPARADOR_MENSAGEM);
	 	  mensagens[i] = (char*) malloc(sizeof(char)*(strlen(lida)+1));
	 	  strcpy(mensagens[i],lida);
          free(lida);
	 }
	 return mensagens;
}



