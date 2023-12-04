#include "src/Game.hpp"

#include <iostream>

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS * 2.5

#define SPEED 230

void initialize_ncurses();
void terminate_ncurses();

int main(int argc, char **argv) {
  initialize_ncurses();

  Game *game = new Game(BOARD_ROWS, BOARD_COLS, SPEED);

  game->run();
  int score = game->get_score();

  delete game;
  terminate_ncurses();

  std::cout << "Game Over" << std::endl;
  std::cout << "Score: " << score << std::endl;
}

void initialize_ncurses() {
  initscr();

  cbreak();
  noecho();
  curs_set(0);

  refresh();
}

void terminate_ncurses() {
  refresh();
  endwin();
}
