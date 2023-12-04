#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

#include <queue>

#define SNAKE_ICON '#';

class SnakePiece: public Drawable {
public:
  SnakePiece() {
    this->y = this->x = 0;
    this->icon = SNAKE_ICON;
  }

  SnakePiece(int y, int x) {
    this->y = y;
    this->x = x;
    this->icon = SNAKE_ICON;
  }
};

enum Direction {
  UP = -1,
  DOWN = 1,
  LEFT = -2,
  RIGHT = 2
};

class Snake {
private:
  std::queue<SnakePiece> prev_pieces;
  Direction direction;
public:
  Snake() {
    direction = DOWN;
  }

  void add_piece(SnakePiece piece) {
    prev_pieces.push(piece);
  }

  void remove_piece() {
    prev_pieces.pop();
  }

  SnakePiece tail() {
    return prev_pieces.front();
  }

  SnakePiece head() {
    return prev_pieces.back();
  }

  Direction get_direction() {
    return direction;
  }

void set_direction(Direction direction) {
  if (this->direction + direction != 0) {
    this->direction = direction;
  }
}

  SnakePiece next_head() {
    int row = head().get_y();
    int col = head().get_x();

    switch (direction) {
    case DOWN:
      ++row;
      break;
    case UP:
      --row;
      break;
    case LEFT:
      --col;
      break;
    case RIGHT:
      ++col;
      break;
    }

    return SnakePiece(row, col);
  }
};
