#pragma once

class Scoreboard {
private:
  WINDOW *win;
public:
  Scoreboard() {
    
  }

  Scoreboard(int game_board_width, int y, int x) {
    win = newwin(1, game_board_width, y, x);
  }

  void update_score(int score) {
    mvwprintw(win, 0, win->_maxx-10, "%11llu", score);
  }

  void initialize(int initial_score) {
    clear();
    mvwprintw(win, 0, 0, "Score:");
    update_score(initial_score);
    refresh();
  }

  void clear() {
    wclear(win);
  }

  void refresh() {
    wrefresh(win);
  }
};
