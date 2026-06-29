// Bubblesort
// Referencia: https://www.geeksforgeeks.org/bubble-sort/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000  // Altere para 10000 para entrada grande

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[N];
    srand(42);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100000;

    bubbleSort(arr, N);

    // Verifica se ordenou corretamente
    for (int i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("ERRO: array nao esta ordenado!\n");
            return 1;
        }
    }
    printf("Bubblesort concluido. N=%d\n", N);
    return 0;
}
