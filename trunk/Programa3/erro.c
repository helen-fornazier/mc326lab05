#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "erro.h"
/*#include "read_arq.h"*/

void erro_argumentos (int argumento, char **argv, char **mensagens){
    if (argumento != n_arg) {
       fprintf(stderr,"%s\n", mensagens[0]);
       system("pause");
       exit (1);
    }
    if (strlen (argv[1]) == 0){
      fprintf (stderr,"%s\n", mensagens[1]);
      system("pause");
      exit(1);
    }
}
   
int Fclose (FILE *nome, char **mensagens){
     int i;
     if ((i=fclose(nome)) != 0){            
       fprintf (stderr,"%s\n", mensagens[3]);
       system("pause");
       exit (1);
     }
     return (i);
}

FILE *Fopen (char *nome, char *tipo, char **mensagens){
     FILE *pointer = fopen (nome,tipo);
     if (pointer == NULL) { 
         if(mensagens == NULL){
             fprintf (stderr,"Nao foi encontrado o arquivo %s na pasta do executavel.\nFavor inserir o arquivo de mensagens erro no idioma de sua preferencia\n", ARQUIVO_DE_MENSAGENS);
             system("pause");
             exit (1);
         }
         else
             fprintf (stderr,"%s\"%s\"\n", mensagens[2], nome); system("pause");exit (1); 
     }
     return (pointer);
}

void libera_erros(char **mensagens){
     int i;
	 for (i=0;i<NUMERO_DE_MENSAGENS;i++)
	 	  free(mensagens[i]);
	 free(mensagens);
}

int dif_num(char *texto){
     int cont;
     for (cont=strlen(texto)-1; cont>=0; cont--)
         if (!(isdigit(texto[cont]))) 
            return 1;
     return 0;
} 

int dif_alfanum(char *texto){
     int cont;
     for (cont=strlen(texto)-1; cont>=0; cont--)
         if (!(isalnum(texto[cont])) && (texto[cont] != ' ')) 
            return 1;
     return 0;
}

void testa_obrigatorio(char obrigatorio, int i, char *texto, char **mensagens){
     if(obrigatorio == 'N') return;
     if(texto == NULL) {
            fprintf(stderr,"O %d%s\n",i,mensagens[4]);
            system("PAUSE");
            exit (1);
     }
}
void falta_registro (char **mensagens){
     fprintf(stderr,"%s\n",mensagens[7]);
}

void removido_registro (char **mensagens){
     fprintf(stderr,"%s\n",mensagens[8]);
}

void sucesso (char **mensagens){
     fprintf(stderr,"%s\n",mensagens[11]);
}
