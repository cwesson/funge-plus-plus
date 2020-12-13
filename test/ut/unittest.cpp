#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <iostream>
#include "Vector.h"
#include "VectorRange.h"

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


TEST(FungeTestGroup, VectorRangeTestPP)
{
	Funge::Vector a{1, 2};
	Funge::Vector b{3, 6};
	Funge::VectorRange range(a, b);
	CHECK(range.begin() == a);
	CHECK(range.end()   != b);
	CHECK(*range == a);
	CHECK(++range == Funge::Vector({2,2}));
	CHECK( *range == Funge::Vector({2,2}));
	CHECK(++range == Funge::Vector({3,2}));
	CHECK( *range == Funge::Vector({3,2}));
	CHECK(++range == Funge::Vector({1,3}));
	CHECK( *range == Funge::Vector({1,3}));
	CHECK(++range == Funge::Vector({2,3}));
	CHECK(++range == Funge::Vector({3,3}));
	CHECK(++range == Funge::Vector({1,4}));
	CHECK(++range == Funge::Vector({2,4}));
	CHECK(++range == Funge::Vector({3,4}));
	CHECK(++range == Funge::Vector({1,5}));
	CHECK(++range == Funge::Vector({2,5}));
	CHECK(++range == Funge::Vector({3,5}));
	CHECK(++range == Funge::Vector({1,6}));
	CHECK(++range == Funge::Vector({2,6}));
	CHECK(++range == Funge::Vector({3,6}));
	CHECK(++range == range.end());
}

TEST(FungeTestGroup, VectorRangeTestPM)
{
	Funge::Vector a{1, 6};
	Funge::Vector b{3, 2};
	Funge::VectorRange range(a, b);
	CHECK(range.begin() == a);
	CHECK(range.end()   != b);
	CHECK(*range == a);
	CHECK(++range == Funge::Vector({2,6}));
	CHECK( *range == Funge::Vector({2,6}));
	CHECK(++range == Funge::Vector({3,6}));
	CHECK( *range == Funge::Vector({3,6}));
	CHECK(++range == Funge::Vector({1,5}));
	CHECK(++range == Funge::Vector({2,5}));
	CHECK(++range == Funge::Vector({3,5}));
	CHECK(++range == Funge::Vector({1,4}));
	CHECK(++range == Funge::Vector({2,4}));
	CHECK(++range == Funge::Vector({3,4}));
	CHECK(++range == Funge::Vector({1,3}));
	CHECK(++range == Funge::Vector({2,3}));
	CHECK(++range == Funge::Vector({3,3}));
	CHECK(++range == Funge::Vector({1,2}));
	CHECK(++range == Funge::Vector({2,2}));
	CHECK(++range == Funge::Vector({3,2}));
	CHECK(++range == range.end());
}

TEST(FungeTestGroup, VectorRangeTestMP)
{
	Funge::Vector a{3, 2};
	Funge::Vector b{1, 6};
	Funge::VectorRange range(a, b);
	CHECK(range.begin() == a);
	CHECK(range.end()   != b);
	CHECK(*range == a);
	CHECK(++range == Funge::Vector({2,2}));
	CHECK( *range == Funge::Vector({2,2}));
	CHECK(++range == Funge::Vector({1,2}));
	CHECK( *range == Funge::Vector({1,2}));
	CHECK(++range == Funge::Vector({3,3}));
	CHECK(++range == Funge::Vector({2,3}));
	CHECK(++range == Funge::Vector({1,3}));
	CHECK(++range == Funge::Vector({3,4}));
	CHECK(++range == Funge::Vector({2,4}));
	CHECK(++range == Funge::Vector({1,4}));
	CHECK(++range == Funge::Vector({3,5}));
	CHECK(++range == Funge::Vector({2,5}));
	CHECK(++range == Funge::Vector({1,5}));
	CHECK(++range == Funge::Vector({3,6}));
	CHECK(++range == Funge::Vector({2,6}));
	CHECK(++range == Funge::Vector({1,6}));
	CHECK(++range == range.end());
}

int main(int argc, char* argv[]){
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
