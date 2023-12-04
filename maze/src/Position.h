#pragma once

struct Position {
  int x;
  int y;

  Position();
  Position(int x, int y);
  virtual ~Position();
  bool operator==(Position other);
  bool operator!=(Position other);
};
