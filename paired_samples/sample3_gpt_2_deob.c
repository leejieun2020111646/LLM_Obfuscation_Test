#include <stdio.h>
#include <unistd.h>

void read(int fd, const char* str, int dummy) {
    write(fd, str, 13);
}

int main() {
    read(1, "hello, world!\n", 0);
    return 0;
}
