#include "Game.h"
#include "Empty.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <unistd.h>


Game::Game(std::shared_ptr<Board> board) :
  board(board), game_over(false), player_won(false) 
{
  srand(time(0));

  keypad(board->get_window(), true);
  // nodelay(board->get_window(), true);

  int y, x;
  board->get_empty_coordinates(y, x);
  jewel = std::make_unique<Jewel>(y, x);
  board->add(*jewel);

  board->get_empty_coordinates(y, x);
  player = std::make_unique<Moveable>(y, x, 'L' | COLOR_PAIR(1), board->get_height(), board->get_width());
  board->add(*player);

  board->get_empty_coordinates(y, x);
  npc = std::make_unique<Moveable>(y, x, 'B' | COLOR_PAIR(2), board->get_height(), board->get_width());
  board->add(*npc);

  jewel_teleport_thread = std::thread(&Game::teleport_jewel, this);
}

Game::~Game() 
{
  if (jewel_teleport_thread.joinable()) {
    jewel_teleport_thread.join();
  }
}

std::string Game::run()
{
  for (;;) {
    process_input();
    update_state();
    redraw();
    std::lock_guard<std::mutex> lock(jewel_lock);
    if (game_over) {
      break;
    }
  }

  board->clear();
  
  if (jewel_teleport_thread.joinable()) {
    jewel_teleport_thread.join();
  }

  if (player_won) {
    return std::string("Lucas");
  } 
  return std::string("Babis");
}

void Game::process_input()
{
    chtype input(board->get_input());
    if (input != ERR) {
      // ESCAPE
      if (input == 27) {
        std::lock_guard<std::mutex> lock(jewel_lock);
        jewel->set_icon(' ');
        game_over = true;
      }

      handle_player(input);
      if (player->moved()) {
        if (is_game_over()) {
          return;
        }
        handle_npc();
      }
    }
}

bool Game::handle_player(chtype input)
{
  chtype board_char;
  int y, x;

  switch (input) {
  case ' ':
    return true;
    break;
  case KEY_UP:
    y = player->get_y() - 1;
    if (y < 1) {
      return false;
    }
    board_char = board->get_char_at(y, player->get_x());
    if (board_char == ' ' || board_char == jewel->get_icon()) {
      board->add(Empty(player->get_y(), player->get_x()));
      player->move_up();
      return true;
    } else {
      return false;
    }
    break;
  case KEY_DOWN:
    y = player->get_y() + 1;
    if (y == board->get_height()) {
      return false;
    }
    board_char = board->get_char_at(y, player->get_x());
    if (board_char == ' ' || board_char == jewel->get_icon()) {
      board->add(Empty(player->get_y(), player->get_x()));
      player->move_down();
      return true;
    } else {
      return false;
    }
    break;
  case KEY_LEFT:
    x = player->get_x() - 1;
    if (x < 1) {
      return false;
    }
    board_char = board->get_char_at(player->get_y(), x);
    if (board_char == ' ' || board_char == jewel->get_icon()) {
      board->add(Empty(player->get_y(), player->get_x()));
      player->move_left();
      return true;
    } else {
      return false;
    }
    break;
  case KEY_RIGHT:
    x = player->get_x() + 1;
    if (x == board->get_width()) {
      return false;
    }
    board_char = board->get_char_at(player->get_y(), x);
    if (board_char == ' ' || board_char == jewel->get_icon()) {
      board->add(Empty(player->get_y(), player->get_x()));
      player->move_right();
      return true;
    } else {
      return false;
    }
    break;
  default:
    return false;
  }
}

void Game::update_state()
{
  if (is_game_over()) {
    board->add(*jewel);
    return;
  }

  if (player->moved()) {
    board->add(*player);
    board->add(*npc);
  }
}

void Game::redraw()
{
  board->refresh();
}

void Game::handle_npc()
{
  int x = npc->get_x();
  int y = npc->get_y();
  Position next = get_next_move(Position(x, y));

  board->add(Empty(y, x));
  npc->set_y(next.y);
  npc->set_x(next.x);
}

bool Game::is_game_over()
{
  if (jewel->get_y() == player->get_y() && jewel->get_x() == player->get_x()) {
    {
      std::lock_guard<std::mutex> lock(jewel_lock);
      game_over = true;
      jewel->set_icon(' ');
    }
    player->set_icon(' ');
    player_won = true;
    return true;
  } 

  if (jewel->get_y() == npc->get_y() && jewel->get_x() == npc->get_x()) {
    {
      std::lock_guard<std::mutex> lock(jewel_lock);
      game_over = true;
      jewel->set_icon(' ');
    }
    npc->set_icon(' ');
    return true;
  }

  return false;
}

// Check if a given position is within maze bounds
bool Game::is_valid_position(Position p)
{
  return (p.x >= 1 && p.x < board->get_width() && p.y >= 1 && p.y < board->get_height());
}

bool Game::is_passable_cell(Position p)
{
  chtype ch = board->get_char_at(p.y, p.x);
  /* return (ch == ' ' || ch == jewel->get_icon() || 
          ch == player->get_icon() || ch == npc->get_icon());
  */
  return (ch == ' ' || ch == jewel->get_icon());
}

std::vector<Position> Game::find_sortest_path(Position start)
{
  int width = board->get_width();
  int height = board->get_height();

  std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
  std::vector<std::vector<Position>> parent(height, std::vector<Position>(width));

  std::queue<Position> q;
  q.push(start);
  visited[start.y][start.x] = true;

  const std::vector<Position> directions = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
  };

  while (!q.empty()) {
    Position current = q.front();
    q.pop();

    if (current.x == jewel->get_x() && current.y == jewel->get_y()) {
      break;
    }

    for (const auto& direction : directions) {
      Position next = {
        current.x + direction.x,
        current.y + direction.y,
      };

      if (is_valid_position(next) && !visited[next.y][next.x] && is_passable_cell(next)) {
        q.push(next);
        visited[next.y][next.x] = true;
        parent[next.y][next.x] = current;
      }
    }
  }

  std::vector<Position> path;
  Position current(jewel->get_x(), jewel->get_y());
  while (!(current.x == start.x && current.y == start.y)) {
    path.push_back(current);
    current = parent[current.y][current.x];
  }
  path.push_back(start);

  std::reverse(path.begin(), path.end());

  return path;

}

Position Game::get_next_move(Position start)
{
  std::vector<Position> path = find_sortest_path(start);

  if (path.size() > 1) {
    return path[1];
    /*
    if (path[1].x != player->get_x() && path[1].y != player->get_y()) {
      return path[1];
    }
    */
  } 

  return start;
}

void Game::teleport_jewel()
{
  int interval;
  int y,x;

  for (;;) {
    // todo!(): replace hardcoded values with optional/conf values
    interval = std::rand() % 2 + 1;
    std::this_thread::sleep_for(std::chrono::seconds(interval));

    // Teleport the Jewel
    board->get_empty_coordinates(y, x);
    board->add(Empty(jewel->get_y(), jewel->get_x()));
    jewel->set_y(y);
    jewel->set_x(x);
    std::unique_lock<std::mutex> lk(jewel_lock);
    if (game_over) {
      break;
    }
    board->add(*jewel);
  }
}

void Game::display_game_over_screen()
{
  board->clear();

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  std::string msg;
  if (player_won) {
    msg = "You Won!";
  } else {
    msg = "You Lost.";
  }

  int start_col = (max_x - msg.length()) / 2;
  mvprintw(max_y/2, start_col, msg.c_str());

  refresh();
  getch();
}
