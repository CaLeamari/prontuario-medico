#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Para QueryPerformanceCounter
#include "prontuario.h"

#define NUM_TESTES 1000000

// Função para gerar string aleatória
void gerar_string_aleatoria(char *str, int tamanho) {
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < tamanho-1; i++) {
        str[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    str[tamanho-1] = '\0';
}

// Função para obter tempo de alta precisão
double get_high_res_time() {
    LARGE_INTEGER frequency, time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return (double)time.QuadPart / frequency.QuadPart;
}

// Função para imprimir tempo formatado
void print_time(const char* label, double seconds) {
    if (seconds < 0.0001) {
        printf("%s: 0.0001 segundos\n", label);
    } else {
        printf("%s: %.4f segundos\n", label, seconds);
    }
}

// Versão automática da função de atualização para benchmark
int atualizarProntuario_benchmark(ListaProntuarios* lista, const char* cpf) {
    No* no = buscarProntuario(lista, cpf);
    if (no == NULL) return 0;

    // Atualizações automáticas para o teste
    strcpy(no->dados.nome, "Nome Atualizado");
    strcpy(no->dados.data_nasc, "01/01/2023");
    strcpy(no->dados.historico, "Historico atualizado pelo benchmark");
    
    return 1;
}

int main() {
    ListaProntuarios lista;
    inicializarLista(&lista);
    double start_time, end_time;
    double insert_time = 0, search_time = 0, update_time = 0, remove_time = 0;

    // Inicializa o gerador de números aleatórios
    srand((unsigned int)time(NULL));

    printf("\n Iniciando benchmark...\n");
    printf("Testando com %d elementos\n\n", NUM_TESTES);

    // Pré-aquecimento
    for (int i = 0; i < NUM_TESTES; i++) {
        Prontuario p;
        snprintf(p.cpf, sizeof(p.cpf), "%011d", rand());
        inserirProntuario(&lista, p);
    }
    while (lista.inicio != NULL) {
        removerProntuario(&lista, lista.inicio->dados.cpf);
    }

    // Teste de Inserção Aleatória
    printf("Inserindo %d elementos aleatoriamente...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        Prontuario p;
        snprintf(p.cpf, sizeof(p.cpf), "%011d", rand()); // CPF aleatório
        gerar_string_aleatoria(p.nome, sizeof(p.nome)); // Nome aleatório
        
        // Data aleatória entre 01/01/1950 e 31/12/2010
        int dia = 1 + rand() % 31;
        int mes = 1 + rand() % 12;
        int ano = 1950 + rand() % 61;
        snprintf(p.data_nasc, sizeof(p.data_nasc), "%02d/%02d/%04d", dia, mes, ano);
        
        gerar_string_aleatoria(p.historico, sizeof(p.historico)); // Histórico aleatório
        
        inserirProntuario(&lista, p);
    }
    end_time = get_high_res_time();
    insert_time = end_time - start_time;
    printf("Insercao concluida.\n\n");

    // Teste de Busca (agora busca por CPFs aleatórios que podem não existir)
    printf("Buscando %d elementos aleatoriamente...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        char cpf[12];
        snprintf(cpf, sizeof(cpf), "%011d", rand()); // Busca por CPF aleatório
        buscarProntuario(&lista, cpf);
    }
    end_time = get_high_res_time();
    search_time = end_time - start_time;
    printf("Busca concluida.\n\n");

    // Teste de Atualização (tenta atualizar CPFs aleatórios)
    printf("Atualizando %d elementos aleatoriamente...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        char cpf[12];
        snprintf(cpf, sizeof(cpf), "%011d", rand()); // CPF aleatório
        atualizarProntuario_benchmark(&lista, cpf);
    }
    end_time = get_high_res_time();
    update_time = end_time - start_time;
    printf("Atualizacao concluida.\n\n");

    // Teste de Remoção (remove em ordem aleatória)
    printf("Removendo %d elementos aleatoriamente...\n", NUM_TESTES);
    start_time = get_high_res_time();
    
    // Primeiro coletamos todos os CPFs existentes
    char** cpfs = (char**)malloc(NUM_TESTES * sizeof(char*));
    No* atual = lista.inicio;
    for (int i = 0; i < NUM_TESTES && atual != NULL; i++) {
        cpfs[i] = strdup(atual->dados.cpf);
        atual = atual->prox;
    }
    
    // Depois removemos em ordem aleatória
    for (int i = 0; i < NUM_TESTES; i++) {
        int idx = rand() % NUM_TESTES;
        if (cpfs[idx] != NULL) {
            removerProntuario(&lista, cpfs[idx]);
            free(cpfs[idx]);
            cpfs[idx] = NULL;
        }
    }
    free(cpfs);
    
    end_time = get_high_res_time();
    remove_time = end_time - start_time;
    printf("Remocao concluida.\n\n");

    // Resultados
    printf("---\n");
    printf("--- Resultados do Benchmark Aleatório ---\n");
    print_time("Tempo de insercao", insert_time);
    print_time("Tempo de busca", search_time);
    print_time("Tempo de atualizacao", update_time);
    print_time("Tempo de remocao", remove_time);
    printf("Tempo total: %.4f segundos\n", 
          insert_time + search_time + update_time + remove_time);

    return 0;
}