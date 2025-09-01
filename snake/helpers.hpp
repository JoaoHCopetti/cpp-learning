#include <algorithm>
#include <vector>

#ifndef SNAKE_HELPERS_H
#define SNAKE_HELPERS_H

template <typename T> void removeVectorEl(std::vector<T> &arr, T value) {
  auto it = std::find(arr.begin(), arr.end(), value);

  if (it != arr.end()) {
    int index = std::distance(arr.begin(), it);

    arr.erase(arr.begin() + index);
  }
}

#endif
