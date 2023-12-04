# Maze Game written in C++ using ncurses

## Demo



https://github.com/zoumas/ncurses-games/assets/132769996/ff3ecdb1-aa55-4797-96cf-5bbcce233643



## Subject of the Work

This work was the final assignment for the Object Oriented Programming with C++ course in University.

## How to play

Clone the repository and navigate to the `maze` directory. Inside it run `make`.

`make` produce the executable binary with the name `maze`.

To play the game, you need to supply a `map` as a command line argument. Two maps can be found in the `maps` directory.

An example of how to run the game:
```bash
$ make && ./maze maps/medium_maze.txt 
```

## Goal of the Game

The goal is pretty simple. Two players are trapped inside a maze. A magic gem spawns. The first one to claim the magic gem gets to teleport out. 
The fun part is that the gem itself can teleport across the maze in random intervals.

## Navigation

The player's character is Lucas(L). 
The opponent is Babis(B).

Control your player with the arrow keys.
