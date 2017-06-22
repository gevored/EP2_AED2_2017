#include <stdio.h>
#include <stdlib.h>


//leitura dos arquivos 
void Leitura1() {
	char url[] = "C:\\Users\\Gerson\\Desktop\\EP2_AED2\\entrada21.txt";
	char ch;
	FILE *arq;

	arq = fopen(url, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while ((ch = fgetc(arq)) != EOF) {

			putchar(ch);
			if (ch == '\n') {
				break;
			}
		}
		
	fclose(arq);
}

void main(void) {
	printf("Olá mundo\n"); //este comando exibe um texto na tela
	Leitura1();
	system("pause");

}
