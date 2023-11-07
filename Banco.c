#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------
/*
    Sempre que for chamar uma função na main.c chame ela entre ".h", 
    pois é uma biblioteca criada para no local, já as outras que 
    contem <> são bibliotecas já feitas para otimizar trabalhos 
    complexos, estilo a <math.h> que ajuda a minimizar os códigos com 
    muitas operações de matemática.
*/ 
#include "funcoes.h"



//---------------------------------------------------------------------
int main(){
    //-----------------------Variável-local-main-----------------------
    int opcao;
    //-----------------------inicio-dos-códigos------------------------
    /*
        Chamando função para limpar a tela, 
        está mais fácil de ser vista em funções.h
    */
    system(Limpar_Tela);

    printf("Seja Bem-vind@ ao Banco Imobiliario\n");
    printf("Onde nossa FUNCAO e fazer voce ficar RICO!!\n\n");
    //-----------------------------------------------------------------
    /*
        Aqui temos um laço de repetição de DO WHILE, onde o usuário só 
        vai sair se a variável for 0, após ver a opção que o usuário 
        digitar segue para as funções desejadas! 
    */
    do {
        //-------------------------------------------------------------
        /*
            Uma função para imprimir o menu principal chamada 
            telaMenu();
        */
        telaMenu();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        //------------------------------------------------------------- 
        /*
            Lendo a opção do usuário e fazendo uma limpeza de buffer 
            do teclado.
        */

        /*
            Todas as funções estão mais fáceis de se ver em funcoes.c
        */
        switch(opcao) {
            case 1:
                system(Limpar_Tela);
                adicionarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                system(Limpar_Tela);
                fazerDeposito();
                break;
            case 4:
                system(Limpar_Tela);
                fazerSaque();
                break;
            case 5:
                system(Limpar_Tela);
                fecharConta();
                break;
            case 6:
                system(Limpar_Tela);
                fazerEmprestimo();
                break;
            case 0:
                system(Limpar_Tela);
                printf(" _____________________________________ \n");
                printf("|                                     |\n");
                printf("|           Saindo do sistema         |\n");
                printf("|_____________________________________|\n");
                
                break;

            default:
            //-------------------------------------------------------------
            /*
                caso o usuário digitar um número indesejado ele caira nesse
                caso e voltará ao menu principal
            */
                printf("Opcao invalida.\n");
        }
        
    } while(opcao != 0);
    //---------------------------------------------------------------------
    /*
        Quando o usuário sair do programa com a opção 0 irá limpar todas 
        as memórias que foram alocadas para a struct clientes.
    */
    free(clientes);

    return 0;
}
