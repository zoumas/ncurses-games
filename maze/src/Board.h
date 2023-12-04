#pragma once

#include <ncurses.h>
#include "Drawable.h"
#include <memory>
#include <vector>
#include <string>

/// The Game Board [View]
class Board {
public:
  Board(std::shared_ptr<std::vector<std::string>> maze);
  ~Board();

  void add_border();
  void clear();
  void refresh();
  void initialize();

  void draw_maze(std::shared_ptr<std::vector<std::string>> maze);

  void add_at(int y, int x, chtype icon);
  chtype get_input();
  void add(Drawable d);

  void get_empty_coordinates(int& y, int& x);
  chtype get_char_at(int y, int x);

  int get_height() const;
  int get_width() const;
  WINDOW* get_window() const;

// Attributes
private:
  WINDOW* window;
  int height; 
  int width;
};
