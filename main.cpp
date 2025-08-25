#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std;

int main() {
  Game game{40, 20};

  game.isAI = true;

  while (game.isRunning) {
    game.render();
    game.handleMovement();
    this_thread::sleep_for(chrono::milliseconds(100));
  }

  return 0;
}