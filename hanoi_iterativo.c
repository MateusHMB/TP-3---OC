// Torre de Hanoi — versao ITERATIVA com pilha explicita

// Referencia base da logica iterativa:
//   https://www.geeksforgeeks.org/iterative-tower-of-hanoi/

#include <stdio.h>
#include <stdlib.h>

#define N_DISCOS 20  // mesmo valor do recursivo para comparacao justa

// Estrutura compacta para cada frame da pilha manual (16 bytes)
typedef struct {
    int  n;      // numero de discos neste subproblema
    char from;   // pino de origem
    char to;     // pino de destino
    char aux;    // pino auxiliar
    char phase;  // 0 = primeira chamada, 1 = apos mover disco maior
} Frame;

long long moves = 0;

void hanoi_iterativo(int n_inicial, char from, char to, char aux) {
    // Tamanho maximo da pilha: 2*n - 1 frames ativos simultaneamente
    int max_frames = 2 * n_inicial + 2;
    Frame *pilha = (Frame *)malloc(max_frames * sizeof(Frame));
    if (!pilha) {
        fprintf(stderr, "Erro: malloc falhou\n");
        exit(1);
    }

    int top = 0;
    pilha[top].n     = n_inicial;
    pilha[top].from  = from;
    pilha[top].to    = to;
    pilha[top].aux   = aux;
    pilha[top].phase = 0;

    while (top >= 0) {
        Frame *f = &pilha[top];  // acesso ao topo — localidade temporal

        if (f->n == 1) {
            // Caso base: move o disco diretamente
            moves++;
            top--;
        } else if (f->phase == 0) {
            // Fase 0: empilha subproblema (n-1, from -> aux)
            f->phase = 1;  // na volta, faremos a fase 1
            top++;
            pilha[top].n     = f->n - 1;
            pilha[top].from  = f->from;
            pilha[top].to    = f->aux;
            pilha[top].aux   = f->to;
            pilha[top].phase = 0;
        } else {
            // Fase 1: move o disco maior e empilha (n-1, aux -> to)
            moves++;
            char aux_saved = f->aux;
            char to_saved  = f->to;
            int  n_saved   = f->n;
            top--;  // descarta frame atual
            top++;
            pilha[top].n     = n_saved - 1;
            pilha[top].from  = aux_saved;
            pilha[top].to    = to_saved;
            pilha[top].aux   = f ? f->from : ' ';  // recupera do frame anterior nao mais disponivel
            // Correcao: recalcula aux como o pino restante
            // Os tres pinos sao A, B, C. O aux e o que nao e from nem to.
            char pinos[3] = {'A', 'B', 'C'};
            char novo_aux = ' ';
            for (int i = 0; i < 3; i++) {
                if (pinos[i] != pilha[top].from && pinos[i] != pilha[top].to) {
                    novo_aux = pinos[i];
                    break;
                }
            }
            pilha[top].aux   = novo_aux;
            pilha[top].phase = 0;
        }
    }

    free(pilha);
}

int main() {
    moves = 0;
    hanoi_iterativo(N_DISCOS, 'A', 'C', 'B');
    printf("Hanoi iterativo (cache-friendly) com %d discos: %lld movimentos\n", N_DISCOS, moves);
    return 0;
}
