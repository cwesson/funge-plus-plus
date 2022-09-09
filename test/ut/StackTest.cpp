#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "Stack.h"

TEST_GROUP(StackTestGroup)
{

};

TEST(StackTestGroup, InvertQueueStackTest)
{
	Funge::Stack stack;
	// [empty]
	CHECK_EQUAL(0, stack.size());
	// 54 76 98
	stack.push(98); // 1
	stack.push(76); // 2
	stack.push(54); // 3
	stack.setMode(Funge::FUNGE_MODE_INVERT);
	// 54 76 98 32 10
	stack.push(32); // 4
	stack.push(10); // 5
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(54, stack.peek());
	CHECK_EQUAL(5, stack.age());
	// 98 32 10
	CHECK_EQUAL(54, stack.pop()); // 6
	CHECK_EQUAL(76, stack.pop()); // 7
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(7, stack.age());
	CHECK_EQUAL(10, stack.get(3));
	stack.setMode(Funge::FUNGE_MODE_INVERT | Funge::FUNGE_MODE_QUEUE);
	// 98 32 10 89 67
	stack.push(89); // 8
	stack.push(67); // 9
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(9, stack.age());
	CHECK_EQUAL(32, stack.get(4));
	// 98 32 10
	CHECK_EQUAL(67, stack.pop()); // 10
	CHECK_EQUAL(89, stack.pop()); // 11
	// [empty]
	stack.clear(); // 12
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.peek());
	CHECK_EQUAL(12, stack.age());
};

TEST(StackTestGroup, QueueStackTest)
{
	Funge::Stack stack;
	// [empty]
	CHECK_EQUAL(0, stack.size());
	// 54 76 98
	stack.push(98); // 1
	stack.push(76); // 2
	stack.push(54); // 3
	stack.setMode(Funge::FUNGE_MODE_QUEUE);
	// 10 32 54 76 98
	stack.push(32); // 4
	stack.push(10); // 5
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(98, stack.peek());
	CHECK_EQUAL(5, stack.age());
	// 10 32 54
	CHECK_EQUAL(98, stack.pop()); // 6
	CHECK_EQUAL(76, stack.pop()); // 7
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(7, stack.age());
	CHECK_EQUAL(10, stack.get(3));
	// 67 89 10 32 54
	stack.push(89); // 8
	stack.push(67); // 9
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(9, stack.age());
	CHECK_EQUAL(10, stack.get(3));
	// [empty]
	stack.clear(); // 10
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.peek());
	CHECK_EQUAL(10, stack.age());
};

TEST(StackTestGroup, InvertStackTest)
{
	Funge::Stack stack;
	// [empty]
	CHECK_EQUAL(0, stack.size());
	// 54 76 98
	stack.push(98); // 1
	stack.push(76); // 2
	stack.push(54); // 3
	stack.setMode(Funge::FUNGE_MODE_INVERT);
	// 54 76 98 32 10
	stack.push(32); // 4
	stack.push(10); // 5
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(54, stack.peek());
	CHECK_EQUAL(5, stack.age());
	// 98 32 10
	CHECK_EQUAL(54, stack.pop()); // 6
	CHECK_EQUAL(76, stack.pop()); // 7
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(7, stack.age());
	CHECK_EQUAL(10, stack.get(3));
	// 98 32 10 89 67
	stack.push(89); // 8
	stack.push(67); // 9
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(9, stack.age());
	CHECK_EQUAL(89, stack.get(4));
	// [empty]
	stack.clear(); // 10
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.peek());
	CHECK_EQUAL(10, stack.age());
};

TEST(StackTestGroup, BasicStackTest)
{
	Funge::Stack stack;
	// [empty]
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.pop()); // 1
	CHECK_EQUAL(0, stack.size());
	// 12
	stack.push(12); // 2
	CHECK_EQUAL(1, stack.size());
	CHECK_EQUAL(12, stack.peek());
	// 34 12
	stack.push(34); // 3
	CHECK_EQUAL(2, stack.size());
	CHECK_EQUAL(34, stack.peek());
	// 56 34 12
	stack.push(56); // 4
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(56, stack.peek());
	CHECK_EQUAL(4, stack.age());
	// 34 12
	CHECK_EQUAL(56, stack.pop()); // 5
	CHECK_EQUAL(2, stack.size());
	CHECK_EQUAL(34, stack.peek());
	// 12
	CHECK_EQUAL(34, stack.pop()); // 6
	CHECK_EQUAL(1, stack.size());
	CHECK_EQUAL(12, stack.peek());
	CHECK_EQUAL(6, stack.age());
	// [empty]
	CHECK_EQUAL(12, stack.pop()); // 7
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.peek());
	// 24 13 90 78
	stack.push(78); // 8
	stack.push(90); // 9
	stack.push(13); // 10
	stack.push(24); // 11
	CHECK_EQUAL(4, stack.size());
	// 13 90 78
	CHECK_EQUAL(24, stack.pop()); // 12
	CHECK_EQUAL(3, stack.size());
	CHECK_EQUAL(13, stack.peek());
	// 46 35 13 90 78
	stack.push(35); // 13
	stack.push(46); // 14
	CHECK_EQUAL(5, stack.size());
	CHECK_EQUAL(13, stack.get(3));
	CHECK_EQUAL(14, stack.age());
	// [empty]
	stack.clear(); // 15
	CHECK_EQUAL(0, stack.size());
	CHECK_EQUAL(0, stack.peek());
	CHECK_EQUAL(15, stack.age());
};
