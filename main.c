#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void tabuleiro() {

    int tabuleiro[25][25];

    for (int i = 0; i <= 25 ; i++)
    {
    	printf("\n");
       for (int j = 0; j <= 25; j++)
       {
        printf(". ", tabuleiro[i,j]);
       }
    }
    system("pause");
}

int main () {
    int option;
    //tabuleiro();
    while (option != 0)
    {
        option = menu();
         switch (option)
        {
        case 0:
            break;
        case 1:
            tabuleiro();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            tabuleiro();
            break;
        case 9:
            break;                      
        default:
            printf("Opcao invalida, introduza uma opcao valida!");
            system("pause");
            menu();
            break;
        }
    } 
	return 0;
}