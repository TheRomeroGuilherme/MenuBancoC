#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//---------------------------------------------------------------------
//Área de variável global
int totalClientes = 0;
int capacidadeClientes = 0;

//----------------------------structs----------------------------------
struct Cliente {
    char nome[50];
    int idade;
    //CPF sigla para cadastro pessoa fisica 
    char CPF[12]; 
    int numeroConta;
    char tipoConta[20];
    float saldo;
    char status[15];
};
/*
    struct Clientes* e uma variável do tipo ponteiro chamada clientes 
    inicializado como NULL
*/
struct Cliente* clientes = NULL;

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
//----------------------------Funções----------------------------------
//Função para alocação de memória
void realocarMemoriaClientes() {
    /*
        Comparação se cliente igual a null, aumenta a capacidade para 10,
        malloc pega o struct Cliente e aumenta a capacidade para cada 
        campo específico dentro dela.
    */
    if (clientes == NULL) {
        capacidadeClientes = 10;
        clientes = (struct Cliente*)malloc(capacidadeClientes * sizeof(struct Cliente));
    } else {
        /*
            Se capacidade não for necessária ela aumenta mais 10 de espaço
        */
        capacidadeClientes += 10;
        clientes = (struct Cliente*)realloc(clientes, capacidadeClientes * sizeof(struct Cliente));
    }

    /*
        Caso der erro ao alocar clientes monstra uma mensagem de erro
    */
    if (clientes == NULL) {
        printf("Erro ao alocar memoria para clientes.\n");
        exit(1);
    }
}

//---------------------------------------------------------------------
void adicionarCliente() {
    /*
        Verifica se o número atual de clientes atingiu a capacidade 
        alocada e realoca a memória para acomodar mais clientes
    */
    if (totalClientes >= capacidadeClientes) {
        realocarMemoriaClientes(); 
    }

    //Cria uma nova estrutura para armazenar as informações do novo cliente
    struct Cliente novoCliente;  

    //Coleta o nome do cliente
    printf("Por gentileza nos informe o seu nome completo: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';  


    //Coleta a idade do cliente
    printf("Nos informe a sua idade: ");
    scanf("%d", &novoCliente.idade);
    getchar();

    //Coleta o CPF do cliente
    printf("Nos informe o seu CPF: ");
    fgets(novoCliente.CPF, sizeof(novoCliente.CPF), stdin);
    novoCliente.CPF[strcspn(novoCliente.CPF, "\n")] = '\0';  

    //Verifica se o cliente já está cadastrado com base no CPF
    int indiceCliente = encontrarClientePorCPF(novoCliente.CPF);
    if (indiceCliente != -1) {
        printf("Cliente já cadastrado.\n");
        return;
    }

    //Verifica se o cliente é maior de idade
    if (novoCliente.idade < 18) {
        printf("Cliente precisa ser maior de idade.\n");
        return;
    }

    //Coleta o tipo de conta desejada pelo cliente
    printf("Qual tipo de conta deseja abrir?\n");
    printf("1 - Conta Corrente\n");
    printf("2 - Conta Poupança\n");
    printf("0 - Voltar\n");
    int escolhaConta;
    scanf("%d", &escolhaConta);
    getchar();  
    
    //Define o tipo da conta com base na escolha do cliente
    if (escolhaConta == 0) {
        //Retorna se a escolha for voltar
        return;  
    } else if (escolhaConta == 1) {
        strcpy(novoCliente.tipoConta, "Conta Corrente");
    } else if (escolhaConta == 2) {
        strcpy(novoCliente.tipoConta, "Conta Poupança");
    } else {
        printf("Opção inválida.\n");
        return;
    }

    //Atribui os demais dados ao novo cliente e incrementando os com +1
    novoCliente.numeroConta = totalClientes + 1;
    novoCliente.saldo = 0;
    strcpy(novoCliente.status, "Aberta");

    // Adiciona o novo cliente ao banco de dados
    clientes[totalClientes] = novoCliente;
    totalClientes++;

    printf("Cliente adicionado com sucesso.\n");
}
//---------------------------------------------------------------------
/*
    Função para listar clientes, percorre um for para total de clientes
    mostrando seus campos preenchidos ao cadastrar.
*/
void listarClientes() {
    for (int i = 0; i < totalClientes; i++) {
        printf("______________________________________________\n");
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s", clientes[i].nome);
        printf("\tIdade: %d\n", clientes[i].idade);
        printf("CPF: %s\n", clientes[i].CPF);
        printf("'''''''''''''''''''''''''''''''''''''''''''''''\n");
        printf("Numero da Conta: %d\t", clientes[i].numeroConta);
        printf("Tipo da Conta: %s", clientes[i].tipoConta);
        printf("\nStatus: %s", clientes[i].status);
        printf("\t\tSaldo: %.2f\n\n", clientes[i].saldo);
        printf("______________________________________________\n");
    }
}
//---------------------------------------------------------------------
/*
    Função para encontrar clientes pelo CPF, percorre um for para cada
    cliente cadastrado, onde será analisado o campo somente do CPF de
    cada um, e se CPF encontrado for o mesmo que o cliente digitou,
    retornará o i, que será o Id da conta do cliente, pegando suas
    informações para ser alterado.
    Essa função está sendo chamada em outras funções como fazerDeposito,
    fazerSaque, fecharConta, fazerEmprestimo.
*/
int encontrarClientePorCPF(char CPF[]) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].CPF, CPF) == 0) {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------
/*
    Função para fazer o depósito da conta-corrente de cliente, abrir e
    verificar a conta do cliente pelo CPF, onde se aprovado o cliente
    digita o valor do depósito, se procedimento der erro a mensagem
    de cliente não encontrado irá ser impressa na tela, caso ao contraio
    o cliente recebera um aviso de depósito efetuado com sucesso e o seu
    saldo da conta atualizado.
*/
void fazerDeposito() {
    char CPF[12];
    float valorDeposito;

    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
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
    printf("Deposito efetuado com sucesso.\nNovo saldo: %.2f\n", clientes[indiceCliente].saldo);
}
//---------------------------------------------------------------------
/*
    Função saque, iniciará pegando o CPF do cliente vai chamar a função
    encontrarClientePorCPF(CPF), se cliente encontrado ele poderá fazer
    o saque que ele tem na conta, lembrando que ele não poderá fazer o 
    saque maior que a quantia que ele tem guardada no banco, caso a 
    quantia for menor ou igual, o saque poderá ser efetuado.
*/

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
//---------------------------------------------------------------------

void fecharConta() {
    char CPF[12];
    /*Pedindo o CPF do cliente e analisando na função encontrarClientePorCPF(CPF)*/
    printf("Digite o CPF do cliente: ");
    fgets(CPF, sizeof(CPF), stdin);
    CPF[strcspn(CPF, "\n")] = '\0';

    printf("______________________________________________\n");

    int indiceCliente = encontrarClientePorCPF(CPF);
    /*analise bem sussedida bora pro próximo passo. */

    /*caso o cliente não seja encontrado ligue 190 e começa a rezar! kkkkkkkk*/
    if (indiceCliente == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    /*caso o cliente encontrado e não tem nada na conta dele podemos fechar a conta*/
    if (clientes[indiceCliente].saldo == 0) {
        strcpy(clientes[indiceCliente].status, "Fechada");
        printf("Conta fechada com sucesso.\n");
    } 
    /*Se a conta tiver dinheiro o banco não pode aceitar o dinheiro, então pedimos 
    para o nosso cliente tirar o dinheiro da conta*/
    else {
        printf("E necessario esvaziar a conta antes de fecha-la.\n");
    }
    printf("______________________________________________\n");
}
//---------------------------------------------------------------------
/*
    Função fazer empréstimo, inicia pedindo o CPF do cliente, analisando
    se já tem cadastro ou não, se tiver o próximo passo será digitar o 
    valor do empréstimo, caso o valor do empréstimo seja menor que 20%, e
    somando os saldos da conta, o empréstimo será efetuado.
*/

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
//ultima atualização 08/11/2023