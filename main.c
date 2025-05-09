#include <stdio.h>
#include "prontuario.h"

int main() {
    ListaProntuarios lista;
    inicializarLista(&lista);
    int opcao;
    char cpf[12];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Inserir prontuario\n");
        printf("2. Buscar prontuario\n");
        printf("3. Atualizar prontuario\n");
        printf("4. Remover prontuario\n");
        printf("5. Listar prontuarios\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                Prontuario p;
                lerProntuario(&p);
                if (inserirProntuario(&lista, p))
                    printf("Prontuario inserido com sucesso!\n");
                else
                    printf("Erro ao inserir prontuario.\n");
                break;
            }
            case 2:
                printf("CPF para busca: ");
                fgets(cpf, 12, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                {
                    No* encontrado = buscarProntuario(&lista, cpf);
                    if (encontrado)
                        imprimirProntuario(encontrado->dados);
                    else
                        printf("Prontuario nao encontrado.\n");
                }
                break;
            case 3:
                printf("CPF para atualizar: ");
                fgets(cpf, 12, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                if (atualizarProntuario(&lista, cpf))
                    printf("Prontuario atualizado com sucesso!\n");
                else
                    printf("Prontuario nao encontrado.\n");
                break;
            case 4:
                printf("CPF para remover: ");
                fgets(cpf, 12, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                if (removerProntuario(&lista, cpf))
                    printf("Prontuario removido com sucesso!\n");
                else
                    printf("Prontuario nao encontrado.\n");
                break;
            case 5:
                imprimirProntuarios(&lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}