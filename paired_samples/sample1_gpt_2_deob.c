#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

char character_x[] = "((((((((((((((((((((((";
char erase[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
char character_shapes[] = {92, 124, 47};
char colors[] = {2, 3, 1, 0};
char *animation_frames[] = {"  |", "  |", "%\\|/%", " %%%", ""};

int direction = 1;
int player_x = 40, player_y = 40;
int move_direction = 0;
int game_color = -1, target_color, animation_frame_index = 0;
unsigned int score = 0;
int sound_enabled = 0;

void update_game(int sig) {
    int random_value;

    printf(
        "\033[%u;%uH%c\033[%u;%uH%c\033[%u;%uH%s\03322;%uH@\03323;%uH \n",
        player_x, character_shapes[direction], player_x, character_shapes[direction],
        animation_frame_index, animation_frames[animation_frame_index],
        player_x += move_direction, player_y
    );

    if (abs(player_x - character_x[21]) >= erase[21]) {
        exit(0);
    }

    if (game_color != target_color) {
        struct itimerval timer = {0, 0, 0, 0};
        game_color += (game_color < target_color ? 1 : -1);
        timer.it_interval.tv_usec = timer.it_value.tv_usec = 72000 / ((game_color >> 3) + 1);
        setitimer(ITIMER_REAL, &timer, NULL);

        if (sound_enabled) {
            printf("\e[10;%u]", game_color + 24);
        }
    }

    score += (9 - erase[21]) * ((game_color >> 3) + 1);
    random_value = rand();

    if (!(random_value & 255) || !--erase[0] || ++erase[0]) {
        if (!animation_frames[++animation_frame_index] || (random_value & 7936)) {
            while (abs((target_color = rand() % 76) - player_x + 2) - erase[21] < 6);
            ++target_color;
            animation_frame_index = 0;
        }
    }

    if ((random_value & 31) < 3) {
        direction = random_value & 31;
    }
    if (!direction && --player_x <= erase[21]) {
        ++player_x;
        direction = 1;
    } else if (direction == 2 && ++player_x + erase[21] > 79) {
        --player_x;
        direction = 1;
    }

    signal(signal, update_game);
}

void end_game() {
    signal(SIGALRM, SIG_IGN);
    printf("\e[0q\ecScore: %u\n", score);
    system("stty echo -cbreak");
}

int main(int argc, char **argv) {
    atexit(end_game);

    if (argc < 2 || argv[1][0] != 'q') {
        sound_enabled = getenv("TERM") && (!strcmp(getenv("TERM"), "linux") || !strcmp(getenv("TERM"), "xterm"));
    }

    srand(getpid());
    system("stty -echo cbreak");

    printf("\e[2q");
    update_game(SIGALRM);

    while (1) {
        switch (getchar()) {
            case 'q':
                return 0;
            case 'w': case 'W': case 91:
                move_direction = -1;
                break;
            case 's': case 'S': case 93:
                move_direction = 1;
                break;
            case 'd': case 'D': case 50:
                target_color = 2;
                break;
            case 'a': case 'A': case 49:
                target_color = 1;
                break;
            default:
                move_direction = 0;
                break;
        }
    }

    return 0;
}
