#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define qtdAlfabeto 26
#define tamMaxPalavra 50

 typedef struct  trie{
    struct noTrie *noFilho[qtdAlfabeto];
    int qtdFilhos;
};

 typedef struct  noTrie{

    char finalPalavra;
    char caracter;
    char * teste;
    struct noTrie *noFilho[qtdAlfabeto];
    int qtdFilhos;

};
char *palavra;

void limpaPalavra(){
    strcpy( palavra, "" );
}

void InicializaTRIE(struct  trie trieNo){
   int i;
   trieNo.qtdFilhos = 0;

   for(i = 0; i<qtdAlfabeto ; i++){
        trieNo.noFilho[i] = NULL;
   }
}

void inserirTRIE(char * vetorPalavra){
    int i  = 0;
    int j =0;
    int qtd = strlen(vetorPalavra);

}

    //leitura dos arquivos
void Leitura1(struct  trie trieNo) {

    InicializaTRIE(trieNo);
    palavra = (char*)malloc(tamMaxPalavra  * sizeof(char));
    int countWord = 0;
	char url[] = "//home//gerson//Documents//entrada_ep2_aed2//entrada21.txt";
	char ch;
	FILE *arq;


	arq = fopen(url, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while ((ch = fgetc(arq)) != EOF) {

            if (ch == '\n') {
				break;
			}

            if(ch != ' '){
                putchar(ch);
                formaPalavra(ch, countWord);

            }else{
                if (ch == ' '){
                    inserirTRIE(palavra);
                    limpaPalavra();
                    countWord = 0;
                }
            }
            countWord++;
            printf("%s \n",palavra );
		}
	fclose(arq);
}

void formaPalavra(char letra, int local){
    palavra[local] = letra;
}

void main(void) {

   struct  trie trieInicial;
	Leitura1(trieInicial);
	system("pause");

}
