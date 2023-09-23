#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***********************************************/
/* Definição dos Registros                     */
/***********************************************/
typedef struct {
    int cliente;
} INFORMACAO;

typedef struct nodo {
    INFORMACAO info;
    struct nodo* prox;
} NODO;

typedef struct {
    NODO* inicio;
    NODO* fim;
} dNODO;

/***********************************************/
/* Funções Auxiliares                          */
/***********************************************/
dNODO* inicializaFila() {
    dNODO* fila = (dNODO*)malloc(sizeof(dNODO));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void insereCliente(dNODO* fila, int numCliente) {
    NODO* novoNodo = (NODO*)malloc(sizeof(NODO));
    novoNodo->info.cliente = numCliente;
    novoNodo->prox = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novoNodo;
        fila->fim = novoNodo;
    } else {
        fila->fim->prox = novoNodo;
        fila->fim = novoNodo;
    }
}

int removeCliente(dNODO* fila) {
    if (fila->inicio == NULL) {
        return -1; // Fila vazia
    }

    NODO* temp = fila->inicio;
    int numCliente = temp->info.cliente;

    if (fila->inicio == fila->fim) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = fila->inicio->prox;
    }

    free(temp);
    return numCliente;
}

void liberaFila(dNODO* fila) {
    while (fila->inicio != NULL) {
        removeCliente(fila);
    }
    free(fila);
}

/***********************************************/
/* Função Principal                            */
/**********************************************/

int main() {

        srand(time(NULL)); // Inicializa a semente para números aleatórios

        int ciclos, clientesPorCiclo;
        printf("Bem-vindo ao WaitWise\n");
        printf("Insira o tempo de simulação (ciclos): ");
        scanf("%d", &ciclos);
        printf("Insira a quantidade de entrada de clientes na fila (ciclo): ");
        scanf("%d", &clientesPorCiclo);

        dNODO *fila = inicializaFila();

        int clientesAtendidos = 0;
        for (int i = 0; i < ciclos; i++) {
            printf("\nClientes atendidos no ciclo %d:\n", i + 1);
            for (int j = 0; j < clientesPorCiclo; j++) {
                insereCliente(fila, i * clientesPorCiclo + j); // Atribui um número único de cliente
                printf("Cliente %d\n", i * clientesPorCiclo + j);
            }

            // Atendimento
            int cicloAtual = 0;
            while (cicloAtual < clientesPorCiclo && fila->inicio != NULL) {
                int tempoAtendimento = rand() % 6 + 1; // Tempo de atendimento aleatório de 1 a 6 ciclos
                int cliente = removeCliente(fila);
                clientesAtendidos++;
                printf("Cliente %d atendido em %d ciclo(s)\n", cliente, tempoAtendimento);
                cicloAtual++;
            }
        }

        printf("\nResultados da simulação da fila do WaitWise\n");
        printf("Número de clientes atendidos: %d\n", clientesAtendidos);
        printf("Número de clientes restantes na fila: %d\n",
               fila->inicio != NULL ? 1 : 0); // Se a fila não estiver vazia, há pelo menos 1 cliente
        printf("Tempo de espera na fila (ciclos): %d\n", ciclos);

        liberaFila(fila);

        return 0;
    }
