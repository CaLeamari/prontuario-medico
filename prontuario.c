#include "prontuario.h"

void inicializarLista(ListaProntuarios* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

int inserirProntuario(ListaProntuarios* lista, Prontuario novo) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 0;
    }

    novoNo->dados = novo;
    novoNo->prox = lista->inicio;
    lista->inicio = novoNo;
    lista->tamanho++;
    return 1;
}

No* buscarProntuario(ListaProntuarios* lista, const char* cpf) {
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->dados.cpf, cpf) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int removerProntuario(ListaProntuarios* lista, const char* cpf) {
    No* anterior = NULL;
    No* atual = lista->inicio;

    while (atual != NULL && strcmp(atual->dados.cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return 0;

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    lista->tamanho--;
    return 1;
}

int atualizarProntuario(ListaProntuarios* lista, const char* cpf) {
    No* no = buscarProntuario(lista, cpf);
    if (no == NULL) return 0;

    printf("\n=== Atualizar Prontuario ===\n");
    printf("Novo nome (deixe vazio para manter): ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(no->dados.nome, buffer);
    }

    printf("Nova data de nascimento (DD/MM/AAAA, vazio para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(no->dados.data_nasc, buffer);
    }

    printf("Novo historico (vazio para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(no->dados.historico, buffer);
    }

    return 1;
}

void imprimirProntuarios(ListaProntuarios* lista) {
    if (lista->tamanho == 0) {
        printf("Lista vazia!\n");
        return;
    }

    No* atual = lista->inicio;
    printf("\n=== PRONTUARIOS (%d) ===\n", lista->tamanho);

    while (atual != NULL) {
        imprimirProntuario(atual->dados);
        printf("\n\n");
        atual = atual->prox;
    }
}

void imprimirData(const char* data) {
    printf("Data: %s\n", data);
}

void imprimirProntuario(Prontuario p) {
    printf("\nNome: %s\n", p.nome);
    printf("CPF: %s\n", p.cpf);
    printf("Nascimento: %s\n", p.data_nasc);
    printf("Historico: %s\n", p.historico);
}

void lerData(char* data) {
    printf("Data nascimento (DD/MM/AAAA): ");
    fflush(stdin);
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = '\0';
}

void lerProntuario(Prontuario* p) {
    printf("\nNome: ");
    fgets(p->nome, 100, stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(p->cpf, 12, stdin);
    p->cpf[strcspn(p->cpf, "\n")] = '\0';

    lerData(p->data_nasc);

    strcpy(p->historico, "Historico inicial");
}
