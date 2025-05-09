
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //Para QueryPerformanceCounter
#include "prontuario.h"

#define NUM_TESTES 8000

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

    printf("\n Iniciando benchmark...\n");
    printf("Testando com %d elementos\n\n", NUM_TESTES);

    // Pré-aquecimento
    for (int i = 0; i < NUM_TESTES; i++) {
        Prontuario p;
        snprintf(p.cpf, sizeof(p.cpf), "%011d", i);
        inserirProntuario(&lista, p);
    }
    while (lista.inicio != NULL) {
        removerProntuario(&lista, lista.inicio->dados.cpf);
    }

    // Teste de Inserção
    printf("Inserindo %d elementos...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        Prontuario p;
        snprintf(p.nome, sizeof(p.nome), "Paciente %d", i);
        snprintf(p.cpf, sizeof(p.cpf), "%011d", i);
        strcpy(p.data_nasc, "01/01/2000");
        strcpy(p.historico, "Historico inicial");
        inserirProntuario(&lista, p);
    }
    end_time = get_high_res_time();
    insert_time = end_time - start_time;
    printf("Insercao concluida.\n\n");

    // Teste de Busca
    printf("Buscando %d elementos...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        char cpf[12];
        snprintf(cpf, sizeof(cpf), "%011d", rand() % NUM_TESTES);
        buscarProntuario(&lista, cpf);
    }
    end_time = get_high_res_time();
    search_time = end_time - start_time;
    printf("Busca concluida.\n\n");

    // Teste de Atualização
    printf("Atualizando %d elementos...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        char cpf[12];
        snprintf(cpf, sizeof(cpf), "%011d", rand() % NUM_TESTES);
        atualizarProntuario_benchmark(&lista, cpf);
    }
    end_time = get_high_res_time();
    update_time = end_time - start_time;
    printf("Atualizacao concluida.\n\n");

    // Teste de Remoção
    printf("Removendo %d elementos...\n", NUM_TESTES);
    start_time = get_high_res_time();
    for (int i = 0; i < NUM_TESTES; i++) {
        char cpf[12];
        snprintf(cpf, sizeof(cpf), "%011d", i);
        removerProntuario(&lista, cpf);
    }
    end_time = get_high_res_time();
    remove_time = end_time - start_time;
    printf("Remocao concluida.\n\n");

    // Resultados
    printf("---\n");
    printf("--- Resultados do Benchmark ---\n");
    print_time("Tempo de insercao", insert_time);
    print_time("Tempo de busca", search_time);
    print_time("Tempo de atualizacao", update_time);  // NOVO
    print_time("Tempo de remocao", remove_time);
    printf("Tempo total: %.4f segundos\n", 
          insert_time + search_time + update_time + remove_time);

    return 0;
}