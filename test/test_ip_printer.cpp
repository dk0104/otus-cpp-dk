
#include "print_ip.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

using namespace ::testing;

class TestPrintIp : public Test {
public:
  TestPrintIp() = default;
  ~TestPrintIp() = default;

protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestPrintIp, TestPrintIpChar) {
  std::stringstream ss;
  std::string ip("192.168.1.142");
  HA4::print_ip(ip, ss);
  std::string result("192.168.1.142\n");
  ASSERT_EQ(ss.str(), result);
}

TEST_F(TestPrintIp, TestPrintIpBind) {
  std::stringstream ss;
  int in = -1;
  HA4::print_ip(in, ss);
  std::string result("255.255.255.255\n");
  ASSERT_EQ(ss.str(), result);
}

TEST_F(TestPrintIp, TestPrintIpDigit) {
  std::stringstream ss;
  int in = 2130706433;
  HA4::print_ip(in, ss);
  std::string result("127.0.0.1\n");
  ASSERT_EQ(ss.str(), result);
}

TEST_F(TestPrintIp, TestPrintIpString) {
  std::stringstream ss;
  std::string in = "Hello";
  HA4::print_ip(in, ss);
  std::string result("Hello\n");
  ASSERT_EQ(ss.str(), result);
}
