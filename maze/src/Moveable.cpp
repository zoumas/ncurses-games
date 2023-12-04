#include "Moveable.h"

Moveable::Moveable(int y, int x, chtype icon, int max_y, int max_x)
  : Drawable(y, x, icon), max_y(max_y), max_x(max_x), prev_y(y), prev_x(x), moved_(false) {}

Moveable::~Moveable() {}

void Moveable::move_up() 
{ 
  moved_ = true;
  prev_y = y;
  --y;
}

void Moveable::move_down() 
{ 
  moved_ = true;
  prev_y = y;
  ++y;
}

void Moveable::move_left() 
{ 
  moved_ = true;
  prev_x = x;
  --x;
}

void Moveable::move_right() 
{ 
  moved_ = true;
  prev_x = x;
  ++x;
}

bool Moveable::moved()
{
  return moved_;
}

int Moveable::get_prev_y() const
{
  return prev_y;
}

int Moveable::get_prev_x() const
{
  return prev_x;
}
