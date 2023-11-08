#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Área para descobrir se o usuário está no windows ou no linux 
//---------------------------------------------------------------------
/*
    if para define, se usuário usa windowns ele tem uma biblioteca _WIN32 
    então a #define dele será de cls para a função Limpar_Tela() 
    caso não tenha será considerado a função Limpar_Tela() com clear
*/
#ifdef _WIN32
    #define Limpar_Tela "cls"
#else
    #define Limpar_Tela "clear"
#endif

//---------------------------------------------------------------------
/*
    Cabeçalho de Funções existentes no programa funcoes.c.
    Todas as funções estão mais fáceis de se ver em funcoes.c
*/
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
//Área de estrutura externa
extern struct Cliente* clientes;
//ultima atualização 08/11/2023