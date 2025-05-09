#ifndef PRONTUARIO_H
#define PRONTUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char cpf[12];
    char data_nasc[11];
    char historico[200];
} Prontuario;

//no da lista 
typedef struct No {
    Prontuario dados;
    struct No* prox; //ponteiro para o prox no
} No;

typedef struct {
    No* inicio; 
    int tamanho; //qntd de pront na lista
} ListaProntuarios;

// Fun
void inicializarLista(ListaProntuarios* lista);
int inserirProntuario(ListaProntuarios* lista, Prontuario novo);
No* buscarProntuario(ListaProntuarios* lista, const char* cpf);
int removerProntuario(ListaProntuarios* lista, const char* cpf);
void imprimirProntuarios(ListaProntuarios* lista);
void imprimirData(const char* data);
void imprimirProntuario(Prontuario p);
void lerData(char* data);
void lerProntuario(Prontuario* p);
int atualizarProntuario(ListaProntuarios* lista, const char* cpf);

#endif
