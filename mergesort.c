// Mergesort
// Referencia: https://www.geeksforgeeks.org/merge-sort/

#include <stdio.h>
#include <stdlib.h>

#define N 1000  // Altere para 10000 para entrada grande

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[N];
    srand(42);
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100000;

    mergeSort(arr, 0, N - 1);

    for (int i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("ERRO: array nao esta ordenado!\n");
            return 1;
        }
    }
    printf("Mergesort concluido. N=%d\n", N);
    return 0;
}
