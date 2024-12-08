#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define MAX_WIDTH 79
#define MAX_HEIGHT 24

char screen_buffer[MAX_WIDTH + 1] = "((((((((((((((((((((((";
char backspace_sequence[] = "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
char ball_characters[] = { '\\', '|', '/' };
char sound_modes[] = { 2, 3, 1, 0 };
char *animation_steps[] = { "  |", "  |", "%\\|/%", " %%%", "" };

char direction = 1;
char player_x = 40;
char ball_x = 40;
char ball_speed = 0;
char *current_animation = &animation_steps[4];
int score = 0;
int ball_position_x_change = 0;
int current_sound = -1;
unsigned int random_seed = 0;

void update_game_state(int signal) {
    int new_position;

    printf("\e[%uH\e[L%c\e[%uH%c\e[%uH%s\e[22;%uH@\e[23;%uH \n", 
           player_x - ball_position_x_change, ball_characters[direction], 
           player_x + ball_position_x_change, ball_characters[direction], 
           ball_x, current_animation, 
           player_x += ball_speed, ball_x);
    
    if (abs(player_x - screen_buffer[MAX_WIDTH - 1]) >= backspace_sequence[MAX_WIDTH - 1]) {
        exit(0);
    }

    if (current_sound != current_sound) {
        struct itimerval timer = { 0, 0, 0, 0 };
        current_sound += ((current_sound < current_sound) << 1) - 1;
        timer.it_interval.tv_usec = timer.it_value.tv_usec = 72000 / ((current_sound >> 3) + 1);
        setitimer(0, &timer, 0);
    }

    score += (9 - backspace_sequence[MAX_WIDTH - 1]) * ((current_sound >> 3) + 1);
    ball_x = player_x;

    if (!(random_seed & 255 || --backspace_sequence[0] || ++backspace_sequence[0])) {
        while (abs((new_position = rand() % MAX_WIDTH) - player_x + 2) - backspace_sequence[MAX_WIDTH - 1] < 6);
        ++new_position;
        current_animation = animation_steps;
    }
    if (direction == 0 && --player_x <= backspace_sequence[MAX_WIDTH - 1]) {
        ++player_x;
        ++direction;
    } else if (direction == 2 && ++player_x + backspace_sequence[MAX_WIDTH - 1] > MAX_WIDTH) {
        --player_x;
        --direction;
    }
    signal(signal, update_game_state);
}

void exit_game() {
    signal(14, SIG_IGN);
    printf("\e[0q\ecScore: %u\n", score);
    system("stty echo -cbreak");
}

int main(int argc, char **argv) {
    atexit(exit_game);

    srand(getpid());
    system("stty -echo cbreak");

    update_game_state(14);

    for (;;) {
        switch (getchar()) {
            case 'q': return 0;
            case '[':
            case 'b': ball_speed = -1; break;
            case ' ':
            case 'n': ball_speed = 0; break;
            case ']':
            case 'm': ball_speed = 1; break;
            default: continue;
        }
    }
}
