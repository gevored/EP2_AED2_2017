#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define qtdAlfabeto 26
#define tamMaxPalavra 50


 typedef struct  noTrie{
    char finalPalavra;
    struct noTrie *noFilho[qtdAlfabeto];
    int contadorCarcater;
};

char *palavra;
struct  noTrie  *trieGlobal;
char ** palavrasBusca;

void limpaPalavra(){
    strcpy( palavra, "" );
}

 void InicializaTRIE(){
   int i;

   trieGlobal = (struct  noTrie *) malloc (sizeof(struct  noTrie));
   trieGlobal->contadorCarcater = 0;
   trieGlobal->finalPalavra = "N";

   for(i = 0; i<qtdAlfabeto ; i++){
        trieGlobal->noFilho[i] = NULL;
   }
}

void inserirTRIE(char * vetorPalavra){
    int i ;
    int j ;

    int letra;
    struct  noTrie * noAtual = trieGlobal;

    int qtd = strlen(palavra);

    for (i = 0; i<qtd ; i++){
        letra = vetorPalavra[i] - 97;

        if(noAtual->noFilho[letra] == NULL){
            noAtual->noFilho[letra] = (struct  noTrie *) malloc (sizeof(struct  noTrie));
            noAtual->noFilho[letra]->finalPalavra = "N";

            for(j = 0; j<qtdAlfabeto ; j++){
                noAtual->noFilho[letra]->noFilho[j] = NULL;
            }
        }
        noAtual->contadorCarcater++;
        noAtual = noAtual->noFilho[letra];
    }
    noAtual->finalPalavra = "S";
}

//leitura dos arquivos
void LeituraTexto1() {

    InicializaTRIE();
    int x = 0;

    palavra = (char*)malloc(tamMaxPalavra  * sizeof(char));
    int countWord = 0;
	char url[] = "//home//gerson//Documents//entrada_ep2_aed2//entrada21.txt";
	char ch;
	FILE *arq;
	int qtdPalavrasBusca = 0;

	int etapa = 1;

	arq = fopen(url, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else
        while ((ch = fgetc(arq)) != EOF) {
            if (ch == '\n') {
                etapa++;
            }
    switch (etapa){

    case 1: //inserção das palavras
        if (ch == '\n')
            continue;

        if(ch != ' ' ){
            formaPalavra(ch, countWord);
        }else{
            if (ch == ' '){
                inserirTRIE(palavra);

                countWord = 0;
            }
        }
        countWord++;
    continue;

    case 2: // leitura da quantidade de palavras
        fscanf(arq,"%d", &qtdPalavrasBusca);
        palavrasBusca = (char**)malloc(qtdPalavrasBusca * sizeof(char*));
        countWord = 0;
        continue;

    case 3:
        if (ch == '\n')
            continue;

         if(ch != ' ' ){
            formaPalavra(ch, countWord);
        }else{
            if (ch == ' '){

                palavrasBusca[x] = palavra;
                printf(palavra);
                printf("\n");
                x++;
                countWord = 0;
            }
        }
        countWord++;
        continue;
    }
        fclose(arq);
    }
}

void formaPalavra(  char letra, int local){
    palavra[local] = letra;
}

void main(void) {
	LeituraTexto1();
	system("pause");
}
