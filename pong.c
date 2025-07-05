#include <stdio.h>

void clearScreen();
char input();
int limitRacketPosition(int playerY);
int getBallDx(int ballX, int ballY, int ballDx, int ballDy, int player1y,
              int player2y);
int getBallDyAfterWall(int ballY, int ballDy);
void draw(int ballX, int ballY, int player1y, int player2y);
void drawScore(int playerScoreFirst, int playerScoreSecond);
int getNewBallDx(int lastScorer);
int getNewBallDy(int directionCounter);

int main() {
  int player1y = 12, playerScoreFirst = 0;
  int player2y = 12, playerScoreSecond = 0;
  int ballX = 40, ballY = 13;
  int directionCounter = 0;
  int ballDx = getNewBallDx(0);
  int ballDy = getNewBallDy(directionCounter++);

  int resetFlag = 0;
  int lastScorer = 0;

  clearScreen();
  draw(ballX, ballY, player1y, player2y);
  drawScore(playerScoreFirst, playerScoreSecond);

  while (playerScoreFirst < 21 && playerScoreSecond < 21) {
    char c = input();
    if (c == 'A') {
      player1y--;
    }
    if (c == 'Z') {
      player1y++;
    }
    if (c == 'K') {
      player2y--;
    }
    if (c == 'M') {
      player2y++;
    }
    player1y = limitRacketPosition(player1y);
    player2y = limitRacketPosition(player2y);

    if (ballX <= 0) {
      playerScoreSecond++;
      lastScorer = 2;
      resetFlag = 1;
    } else if (ballX >= 79) {
      playerScoreFirst++;
      lastScorer = 1;
      resetFlag = 1;
    }

    if (resetFlag) {
      player1y = 12;
      player2y = 12;

      ballX = 40;
      ballY = 13;

      ballDx = getNewBallDx(lastScorer);
      ballDy = getNewBallDy(directionCounter++);

      resetFlag = 0;
    }

    ballDx = getBallDx(ballX, ballY, ballDx, ballDy, player1y, player2y);
    ballDy = getBallDyAfterWall(ballY, ballDy);

    ballX += ballDx;
    ballY += ballDy;

    draw(ballX, ballY, player1y, player2y);
    drawScore(playerScoreFirst, playerScoreSecond);
  }

  clearScreen();

  if (playerScoreFirst == 21) {
    printf("PLAYER %c WIN!\n", '1');
  } else {
    printf("PLAYER %c WIN!\n", '2');
  }

  return 0;
}

void clearScreen() { printf("\e[1;1H\e[2J"); }

char input() {
  int symbol;
  do {
    symbol = getchar();
    while (getchar() != '\n')
      ;
  } while (!(symbol == 'A' || symbol == 'Z' || symbol == 'K' || symbol == 'M' ||
             symbol == ' '));
  return symbol;
}

int limitRacketPosition(int playerY) {
  int result = playerY;
  if (playerY < 1) {
    result = 1;
  } else if (playerY > 21) {
    result = 21;
  }
  return result;
}

int getBallDx(int ballX, int ballY, int ballDx, int ballDy, int player1y,
              int player2y) {
  int result = ballDx;
  if (ballX + ballDx == 3 && ballY + ballDy >= player1y &&
      ballY + ballDy <= player1y + 2) {
    result = 1;
  } else if (ballX + ballDx == 77 && ballY + ballDy >= player2y &&
             ballY + ballDy <= player2y + 2) {
    result = -1;
  }
  return result;
}

int getBallDyAfterWall(int ballY, int ballDy) {
  int result = ballDy;
  if (ballY + ballDy <= 0) {
    result = 1;
  } else if (ballY + ballDy >= 24) {
    result = -1;
  }
  return result;
}

void draw(int ballX, int ballY, int player1y, int player2y) {
  clearScreen();
  for (int j = 0; j < 25; j++) {
    for (int i = 0; i < 80; i++) {
      if (i == ballX && j == ballY) {
        printf("o");
      } else if ((i == 3 && j >= player1y && j <= player1y + 2) ||
                 (i == 77 && j >= player2y && j <= player2y + 2)) {
        printf("|");
      } else if (j == 0 || j == 24) {
        printf("-");
      } else if (i == 0 || i == 79) {
        printf("|");
      } else if (i == 40) {
        printf("|");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void drawScore(int playerScoreFirst, int playerScoreSecond) {
  printf("P1: %d   -   P2: %d\n", playerScoreFirst, playerScoreSecond);
}

int getNewBallDx(int lastScorer) {
  int result = 1;
  if (lastScorer == 1) {
    result = 1;
  } else if (lastScorer == 2) {
    result = -1;
  }
  return result;
}

int getNewBallDy(int directionCounter) {
  return (directionCounter % 2 == 0) ? 1 : -1;
}