#include "CppUTest/TestHarness.h"
#include "StackStack.h"

TEST_GROUP(StackStackTestGroup)
{

};

TEST(StackStackTestGroup, StackStackTest)
{
	Funge::StackStack stack;
	CHECK_EQUAL(1, stack.size());
	CHECK_EQUAL(0, stack.top().size());
	// 34 12
	stack.top().push(12);
	stack.top().push(34);
	CHECK_EQUAL(1, stack.size());
	CHECK_EQUAL(2, stack.top().size());
	// [empty]
	// 34 12
	stack.push();
	CHECK_EQUAL(2, stack.size());
	CHECK_EQUAL(0, stack.top().size());
	CHECK_EQUAL(34, stack.second().peek());
	// 90 78 56
	// 34 12
	stack.top().push(56);
	stack.top().push(78);
	stack.top().push(90);
	CHECK_EQUAL(2, stack.size());
	CHECK_EQUAL(3, stack.top().size());
	CHECK_EQUAL(90, stack.top().peek());
	CHECK_EQUAL(34, stack.second().peek());
	// [empty]
	// 90 78 56
	// 34 12
	stack.push();
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(0, stack.top().size());
	CHECK_EQUAL(34, stack.at(2).peek());
	CHECK_EQUAL(90, stack.at(1).peek());
	// 76 98
	// 90 78 56
	// 34 12
	stack.top().push(98);
	stack.top().push(76);
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(2, stack.top().size());
	CHECK_EQUAL(76, stack.top().peek());
	stack.insert(2);
	// 76 98
	// 90 78 56
	// [empty]
	// 34 12
	CHECK_EQUAL(4, stack.size());
	CHECK_EQUAL(0, stack.at(2).size());
	CHECK_EQUAL(76, stack.top().peek());
	CHECK_EQUAL(90, stack.second().peek());
	CHECK_EQUAL(0, stack.at(2).peek());
	// 90 78 56
	// [empty]
	// 34 12
	stack.pop();
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(34, stack.at(2).peek());
	CHECK_EQUAL(0, stack.second().peek());
	CHECK_EQUAL(90, stack.top().peek());
	// 90 78 56
	// 21 43 65
	// 34 12
	stack.second().push(65);
	stack.second().push(43);
	stack.second().push(21);
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(90, stack.top().peek());
	CHECK_EQUAL(21, stack.second().peek());
	CHECK_EQUAL(34, stack.at(2).peek());
	// [empty]
	// 90 78 56
	// 21 43 65
	// 34 12
	stack.insert(0);
	CHECK_EQUAL(4, stack.size());
	CHECK_EQUAL(0, stack.top().peek());
	CHECK_EQUAL(90, stack.second().peek());
	CHECK_EQUAL(21, stack.at(2).peek());
	CHECK_EQUAL(34, stack.at(3).peek());
	// 19 28 37 46
	// 90 78 56
	// 21 43 65
	// 34 12
	stack.top().push(46);
	stack.top().push(37);
	stack.top().push(28);
	stack.top().push(19);
	CHECK_EQUAL(4, stack.top().size());
	CHECK_EQUAL(19, stack.top().peek());
	// 19 28 37 46
	// 90 78 56
	// 21 43 65
	// 34 12
	// [empty]
	stack.insert(4);
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(19, stack.top().peek());
	CHECK_EQUAL(90, stack.second().peek());
	CHECK_EQUAL(21, stack.at(2).peek());
	CHECK_EQUAL(34, stack.at(3).peek());
	CHECK_EQUAL(0, stack.at(4).peek());
}
