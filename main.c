#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 25

//se table == 1 significa que a celula esta viva / se table == 0 a celula esta morta

//table (tabuleiro) como variavel global para ser mais facil de se acessar fora do main e etc.
int table[TAM][TAM], cellsToBorn[TAM][TAM], cellsToKill[TAM][TAM];

void resetTable(){
	int line, column;
	for (int line = 0; line < TAM; line++){
		for (int column = 0; column < TAM; column++){
			table[line][column] = 0;
			cellsToBorn[line][column] = 0;
			cellsToKill[line][column] = 0;
		}
	}
}

void showTable(){
	int line, column;
	
	system("cls");
	
	for (line = 0; line < TAM; line++) {
		for (column = 0; column < TAM; column++) {
			if (table[line][column] == 1) {
				printf(" * ");
			} else {
				printf(" . ");
			}
		}
		printf("\n");
	}
}

//Adiciona apenas 1 celula
//TODO: If's para lidar com erros
void addOneCell(){
	int line, column;
	
	fflush(stdin);
	
	printf("\nInsira as coordenadas da celula (linha, coluna): ");
	scanf("(%d, %d)", &line, &column);
	table[line][column] = 1;
	
}

//Apaga apenas 1 celula, os parametros sao as coordenadas inseridas pelo utilizador
//TODO: If's para lidar com erros
void deleteOneCell(){
	int line, column;
	
	fflush(stdin);
	
	printf("\nInsira as coordenadas da celula (linha, coluna): ");
	scanf("(%d, %d)", &line, &column);
	table[line][column] = 0;
	
}

//Adiciona Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
//TODO: If's para lidar com erros
void addCells(){
	int line, column, quant_cells;
	
	fflush(stdin);
	
	printf("\nInsira a quantidade de celulas que deseja adicionar: ");
	scanf("%d", &quant_cells);
	
	for (int i = 1; i <= quant_cells; i++){
		showTable();
		
		fflush(stdin);
		
		printf("\nInsira as coordenadas da celula (linha, coluna): ");
		scanf("(%d, %d)", &line, &column);
		table[line][column] = 1;
	}
}

//Apaga Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
///TODO: If's para lidar com erros
void deleteCells(){
	int line, column, quant_cells;
	
	fflush(stdin);
	
	printf("\nInsira a quantidade de celulas que deseja apagar: ");
	scanf("%d", &quant_cells);
	
	for (int i = 1; i <= quant_cells; i++){
		showTable();
		
		fflush(stdin);
		
		printf("\nInsira as coordenadas da celula (linha, coluna): ");
		scanf("(%d, %d)", &line, &column);
		table[line][column] = 0;
	}
}

//neighbours: Celulas vizinhas vivas
//Avanca Varias geracoes;
//Se for preciso avancar apenas 1 geracao fazer advanceGen(1);
//Se for preciso avancar varias geracoes fazer advanceGen(quantidade_de_geracoes);
int advanceGen(int quant_gens){
	int line, column, neighbours = 0;
	if (quant_gens == 0) {
		return 0;
	} else {
		showTable();
		system("pause");
		
		for (line = 0; line < TAM; line++) {
			for (column = 0; column < TAM; column++) {
				
				if (line == 0 && column == 0) {
					if (table[line + 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column + 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line + 1][column + 1] == 1) {
						neighbours += 1;
					}
					
				} else if (line == 0 && column > 0 && column < TAM) {
					if (table[line + 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column + 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line + 1][column + 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line + 1][column - 1] == 1) {
						neighbours += 1;
					}
					
				} else if (line == TAM - 1 && column == TAM - 1) {
					if (table[line - 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column - 1] == 1) {
						neighbours += 1;
					}
					
					
				} else if (line == TAM - 1 && column < TAM && column >= 0) {
					if (table[line - 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					
					if (table[line][column + 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column + 1] == 1) {
						neighbours += 1;
					}
				
				} else {
					if (table[line + 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column + 1] == 1) {
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
					
					if (table[line + 1][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column + 1] == 1) {
						neighbours += 1;
					}
					
				}
				
				if (neighbours == 3 && table[line][column] == 0) {
					cellsToBorn[line][column] = 1;
				}
				
				if (neighbours >= 4 || neighbours == 1 && table[line][column] == 1) {
					cellsToKill[line][column] = 1;
				}
				
				neighbours = 0;
			}
		}
		
	for (line = 0; line < TAM; line++) {
		for (column = 0; column < TAM; column++) {
			if (cellsToBorn[line][column] == 1) {
				table[line][column] = 1;
				cellsToBorn[line][column] = 0;
			}
			
			if (cellsToKill[line][column] == 1) {
				table[line][column] = 0;
				cellsToKill[line][column] = 0;
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

int menu() {
    int option;
	printf("*-------------------------------------------------------------------------------------*\n");
    printf("|       _                                 _            __      __  _       _          |\n");
    printf("|      | |                               | |           \\ \\    / / (_)     | |         |\n");
    printf("|      | |   ___     __ _    ___       __| |   __ _     \\ \\  / /   _    __| |   __ _  |\n");
    printf("|  _   | |  / _ \\   / _` |  / _ \\     / _` |  / _` |     \\ \\/ /   | |  / _` |  / _` | |\n");
    printf("| | |__| | | (_) | | (_| | | (_) |   | (_| | | (_| |      \\  /    | | | (_| | | (_| | |\n");
    printf("|  \\____/   \\___/   \\__, |  \\___/     \\__,_|  \\__,_|       \\/     |_|  \\__,_|  \\__,_| |\n");
    printf("|                    __/ |                                                            |\n");
    printf("|                   |___/                                                             |\n");
    printf("|                                                                                     |\n");
    printf("|*************************************************************************************|\n");
    printf("|******************************** MENU PRINCIPAL *************************************|\n");
    printf("|************************************ Opcoes *****************************************|\n");
    printf("|*************************************************************************************|\n");
    printf("|**      {1} - Inserir celula           **       {6} - Avancar uma geracao          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**      {2} - Apagar celula            **       {7} - Avancar n geracoes           **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**      {3} - Inserir varias celulas   **       {8} - Estatisticas                 **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**      {4} - Apagar varias celulas    **       {9} - Configuracoes                **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**      {5} - Apagar o tabuleiro       **       {0} - Sair                         **|\n");
    printf("*-------------------------------------------------------------------------------------*\n");

    printf("Escolha uma opcao:");
    scanf("%d", &option);
    fflush(stdin);
    return option;
}

int main () {
    int option = 10, quant_gens;
    
    resetTable();
    
    while (option != 0)
    {    	
    	showTable();
        
		option = menu();
        
		switch (option)
        {
        	case 0:
            	break;
        	case 1:
        		addOneCell();
            	break;
        	case 2:
        		deleteOneCell();
            	break;
        	case 3:
        		addCells();
            	break;
        	case 4:
        		deleteCells();
            	break;
        	case 5:
        		resetTable();
            	break;
        	case 6:
        		advanceGen(1);
            	break;
        	case 7:
        		fflush(stdin);
        		printf("\nIntroduza a quantidade de geracoes que deseja avancar: ");
        		scanf("%d", &quant_gens);
        		advanceGen(quant_gens);
            	break;
        	case 8:
            	break;
        	case 9:
            	break;              
        	default:
            	printf("Opcao invalida, introduza uma opcao valida!");
            	system("pause");
            	break;
        }
    } 
	return 0;
}
