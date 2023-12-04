#include "Position.h"

Position::Position(): x(-1), y(-1) {}
Position::Position(int x, int y): x(x), y(y) {}
Position::~Position() {}

bool Position::operator==(Position other)
{
  return (x == other.x && y == other.y);
}

bool Position::operator!=(Position other)
{
  return !(x == other.x && y == other.y);
}

