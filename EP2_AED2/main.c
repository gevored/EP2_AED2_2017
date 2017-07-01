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

    int *vetorRepeticao;
    int  qtdRepeticao;
};

int contadorCaracter= -1;
char *palavra;
struct  noTrie  *trieGlobal;
char ** palavrasBusca;



 void InicializaTRIE(){
   int i;

   trieGlobal = (struct  noTrie *) malloc (sizeof(struct  noTrie));
   trieGlobal->contadorCarcater = 0;
   trieGlobal->finalPalavra = "N";

   for(i = 0; i<qtdAlfabeto ; i++){
        trieGlobal->noFilho[i] = NULL;
        trieGlobal->vetorRepeticao = NULL;
        trieGlobal->qtdRepeticao = 0;
   }
}

void VetorRepeticao(int qtdeRepeticao, struct  noTrie * noAtual, int posicaoInicial){
    int i ;
    int * vetorTemp = (int* ) malloc(sizeof(int) * (qtdeRepeticao+1));

    for(i = 0; i < qtdeRepeticao ; i++){
        vetorTemp[i] =  noAtual->vetorRepeticao[i];
    }
    vetorTemp[i] =posicaoInicial;

     free(noAtual->vetorRepeticao);
     noAtual->vetorRepeticao = vetorTemp;
}

void inserirTRIE(char * vetorPalavra){
    int i ;
    int j ;
    contadorCaracter++;
    int letra;
    struct  noTrie * noAtual = trieGlobal;
    char * palavraTemp = palavra;

    int qtd = strlen(palavra);

    for (i = 0; i<qtd ; i++){
        letra = vetorPalavra[i] - 97;

        if (letra <=26 && letra >=0){

            if(noAtual->noFilho[letra] == NULL){
                noAtual->noFilho[letra] = (struct  noTrie *) malloc (sizeof(struct  noTrie));
                noAtual->noFilho[letra]->finalPalavra = "N";
                noAtual->qtdRepeticao = 0;
                noAtual->vetorRepeticao = NULL;

                for(j = 0; j<qtdAlfabeto ; j++){
                    noAtual->noFilho[letra]->noFilho[j] = NULL;
                }
            }
            contadorCaracter++;
            noAtual = noAtual->noFilho[letra];
        }
    }

    noAtual->finalPalavra = "S";

  VetorRepeticao(noAtual->qtdRepeticao,noAtual,contadorCaracter - qtd);
  noAtual->qtdRepeticao++;
  printf("%s \n",vetorPalavra);

}

void BuscaPalavrasTries (int countWord){
    int count =1;
    int x =0;
    int i;
    int tamanhoPalavra;


    char url[] = "saida1_TRIE.txt";
	FILE *arq;
	arq = fopen(url, "w");

    struct  noTrie * noAtual ;

    while(count <= countWord){

        noAtual = trieGlobal;
        tamanhoPalavra = strlen(palavrasBusca[x]);

        for(i = 0 ; i < tamanhoPalavra ; i++){
            if (noAtual->noFilho[palavrasBusca[x][i]- 97]  == NULL){
                fprintf(arq, "%d \n", -1);

                break;
            }
            noAtual = noAtual->noFilho[palavrasBusca[x][i]- 97];
        }

        if (noAtual->noFilho[palavrasBusca[x][i]- 97]  == NULL &&  i < tamanhoPalavra  ){
            count++;
            x++;
            continue;
        }
            for(i = 0 ;i < noAtual->qtdRepeticao;i++){
                if(i  == noAtual->qtdRepeticao-1){
                    fprintf(arq, "%d", noAtual->vetorRepeticao[i]);
                }else{
                    fprintf(arq, "%d ", noAtual->vetorRepeticao[i]);
                 }
            }
            fprintf(arq, "\n");

        count++;
        x++;
    }
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

                palavra = '\0';
                free(palavra);
                palavra = (char*)malloc (tamMaxPalavra  * sizeof(char));
                countWord = 0;
                continue;
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
        if (ch == '\n'){
            palavra = '\0';
            palavra = (char*)malloc(tamMaxPalavra  * sizeof(char));
            continue;
            }

         if(ch != ' ' ){
            formaPalavra(ch, countWord);
        }else{
            if (ch == ' '){

                palavrasBusca[x] = palavra;
                palavra = (char*)malloc(tamMaxPalavra  * sizeof(char));
                x++;
                countWord = 0;
                continue;
            }
        }
        countWord++;
        continue;
    }
        fclose(arq);
    }
     palavrasBusca[x] = palavra;
     //free(palavra);

     BuscaPalavrasTries(qtdPalavrasBusca);
}

void formaPalavra(  char letra, int local){
    palavra[local] = letra;
}

void main(void) {
	LeituraTexto1();
	system("pause");
}
