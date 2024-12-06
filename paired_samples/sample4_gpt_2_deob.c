#include <stdio.h>
#include <unistd.h>
#include <complex.h>

double complex a[97687], *p, *q, *r = a, w = 0, d;
int x, y;
char b[6856] = "\x1b[2J\x1b[1;1H", *o = b, *t;

int main() {
    while ((x = getc(stdin)) > 0) {
        if (x > 10) {
            if (x > 32) {
                *r++ = w = 4;
                *r++ = w + 1;
                *r++ = (x == '#');
                r += 6;
            } else {
                w = x - 'I';
            }
        } else {
            w = x + 2;
        }
    }

    for (;;) {
        puts(o);
        o = b + 4;

        for (p = a; p < r; p += 5) {
            for (q = a; q < r; q += 5) {
                if (p == q) continue;
                d = *p - *q;
                w = cabs(d) / 2 - 1;
                if (w > 0) {
                    x = 1 - w;
                    p[2] += x * d;
                }
            }
        }

        for (p = a; p < r; p += 5) {
            x = *p * I;
            y = *p / 2;
            t = b + 10 + x + 80 * y;
            *p += p[4] += p[3] / 10 * (!p[1]);

            if (0 <= x && x < 79 && 0 <= y && y < 23) {
                t[1] |= 8;
                t[1] |= 4;
                t[80] |= 2;
            }
        }

        usleep(12321);
    }

    return 0;
}
