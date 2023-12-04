#pragma once
#include <ncurses.h>

/// Class Drawable enables derived classes 
/// to be easily displayed on the Game Board
class Drawable {
public:
  Drawable(int y, int x, chtype icon);
  virtual ~Drawable();

  /// Accessors
  int get_y() const;
  void set_y(int y);
  int get_x() const;
  void set_x(int x);
  chtype get_icon() const;
  void set_icon(chtype icon);
protected:
  int y;
  int x;
  chtype icon;
};
