#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 25

//se table == 1 significa que a celula esta viva / se table == 0 a celula esta morta

//table (tabuleiro) como variavel global para ser mais facil de se acessar fora do main e etc.
int table[TAM][TAM];

void resetTable(){
	for (int i = 0; i < TAM; i++){
		for (int j = 0; j < TAM; j++){
			table[i][j] = 0;
		}
	}
}

//Adiciona apenas 1 celula, os parametros sao as coordenadas inseridas pelo utilizador
//TODO: If's para lidar com erros
void addOneCell(int line, int column){
	table[line][column] = 1;
	
}

//Apaga apenas 1 celula, os parametros sao as coordenadas inseridas pelo utilizador
//TODO: If's para lidar com erros
void deleteOneCell(int line, int column){
	table[line][column] = 0;
	
}

//Adiciona Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
//TODO: If's para lidar com erros
void addCells(int quant_cells){
	int line, column;
	for (int i = 1; i <= quant_cells; i++){
		fflush(stdin);
		print("\nIntroduza o numero da linha: ");
		scanf("%d", line);
		fflush(stdin);
		printf("\nIntroduza o numero da coluna: ");
		scanf("%d", column);
		table[line][column] = 1;
	}
}

//Apaga Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
///TODO: If's para lidar com erros
void deleteCells(int quant_cells){
	int line, column;
	for (int i = 1; i <= quant_cells; i++){
		fflush(stdin);
		print("\nIntroduza o numero da linha: ");
		scanf("%d", line);
		fflush(stdin);
		printf("\nIntroduza o numero da coluna: ");
		scanf("%d", column);
		table[line][column] = 0;
	}
}

//Avanca 1 geracao
//Talvez de para fazer esta funcao com recursao e assim avancar nao precisar da advanceGens
void advanceOneGen(){
	//TODO
}

//Avanca Varias geracoes (Inseridas pelo utilizador com quant_gens)
void advanceGens(int quant_gens){
	//TODO
}

//Funcoes para as Estatisticas do jogo
//Celulas vivas na presente geracao
int aliveCells(){
	int contAliveCells = 0;
	for (int line = 0; line < TAM; line++) {
		for (int column = 0; column < TAM; column++) {
			if (table[line][column] == 1) {
				contAliveCells += 1;
			}
			
		}
	}
	
	return contAliveCells;
}



int main () {
	
    return 0;
} 
