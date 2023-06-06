#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 1000

typedef struct r {
	int noUSP;
	char nome[30];
	char estado[30];
	char cpf[30];
	char curso[30];
} REGISTRO;

typedef struct k {
	int chave;
	int end;
} KEY;

REGISTRO * loadTXT(FILE * f, int * N){
	REGISTRO * info = (REGISTRO *)malloc(sizeof(REGISTRO) * TAM);
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%i@", &info[i].noUSP);
		fscanf(f, "%[^@]%*c", info[i].nome);
		fscanf(f, "%[^@]%*c", info[i].estado);
		fscanf(f, "%[^@]%*c", info[i].cpf);
		fscanf(f, "%[^\n]%*c", info[i].curso);
		i++;
	}
	*N = i;

	return info;
}

FILE * createBIN(REGISTRO * info, int N){
	FILE * bin = fopen("Saida\\arq_bin1.bin", "wb+");
	for(int  i = 0;i < N;i++){
		fwrite(&info[i], sizeof(REGISTRO), 1, bin);
	}



	return bin;
}


void imprimeRegistros(REGISTRO * info, int N){
	printf("Registros do arquivo txt:\n");
	for(int i = 0;i < N;i++){
		printf("%d\t", info[i].noUSP);
		printf("%s\t", info[i].nome);
		printf("%s\t", info[i].estado);
		printf("%s\t", info[i].cpf);
		printf("%s\n", info[i].curso);
	}

}

bool inserirIndice(KEY * table, int chave, int prox){
	if(prox >= TAM) return false;
	for(int i = 0;i < TAM;i++)
		if(table[i].chave == chave)
			return false;


	table[prox].chave = chave;
	table[prox].end = prox;
	return true;
}

KEY * createTable(FILE * bin){
	KEY * table = (KEY *)malloc(sizeof(KEY) * TAM);
	REGISTRO aux;
	int prox = 0;
	rewind(bin);
	printf("\n");

	while(1 == fread(&aux, sizeof(REGISTRO), 1, bin)){

		if(inserirIndice(table, aux.noUSP, prox))
			printf("%d inserido na tabela de indices primarios\n", aux.noUSP);
		prox++;

	}
	return table;

}

void bubbleSortTabble(KEY * table, int N){
	printf("\n*******Ordenando tabela de indices primarios\n");
	KEY aux;
	int i, j;
	for(j = N - 1;j > 0;j--){
		for(i = 0;i < j;i++){
			if(table[i].chave > table[i + 1].chave){
				aux = table[i];
				table[i] = table[i + 1];
				table[i + 1] = aux;
			}
		}
	}

}

void imprimeTabela(KEY * table, int N){
	printf("\nTabela\n");
	for(int i = 0;i < N;i++){
		printf("Chave: %d\t", table[i].chave);
		printf("End: %d\n", table[i].end);
	}
	printf("\n");
}

FILE * Key_Sort(FILE * bin, KEY * table, int N){
	FILE * bin_ord = fopen("Saida\\arq_bin1_ord.bin", "wb+");
	REGISTRO aux;
	int escritos;
	for(int i = 0;i < N;i++){
		fseek(bin, sizeof(REGISTRO) * table[i].end, SEEK_SET);
		fread(&aux, sizeof(REGISTRO), 1, bin);
		printf("Inserindo %d no binario ordenado\n", aux.noUSP);
		fwrite(&aux, sizeof(REGISTRO), 1, bin_ord);
	}
	printf("\n");

	return bin_ord;
}

void imprimeBIN(FILE * bin){
	REGISTRO aux;
	fseek(bin, 0, SEEK_SET);
	printf("Chaves do binario ordenado:\n");
	while(1 == fread(&aux, sizeof(REGISTRO), 1, bin)){
		printf("%d\n", aux.noUSP);
	}

	printf("\n");

}

FILE * cria_TXT(FILE * bin){
	printf("*******Criando arquivo txt\n");
	fseek(bin, 0, SEEK_SET);
	REGISTRO aux;
	FILE * f = fopen("Saida\\arq1ord.txt", "w");
	while(1 == fread(&aux, sizeof(REGISTRO), 1, bin)){
		fprintf(f, "%d@", aux.noUSP);
		fprintf(f, "%s@", aux.nome);
		fprintf(f, "%s@", aux.estado);
		fprintf(f, "%s@", aux.cpf);
		fprintf(f, "%s\n", aux.curso);
	}
}

int main(int argc, char ** argv){
	int N;
	FILE * f = fopen(argv[1], "r+");
	REGISTRO * info = loadTXT(f, &N);
	imprimeRegistros(info, N);
	FILE * bin = createBIN(info, N);
	KEY * table = createTable(bin);
	bubbleSortTabble(table, N);
	imprimeTabela(table, N);
	FILE * bin_ord = Key_Sort(bin, table, N);
	imprimeBIN(bin_ord);
	cria_TXT(bin_ord);
	return 0;
}