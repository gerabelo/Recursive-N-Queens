#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> //sleep

FILE *arquivo = NULL;

int numero_de_rainhas           = 8;
long int *linha_inteira              = NULL;
int contador_solucoes           = 0;
int contador_printlinha         = 1;

void printlinha_inteira() {	
        printf("\n\t[%d]\t",contador_printlinha);
        for (int contador = 0; contador < numero_de_rainhas; contador++) {
                printf("%ld ",linha_inteira[contador]);
        }
	contador_printlinha++;
}

int printlinha_inteira_em_arquivo(FILE *arquivo) {
        for (int contador = 0; contador < numero_de_rainhas; contador++) {
                fprintf(arquivo,"%ld;",linha_inteira[contador]);
        }
        fprintf(arquivo,"\n");
        return 1;
}

int isValid(int coluna, long int linha, int steps) {
//        sleep(0.5);
        if (coluna == 0) {
                return 1;
        } else if (linha == linha_inteira[coluna-1] || linha == linha_inteira[coluna-1]+1+steps || linha == linha_inteira[coluna-1]-1-steps) { return 0; }
        return isValid(coluna-1,linha,steps+1);
}

int busca(int coluna, long int linha) {

        //printf("%d %d; ",coluna,linha);
        
        if (isValid(coluna, linha, 0)) {
                if (coluna == numero_de_rainhas-1) {
                        linha_inteira[coluna] = linha;
                        printlinha_inteira();
                        if (printlinha_inteira_em_arquivo(arquivo)) { sleep(0.5); }
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

        char *file = malloc(32*sizeof(char));
        double start_t, end_t, total_t;
        
        while(1) {

                start_t = clock();
                
                memset(file,'\0',32);
                sprintf(file,"%dx%d_queens.txt",numero_de_rainhas,numero_de_rainhas);
                arquivo = fopen(file,"a+");                

                linha_inteira = malloc(numero_de_rainhas*sizeof(long int));        
                for (int coluna = 1; coluna <= numero_de_rainhas ; coluna++) {
                        if (busca(0,coluna)) { 
                                printlinha_inteira();
                                if (printlinha_inteira_em_arquivo(arquivo)) { sleep(0.5); }
                                //sleep(0.5);
                        }
                        
                }
                end_t = clock();       
                total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
                //printlinha_inteira();
                printf("\n\n\t%d soluções possíveis no tabuleiro %dx%d encontradas em %f segundos\n\tobs.: algumas soluções são meras inversões de outras.\n\n",contador_solucoes,numero_de_rainhas,numero_de_rainhas,total_t);

                free(linha_inteira);
                numero_de_rainhas++;
                contador_solucoes           = 0;
                contador_printlinha         = 1;
                fclose(arquivo);
                sleep(5);
        }
        free(file);
        return 0;
}
