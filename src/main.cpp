#include "lib/hpp/customAllocator.h"
#include "lib/hpp/ipfilter.h"
#include "lib/hpp/lib.h"
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

template <typename T> constexpr T factorial(T n) {
  return (n == 0) ? 1 : n * factorial(n - 1);
}

int main(int, char **) {
  std::cout << "Version: " << version() << std::endl;
  std::ifstream file("ip_filter.tsv");

  /// Ip Filter
  IpFilter ipf(file);
  std::cout << ipf;

  /// Custom Allocator
  CustomAllocator<int> ca(10);
  std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>>
      map;
  for (int i = 0; i < 10; i++) {
    map[i] = factorial(i);
  }

  for (auto [key, value] : map) {
    std::cout << key << " " << value << std::endl;
  }

  return version();
}
