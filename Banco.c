#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//Área para descobrir se o usuário está no windows ou no linux 
//e criando uma definicão para limpar tela
#ifdef _WIN32
    #define LimparTela "cls"
#else
    #define LimparTela "clear"
#endif
//---------------------------------------------------------------------
//Área de struct 
struct Cliente {
    char nome[50];
    int idade;
    char CPF[15];
    int numeroConta;
    char tipoConta[20];
    float saldo;
    char status[15];
};
struct Cliente* clientes = NULL;
//---------------------------------------------------------------------
//Cabeçalho de Funções
void tela_menu();
void adicionarCliente();
void listarClientes();
void fazerDeposito();
void fazerSaque();
void fecharConta();
void fazerEmprestimo();

//---------------------------------------------------------------------
//Área de variável global
int totalClientes = 0;
int capacidadeClientes = 0;

//---------------------------------------------------------------------
int main(){
    int opcao;
    //-----------------------inicio-dos-códigos------------------------
    do {
        tela_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch(opcao) {
            case 1:
                adicionarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                fazerDeposito();
                break;
            case 4:
                fazerSaque();
                break;
            case 5:
                fecharConta();
                break;
            case 6:
                fazerEmprestimo();
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
    free(clientes);

    return 0;
}

//----------------------------Funções
void tela_menu(void){
    printf("_________________________________\n");
    printf("|__Opcoes__|____________________|\n");
    printf("|    0     |   Sair             |\n");
    printf("|    1     |   Cadastrar        |\n");
    printf("|    2     |   Listar clientes  |\n");
    printf("|    3     |   Fazer deposito   |\n");
    printf("|    4     |   Fazer saque      |\n");
    printf("|    5     |   Fechar conta     |\n");
    printf("|    6     |   Fazer emprestimo |\n");
    printf("'''''''''''''''''''''''''''''''''");
}
void realocarMemoriaClientes() {
    if (clientes == NULL) {
        capacidadeClientes = 10;
        clientes = (struct Cliente*)malloc(capacidadeClientes * sizeof(struct Cliente));
    } else {
        capacidadeClientes += 10;
        clientes = (struct Cliente*)realloc(clientes, capacidadeClientes * sizeof(struct Cliente));
    }

    if (clientes == NULL) {
        printf("Erro ao alocar memória para clientes.\n");
        exit(1);
    }
}

void adicionarCliente(){
    if (totalClientes >= capacidadeClientes) {
        realocarMemoriaClientes();
    }

    struct Cliente novoCliente;
    printf("______________________________________________\n");
    printf("Por gentileza nos informe o seu nome completo: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    printf("Nos informe a sua idade: ");
    scanf("%d", &novoCliente.idade);
    getchar();
    printf("Nos informe o seu CPF: ");
    fgets(novoCliente.CPF, sizeof(novoCliente.CPF), stdin);

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].CPF, novoCliente.CPF) == 0) {
            printf("Cliente já cadastrado.\n");
            return;
        }
    }
    if (novoCliente.idade < 18) {
        printf("Cliente precisa ser maior de idade.\n");
        return;
    }
}

void listarClientes() {
    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s", clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("CPF: %s", clientes[i].CPF);
        printf("Numero da Conta: %d\n", clientes[i].numeroConta);
        printf("Tipo da Conta: %s", clientes[i].tipoConta);
        printf("Status: %s\n", clientes[i].status);
        printf("Saldo: %.2f\n\n", clientes[i].saldo);
    }
}

void fazerDeposito() {
    int numeroConta;
    float valor;
    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].numeroConta == numeroConta) {
            clientes[i].saldo += valor;
            printf("Deposito efetuado com sucesso.\n");
            return;
        }
    }

    printf("Conta nao encontrada.\n");
}
void fazerSaque() {
    int numeroConta;
    float valor;
    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);
    printf("Digite o valor a ser sacado: ");
    scanf("%f", &valor);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].numeroConta == numeroConta) {
            if (clientes[i].saldo >= valor) {
                clientes[i].saldo -= valor;
                printf("Saque efetuado com sucesso.\n");
            } else {
                printf("Saldo insuficiente.\n");
            }
            return;
        }
    }
    printf("Conta nao encontrada.\n");
}
void fecharConta() {
    int numeroConta;
    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].numeroConta == numeroConta) {
            if (clientes[i].saldo == 0) {
                strcpy(clientes[i].status, "Fechada");
                printf("Conta fechada com sucesso.\n");
            } else {
                printf("E necessario esvaziar a conta antes de fecha-la.\n");
            }
            return;
        }
    }
    printf("Conta nao encontrada.\n");
}

