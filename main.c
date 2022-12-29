#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 25

//se table == 1 significa que a celula esta viva / se table == 0 a celula esta morta

//Esta variaveis sao globais para uma maior facilidade ao manuzia-las
int table[TAM][TAM],
cellsToBorn[TAM][TAM],
cellsToKill[TAM][TAM],
mostCellsLived = 0,
gen = 0,
genMostCellsAlive = 0,
ages[TAM][TAM],
oldestCell = 0,
youngestCell = 0,
genYoungestCellBorn = 0,
genOldestCellBorn = 0,
lessCellsAlive = 0,
genLessCellsAlive = 0;

//Estas funcoes sao chamadas no case mas nao estao no menu, sao apenas para facilitar os testes
void addGlider() {
	table[23][23] = 1;
	table[22][22] = 1;
	table[21][22] = 1;
	table[21][23] = 1;
	table[21][24] = 1;
	
	genMostCellsAlive = 5;
	genLessCellsAlive = 5;
	lessCellsAlive = 5;
	mostCellsLived = 5;
}

void addBlinker() {
	table[1][1] = 1;
	table[1][2] = 1;
	table[1][3] = 1;
	
	genMostCellsAlive = 3;
	genLessCellsAlive = 3;
	lessCellsAlive = 3;
	mostCellsLived = 3;
}

void addBlock() {
	table[1][1] = 1;
	table[1][2] = 1;
	table[2][1] = 1;
	table[2][2] = 1;
	
	genMostCellsAlive = 4;
	genLessCellsAlive = 4;
	lessCellsAlive = 4;
	mostCellsLived = 4;
}

void addBote() {
	table[20][20] = 1;
	table[19][19] = 1;
	table[18][19] = 1;
	table[18][20] = 1;
	table[19][21] = 1;
	
	genMostCellsAlive = 5;
	genLessCellsAlive = 5;
	lessCellsAlive = 5;
	mostCellsLived = 5;
}

void resetTable(){
	int line, column;
	for (int line = 0; line < TAM; line++){
		for (int column = 0; column < TAM; column++){
			table[line][column] = 0;
			cellsToBorn[line][column] = 0;
			cellsToKill[line][column] = 0;
			ages[line][column] = 0;
		}
	}
	mostCellsLived = 0;
	genMostCellsAlive = 0;
	gen = 0;
	oldestCell = 0;
	youngestCell = 0;
	genYoungestCellBorn = 0;
	genOldestCellBorn = 0;
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
	
	mostCellsLived += 1;
	mostCellsLived += 1;
	
	fflush(stdin);
	
	printf("\nInsira as coordenadas da celula (linha, coluna): ");
	scanf("(%d, %d)", &line, &column);
	table[line][column] = 1;
	
}

//Apaga apenas 1 celula, os parametros sao as coordenadas inseridas pelo utilizador
//TODO: If's para lidar com erros
void deleteOneCell(){
	int line, column;
	
	mostCellsLived -= 1;
	
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
	
	mostCellsLived += quant_cells;
	lessCellsAlive += quant_cells;
	
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
	
	mostCellsLived -= quant_cells;
	
	for (int i = 1; i <= quant_cells; i++){
		showTable();
		
		fflush(stdin);
		
		printf("\nInsira as coordenadas da celula (linha, coluna): ");
		scanf("(%d, %d)", &line, &column);
		table[line][column] = 0;
	}
}

//Celulas vivas na presente geracao
int aliveCells(){
	int countAliveCells = 0, line, column;;
	for (int line = 0; line < TAM; line++) {
		for (int column = 0; column < TAM; column++) {
			if (table[line][column] == 1) {
				countAliveCells += 1;
			}
			
		}
	}
	
	return countAliveCells;
}

//neighbours: Celulas vizinhas vivas
//Avanca Varias geracoes;
//Se for preciso avancar apenas 1 geracao fazer advanceGen(1);
//Se for preciso avancar varias geracoes fazer advanceGen(quantidade_de_geracoes);
int advanceGen(int quant_gens){
	int line, column, neighbours = 0, countAliveCells = 0;
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
				
				if ((table[line][column] == 1 && neighbours >= 4) || (table[line][column] == 1 && neighbours <= 1)) {
					cellsToKill[line][column] = 1;
				}
				
				neighbours = 0;
			}
		}
	// Se o valor de cellsToBorn == 1 Significa que uma nova celula vai nascer
	for (line = 0; line < TAM; line++) {
		for (column = 0; column < TAM; column++) {
			if (cellsToBorn[line][column] == 1) {
				table[line][column] = 1;
				cellsToBorn[line][column] = 0;
			}
	// Se o valor de cellsToKill == 1 Significa que uma nova celula vai morrer
			if (cellsToKill[line][column] == 1) {
				table[line][column] = 0;
				
				if (youngestCell == ages[line][column]) {
					youngestCell = gen;
				}
				
				if (oldestCell - 1 == ages[line][column]) {
					oldestCell = 0;
				}
				
				ages[line][column] = 0;
				cellsToKill[line][column] = 0;
			}
		}
	}
	
	countAliveCells = aliveCells();
	
	if (lessCellsAlive >= countAliveCells) {
		lessCellsAlive = countAliveCells;
		genLessCellsAlive = gen + 1;
	}
	
	if (countAliveCells >= mostCellsLived) {
		mostCellsLived = countAliveCells;
		genMostCellsAlive = gen + 1;
	}
	
	for (int line = 0; line < TAM; line++) {
		for (column = 0; column < TAM; column++) {
			if (table[line][column] == 1) {
				ages[line][column] += 1;
			}
			
			if (table[line][column] == 1 && oldestCell < ages[line][column]) {
				oldestCell = ages[line][column];
				genOldestCellBorn = (gen + 1) - ages[line][column];
			}
			
			if (table[line][column] == 1 && youngestCell >= ages[line][column]) {
				youngestCell = ages[line][column];
				//O contador de geracoes (a variavel gen) ainda nao avancou por isso é que adiciona + 1 nesta conta
				genYoungestCellBorn = (gen + 1) - ages[line][column];
			}
		}
	}
	
	youngestCell += 1;
	oldestCell += 1;
	gen += 1;
	quant_gens -= 1;
	advanceGen(quant_gens);
	
	}
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

void getGameStatistics() {
	printf("\n");
	printf("\nQuantidade de celulas vivas: %d", aliveCells());
	printf("\nNumero maximo de celulas vivas %d; Geracao: %d", mostCellsLived, genMostCellsAlive);
	printf("\nNumero minimo de celulas vivas %d; Geracao: %d", lessCellsAlive, genLessCellsAlive);
	printf("\nIdade da celula mais velha %d; Nasceu na geracao: %d", oldestCell, genOldestCellBorn);
	printf("\nIdade da celula mais nova %d; Nasceu na geracao: %d", youngestCell, genYoungestCellBorn);
	printf("\nGeracao atual: %d", gen);
	printf("\n");
	printf("\nHistograma de todas as celulas vivas:");
	for (int line = 0; line < TAM; line++) {
		for (int column = 0; column < TAM; column++) {
			if (table[line][column] == 1) {
				printf("\nIdade da celula (%d, %d): %d; \nNasceu na geracao: %d", line, column, ages[line][column], gen - ages[line][column]);
			}
		}
	}
	
	printf("\n");
	system("pause");
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
        		getGameStatistics();
            	break;
        	case 9:
            	break;
            	
			//Padroes para testes
			case 10:
				addGlider();
				break;
			case 11:
				addBlinker();
				break;
			case 12:
				addBlock();
				break;
			case 13:
				addBote();
				break; 
        	default:
            	printf("Opcao invalida, introduza uma opcao valida!");
            	system("pause");
            	break;
        }
    } 
	return 0;
}
