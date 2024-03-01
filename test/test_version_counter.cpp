#include <gtest/gtest.h>
#include "lib.h"
using namespace ::testing;

class TestVersionCounter : public ::testing::Test {
public:
	TestVersionCounter(){};
	virtual ~TestVersionCounter(){};
protected:
	void SetUp(){};
	void TearDown(){};

};

TEST_F(TestVersionCounter,Test_VersionCounter_GreenBuid_MoreThenOnce){
	EXPECT_TRUE(version() > 0 );
}

