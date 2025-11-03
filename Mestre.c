#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

void listarItens(Item mochila[], int total) {
    printf("\n=== Itens na Mochila ===\n");
    printf("%-3s %-20s %-15s %-10s %-10s\n", "#", "Nome", "Tipo", "Quantidade", "Prioridade");
    for (int i = 0; i < total; i++) {
        printf("%-3d %-20s %-15s %-10d %-10d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
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

void exibirDetalhesItem(const Item* item) {
    printf("\nDetalhes do item:\n");
    printf("Nome: %s\n", item->nome);
    printf("Tipo: %s\n", item->tipo);
    printf("Quantidade: %d\n", item->quantidade);
    printf("Prioridade: %d\n", item->prioridade);
}

void insertionSort(Item mochila[], int total, CriterioOrdenacao criterio, int* comparacoes) {
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            bool cond = false;
            if (criterio == ORDENAR_NOME) {
                cond = strcmp(chave.nome, mochila[j].nome) < 0;
            } else if (criterio == ORDENAR_TIPO) {
                cond = strcmp(chave.tipo, mochila[j].tipo) < 0;
            } else if (criterio == ORDENAR_PRIORIDADE) {
                cond = chave.prioridade < mochila[j].prioridade;
            }
            if (!cond) break;
            mochila[j+1] = mochila[j];
            j--;
        }
        mochila[j+1] = chave;
    }
}

bool estaOrdenadoPorNome(Item mochila[], int total) {
    for (int i = 1; i < total; i++) {
        if (strcmp(mochila[i-1].nome, mochila[i].nome) > 0) return false;
    }
    return true;
}

int buscaBinaria(Item mochila[], int total, const char* nome, int* comparacoes) {
    int ini = 0, fim = total-1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    do {
        printf("\nMenu:\n1 - Adicionar item\n2 - Remover item\n3 - Listar itens\n4 - Ordenar mochila\n5 - Busca binária por nome\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();
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
                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[total].prioridade);
                getchar();
                if (mochila[total].prioridade < 1 || mochila[total].prioridade > 5) {
                    printf("Prioridade inválida!\n");
                    break;
                }
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
            case 4: {
                printf("Critério de ordenação:\n1 - Nome\n2 - Tipo\n3 - Prioridade\nEscolha: ");
                int crit;
                scanf("%d", &crit);
                getchar();
                if (crit < 1 || crit > 3) {
                    printf("Critério inválido!\n");
                    break;
                }
                int comparacoes = 0;
                insertionSort(mochila, total, (CriterioOrdenacao)crit, &comparacoes);
                printf("Mochila ordenada! Comparações realizadas: %d\n", comparacoes);
                listarItens(mochila, total);
                break;
            }
            case 5: {
                if (!estaOrdenadoPorNome(mochila, total)) {
                    printf("A mochila deve estar ordenada por nome para busca binária!\n");
                    break;
                }
                char nomeBusca[TAM_NOME];
                printf("Nome do item a buscar: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                int comparacoes = 0;
                int idx = buscaBinaria(mochila, total, nomeBusca, &comparacoes);
                if (idx == -1) {
                    printf("Item não encontrado! Comparações: %d\n", comparacoes);
                } else {
                    exibirDetalhesItem(&mochila[idx]);
                    printf("Comparações realizadas: %d\n", comparacoes);
                }
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}