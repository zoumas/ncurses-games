#include "Drawable.h"

Drawable::Drawable(int y, int x, chtype icon): y(y), x(x), icon(icon) {}
Drawable::~Drawable() {}

int Drawable::get_y() const 
{
  return y;
}

void Drawable::set_y(int y)
{
  this->y = y;
}

int Drawable::get_x() const 
{
  return x;
}

void Drawable::set_x(int x)
{
  this->x = x;
}

chtype Drawable::get_icon() const
{
  return icon;
}

void Drawable::set_icon(chtype icon)
{
  this->icon = icon;
}
