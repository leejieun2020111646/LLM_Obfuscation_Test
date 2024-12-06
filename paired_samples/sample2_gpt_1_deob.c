#include <stdio.h>

int main() {
    static int num = 0;
    for (; num != 3; ++num) {
        if (!!(num & 1 << 0)) {
            printf("%d\n", num);
        }
    }
    return 0;
}
