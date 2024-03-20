#pragma once
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>

struct IpAddrType {
  explicit IpAddrType(const std::string &ip);

  // Op section
  auto operator<=>(const IpAddrType &rhs) const = default;
  operator std::string() const;
  friend std::ostream &operator<<(std::ostream &os, const IpAddrType &ip);

  // Method section
  static bool isValidIP(const std::string &ip);

  // Data section
  uint16_t firstOctet;
  uint16_t secondOctet;
  uint16_t thirdOctet;
  uint16_t fourthOctet;
};

enum filterType { kAny, kfirst, k46_70, k46any };

class IpFilter {
public:
  IpFilter(std::ifstream &in);
  virtual ~IpFilter();
  void print(std::stringstream &ss, filterType type = kAny) const;
  friend std::ostream &operator<<(std::ostream &os, const IpFilter &ipf);

protected:
  std::vector<IpAddrType> ip_pool;
};
