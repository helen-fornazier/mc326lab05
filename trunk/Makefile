CC = gcc
CFLAG = -Wall -c -g
CLIB = erro.c file.c read_arq.c save_arq.c trees.c
CLIB_OBJ = erro.o file.o read_arq.o save_arq.o trees.o
CPROG = Btree.c
CPROG_OBJ = Btree.o
PROG = teste
PARAMS = 9 listafinal1000.txt pagina.txt desprezados.txt descricao.txt

$(PROG): $(CLIB) $(CLIB_OBJ) $(CPROG) $(CPROG_OBJ)
	$(CC) $(CFLAG) $(CLIB)
	$(CC) $(CFLAG) $(CPROG)
	$(CC) $(CLIB_OBJ) $(CPROG_OBJ) -o $(PROG)	

clean:
	rm *.o
	rm $(PROG)

run:
	./$(PROG) $(PARAMS)

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-reachable=yes ./$(PROG) $(PARAMS)
