#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <iostream>
#include "Vector.h"

TEST_GROUP(FungeTestGroup)
{

};

TEST(FungeTestGroup, VectorTest)
{
	Funge::Vector a{1, 2};
	Funge::Vector b{1, 2};
	Funge::Vector c{2, 1};
	Funge::Vector d{2};
	CHECK(a == b);
	CHECK_FALSE(a == c);
	CHECK_FALSE(a < c);
	CHECK(c < a);
	CHECK_FALSE(a < b);
	CHECK_FALSE(c == d);
	CHECK(d < c);
	CHECK_FALSE(c < d);
}

int main(int argc, char* argv[]){
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
