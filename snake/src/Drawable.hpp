#pragma once
#include <ncurses.h>

#define DEFAULT_ICON '@'

class Drawable {
protected:
  int y;
  int x;
  chtype icon;
public:
  Drawable() {
    y = x = 0;
    icon = DEFAULT_ICON;
  }

  Drawable(int y, int x, chtype icon) {
    this->y = y;
    this->x = x;
    this->icon = icon;
  }

  int get_y() const {
    return y;
  }

  int get_x() const {
    return x;
  }

  chtype get_icon() const {
    return icon;
  }
};
