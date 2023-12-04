#pragma once

#include "Board.h"
#include "Jewel.h"
#include "Moveable.h"
#include "Position.h"

#include <memory>
#include <string>

#include <thread>
#include <mutex>
#include <condition_variable>

/// The Game Class [Controller]
class Game {
public:
  Game(std::shared_ptr<Board> board);
  ~Game();

  std::string run();

private:
  void process_input();
  void update_state();
  void redraw();
  bool is_game_over();

  bool handle_player(chtype input);
  void handle_npc();

  bool is_valid_position(Position p);
  bool is_passable_cell(Position p);
  std::vector<Position> find_sortest_path(Position start);
  Position get_next_move(Position start);

  void teleport_jewel();
  void display_game_over_screen();
private:
  std::shared_ptr<Board> board;
  std::unique_ptr<Jewel> jewel;
  std::unique_ptr<Moveable> player;
  std::unique_ptr<Moveable> npc;

  bool game_over;
  bool player_won;

  std::thread jewel_teleport_thread;
  std::mutex jewel_lock;
};
