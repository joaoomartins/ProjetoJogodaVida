#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
genLessCellsAlive = 0,
TAMColumnsConfigs = TAM,
TAMLinesConfigs = TAM,
showGameStatisticsAdvanceGen = 0,
showTableAdvanceGen = 1;

float secsPerGen = 0.5;

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

void cooldown(float seconds) {
	clock_t start = clock();
	clock_t period = seconds * CLOCKS_PER_SEC;
	clock_t elapsed;
	
	do {
		elapsed = clock() - start;
	} while (elapsed < period);
}

void resetTable(){
	int line, column;
	for (int line = 0; line < TAMLinesConfigs; line++){
		for (int column = 0; column < TAMColumnsConfigs; column++){
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
	TAMColumnsConfigs = TAM;
	TAMLinesConfigs = TAM;
	secsPerGen = 0.5;
}

void showTable(){
	int line, column;
	
	system("cls");
	
	for (line = 0; line < TAMLinesConfigs; line++) {
		if (line != 0)
		{
			printf("%d", line);
		}
				
		if (line < 10) {
			printf(" ");
		}
		for (column = 0; column < TAMColumnsConfigs; column++) {
			if (column == 0 && line == 0)
			{
				for (int i = 0; i < TAMColumnsConfigs; i++)
				{
					if (i < 10)
					{
						printf(" ");
					}
					printf(" %d", i);
				}
				printf("\n");
				if (line == 0)
				{
					printf("%d", line);
				}
				
			}
			if (line == 0 && column == 0)
			{
				printf(" ");
			}
			
			if (table[line][column] == 1) {
				printf(" * ");
			} else {
				printf(" . ");
			}
		}
		printf("\n");
	}
}

int limitsVerification(int line, int column) {
	if (line >= TAMLinesConfigs || column >= TAMColumnsConfigs || line < 0 || column < 0 ) {
		return 0;
	}
	else {
		return 1;
	}
}

//Adiciona apenas 1 celula
void addOneCell(){
	int line, column, verification;
	
	do
	{
		fflush(stdin);

		printf("\nInsira as coordenadas da celula (linha, coluna): ");
		scanf("(%d, %d)", &line, &column);

		verification = limitsVerification(line, column);

		if (verification == 0)
		{
			printf("\nFora dos limites, reintroduza novos valores!");
			printf("\nLimites do tabuleiro\n Linhas: 0-%d \n Colunas: 0-%d", TAMLinesConfigs, TAMColumnsConfigs);
		}
		

	} while (verification == 0);

	table[line][column] = 1;
	
	mostCellsLived += 1;
	mostCellsLived += 1;
}

//Apaga apenas 1 celula, os parametros sao as coordenadas inseridas pelo utilizador
void deleteOneCell(){
	int line, column, verification;
	
	do
	{
		fflush(stdin);

		printf("\nInsira as coordenadas da celula (linha, coluna): ");
		scanf("(%d, %d)", &line, &column);

		verification = limitsVerification(line, column);

		if (verification == 0)
		{
			printf("\nFora dos limites, reintroduza novos valores!");
			printf("\nLimites do tabuleiro\n Linhas: 0-%d \n Colunas: 0-%d", TAMLinesConfigs, TAMColumnsConfigs);
		}
		

	} while (verification == 0);

	table[line][column] = 0;

	mostCellsLived -= 1;
	
}

//Adiciona Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
void addCells(){
	int line, column, quant_cells, verification;
	
	do
	{
		fflush(stdin);

		printf("\nInsira a quantidade de celulas que deseja adicionar: ");
		scanf("%d", &quant_cells);

		if (quant_cells <= 0)
		{
			printf("\nIntroduza um valor valido!");
		}
		
	} while (quant_cells <= 0);
	
	
	
	for (int i = 1; i <= quant_cells; i++){
		showTable();
		
		do
		{
			fflush(stdin);
		
			printf("\nInsira as coordenadas da celula (linha, coluna): ");
			scanf("(%d, %d)", &line, &column);

			verification = limitsVerification(line, column);

			if (verification == 0)
			{
				printf("\nFora dos limites, reintroduza novos valores!");
				printf("\nLimites do tabuleiro\n Linhas: 0-%d \n Colunas: 0-%d", TAMLinesConfigs, TAMColumnsConfigs);
			}

		} while (verification == 0);

		table[line][column] = 1;
	}

	mostCellsLived += quant_cells;
	lessCellsAlive += quant_cells;

}

//Apaga Varias Celulas
//quant_cells == Quantidade de Celulas a inserir pelo utilizador
void deleteCells(){
	int line, column, quant_cells, verification;
	
	do
	{
		fflush(stdin);
	
		printf("\nInsira a quantidade de celulas que deseja apagar: ");
		scanf("%d", &quant_cells);

		if (quant_cells <= 0)
		{
			printf("\nIntroduza um valor valido!");
		}
	} while (quant_cells <= 0);
	
	
	for (int i = 1; i <= quant_cells; i++){
		showTable();
		
		do
		{
			fflush(stdin);
		
			printf("\nInsira as coordenadas da celula (linha, coluna): ");
			scanf("(%d, %d)", &line, &column);

			verification = limitsVerification(line, column);

			if (verification == 0)
			{
				printf("\nFora dos limites, reintroduza novos valores!");
				printf("\nLimites do tabuleiro\n Linhas: 0-%d \n Colunas: 0-%d", TAMLinesConfigs, TAMColumnsConfigs);
			}
		} while (verification == 0);
		
		table[line][column] = 0;
	}

	mostCellsLived -= quant_cells;
}

//Celulas vivas na presente geracao
int aliveCells(){
	int countAliveCells = 0, line, column;;
	for (int line = 0; line < TAMLinesConfigs; line++) {
		for (int column = 0; column < TAMColumnsConfigs; column++) {
			if (table[line][column] == 1) {
				countAliveCells += 1;
			}
			
		}
	}
	
	return countAliveCells;
}

void changeTableTAM() {
	int TAMLines, TAMColumns;
	printf("\nALERTA: Por limitacoes tecnicas o tamanho MAXIMO do tabuleiro e 25x25.");
	printf("\nTamanho atual do tabuleiro: %dx%d", TAMLinesConfigs, TAMColumnsConfigs);
	printf("\nIntroduza o tamanho do tabuleiro (Exemplo: 25x25): ");
	scanf("%dx%d", &TAMLines, &TAMColumns);
	if (TAM - TAMLines > 0 && TAM - TAMColumns > 0) {
		TAMLinesConfigs = TAMLines;
		TAMColumnsConfigs = TAMColumns;
		printf("\nTamanho do tabuleiro atualizado com sucesso!\n");
		cooldown(3.0);
	} else {
		printf("\nLimite de tabuleiro excedido. Por favor insira um numero menor que 25 no tamanho do tabuleiro.\n");
		system("pause");
	}
}

void changeTableVelocity() {
	float newSecs = 0;
	printf("\nIntroduza a quantidade de tempo que deseja que o programa demore ao avancar de geracao em segundos (Exemplo: 1): ");
	scanf("%f", &newSecs);
	
	if (newSecs >= 0) {
		secsPerGen = newSecs;
		printf("\nTempo atualizado com sucesso!\n");
		cooldown(3);
	} else {
		printf("\nPor favor introduza um valor valido e em segundos!");
	}
}
//ED para Enable/Disable. Esta funcao serve para mostrar/nao mostrar o tabuleiro quando se avanca de geracao
//Por pre-definicao o tabuleiro e mostrado, o utilizador pode, ativar ou desativar essa funcionalidade.
void EDTableOnAdvanceGen() {
	if (showTableAdvanceGen == 1) {
		showTableAdvanceGen = 0;
		printf("\nO tabuleiro nao ira aparecer ao avancar a geracao!\n");
		cooldown(3.0);
	} else {
		showTableAdvanceGen = 1;
		printf("\nO tabuleiro ira aparecer ao avancar a geracao!\n");
		cooldown(3.0);
	}
}

void EDStatisticsOnAdvanceGen() {
	if (showGameStatisticsAdvanceGen == 1) {
		showGameStatisticsAdvanceGen = 0;
		printf("\nAs estatisticas do jogo nao irao aparecer ao avancar a geracao!\n");
		cooldown(3.0);
	} else {
		showGameStatisticsAdvanceGen = 1;
		printf("\nAs estatisticas do jogo irao  aparecer ao avancar a geracao!\n");
		cooldown(3.0);
	}
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
	for (int line = 0; line < TAMLinesConfigs; line++) {
		for (int column = 0; column < TAMColumnsConfigs; column++) {
			if (table[line][column] == 1) {
				printf("\nIdade da celula (%d, %d): %d; \nNasceu na geracao: %d", line, column, ages[line][column], gen - ages[line][column]);
			}
		}
	}
	printf("\n");
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
		
	if (showTableAdvanceGen == 1 && gen > 0) {
		showTable();
		if (showGameStatisticsAdvanceGen == 1) {
			getGameStatistics();
			cooldown(2.5);
		}
		cooldown(secsPerGen);
	}
		
		for (line = 0; line < TAMLinesConfigs; line++) {
			for (column = 0; column < TAMColumnsConfigs; column++) {
				
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
					
				} else if (line == 0 && column > 0 && column < TAMColumnsConfigs) {
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
					
				} else if (line == TAMLinesConfigs - 1 && column == TAMColumnsConfigs - 1) {
					if (table[line - 1][column] == 1) {
						neighbours += 1;
					}
					
					if (table[line][column - 1] == 1) {
						neighbours += 1;
					}
					
					if (table[line - 1][column - 1] == 1) {
						neighbours += 1;
					}
					
					
				} else if (line == TAMLinesConfigs - 1 && column < TAMColumnsConfigs && column >= 0) {
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
	for (line = 0; line < TAMLinesConfigs; line++) {
		for (column = 0; column < TAMColumnsConfigs; column++) {
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
	
	for (int line = 0; line < TAMLinesConfigs; line++) {
		for (column = 0; column < TAMColumnsConfigs; column++) {
			if (table[line][column] == 1) {
				ages[line][column] += 1;
			}
			
			if (table[line][column] == 1 && oldestCell < ages[line][column]) {
				oldestCell = ages[line][column];
				genOldestCellBorn = (gen + 1) - ages[line][column];
			}
			
			if (table[line][column] == 1 && youngestCell >= ages[line][column]) {
				youngestCell = ages[line][column];
				//O contador de geracoes (a variavel gen) ainda nao avancou por isso � que adiciona + 1 nesta conta
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

int menuConfigs() {
    int option;
    system("cls");
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
    printf("|******************************* MENU CONFIGURACOES **********************************|\n");
    printf("|************************************ Opcoes *****************************************|\n");
    printf("|*************************************************************************************|\n");
    printf("|**      {1} - Dimensoes do tabuleiro   **       {3} - Exibicao do tabuleiro        **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**      {2} - Velocidade de simulacao  **       {4} - Exibicao das estatisticas    **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                       {0} - Voltar ao menu principal                            **|\n");
    printf("|**                                     **                                          **|\n");
    printf("|**                                     **                                          **|\n");
    printf("*-------------------------------------------------------------------------------------*\n");

    printf("Escolha uma opcao:");
    scanf("%d", &option);
    fflush(stdin);
    return option;
}

int main () {
    int option = 10, quant_gens, optionConfigs = 10;
    
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
				system("pause");
            	break;
        	case 9:
        		while (optionConfigs != 0) {
        			optionConfigs = menuConfigs();
	        		switch (optionConfigs) {
	        			case 0:
	        				break;
	        			case 1:
	        				changeTableTAM();
	        				break;
	        			case 2:
	        				changeTableVelocity();
	        				break;
	        			case 3:
	        				EDTableOnAdvanceGen();
	        				break;
	        			case 4:
	        				EDStatisticsOnAdvanceGen();
	        				break;
	        			default:
	        				printf("\nOpcao invalida, introduza uma opcao valida!");
	        				system("pause");
	        				break;
					}
				}
				optionConfigs = 10;
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
