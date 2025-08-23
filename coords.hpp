#ifndef SNAKE_GAME_COORDS_H
#define SNAKE_GAME_COORDS_H

class Game;

class Coords {
private:
  int x, y;

public:
  Coords(int x = 0, int y = 0) { this->setCoords(x, y); }

  int getX() { return this->x; }
  int getY() { return this->y; }

  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }

  void incrementX() { this->x++; }
  void decrementX() { this->x--; }
  void incrementY() { this->y++; }
  void decrementY() { this->y--; }

  void setCoords(int x, int y) {
    this->x = x;
    this->y = y;
  }

  bool matchCoords(int x, int y) { return this->x == x && this->y == y; }
};

#endif