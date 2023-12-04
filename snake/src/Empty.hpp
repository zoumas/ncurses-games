#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

#define DEFAULT_EMPTY_ICON ' '

class Empty: public Drawable {
public:
  Empty(int y, int x) {
    this->y = y;
    this->x = x;
    this->icon = DEFAULT_EMPTY_ICON;
  }
};
