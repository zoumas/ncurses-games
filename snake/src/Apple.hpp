#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

#define APPLE_ICON 'A'

class Apple: public Drawable {
public:
  Apple(int y, int x) {
    this->y = y;
    this->x = x;
    this->icon = APPLE_ICON;
  }
};
