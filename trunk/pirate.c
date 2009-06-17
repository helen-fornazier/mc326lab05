
int calc_adress(){
	int total;
	total=9*sizeof(long int)+11*sizeof(int)+20;
	return total;
}

noh new_node(){
	noh node;
	node.valor=-1;
	node.end_noh=-1;
	return node;
}

pagina new_page(){
	int i;
	pagina pag;
	pag.ap_pai=-1;
	for(i=0;i<9;i++){
		pag.n[i]=new_node;
		pag.f[i]=-1;
	}
	pag.f[9]=-1;
	return pag;
}

void escreve_pag(FILE *f, long int ad, pagina pag){
	int i;
	
	fwrite(&pag.ap_pai,sizeof(long int),1,f);
	for(i=0;i<9;i++){
		fprintf(f," ");
		fwrite(&pag.n[i].valor,sizeof(int),1,f);
		fprintf(f," ");
		fwrite(&pag.n[i].end_noh,sizeof(long int),1,f);
	}
	for(i=0;i<10;i++){
		fprintf(f," ");
		fwrite(&pag.f[i],sizeof(long int),1,f);
	}
	fprintf(f,"\n");
}

pagina le_pag(FILE *f, long int ad){
	int i;
	pagina pag;
	
	fread(&pag.ap_pai,sizeof(long int),1,f);
	fseek(f,1,SEEK_CUR);
	for(i=0;i<9;i++){
		fread(&pag.n[i].valor,sizeof(int),1,f);
		fseek(f,1,SEEK_CUR);
		fread(&pag.n[i].end_noh,sizeof(long int),1,f);
		fseek(f,1,SEEK_CUR);
	}
	for(i=0;i<10;i++){
		fread(&pag.f[i],sizeof(long int),1,f);
		fseek(f,1,SEEK_CUR);
	}
	return pag;
}

long int newpagespace(FILE *f){
	long int n;
	char a='\n';
	fseek(f,0,SEEK_END);
	while(a=='\n'){
		fseek(f,-2,SEEK_CUR);
		fscanf(f,"%c",&a);
	}
	fseek(f,1,SEEK_CUR);
	n=ftell(f);
	return n;
}

void add_node(FILE *f, long int *root, noh reg, int ord, long int ad, long int adright){
	pagina pag;
	noh tempnoh, tempnoh2;
	int i, j, tempint=0;
	long int, templint, templint2;
	
	pag=le_pagina(f,ad);
	for(i=0;i<ord;i++)
		if(pag.n[i].valor==-1) tempint=1;
	
	if(tempint){
		for(i=0;i<ord;i++){
			if(reg.valor<pag.n[i].valor){
				tempnoh=pag.n[i];
				pag.n[i]=reg;
				reg=tempnoh;
				templint=pag.f[i+1];
				pag.f[i+1]=adright;
				adright=templint;
			}
		}
	}
	
	else{
		pagina newpag;
		if(pag.ap_pai==-1){
			newpag=new_page();
			newpag.f[0]=ad;
			*root=newpagespace(f);
			escreve_pag(f,*root,newpag);
			pag.ap_pai=*root;
		}
		
		
		tempint=(ord/2)+1;
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
			if(i=tempint){ 
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
		newpag.n[j]=reg;
		newpag.f[j]=pag.f[i];
		pag.f[i]=-1;	
		newpag.ap_pai=pag.ap_pai;
		
		templint=newpagespace(f);
		escreve_pag(f,templint,newpag);

		for(i=0;newpag.f[i]!=-1;i++){
			pag=le_pag(f,newpag.f[i]);
			pag.ap_pai=templint;
			escreve_pag(f,newpag.f[i],pag);
		}

		add_node(f,root,tempnoh2,ord,newpag.ap_pai,templint);
	
	}

}


void adiciona_na_tree(FILE *f, long int *root, noh reg, int ord){
	noh temp;

	temp=busca_noh(f,reg,*add_root,ord);
	if(temp.valor) return;

	add_node(f,*root,reg,ord,temp.end_noh,-1);

}

