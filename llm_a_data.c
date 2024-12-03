#include <stdio.h>
#include <stdlib.h>

void bead_sort(int *a, size_t len) {
    int i, j, max, sum;
    unsigned char *beads;

    // Find maximum value in the array
    max = a[0];
    for (i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    // Allocate beads
    beads = calloc(1, max * len);

    // Place beads
    for (i = 0; i < len; i++) {
        for (j = 0; j < a[i]; j++) {
            beads[i * max + j] = 1;
        }
    }

    // Let beads fall
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

    // Write sorted values back to the array
    for (i = 0; i < len; i++) {
        j = 0;
        while (j < max && beads[i * max + j]) {
            j++;
        }
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
    int n, *arr;

    printf("Enter size of array:\n");
    scanf("%d", &n);

    arr = malloc(sizeof(int) * n);

    printf("Enter the elements of the array:\n");
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
