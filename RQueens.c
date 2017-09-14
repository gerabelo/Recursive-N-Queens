#include <stdio.h>
#include <stdlib.h>

int numero_de_rainhas = 8;
int *linha_inteira = NULL;
int contador_solucoes = 0;
int contador_printlinha = 1;

int isValid(int coluna, int linha, int steps) {
        if (coluna == 0) {
                return 1;
        } else if (linha == linha_inteira[coluna-1] || linha == linha_inteira[coluna-1]+1+steps || linha == linha_inteira[coluna-1]-1-steps) { return 0; }
        return isValid(coluna-1,linha,steps+1);
}

void printlinha_inteira() {
	
        printf("\n\t[%d]",contador_printlinha);
        for (int contador = 0; contador < numero_de_rainhas; contador++) {
                printf("%d ",linha_inteira[contador]);
        }
	contador_printlinha++;
}

int busca(int coluna, int linha) {

        //printf("%d %d; ",coluna,linha);
        
        if (isValid(coluna, linha, 0)) {
                if (coluna == numero_de_rainhas-1) {
                        linha_inteira[coluna] = linha;
                        printlinha_inteira();
                        contador_solucoes++;
                        return 0;
                } else {
                        linha_inteira[coluna] = linha;
                        return busca(coluna+1,1);
                }
        } 

        if (linha == numero_de_rainhas) {
                return 0;
        }
        
        if (!busca(coluna,linha+1)) {
                if (coluna > 1 && linha_inteira[coluna-1]+1 <= numero_de_rainhas) {
                        return busca(coluna-1,linha_inteira[coluna-1]+1);
                } else return 0;
        }
        
                
        
}


int main() {    

        linha_inteira = malloc(numero_de_rainhas*sizeof(int));
//        int contador_solucoes = 0;
          
        for (int coluna = 1; coluna <= numero_de_rainhas ; coluna++) {
                if (busca(0,coluna)) { 
                        printlinha_inteira();
  //                      contador_solucoes++;
                }
        }
        printf("\n\n\t%d soluções possíveis no tabuleiro %dx%d\n\n",contador_solucoes,numero_de_rainhas,numero_de_rainhas);
        free(linha_inteira);
        return 0;
}
