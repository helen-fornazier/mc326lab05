void pre_tree(entrada,destino,desprezados,ind_chave,campo,n_campos){
     /*no caso de construir a arvore*/
    noh busc_noh; 
    noh reg;
    char *reg_completo = malloc(do tamanho dos registros);
    fgetc(entrada);
    while(! eof(entrada)){
    seek(entrada,-1,SEEK_CUR);
    reg = le_chave(reg_completo,campo,n_campos); /*le no arquivo de entrada o próximo registro, retirando sua chave e endereco*/
    busc_noh = busca_noh(destino,reg); /*verifica se reg.valor esta na tree*/
             /*busca noh na arvore, se não encontrar retorna 0,endereco do noh; se encontrar retorna 1, endereco do registro.
               se a arvore estiver vazia, retorna 0,0 (endereco do primeiro noh na arvore)*/
    
    if(busc_noh == 0) adiciona_na_tree(destino,busc_noh.endereco,reg);
                /*adiciona no noh de endereco busc_noh.endereco o conjunto reg (chave+end do registro no arq de entrada).*/
    else (grava_reg_desp(desprezados,reg_completo);)
         /*grava o registro reg_completo no arquivo de desprezados*/
         
         
         fgetc(entrada);
         }         
}
pagina le_pag(FILE *destino,int endereco){
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
