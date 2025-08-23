#include <chrono>
#include <iostream>

#ifndef SNAKE_GAME_RANDOM_H
#define SNAKE_GAME_RANDOM_H

class Random {
public:
  int numberBetween(int min, int max) {
    srand(this->currentTimestamp());

    return min + (rand() % (max - min + 1));
  }

  bool chanceOfTrue(int chance) {
    srand(this->currentTimestamp());

    int randomValue = rand() % 101;

    return randomValue < chance;
  }

private:
  long int currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    return std::chrono::duration_cast<std::chrono::microseconds>(duration)
        .count();
  }
};

#endif