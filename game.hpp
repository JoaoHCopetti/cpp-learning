#include "coords.hpp"
#include "random.hpp"
#include <iostream>
#include <vector>

using namespace std;

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

enum Direction { INVALID, RIGHT, DOWN, LEFT, UP };

class Game {
public:
  bool isRunning = true;
  bool isAI = false;

private:
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

    this->tail.push_back(Coords{x - 1, y});
  }

  void render() {
    system("clear");

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

    // Handle user input movement
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

    Direction direction = this->getNextDirection();

    if (direction == INVALID) {
      throw "Impossible";
    }

    this->moveHead(direction);
  }

  Direction getNextDirection() {
    if (this->head.getX() > this->fruit.getX()) {
      return LEFT;
    }

    if ((this->head.getX() < this->fruit.getX())) {
      return RIGHT;
    }

    if (this->head.getY() > this->fruit.getY()) {
      return UP;
    }

    if (this->head.getY() < this->fruit.getY()) {
      return DOWN;
    }

    return INVALID;
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