#include "lib/hpp/ipfilter.h"
#include "lib/hpp/lib.h"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int, char **) {
  std::cout << "Version: " << version() << std::endl;
  std::ifstream file("ip_filter.tsv");

  IpFilter ipf(file);
  std::cout << ipf;

  return version();
}
