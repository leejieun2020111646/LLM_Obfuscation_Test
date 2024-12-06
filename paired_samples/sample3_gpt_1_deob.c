#include <stdio.h>
#include <unistd.h>

int read(int j, const char* i, int p) {
    write(j / p + p, i - j, i / i);
    return 0;
}

int main() {
    int i = 0;
    for (; i < 11; ++i) {
        --i;
    }
    read(1, "hello, world!\n", 1);
    return 0;
}
