#pragma once
#include "Drawable.hpp"
#include <cstdlib>
#include "Time.hpp"

class Board {
private:
  WINDOW *win;
  int height;
  int width;
  int start_row, start_col;
  int speed; // timeout
public:
  Board() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    construct(max_y, max_x, 300);
  }

  Board(int height, int width, int speed) {
    construct(height, width, speed);
  }

  Board(const Board&) = delete;
  Board& operator=(const Board&) = delete;

  void refresh() {
    wrefresh(win);
  }

  void add(Drawable drawable) {
    add_at(drawable.get_y(), drawable.get_x(), drawable.get_icon());
  }

  void add_at(int y, int x, chtype ch) {
    mvwaddch(win, y, x, ch);
  }

  chtype get_char_at(int y, int x) {
    return mvwinch(win, y, x);
  }

  chtype get_input() {
    time_t time_last_input = Time::milliseconds();
    chtype input = wgetch(win);
    chtype new_input = -1;

    set_timeout(0);
    while ((time_last_input + speed) > Time::milliseconds()) {
      new_input = wgetch(win);
    }
    set_timeout(speed);

    if (new_input != ERR) {
      input = new_input;
    }

    return input;
  }

  void get_empty_coordinates(int &y, int &x) {
    while (mvwinch(win, y = rand()%height, x = rand()%width) != ' ');
  }

  void set_timeout(int timeout) {
    wtimeout(win, timeout);
  }

  int get_start_row() {
    return start_row;
  }

  int get_start_col() {
    return start_col;
  }

  int get_speed() {
    return speed;
  }

private:
  void construct(int height, int width, int speed) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    this->height = height;
    this->width = width;
    this->speed = speed;

    start_row = (max_y/2) - (height/2);
    start_col = (max_x/2) - (width/2);

    win = newwin(height, width, start_row, start_col);

    initialize();

    set_timeout(speed);
  }

  void initialize() {
    keypad(win, true);
    clear();
    refresh();
  }

  void clear() {
    wclear(win);
    add_border();
  }

  void add_border() {
    box(win, 0, 0);
  }
};
