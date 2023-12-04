#include "src/Game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

std::vector<std::string> load_maze_from_file(const std::string& path);
void initialize_ncurses();
void terminate_ncurses();

/// Main handles parsing the command line arguments,
/// reading the map and setting up the necessary configuration
/// for the game to run.
int main(int argc, char **argv)
{
  if (argc == 1) {
    std::cerr << "Expected maze file" << std::endl;
    exit(1);
  }
  
  auto maze = 
    std::make_shared<std::vector<std::string>>(load_maze_from_file(std::string(argv[1])));

  std::string winner;

  initialize_ncurses();
  {
    auto board = std::make_shared<Board>(maze);
    auto game = std::make_unique<Game>(board);
    winner = game->run();
  }
  terminate_ncurses();


  std::cout << winner << " won!" << std::endl;
  return 0;
}

std::vector<std::string> load_maze_from_file(const std::string& path)
{
  std::ifstream file(path);
  std::vector<std::string> maze;

  if (!file.is_open()) {
    std::cerr << "Failed to open file `" << path << "` for reading" << std::endl;
    exit(1);
  }

  std::string line;
  while (std::getline(file, line)) {
    maze.push_back(line);
  }
  file.close();

  return maze;
}

void initialize_ncurses()
{
  // Initialize the terminal in curses mode.
  initscr();

  // Make the cursor invisible.
  curs_set(0);

  // Disable line buffering while still generating signals.
  cbreak();

  // Switch off echoing
  noecho();

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
}

void terminate_ncurses()
{
  // End curses-mode. Free allocated memory.
  endwin();
}
