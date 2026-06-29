// Torre de Hanoi — versao RECURSIVA (original)

// Referencia: https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/

#include <stdio.h>
#include <stdlib.h>

// N_DISCOS: use 20 para entrada "pequena" (~1M movimentos)
//           use 23 para entrada "grande" (~8M movimentos)
#define N_DISCOS 20

long long moves = 0;  // contador global de movimentos

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        moves++;
        // printf("Mover disco 1 de %c para %c\n", from, to); // descomente para ver movimentos
        return;
    }
    hanoi(n - 1, from, aux, to);
    moves++;
    // printf("Mover disco %d de %c para %c\n", n, from, to);
    hanoi(n - 1, aux, to, from);
}

int main() {
    moves = 0;
    hanoi(N_DISCOS, 'A', 'C', 'B');
    printf("Hanoi recursivo com %d discos: %lld movimentos\n", N_DISCOS, moves);
    return 0;
}
