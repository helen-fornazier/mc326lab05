CC = gcc
CFLAG = -Wall -c -g
CLIB = erro.c file.c read_arq.c save_arq.c trees.c
CLIB_OBJ = erro.o file.o read_arq.o save_arq.o trees.o
CPROG = teste_de_leitura.c
CPROG_OBJ = teste_de_leitura.o
PROG = teste

$(PROG): $(CLIB) $(CLIB_OBJ) $(CPROG) $(CPROG_OBJ)
	$(CC) $(CFLAG) $(CLIB)
	$(CC) $(CFLAG) $(CPROG)
	$(CC) $(CLIB_OBJ) $(CPROG_OBJ) -o $(PROG)	

clean:
	rm *.o
	rm $(PROG)
