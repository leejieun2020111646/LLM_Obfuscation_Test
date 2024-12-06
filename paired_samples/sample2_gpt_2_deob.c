#include <stdio.h>

int main() {
    for (int num = 0; num < 3; ++num) {
        if (num & 1) {
            printf("%d\n", num);
        }
    }
    return 0;
}
