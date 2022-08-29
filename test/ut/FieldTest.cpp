#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Field.h"

TEST_GROUP(FieldTestGroup)
{
	void teardown()
	{
		mock().clear();
		mock().removeAllComparatorsAndCopiers();
	}
};

class VectorComparator : public MockNamedValueComparator
{
public:
	virtual bool isEqual(const void* object1, const void* object2)
	{
		const Funge::Vector* v1 = static_cast<const Funge::Vector*>(object1);
		const Funge::Vector* v2 = static_cast<const Funge::Vector*>(object2);
		return *v1 == *v2;
	}
	virtual SimpleString valueToString(const void* object)
	{
		return StringFrom(object);
	}
};

static void observerFunction(const Funge::Vector& v, Funge::inst_t i){
	mock().actualCall(__func__)
			.withParameterOfType("Vector", "vector", &v)
			.withParameter("inst", i);
}

TEST(FieldTestGroup, CharFieldTest)
{
	Funge::Field field(0, Funge::CELL_CHAR);
	CHECK_EQUAL(0, field.size());
	field.put(Funge::Vector{0}, 70);
	CHECK_EQUAL(1, field.size());
	field.put(Funge::Vector{1}, 73);
	CHECK_EQUAL(1, field.size());
	field.put(Funge::Vector{2}, 0x454C44);
	CHECK_EQUAL(1, field.size());
	CHECK_EQUAL(70, field.get(Funge::Vector{0}));
	CHECK_EQUAL(73, field.get(Funge::Vector{1}));
	CHECK(field.get(Funge::Vector{2}) <= 0xFF);
	field.put(Funge::Vector{1,2,3}, 51);
	CHECK_EQUAL(3, field.size());
	CHECK_EQUAL(' ', field.get(Funge::Vector{3,2,1}));

	VectorComparator comparator;
	mock().installComparator("Vector", comparator);
	field.addObserver(observerFunction);
	Funge::Vector vtwo{2};
	mock().expectOneCall("observerFunction")
			.withParameterOfType("Vector", "vector", &vtwo)
			.withParameter("inst", 79);
	field.put(vtwo, 79);
	mock().checkExpectations();
};

TEST(FieldTestGroup, BasicFieldTest)
{
	Funge::Field field(0, Funge::CELL_INT);
	CHECK_EQUAL(0, field.size());
	field.put(Funge::Vector{0}, 70);
	CHECK_EQUAL(1, field.size());
	field.put(Funge::Vector{1}, 73);
	CHECK_EQUAL(1, field.size());
	field.put(Funge::Vector{2}, 0x454C44);
	CHECK_EQUAL(1, field.size());
	CHECK_EQUAL(70, field.get(Funge::Vector{0}));
	CHECK_EQUAL(73, field.get(Funge::Vector{1}));
	CHECK_EQUAL(0x454C44, field.get(Funge::Vector{2}));
	field.put(Funge::Vector{1,2,3}, 51);
	CHECK_EQUAL(3, field.size());
	CHECK_EQUAL(' ', field.get(Funge::Vector{3,2,1}));

	VectorComparator comparator;
	mock().installComparator("Vector", comparator);
	field.addObserver(observerFunction);
	Funge::Vector vtwo{2};
	mock().expectOneCall("observerFunction")
			.withParameterOfType("Vector", "vector", &vtwo)
			.withParameter("inst", 79);
	field.put(vtwo, 79);
	mock().checkExpectations();
};
