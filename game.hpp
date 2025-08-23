#include "coords.hpp"
#include "random.hpp"
#include <iostream>
#include <vector>

using namespace std;

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

enum Direction { RIGHT, DOWN, LEFT, UP };

class Game {
public:
  bool isRunning = true;

private:
  string output;
  int width, height;
  int points = 0;

  Random random;
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
        this->output += this->getCharForCoord(x, y);
      }

      this->output += '\n';
    }

    cout << this->output;
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
  }

  void moveHeadAuto() {
    if (this->head.getX() > this->fruit.getX()) {
      this->moveHead(LEFT);
      return;
    }

    if ((this->head.getX() < this->fruit.getX())) {
      this->moveHead(RIGHT);
      return;
    }

    if (this->head.getY() > this->fruit.getY()) {
      this->moveHead(UP);
      return;
    }

    if (this->head.getY() < this->fruit.getY()) {
      this->moveHead(DOWN);
      return;
    }

    this->onPointScore();
    this->moveHeadAuto();
  }

private:
  void onPointScore() {
    this->points++;
    this->repositionFruit();

    this->tail.push_back(Coords{});
  }

  void handleTail() {
    for (int i = this->tail.size() - 1; i >= 0; i--) {
      if (i == 0) {
        this->tail.at(i).setCoords(this->head.getX(), this->head.getY());
        continue;
      }

      Coords prevTail = this->tail.at(i - 1);
      int prevTailCoordX = prevTail.getX();
      int prevTailCoordY = prevTail.getY();

      this->tail.at(i).setCoords(prevTailCoordX, prevTailCoordY);
      continue;
    }
  }

  void repositionFruit() {
    int randomCoordX = this->random.numberBetween(1, this->width - 2);
    int randomCoordY = this->random.numberBetween(1, this->height - 2);

    // if (this->coordsMatchSnake(randomCoordX, randomCoordY)) {
    //   this->repositionFruit();
    //   return;
    // }

    this->fruit.setCoords(randomCoordX, randomCoordY);
  }

  char getCharForCoord(int x, int y) {
    if (this->isCoordWall(x, y)) {
      return '#';
    }

    if (this->head.coordsMatch(x, y)) {
      return 'O';
    }

    if (this->fruit.coordsMatch(x, y)) {
      return '*';
    }

    if (this->coordsMatchTail(x, y)) {
      return '*';
    }

    return ' ';
  }

  bool isCoordWall(int x, int y) {
    return (y == 0 || y == this->height - 1) ||
           (x == 0 || x == this->width - 1);
  }

  bool coordsMatchTail(int x, int y) {
    for (Coords tail : this->tail) {
      if (tail.coordsMatch(x, y)) {
        return true;
      }
    }

    return false;
  }

  bool coordsMatchSnake(int x, int y) {
    if (this->head.coordsMatch(x, y)) {
      return true;
    }

    return this->coordsMatchTail(x, y);
  }

  bool handleBorderHit() {
    if (this->head.getX() < 1) {
      this->head.setX(this->width - 2);
      return true;
    }

    if (this->head.getY() < 1) {
      this->head.setY(this->height - 2);
      return true;
    }

    if (this->head.getX() > this->width - 2) {
      this->head.setX(1);
      return true;
    }

    if (this->head.getY() > this->height - 2) {
      this->head.setY(1);
      return true;
    }

    return false;
  }
};

#endif