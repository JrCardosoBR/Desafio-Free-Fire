#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

void listarItens(Item mochila[], int total) {
    printf("\n=== Itens na Mochila ===\n");
    printf("%-3s %-20s %-15s %-10s\n", "#", "Nome", "Tipo", "Quantidade");
    for (int i = 0; i < total; i++) {
        printf("%-3d %-20s %-15s %-10d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (total == 0) printf("(Mochila vazia)\n");
    printf("========================\n");
}

int buscarItem(Item mochila[], int total, const char* nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) return i;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    do {
        printf("\nMenu:\n1 - Adicionar item\n2 - Remover item\n3 - Listar itens\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n
        switch(opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("Mochila cheia!\n");
                    break;
                }
                printf("Nome do item: ");
                fgets(mochila[total].nome, TAM_NOME, stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';
                printf("Tipo do item: ");
                fgets(mochila[total].tipo, TAM_TIPO, stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';
                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                getchar();
                total++;
                printf("Item adicionado!\n");
                break;
            case 2: {
                char nomeBusca[TAM_NOME];
                printf("Nome do item a remover: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                int idx = buscarItem(mochila, total, nomeBusca);
                if (idx == -1) {
                    printf("Item não encontrado!\n");
                } else {
                    for (int j = idx; j < total-1; j++) {
                        mochila[j] = mochila[j+1];
                    }
                    total--;
                    printf("Item removido!\n");
                }
                break;
            }
            case 3:
                listarItens(mochila, total);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}