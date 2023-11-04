#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Área para descobrir se o usuário está no windows ou no linux 
//e criando uma definicão para system(limpar_tela);
#ifdef _WIN32
    #define Limpar_Tela "cls"
#else
    #define Limpar_Tela "clear"
#endif
//---------------------------------------------------------------------
//Área de struct 
struct Cliente {
    char nome[50];
    int idade;
    char CPF[12]; 
    int numeroConta;
    char tipoConta[20];
    float saldo;
    char status[15];
};

struct Cliente* clientes = NULL;
//---------------------------------------------------------------------
//Área de variável global
int totalClientes = 0;
int capacidadeClientes = 0;
//---------------------------------------------------------------------
//Cabeçalho de Funções
void telaMenu(void);
void realocarMemoriaClientes();
void adicionarCliente();
void listarClientes();
int encontrarClientePorCPF(char CPF[]);
void fazerDeposito();
void fazerSaque();
void fecharConta();
void fazerEmprestimo();
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

//----------------------------Funções

//Função para mostrar o Menu
void telaMenu(void){
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
        printf("Erro ao alocar memoria para clientes.\n");
        exit(1);
    }
}

void adicionarCliente() {
    if (totalClientes >= capacidadeClientes) {
        realocarMemoriaClientes();
    }

    struct Cliente novoCliente;

    printf("______________________________________________\n");
    printf("Por gentileza nos informe o seu nome completo: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0'; 

    printf("Nos informe a sua idade: ");
    scanf("%d", &novoCliente.idade);
    getchar();

    printf("Nos informe o seu CPF: ");
    fgets(novoCliente.CPF, sizeof(novoCliente.CPF), stdin);
    novoCliente.CPF[strcspn(novoCliente.CPF, "\n")] = '\0';

    int indiceCliente = encontrarClientePorCPF(novoCliente.CPF);
    if (indiceCliente != -1) {
        printf("Cliente ja cadastrado.\n");
        return;
    }

    if (novoCliente.idade < 18) {
        printf("Cliente precisa ser maior de idade.\n");
        return;
    }

    printf("_________________________________\n");
    printf("|  Opcoes  | Qual tipo de conta |\n");
    printf("|__________|____________________|\n");
    printf("|    0     |   Voltar           |\n");
    printf("|    1     |   Conta Corrente   |\n");
    printf("|    2     |   Conta Poupança   |\n");
    printf("'''''''''''''''''''''''''''''''''\n");
    int escolhaConta;
    scanf("%d", &escolhaConta);
    getchar();

    if (escolhaConta == 0) {
        return ;
    } else if (escolhaConta == 1) {
        strcpy(novoCliente.tipoConta, "Conta Corrente");
    } else if (escolhaConta == 2) {
        strcpy(novoCliente.tipoConta, "Conta Poupança");
    } else {
        printf("Opção inválida.\n");
        return;
    }

    novoCliente.numeroConta = totalClientes + 1; 
    novoCliente.saldo = 0;
    strcpy(novoCliente.status, "Aberta");

    clientes[totalClientes] = novoCliente;
    totalClientes++;

    printf("Cliente adicionado com sucesso.\n");
}

void listarClientes() {
    for (int i = 0; i < totalClientes; i++) {
        printf("______________________________________________\n");
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s", clientes[i].nome);
        printf("\tIdade: %d\n", clientes[i].idade);
        printf("CPF: %s\n", clientes[i].CPF);
        printf("______________________________________________\n");
        printf("Numero da Conta: %d\t", clientes[i].numeroConta);
        printf("Tipo da Conta: %s", clientes[i].tipoConta);
        printf("\nStatus: %s", clientes[i].status);
        printf("\t\tSaldo: %.2f\n\n", clientes[i].saldo);
        printf("______________________________________________\n");
    }
}

int encontrarClientePorCPF(char CPF[]) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].CPF, CPF) == 0) {
            return i;
        }
    }
    return -1;
}

void fazerDeposito() {
    char CPF[12];
    float valorDeposito;

    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    printf("______________________________________________\n");
    int indiceCliente = encontrarClientePorCPF(CPF);

    if (indiceCliente == -1) {
        printf("\t\tCliente nao encontrado.\n");
        return;
    }
    printf("______________________________________________\n");
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valorDeposito);
    getchar();

    clientes[indiceCliente].saldo += valorDeposito;
    printf("______________________________________________\n");
    printf("Deposito efetuado com sucesso.\n Novo saldo: %.2f\n", clientes[indiceCliente].saldo);
}

void fazerSaque() {
    char CPF[12];
    float valorSaque;

    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    printf("______________________________________________\n");

    int indiceCliente = encontrarClientePorCPF(CPF);

    if (indiceCliente == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("______________________________________________\n");
    printf("Digite o valor a ser sacado: ");
    scanf("%f", &valorSaque);
    getchar();

    if (clientes[indiceCliente].saldo >= valorSaque) {
        clientes[indiceCliente].saldo -= valorSaque;
        printf("Saque de %.2f efetuado com sucesso. Novo saldo: %.2f\n", valorSaque, clientes[indiceCliente].saldo);
    } else {
        printf("______________________________________________\n");
        printf("|  Saldo insuficiente para realizar o saque. |\n");
        printf("______________________________________________\n");
    }
}

void fecharConta() {
    char CPF[12];
    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    printf("______________________________________________\n");

    int indiceCliente = encontrarClientePorCPF(CPF);

    if (indiceCliente == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    if (clientes[indiceCliente].saldo == 0) {
        strcpy(clientes[indiceCliente].status, "Fechada");
        printf("Conta fechada com sucesso.\n");
    } else {
        printf("E necessario esvaziar a conta antes de fecha-la.\n");
    }
    printf("______________________________________________\n");
}

void fazerEmprestimo() {
    char CPF[12];
    float valorEmprestimo;
    float totalSaldos = 0;

    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    printf("______________________________________________\n");
    int indiceCliente = encontrarClientePorCPF(CPF);

    if (indiceCliente == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("______________________________________________\n");
    printf("Digite o valor desejado para o emprestimo: ");
    scanf("%f", &valorEmprestimo);
    getchar();

    
    if (valorEmprestimo > (clientes[indiceCliente].saldo * 2)) {
        printf("Valor maior que o seu limite. Insira um novo valor.\n");
        return;
    }

    
    for (int i = 0; i < totalClientes; i++) {
        totalSaldos += clientes[i].saldo;
    }

    
    if (valorEmprestimo > (totalSaldos * 0.2)) {
        printf("Valor maior que o credito disponivel nesta agencia.\n");
        return;
    }
    printf("______________________________________________\n");
    clientes[indiceCliente].saldo += valorEmprestimo;
    printf("Emprestimo efetuado com sucesso.\n");
    printf("______________________________________________\n");
}
