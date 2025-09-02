#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std;

void sleep(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

int main() {
  Game game{40, 20};

  game.isAI = true;

  while (game.isRunning) {
    game.render();
    game.handleMovement();
    sleep(100);
  }

  return 0;
}
