#include <chrono>
#include <iostream>

int main() {
  // Get the current time as a time_point

  while (true) {
    auto now = std::chrono::system_clock::now();

    // Convert to microseconds since epoch
    auto duration = now.time_since_epoch();
    auto microseconds =
        std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    std::cout << microseconds << std::endl;
  }
  // Output the Unix timestamp in microseconds

  return 0;
}