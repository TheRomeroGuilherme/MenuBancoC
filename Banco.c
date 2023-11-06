#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>


//---------------------------------------------------------------------
int main(){
    int opcao;
    //-----------------------inicio-dos-códigos------------------------
    system(Limpar_Tela);
    printf("Seja Bem-vind@ ao Banco Imobiliario\n");
    printf("Onde nossa FUNCAO e fazer voce ficar RICO!!\n\n");
    do {
        telaMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

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
                printf("Opcao invalida.\n");
        }
        
    } while(opcao != 0);
    free(clientes);
    return 0;
}
