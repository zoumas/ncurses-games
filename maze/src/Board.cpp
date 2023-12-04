#include "Board.h"

#include <cstdlib>
#include <iostream>

Board::Board(std::shared_ptr<std::vector<std::string>> maze)
{
  height = maze->size();
  width = (*maze)[0].size();
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);
  int start_y = (max_y - height) / 2;
  int start_x = (max_x - width) / 2;

  window = newwin(height, width, start_y, start_x);
  initialize();

  draw_maze(maze);
  refresh();
}

void Board::draw_maze(std::shared_ptr<std::vector<std::string>> maze)
{
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      char ch = (*maze)[y][x];
      if (ch == '.') {
        add_at(y, x, ' ');
      } else {
        add_at(y, x, ACS_CKBOARD);
      }
    }
  }
}

/// Board Destructor
Board::~Board()
{
  werase(window);
  delwin(window);
}

/// Draw a Border(Box) around the Board Window
void Board::add_border()
{
  box(window, 0, 0);
}

/// Clear the in-memory contents of the Board Window
void Board::clear()
{
  wclear(window);
}

/// Refresh the Board Window
void Board::refresh()
{
  wrefresh(window);
}

/// Clear and Refresh the Board Window
void Board::initialize()
{
  clear();
  add_border();
  refresh();
}

void Board::add_at(int y, int x, chtype icon)
{
  mvwaddch(window, y, x, icon); 
}

void Board::add(Drawable d)
{
  add_at(d.get_y(), d.get_x(), d.get_icon());
}

chtype Board::get_input()
{
  return wgetch(window);
}

void Board::get_empty_coordinates(int& y, int& x)
{
  // Επανάλαβε μέχρις ότου να βρεις συντεταγμένες κενού πεδίου
  while (mvwinch(window, y = rand() % height, x = rand() % width) != ' ');
}

chtype Board::get_char_at(int y, int x)
{
  return mvwinch(window, y, x);
}

int Board::get_height() const
{
  return height;
}

int Board::get_width() const
{
  return width;
}

WINDOW* Board::get_window() const
{
  return window;
}
