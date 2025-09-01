#include <chrono>
#include <cstdlib>
#include <vector>

#ifndef SNAKE_GAME_RANDOM_H
#define SNAKE_GAME_RANDOM_H

namespace chrono = std::chrono;

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

  template <typename T> T randomElement(std::vector<T> arr) {
    return arr.at(this->numberBetween(0, arr.size() - 1));
  }

private:
  long int currentTimestamp() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    return chrono::duration_cast<chrono::microseconds>(duration).count();
  }
};

#endif
