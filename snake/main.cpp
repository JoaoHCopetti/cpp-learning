#include "game.hpp"
#include <chrono>
#include <thread>

using namespace std;

void sleep(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

int main() {
  Game game{40, 20};

  game.isAI = true;

  string name;
  while (game.isRunning) {
    game.render();
    game.handleMovement();
    getline(cin, name);
  }

  return 0;
}
