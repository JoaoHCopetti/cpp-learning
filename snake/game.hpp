#include "coords.hpp"
#include "helpers.hpp"
#include "random.hpp"
#include <iostream>
#include <vector>

using namespace std;

#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#else
#define CLEAR_CONSOLE system("clear")
#endif

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

enum Direction { RIGHT, DOWN, LEFT, UP };
enum GameError { NO_VALID_DIRECTIONS_LEFT };

class Game {
public:
  bool isRunning = true;
  bool isAI = false;

public:
  Random random;

  string output;
  int width, height;
  int points = 0;
  Direction lastDirection;

  Coords head;
  Coords fruit;
  vector<Coords> tail;

public:
  Game(int width, int height) {
    int x = width / 2;
    int y = height / 2;

    this->width = width;
    this->height = height;

    this->head = Coords{x, y};
    this->repositionFruit();
    this->lastDirection = RIGHT;

    this->tail.push_back(Coords{x - 1, y});
  }

  void render() {
    CLEAR_CONSOLE;

    this->output = "POINTS: " + to_string(this->points) + "\n\n";

    for (int y = 0; y < this->height; y++) {
      for (int x = 0; x < this->width; x++) {
        this->output += this->getCharForCoord(Coords{x, y});
      }

      this->output += '\n';
    }

    cout << this->output;
  }

  void handleMovement() {
    if (this->isAI) {
      this->moveHeadAuto();
      return;
    }

    cout << "You should implement user input movement" << endl;
    this->isRunning = false;
  }

private:
  void repositionFruit() {
    int randomCoordX = this->random.numberBetween(1, this->width - 2);
    int randomCoordY = this->random.numberBetween(1, this->height - 2);

    this->fruit.setCoords(Coords{randomCoordX, randomCoordY});
  }

  char getCharForCoord(Coords coords) {
    if (this->isCoordsWall(coords)) {
      return '#';
    }

    if (this->head.matchCoords(coords)) {
      return 'O';
    }

    if (this->fruit.matchCoords(coords)) {
      return 'x';
    }

    if (this->isCoordsTail(coords)) {
      return '*';
    }

    return ' ';
  }

  bool isCoordsWall(Coords coords) {
    int x = coords.getX();
    int y = coords.getY();

    return (x == 0 || x == this->width - 1) ||
           (y == 0 || y == this->height - 1);
  }

  bool isCoordsTail(Coords coords) {
    for (Coords tail : this->tail) {
      if (tail.matchCoords(coords)) {
        return true;
      }
    }

    return false;
  }

  void moveHeadAuto() {
    if (this->head.matchCoords(this->fruit)) {
      this->onPointScore();
      this->moveHeadAuto();
      return;
    }

    Direction nextDirection = this->getNextDirection();

    if (this->isDirectionOpposite(nextDirection, this->lastDirection)) {
      Direction invalidDirections[] = {nextDirection, this->lastDirection};

      nextDirection = this->getRandomValidDirection(invalidDirections);
    }

    this->moveHead(nextDirection);
  }

  template <size_t N>
  Direction getRandomValidDirection(Direction (&invalidDirections)[N]) {
    vector<Direction> directions = {RIGHT, DOWN, LEFT, UP};

    for (Direction dir : invalidDirections) {
      removeVectorEl(directions, dir);
    }

    if (directions.empty()) {
      throw NO_VALID_DIRECTIONS_LEFT;
    }

    return this->random.randomElement(directions);
  }

  Direction getNextDirection() {
    Direction nextDirection = this->lastDirection;

    if (this->head.getX() > this->fruit.getX()) {
      nextDirection = LEFT;
    } else if ((this->head.getX() < this->fruit.getX())) {
      nextDirection = RIGHT;
    } else if (this->head.getY() > this->fruit.getY()) {
      nextDirection = UP;
    } else if (this->head.getY() < this->fruit.getY()) {
      nextDirection = DOWN;
    }

    return nextDirection;
  }

  void moveHead(Direction dir) {
    this->handleTail();

    if (dir == RIGHT) {
      this->head.incrementX();
    }

    if (dir == DOWN) {
      this->head.incrementY();
    }

    if (dir == LEFT) {
      this->head.decrementX();
    }

    if (dir == UP) {
      this->head.decrementY();
    }

    this->handleBorderHit();
    this->lastDirection = dir;
  }

  bool isDirectionOpposite(Direction dir1, Direction dir2) {
    if ((dir1 == RIGHT && dir2 == LEFT) || (dir1 == LEFT && dir2 == RIGHT)) {
      return true;
    }

    if ((dir1 == UP && dir2 == DOWN) || (dir1 == DOWN && dir2 == UP)) {
      return true;
    }

    return false;
  }

  void handleTail() {
    for (int i = this->tail.size() - 1; i >= 0; i--) {
      if (i == 0) {
        this->tail.at(i).setCoords(this->head);
        continue;
      }

      Coords prevTail = this->tail.at(i - 1);
      this->tail.at(i).setCoords(prevTail);
    }
  }

  void handleBorderHit() {
    if (this->head.getX() < 1) {
      this->head.setX(this->width - 2);
    }

    if (this->head.getY() < 1) {
      this->head.setY(this->height - 2);
    }

    if (this->head.getX() > this->width - 2) {
      this->head.setX(1);
    }

    if (this->head.getY() > this->height - 2) {
      this->head.setY(1);
    }
  }

  void onPointScore() {
    this->points++;
    this->repositionFruit();

    this->tail.push_back(Coords{});

    this->render();
  }

  bool isCoordsSnake(Coords coords) {
    if (this->head.matchCoords(coords)) {
      return true;
    }

    return this->isCoordsTail(coords);
  }
};

#endif
