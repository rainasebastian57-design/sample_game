#include <stdio.h>
#include <string.h>
#include <emscripten/emscripten.h>

#define ROWS 10
#define COLS 15

char maze[ROWS][COLS + 1] = {
    "###############",
    "#P###### # ### ",
    "#    #   #   # ",
    "#### # ###### #",
    "#    #        #",
    "# ####### #### ",
    "#       #      ",
    "# ##### ###### ",
    "#     #    E  #",
    "###############"
};

int px = 1, py = 1;

/* Send maze to JS */
EMSCRIPTEN_KEEPALIVE
const char* getMaze() {
    static char buffer[ROWS * (COLS + 2)];
    buffer[0] = '\0';

    for (int i = 0; i < ROWS; i++) {
        strcat(buffer, maze[i]);
        strcat(buffer, "\n");
    }
    return buffer;
}

/* Move player */
EMSCRIPTEN_KEEPALIVE
void movePlayer(char dir) {
    int nx = px;
    int ny = py;

    if (dir == 'w') nx--;
    if (dir == 's') nx++;
    if (dir == 'a') ny--;
    if (dir == 'd') ny++;

    if (maze[nx][ny] != '#') {
        maze[px][py] = ' ';
        px = nx;
        py = ny;
        maze[px][py] = 'P';
    }
}

/* Win check — EXIT POSITION */
EMSCRIPTEN_KEEPALIVE
int hasWon() {
    return (px == 8 && py == 11);
}
