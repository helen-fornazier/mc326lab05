#ifndef LIB_ERRO
#define LIB_ERRO


#define ARQUIVO_DE_MENSAGENS "config_mensagens.txt"
#define NUMERO_DE_MENSAGENS 12
#define SEPARADOR_MENSAGEM "\n"
#define ARQUIVO_DE_FORMATO "config_formato.txt"
#define ARQUIVO_DE_SEPARADOR "config_separador.txt"
#define n_arg 6 /*num de argumento que arg[v] deve ter*/
#define FIM_STRING '\0'
#define BRANCO_CHAR ' '
#define STR_BRANCO " "
#define STR_ENDLINE "\n"
#define saida "_saida"



/* Referencia de Mensagens de Erro:

	00: Numero de argumentos incompativel!
	01: Argumentos invalidos: o 1o e o 2o argumento deve conter o nome de um arquivo valido.
	02: Erro na abertura do arquivo. 
	03: Erro ao fechar o arquivo. 
    04: .o campo eh obrigatorio.
	05: .o campo deve ser preenchido com numeros
    06: .o campo deve ser preenchido com letras ou numeros
    07: Registro inexistente.
    08: Registro removido.
    09: Numero de caracteres do arquivo de entrada
    10: Numero de registros do arquivo de entrada
    11: Operacao concluida com exito.
*/

int Fclose (FILE *nome, char **mensagens);
/*
  Funcao de fechamento e verificacao de erro de arquivo - Programacao defensiva
*/

FILE *Fopen (char *nome, char *tipo, char **mensagens);
/*
  Funcao de abertura e verificacao de erro de arquivo - Programacao defensiva
*/

int dif_num(char *texto);
/*
  verifica se algum caracter de texto nao eh numerico
*/

int dif_alfanum(char *texto);
/*
  verifica se algum caracter de texto nao eh alfanumerico ou espaço em branco
*/

void erro_argumentos (int argumento, char **argv, char **mensagens);
/* 
  Funcao de verificacao de numero de argumentos da chamada do programa - Programacao defensiva 
*/

void libera_erros(char **mensagens);
/*
  Libera vetor de mensagens dos erros
*/

void testa_obrigatorio(char obrigatorio, int i, char *texto, char **mensagens);
/*
  testa se um campo obrigatorio foi preenchido
*/

void falta_registro (char **mensagens);
/*
  caso registro seja inexistente
*/

void removido_registro (char **mensagens);
/*
  caso registro esteja logicamente removido (indicando que, em algum momento, ele estava ativo)
*/
void sucesso (char **mensagens);


#endif     /*LIB_ERRO*/