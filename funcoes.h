#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
extern struct Cliente* clientes;
//Área para descobrir se o usuário está no windows ou no linux 
//e criando uma definicão para system(limpar_tela);
#ifdef _WIN32
    #define Limpar_Tela "cls"
#else
    #define Limpar_Tela "clear"
#endif
