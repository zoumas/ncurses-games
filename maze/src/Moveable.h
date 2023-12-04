#pragma once

#include "Drawable.h"

class Moveable : public Drawable  {
public:
  Moveable(int y, int x, chtype icon, int max_y, int max_x);
  virtual ~Moveable();

  void move(chtype input);
  void move_up();
  void move_down();
  void move_left();
  void move_right();

  bool moved();

  int get_prev_y() const;
  int get_prev_x() const;
private:
  int max_y;
  int max_x;
  int prev_y;
  int prev_x;
  bool moved_;
};
