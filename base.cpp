#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

enum Direction { UP, RIGHT, DOWN, LEFT };

class Random {
public:
  int numberBetween(int min, int max) {
    srand(this->currentTimestamp());

    return min + (rand() % (max - min + 1));
  }

private:
  long int currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    return chrono::duration_cast<chrono::microseconds>(duration).count();
  }
};

class Game {
private:
  int width, height;
  int coordX, coordY;

public:
  Game(int width, int height) {
    this->width = width;
    this->height = height;

    this->coordX = this->width / 2;
    this->coordY = this->height / 2;
  }

  void render() {
    system("clear");

    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        if (i == 0 || i == this->height - 1) {
          cout << "@";
        } else if (j == 0) {
          cout << "@";
        } else if (j == this->width - 1) {
          cout << "@";
        } else if (i == this->coordY && j == this->coordX) {
          cout << "O";
        } else {
          cout << " ";
        }
      }

      cout << endl;
    }
  }

  void moveHead(Direction dir) {
    if (dir == UP) {
      this->setCoords(this->coordX, this->coordY - 1);
    }

    if (dir == RIGHT) {
      this->setCoords(this->coordX + 1, this->coordY);
    }

    if (dir == DOWN) {
      this->setCoords(this->coordX, this->coordY + 1);
    }

    if (dir == LEFT) {
      this->setCoords(this->coordX - 1, this->coordY);
    }
  }

  void setCoords(int x, int y) {
    if (this->handleBorderHit(x, y)) {
      return;
    }

    this->coordX = x;
    this->coordY = y;
  }

  bool handleBorderHit(int x, int y) {
    const int BORDER_OFFSET = 2;

    if (x < BORDER_OFFSET) {
      this->coordX = this->width - 1;
      return true;
    }

    if (x > this->width - BORDER_OFFSET) {
      this->coordX = 1;
      return true;
    }

    if (y < BORDER_OFFSET) {
      this->coordY = this->height - 1;
      return true;
    }

    if (y > this->height - BORDER_OFFSET) {
      this->coordY = 1;
      return true;
    }

    return false;
  }
};

int main() {
  Game game{20, 20};
  Random random;

  while (true) {
    game.render();
    game.moveHead(RIGHT);
    this_thread::sleep_for(chrono::milliseconds(300));
  }

  return 0;
}