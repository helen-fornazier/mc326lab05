#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "file.h"
#include "read_arq.h"
#include "save_arq.h"

void busca_seq(FILE *fileptr,int ind_chave,char *chave,campos *campo, char **mensagens){
     int ind,tam;    
     char *texto,a;

     a = getc(fileptr);
     while (!(feof(fileptr))) {
            fseek(fileptr,-1,SEEK_CUR);
            if(fgetc(fileptr) == ARQ_REM){
                do{
                   a=fgetc(fileptr);
                }while(a != FIM_DE_REGISTRO);
                fgetc(fileptr);
            }
            else {
                 while((a=fgetc(fileptr))!=FIM_DE_REGISTRO){
                    fseek(fileptr,-1,SEEK_CUR);
                    tam=fgetc(fileptr);
                    ind=fgetc(fileptr);
                    if(ind == ind_chave){
                           texto = malloc(sizeof(char)*(tam-1));
                           fread(texto,1,tam-2,fileptr);
                           texto[tam-2] = FIM_STRING;
                           if(strcmp(texto,chave) == 0){
                               imprime_reg(fileptr,campo, mensagens);
                               printf("\n");
                               free(texto);
                               return;
                           }
                           else{
                               do{
                                   a=fgetc(fileptr);
                               }while(a != FIM_DE_REGISTRO);
                               fseek(fileptr,-1,SEEK_CUR);
                           }
                           free(texto);
                    }
                    else
                        fseek(fileptr,tam-2,SEEK_CUR);
                 }
                 a=fgetc(fileptr);
            }
    }
    falta_registro(mensagens);
}
int conta_campos(FILE *nome){    
    char *dado_n;
    char dado_t, dado_o;
    int chave, dado_i, dado_f, i=0;     

    dado_n = (char*)malloc(sizeof(char)*TAM_MAX_NOME);

    while (!(feof(nome))) {
          fscanf (nome, "%d %s %d %d %c %c", &chave, dado_n, &dado_i, &dado_f, &dado_t, &dado_o);
          i++;
    }

    free(dado_n);

    return (i-1);
}
char *le_arq (FILE *pointer, campos data){
     char *texto = (char*)malloc(sizeof(char)*(data.pf - data.pi +2));

     fread (texto, sizeof(char), data.pf - data.pi + 1, pointer);
     texto[data.pf - data.pi +1] = '\0';

     return texto;
}
void imprime_arq(FILE *fileptr, campos *campo, int tam){
     int reg = 0, i;
     char *texto;
     fgetc(fileptr);
     while (!(feof(fileptr))) {
          fseek(fileptr,-1,SEEK_CUR);
          for (i=0; i<tam-1; i++) {
              fseek (fileptr, reg + campo[i].pi -1, SEEK_SET);
              texto = le_arq (fileptr, campo[i]); 
              fprintf(stderr, "%s = %s ",campo[i].nome,texto);
              free (texto);
          }         
          reg += campo[tam-1].pf;
          fgetc(fileptr);
          fprintf(stderr, "\n");          
    }
}
void le_arq_var (FILE *pointer, campos *campo, char **mensagens){
     int tam,indice;
     char *texto;

     tam = fgetc(pointer);
     indice = fgetc(pointer);
     texto = (char*)malloc(sizeof(char)*(tam-1));
     fread (texto, sizeof(char), tam-2, pointer);
     texto[tam-2] = FIM_STRING;
     imprime_campo(indice,campo,texto, mensagens);
     free(texto);
}
void imprime_campo(int indice,campos *campo, char *texto, char **mensagens){
     printf("%s =",campo[indice-1].nome);     
     printf(" %s ",texto);
}
void imprime_reg(FILE *fileptr,campos *campo, char **mensagens){
     int a;
     
     a=fgetc(fileptr);
     do{
         fseek(fileptr,-1,SEEK_CUR);
         le_arq_var (fileptr,campo,mensagens);
     }while(fgetc(fileptr) != FIM_DE_REGISTRO);
}
void imprime_arq_var(FILE *fileptr, campos *campo, char **mensagens){
     char a;
     a = getc(fileptr);
     while (!(feof(fileptr))) {
          fseek(fileptr,-1,SEEK_CUR); 
          if(fgetc(fileptr) == ARQ_REM){
                do{a=fgetc(fileptr);}
                while(a != FIM_DE_REGISTRO);
                fgetc(fileptr);
          }
          else{        
               while((a=fgetc(fileptr)) != FIM_DE_REGISTRO){
                    fseek(fileptr,-1,SEEK_CUR);
                    le_arq_var (fileptr,campo,mensagens);
               } 
               printf("\n");  
               a=fgetc(fileptr); 
          }
                    
    }
}        
campos *vet_campos(FILE *fileptr,int n){
      int i;
      campos *data = (campos*)malloc(sizeof(campos)*n);
      for (i=0;i<n;i++){
        data[i].nome = (char*) malloc (sizeof(char)*TAM_MAX_NOME);
        fscanf (fileptr, "%d %s %d %d %c %c", &data[i].chave, data[i].nome, &data[i].pi, &data[i].pf, &data[i].tipo, &data[i].obrigatorio);
      }
      return data;
}

void imprime_resumo(FILE *fileptr, char **mensagens){
      char c;
      int count_char=0, count_reg=0;

      while ((c=fgetc(fileptr))!=EOF){
        count_char++;
        if (c==FIM_DE_REGISTRO)
          count_reg++;
      }
      printf("%s: %d\n", mensagens[9], count_char);
      printf("%s: %d\n", mensagens[10], count_reg);
}
void libera_campos(campos *vetor_campos, int num_campos){
     int i;
	 for (i=0;i<num_campos;i++)
	 	  free(vetor_campos[i].nome);
	 free(vetor_campos);
}
int ret_indice_chave(campos *campo,int n_campos){
    int i;
    for(i=0;i<n_campos-1;i++)
        if(campo[i].chave == 1)
                return i+1;
    return 1; /*por default a chave sera o primeiro campo*/
}
    
void keys(FILE *fileptr, FILE *destino, int ind_chave, campos *campo){
     int ind,tam,count=0,end=0; /*end guardara o endereco*/        
     char *texto,a;
     
     a = getc(fileptr);
     count++;
     while (!(feof(fileptr))) {
            fseek(fileptr,-1,SEEK_CUR);
            count--;
            if(fgetc(fileptr) == ARQ_REM){
                count++;
                do{
                   a=fgetc(fileptr);
                   count++;
                }while(a != FIM_DE_REGISTRO);
                end = count;
                fgetc(fileptr);
                count++;
            }
            else {
                 count++;
                 while((a=fgetc(fileptr))!=FIM_DE_REGISTRO){
                    count++; 
                    fseek(fileptr,-1,SEEK_CUR);
                    count--;
                    tam=fgetc(fileptr);
                    count++;
                    ind=fgetc(fileptr);
                    count++;
                    if(ind == ind_chave){
                           texto = malloc(sizeof(char)*(tam-1));
                           fread(texto,1,tam-2,fileptr);
                           count += tam-2;
                           texto[tam-2] = FIM_STRING;
                           end++; /*'end' "apontava" ultimo caractere do ultimo registro lido, agora "aponta" o inicio do novo registro a ser gravado  */
                           /*gravacao do arquivo de chaves com estrutura para ser ordenado pelo 'system ("sort")'*/
                           fwrite (STR_ARQ_VAL,sizeof(char),1,destino);
                           fwrite (texto, sizeof(char), strlen (texto), destino);
                           fwrite (STR_BRANCO, sizeof(char), 1, destino);
                           fwrite (&end, sizeof(int), 1, destino);
                           fwrite (STR_ENDLINE, sizeof(char), 1, destino);
                           do{
                                   a=fgetc(fileptr);
                                   count++;
                           }while(a != FIM_DE_REGISTRO);
                           fseek(fileptr,-1,SEEK_CUR);
                           count--;
                           free(texto);
                    }
                    else
                        fseek(fileptr,tam-2,SEEK_CUR);
                 }
                 count++;
                 end = count;
                 a=fgetc(fileptr);
                 count++;
            }
    }
}

