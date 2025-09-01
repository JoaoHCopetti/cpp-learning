#ifndef SNAKE_GAME_COORDS_H
#define SNAKE_GAME_COORDS_H

class Game;

class Coords {
private:
  int x, y;

public:
  Coords(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }

  int getX() { return this->x; }
  int getY() { return this->y; }

  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }

  void incrementX() { this->x++; }
  void decrementX() { this->x--; }
  void incrementY() { this->y++; }
  void decrementY() { this->y--; }

  void setCoords(Coords coords) {
    this->x = coords.getX();
    this->y = coords.getY();
  }

  bool matchCoords(Coords coords) {
    return this->x == coords.getX() && this->y == coords.getY();
  }
};

#endif
