#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Programa: Detective Quest - Mapa da Mansão
    Descrição:
        Este programa representa o mapa da mansão como uma ÁRVORE BINÁRIA.
        Cada nó é um cômodo (Sala) que possui dois possíveis caminhos:
        - esquerda (e)
        - direita (d)
        O jogador inicia no Hall de Entrada e explora os cômodos até chegar
        a um local sem caminhos (nó folha).
*/

// ==============================
// Definição da estrutura da árvore
// ==============================

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];           // Nome da sala
    struct Sala *esquerda;   // Ponteiro para o caminho da esquerda
    struct Sala *direita;    // Ponteiro para o caminho da direita
} Sala;

// ==============================
// Funções auxiliares
// ==============================

/*
    Função: criarSala
    Descrição: aloca dinamicamente uma nova sala, atribui o nome e retorna o ponteiro.
*/
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

/*
    Função: explorarSalas
    Descrição:
        Permite que o jogador explore a mansão.
        O jogador escolhe entre:
        - 'e' para ir à esquerda
        - 'd' para ir à direita
        - 's' para sair da exploração
*/
void explorarSalas(Sala *atual) {
    char escolha;

    printf("\nVocê está no(a): %s\n", atual->nome);

    // Caso o cômodo não tenha caminhos, termina a exploração
    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf(" Este é um cômodo sem saídas. Você chegou ao fim da exploração!\n");
        return;
    }

    // Enquanto o jogador não sair manualmente nem chegar a uma folha
    while (1) {
        printf("\nEscolha seu caminho:\n");
        if (atual->esquerda != NULL)
            printf("e - Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf("d - Ir para a direita (%s)\n", atual->direita->nome);
        printf("s - Sair da mansão\n");
        printf("Opção: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                explorarSalas(atual->esquerda);
                return;
            } else {
                printf(" Não há caminho à esquerda!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                explorarSalas(atual->direita);
                return;
            } else {
                printf(" Não há caminho à direita!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("\nVocê decidiu sair da mansão. \n");
            return;
        } 
        else {
            printf("❌ Opção inválida! Tente novamente.\n");
        }
    }
}

/*
    Função: liberarSalas
    Descrição:
        Libera a memória alocada para toda a árvore (liberação recursiva).
*/
void liberarSalas(Sala *raiz) {
    if (raiz == NULL) return;

    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// ==============================
// Função principal
// ==============================

int main() {
    // Criação da árvore de forma fixa (estrutura da mansão)
    /*
            [Hall de Entrada]
               /           \
        [Sala de Estar]   [Cozinha]
           /      \           \
     [Biblioteca] [Jardim]   [Porão]
    */

    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão");

    // Conexões entre os cômodos
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    // Introdução
    printf("=== DETECTIVE QUEST - MANSÃO MISTERIOSA ===\n");
    printf("Explore a mansão e descubra o caminho certo!\n");
    printf("--------------------------------------------\n");

    // Início da exploração a partir do Hall
    explorarSalas(hall);

    // Libera memória ao final
    liberarSalas(hall);

    printf("\nExploração encerrada. Até a próxima, detetive! \n");

    return 0;
}
