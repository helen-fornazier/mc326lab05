#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"

int grava_arq (FILE *pointer, char *texto){
     if (texto != NULL){
        fwrite (texto, sizeof(char), strlen (texto), pointer);
        return strlen(texto);
     }
     return 0;
}
int grava_arq_nbin (FILE *destino, int n, int qtde){
       fwrite(&n,1,qtde,destino);
       return 1;
}
char *trata_nome(char *ent, char *extensao){
     int tam = strlen(ent);
     int t_saida = strlen(extensao);
     char *temp = malloc(sizeof(char)*(tam+t_saida+1));
     strncpy(temp,ent,tam-1);
     temp[tam-4] = '\0';
     temp = strcat(temp,extensao);
     temp = strcat(temp,".txt");  
     return temp;
}
