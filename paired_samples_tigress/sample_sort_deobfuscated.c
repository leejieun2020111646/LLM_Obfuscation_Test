#include <stdio.h>
#include <stdlib.h>

void bead_sort(int *a, size_t len) {
    int i, j, max, sum;
    unsigned char *beads;

    max = a[0];
    for (i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    beads = calloc(1, max * len);

    for (i = 0; i < len; i++) {
        for (j = 0; j < a[i]; j++) {
            beads[i * max + j] = 1;
        }
    }

    for (j = 0; j < max; j++) {
        sum = 0;
        for (i = 0; i < len; i++) {
            sum += beads[i * max + j];
            beads[i * max + j] = 0;
        }
        for (i = len - sum; i < len; i++) {
            beads[i * max + j] = 1;
        }
    }

    for (i = 0; i < len; i++) {
        for (j = 0; j < max && beads[i * max + j]; j++);
        a[i] = j;
    }

    free(beads);
}

void display(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    int *arr;

    printf("Enter size of array:\n");
    scanf("%d", &n);

    printf("Enter the elements of the array\n");
    arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    display(arr, n);

    bead_sort(arr, n);

    printf("Sorted array: ");
    display(arr, n);

    free(arr);
    return 0;
}
