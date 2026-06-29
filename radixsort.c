// Radixsort
// Referencia: https://www.geeksforgeeks.org/radix-sort/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000  // Altere para 10000 para entrada grande

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    int arr[N];
    srand(42);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100000;

    radixSort(arr, N);

    for (int i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("ERRO: array nao esta ordenado!\n");
            return 1;
        }
    }
    printf("Radixsort concluido. N=%d\n", N);
    return 0;
}
