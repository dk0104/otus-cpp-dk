#include "lib/hpp/print_ip.h"
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template <typename T> constexpr T factorial(T n) {
  return (n == 0) ? 1 : n * factorial(n - 1);
}

int main(int, char **) {
  std::cout << "print ip  - 1" << std::endl;
  HA4::print_ip(-1);

  std::cout << "print ip int16(0) - 0" << std::endl;
  HA4::print_ip(int16_t(0));

  std::cout << "print ip  - 2130706433" << std::endl;
  HA4::print_ip(2130706433);

  std::cout << "print_ip( int64_t{8875824491850138409}" << std::endl;
  HA4::print_ip(int64_t{8875824491850138409});

  std::cout << "print_ip( std::string{“Hello, World!”} )" << std::endl;
  std::string str{"Hello, World!"};
  HA4::print_ip(str);

  std::cout << "print_ip( std::vector<int>{100, 200, 300, 400}" << std::endl;
  HA4::print_ip(std::vector<int>{100, 200, 300, 400});

  std::cout << "print_ip(std::list<shot>{400, 300, 200, 100}" << std::endl;
  HA4::print_ip(std::list<short>{400, 300, 200, 100});

  std::cout << "print_ip(std::make_tuple(123, 456, 789, 0))" << std::endl;
  HA4::print_ip(std::make_tuple(123, 456, 789, 0));

  return 0;
}
