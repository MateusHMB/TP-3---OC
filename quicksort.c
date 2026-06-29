// Quicksort
// Referencia: https://www.geeksforgeeks.org/quick-sort/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000  // Altere para 10000 para entrada grande

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int arr[N];
    srand(42);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100000;

    quickSort(arr, 0, N - 1);

    for (int i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("ERRO: array nao esta ordenado!\n");
            return 1;
        }
    }
    printf("Quicksort concluido. N=%d\n", N);
    return 0;
}
