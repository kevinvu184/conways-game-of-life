#include <stdio.h>

void print(int x, int y, char b[y][x]);

int main(void) {
  int x = 16;
  int y = 16;
  int generation = 53;

  char board[y][x];
  for (int i = 0; i < y; ++i) {
    scanf("%s", board[i]);
  }

  while (generation--) {
    char lives[y][x];
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        lives[i][j] = 0;
      }
    }

    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        int neighbours[8][2];
        for (int n = 0; n < 8; ++n) {
          neighbours[n][0] = -1;
          neighbours[n][1] = -1;
        }

        if (i - 1 > -1) {
          neighbours[0][0] = i - 1;
          neighbours[0][1] = j;
        }
        if (i - 1 > -1 && j + 1 < x) {
          neighbours[1][0] = i - 1;
          neighbours[1][1] = j + 1;
        }
        if (j + 1 < x) {
          neighbours[2][0] = i;
          neighbours[2][1] = j + 1;
        }
        if (i + 1 < y && j + 1 < x) {
          neighbours[3][0] = i + 1;
          neighbours[3][1] = j + 1;
        }
        if (i + 1 < y) {
          neighbours[4][0] = i + 1;
          neighbours[4][1] = j;
        }
        if (i + 1 < y && j - 1 > -1) {
          neighbours[5][0] = i + 1;
          neighbours[5][1] = j - 1;
        }
        if (j - 1 > -1) {
          neighbours[6][0] = i;
          neighbours[6][1] = j - 1;
        }
        if (i - 1 > -1 && j - 1 > -1) {
          neighbours[7][0] = i - 1;
          neighbours[7][1] = j - 1;
        }

        int live = 0;
        for (int n = 0; n < 8; ++n) {
          if (neighbours[n][0] != -1 && neighbours[n][1] != -1 &&
              board[neighbours[n][0]][neighbours[n][1]] == 'x') {
            live += 1;
          }
        }

        lives[i][j] = live;
      }
    }

    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        // Any live cell with fewer than two live neighbours dies, as if by
        // underpopulation.
        if (board[i][j] == 'x' && lives[i][j] < 2) {
          board[i][j] = '.';
        }

        // Any live cell with two or three live neighbours lives on to the next
        // generation.
        if (board[i][j] == 'x' && (lives[i][j] == 2 || lives[i][j] == 3)) {
          board[i][j] = 'x';
        }

        // Any live cell with more than three live neighbours dies, as if by
        // overpopulation.
        if (board[i][j] == 'x' && lives[i][j] > 3) {
          board[i][j] = '.';
        }

        // Any dead cell with exactly three live neighbours becomes a live cell,
        // as if by reproduction.
        if (board[i][j] == '.' && lives[i][j] == 3) {
          board[i][j] = 'x';
        }
      }
    }

    print(x, y, board);
  }

  return 0;
}

void print(int x, int y, char b[y][x]) {
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      printf("%c", b[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}