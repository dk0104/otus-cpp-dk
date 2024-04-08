
#include "print_ip.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace ::testing;

class TestPrintIp : public Test {
public:
  TestPrintIp() = default;
  ~TestPrintIp() = default;

protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestPrintIp, TestPrintIpChar) {}
