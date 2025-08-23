#include "game.hpp"
#include "random.hpp"
#include <chrono>
#include <thread>

using namespace std;

int main() {
  Game game{40, 20};
  Coords coords;

  while (game.isRunning) {
    game.render();
    game.moveHeadAuto();
    this_thread::sleep_for(chrono::milliseconds(20));
  }

  return 0;
}