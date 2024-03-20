#include "../hpp/ipfilter.h"
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

IpAddrType::IpAddrType(const std::string &ip) {
  if (!isValidIP(ip)) {
    throw std::invalid_argument("Invalid IP address");
  }
  stringstream ss(ip);
  char dot;
  ss >> firstOctet >> dot >> secondOctet >> dot >> thirdOctet >> dot >>
      fourthOctet;
}

IpAddrType::operator std::string() const {
  stringstream ss;
  ss << firstOctet << "." << secondOctet << "." << thirdOctet << "."
     << fourthOctet;
  return ss.str();
}

std::ostream &operator<<(std::ostream &os, const IpAddrType &ip) {
  os << static_cast<std::string>(ip);
  return os;
}

IpFilter::IpFilter(std::ifstream &in) {

  auto split = [](const std::string &str, char d) {
    std::vector<std::string> r;
    r.reserve(42);

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
      r.push_back(str.substr(start, stop - start));

      start = stop + 1;
      stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
  };

  for (std::string line; std::getline(in, line);) {
    std::vector<std::string> v = split(line, '\t');
    ip_pool.push_back(IpAddrType(v.at(0)));
  }

  sort(ip_pool.begin(), ip_pool.end(), std::greater<IpAddrType>());
}

IpFilter::~IpFilter() { ip_pool.clear(); }

std::ostream &operator<<(std::ostream &os, const IpFilter &ipf) {
  std::stringstream ss;
  ipf.print(ss, kAny);
  ipf.print(ss, kfirst);
  ipf.print(ss, k46_70);
  ipf.print(ss, k46any);
  os << ss.str();
  return os;
}

void IpFilter::print(stringstream &ss, filterType type) const {
  for (const auto &ip : ip_pool) {
    if (type == kAny) {
      ss << ip << std::endl;
    } else if (type == kfirst) {
      if (ip.firstOctet == 1) {
        ss << ip << std::endl;
      }
    } else if (type == k46_70) {
      if (ip.firstOctet == 46 && ip.secondOctet == 70) {
        ss << ip << std::endl;
      }
    } else if (type == k46any) {
      if (ip.firstOctet == 46 || ip.secondOctet == 46 || ip.thirdOctet == 46 ||
          ip.fourthOctet == 46) {
        ss << ip << std::endl;
      }
    }
  }
}

bool IpAddrType::isValidIP(const std::string &ip) {
  std::vector<std::string> ipParts;
  std::string ipPart;
  std::stringstream ss(ip);
  while (std::getline(ss, ipPart, '.')) {
    ipParts.push_back(ipPart);
  }
  if (ipParts.size() != 4) {
    return false;
  }
  for (const auto &ipPart : ipParts) {
    if (ipPart.empty() || ipPart.size() > 3) {
      return false;
    }
    for (const auto &c : ipPart) {
      if (!std::isdigit(c)) {
        return false;
      }
    }
    if (std::stoi(ipPart) > 255) {
      return false;
    }
  }
  return true;
}
