#include "ipfilter.h"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

using namespace ::testing;

class TestIpFilter : public ::testing::Test {
public:
  TestIpFilter(){};
  virtual ~TestIpFilter(){};

protected:
  void SetUp() {
    std::ifstream file("ip_filter.tsv");
    ipf = std::make_shared<IpFilter>(file);
  }

  void TearDown() { ipf.reset(); }
  std::shared_ptr<IpFilter> ipf;
};

TEST_F(TestIpFilter, Test_IpFilter_All_SortResult) {
  std::stringstream ss;
  ipf->print(ss);
  std::cerr << " Test_IpFilter_SortResult: " << ss.str() << std::endl;

  EXPECT_TRUE(ss.str().size() > 0);
}

TEST_F(TestIpFilter, Test_IpFilter_Kfirst_SortResult) {
  std::stringstream ss;
  std::string result =
      "1.231.69.33\n1.87.203.225\n1.70.44.170\n1.29.168.152\n1.1.234.8\n";
  ipf->print(ss, kfirst);
  std::cerr << " Test_IpFilter_SortResult: " << ss.str() << std::endl;

  EXPECT_TRUE(ss.str().size() > 0);
  EXPECT_EQ(ss.str(), result);
}

TEST_F(TestIpFilter, Test_IpFilter_K46_70_SortResult) {
  std::stringstream ss;
  ipf->print(ss, k46_70);
  std::cerr << " Test_IpFilter_SortResult: " << ss.str() << std::endl;
  std::string result =
      "46.70.225.39\n46.70.147.26\n46.70.113.73\n46.70.29.76\n";

  EXPECT_TRUE(ss.str().size() > 0);
  EXPECT_EQ(ss.str(), result);
}

TEST_F(TestIpFilter, Test_IpFilter_K46any_SortResult) {
  std::stringstream ss;
  ipf->print(ss, k46any);
  std::cerr << " Test_IpFilter_SortResult: " << ss.str() << std::endl;
  std::string result =
      "186.204.34.46\n186.46.222.194\n185.46.87.231\n185.46.86.132\n185.46."
      "86.131\n185.46.86.131\n185.46.86.22\n185.46.85.204\n185.46.85.78\n68.46."
      "218.208\n46.251.197.23\n46.223.254.56\n46.223.254.56\n46.182.19.219\n46."
      "161.63.66\n46.161.61.51\n46.161.60.92\n46.161.60.35\n46.161.58.202\n46."
      "161.56.241\n46.161.56.203\n46.161.56.174\n46.161.56.106\n46"
      ".161.56.106\n46.101.163.119\n46.101.127.145\n46.70.225.39\n46"
      ".70.147.26\n46.70.113.73\n46.70.29.76\n46.55.46.98\n46.49.43.85\n39"
      ".46.86.85\n5.189.203.46\n";
  EXPECT_TRUE(ss.str().size() > 0);
  EXPECT_EQ(ss.str(), result);
}
