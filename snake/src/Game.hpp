#pragma once
#include "Board.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Empty.hpp"
#include "Scoreboard.hpp"
#include "Time.hpp"

#include <cstdlib>
#include <ctime>

class Game {
private:
  bool game_over;
  Board board;
  Apple *apple;
  Snake snake;
  Scoreboard scoreboard;
  int score;
public:
  Game(int height, int width, int speed):
    board(height, width, speed) {
    int sb_row = board.get_start_row() + height;
    int sb_col = board.get_start_col();
    scoreboard = Scoreboard(width, sb_row, sb_col);
    construct(height, width);
  }

  ~Game() {
    delete apple;
  }

  /// runs the main game loop
  void run() {
    do {
      process_input();

      update_state();

      redraw();

    } while (!game_over);
  }

  void process_input() {
    chtype input = board.get_input();
    switch (input) {
      // quit
      case 'q': {
          game_over = true;
          return;
      } break;
      // pause
      case 'p': {
        board.set_timeout(-1);
        while (board.get_input() != 'p');
        board.set_timeout(board.get_speed());
      } break;
      case KEY_UP:
      case 'w':
      case 'k':
                snake.set_direction(UP);
            break;
      case KEY_DOWN:
      case 's':
      case 'j':
                snake.set_direction(DOWN);
            break;
      case KEY_LEFT:
      case 'a':
      case 'h':
                snake.set_direction(LEFT);
            break;
      case KEY_RIGHT:
      case 'd':
      case 'l':
                snake.set_direction(RIGHT);
            break;

      default:
            break;
    }
  }

  void update_state() {
    handle_next_piece(snake.next_head());
    if (apple == NULL) {
      create_apple();
    }
  }

  void redraw() {
    board.refresh();
    scoreboard.refresh();
  }

  bool is_over() {
    return game_over;
  }

  int get_score() {
    return score;
  }

private:
  void construct(int y, int x) {
      game_over = false;
      srand(time(NULL));
      apple = NULL;
      score = 0;
      scoreboard.initialize(score);

      snake.set_direction(DOWN);
      handle_next_piece(SnakePiece(1, 1));

      handle_next_piece(snake.next_head());
      handle_next_piece(snake.next_head());

      snake.set_direction(RIGHT);
      handle_next_piece(snake.next_head());

      if (apple == NULL) {
        create_apple();
      }
    }


    void handle_next_piece(SnakePiece next) {
      if (apple != NULL) {
        switch (board.get_char_at(next.get_y(), next.get_x())) {
          case 'A': {
            // beep();
            eat_apple();
          } break;
          case ' ': {
            int empty_row = snake.tail().get_y();
            int empty_col = snake.tail().get_x();
            board.add(Empty(empty_row, empty_col));
            snake.remove_piece();
          } break;
          default:
            game_over = true;
        }
      }

        board.add(next);
        snake.add_piece(next);
    }

    void create_apple() {
      int empty_y, empty_x;
      board.get_empty_coordinates(empty_y, empty_x);
      apple = new Apple(empty_y, empty_x);
      board.add(*apple);
    }

    void eat_apple() {
      delete apple;
      apple = NULL;
      ++score;
      scoreboard.update_score(score);
    }
};
