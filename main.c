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
		printf("\nIntroduza o numero da linha: ");
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
		printf("\nIntroduza o numero da linha: ");
		scanf("%d", line);
		fflush(stdin);
		printf("\nIntroduza o numero da coluna: ");
		scanf("%d", column);
		table[line][column] = 0;
	}
}

//Avanca Varias geracoes;
//Se for preciso avancar apenas 1 geracao fazer advanceGen(1);
//Se for preciso avancar varias geracoes fazer advanceGen(quantidade_de_geracoes);
int advanceGen(int quant_gens){
	int line, column, neighbours;
	if (quant_gens == 0) {
		return 0;
	} else {
		
		for (line = 0; line < TAM; line++) {
			for (column = 0; column < TAM; column++) {
				if (line == 0 && column == 0) {
					if (table[line + 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line + 1][column + 1] == 1) {
						neighbours += 1;
					}
				} else if (line < TAM && column < TAM) {
					if (table[line + 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line + 1][column + 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column - 1] == 1) {
						neighbours += 1;
					}
				} else {
					if (table[line - 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column - 1] == 1) {
						neighbours += 1;
					}
				}
				
				if (neighbours >= 4 || neighbours == 1 && table[line][column] == 1) {
					table[line][column] = 0;
					
				} else if (neighbours == 3 && table[line][column] == 0) {
					table[line][column] == 1;
				}
				
			}
		}
		
		quant_gens -= 1;
		advanceGen(quant_gens);
	}
}

//Funcoes para as Estatisticas do jogo
//Celulas vivas na presente geracao
int aliveCells(){
	int contAliveCells = 0, line, column;;
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
