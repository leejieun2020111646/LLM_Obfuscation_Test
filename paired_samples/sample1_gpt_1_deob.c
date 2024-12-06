#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define swap(b) a = b; z = *a; while (*++a) { y = *a; *a = z; z = y; }
#define set_color(u) G = u << 3; printf("\e[%uq", l[u])
#define case_action(n, action) case n: action; continue

char x[] = "((((((((((((((((((((((",
     w[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
char r[] = {92, 124, 47},
     l[] = {2, 3, 1, 0};
char *T[] = {"  |", "  |", "%\\|/%", " %%%", ""};
char direction = 1,
     player_x = 40, player_y = 40,
     move_direction = 0,
     *a, y, z, g = -1, G, X, **P = &T[4];
unsigned int score = 0;
int f = 0;

void update(int signal) {
    int random_val;
    printf(
        "\033[%u;%uH\033L%c\033[%u;%uH%c\033[%u;%uH%s\03322;%uH@\03323;%uH \n",
        *x - *w, r[direction], *x + *w, r[direction], X, *P, player_x += move_direction, player_y
    );
    if (abs(player_x - x[21]) >= w[21]) exit(0);
    if (g != G) {
        struct itimerval timer = {0, 0, 0, 0};
        g += ((g < G) << 1) - 1;
        timer.it_interval.tv_usec = timer.it_value.tv_usec = 72000 / ((g >> 3) + 1);
        setitimer(0, &timer, 0);
        if (f) printf("\e[10;%u]", g + 24);
    }
    score += (9 - w[21]) * ((g >> 3) + 1);
    player_y = player_x;
    swap(x);
    swap(w);
    random_val = rand();
    if (!(random_val & 255) || !--*w || ++*w) {
        if (!(**P && P++ || random_val & 7936)) {
            while (abs((X = rand() % 76) - *x + 2) - *w < 6);
            ++X;
            P = T;
        }
    }
    if ((random_val & 31) < 3) direction = random_val & 31;
    if (!direction && --*x <= *w && (++*x, ++direction));
    if (direction == 2 && ++*x + *w > 79 && (--*x, --direction));
    signal(signal, update);
}

void end_game() {
    signal(14, SIG_IGN);
    printf("\e[0q\ecScore: %u\n", score);
    system("stty echo -cbreak");
}

int main(int argc, char **argv) {
    atexit(end_game);
    if (argc < 2 || *argv[1] != 113) {
        f = (argc = *(int *)getenv("TERM")) == (int)0x756E696C || argc == (int)0x6C696E75;
    }
    srand(getpid());
    system("stty -echo cbreak");
    set_color(0);
    update(14);
    for (;;) {
        switch (getchar()) {
            case 113: return 0;
            case 91: case 98: case_action(44, move_direction = -1);
            case 32: case 110: case_action(46, move_direction = 0);
            case 93: case 109: case_action(47, move_direction = 1);
            case_action(49, set_color(0));
            case_action(50, set_color(1));
            case_action(51, set_color(2));
            case_action(52, set_color(3));
        }
    }
}
