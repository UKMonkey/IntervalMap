// IntervalMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IntervalMap.h"


class ExampleKey
{
public:
    static ExampleKey GetKey(int value)
    {
		return ExampleKey(value);
    }

    ExampleKey(const ExampleKey& other)
        : v(other.v)
    {}

    ExampleKey& operator = (const ExampleKey& other)
    {
        v = other.v;
		return *this;
    }

    bool operator < (const ExampleKey& other) const {
        return v < other.v;
    }

private:
    ExampleKey(int v)
        : v(v)
    {}

    int v;
};


class ExampleValue
{
public:
    static ExampleValue GetValue(char x)
    {
        return ExampleValue(x);
    }

    ExampleValue(const ExampleValue& other)
		: x(other.x)
    {
    }

    bool operator == (const ExampleValue& other) const
    {
        return x == other.x;
    }

    ExampleValue& operator = (const ExampleValue& other)
    {
        x = other.x;
    }

private:
    ExampleValue(char x)
        : x(x)
    {}

    char x;
};

#define TEST(x) \
{ \
    if (!(x)) \
        std::cout << "Failure: " << #x << std::endl; \
    else      \
        std::cout << "Success: " << #x << std::endl; \
} \

int main()
{
    interval_map <ExampleKey, ExampleValue> test(ExampleValue::GetValue('a'));
    test.assign(ExampleKey::GetKey(5), ExampleKey::GetKey(1), ExampleValue::GetValue('b'));
	test.assign(ExampleKey::GetKey(10), ExampleKey::GetKey(15), ExampleValue::GetValue('c'));

    TEST(test[ExampleKey::GetKey(1)] == ExampleValue::GetValue('a'));
    TEST(test[ExampleKey::GetKey(4)] == ExampleValue::GetValue('a'));
    TEST(test[ExampleKey::GetKey(9)] == ExampleValue::GetValue('a'));
    TEST(test[ExampleKey::GetKey(10)] == ExampleValue::GetValue('c'));
    TEST(test[ExampleKey::GetKey(15)] == ExampleValue::GetValue('a'));

    test.assign(ExampleKey::GetKey(20), ExampleKey::GetKey(30), ExampleValue::GetValue('d'));
    test.assign(ExampleKey::GetKey(25), ExampleKey::GetKey(28), ExampleValue::GetValue('e'));

    TEST(test[ExampleKey::GetKey(20)] == ExampleValue::GetValue('d'));
    TEST(test[ExampleKey::GetKey(25)] == ExampleValue::GetValue('e'));
    TEST(test[ExampleKey::GetKey(26)] == ExampleValue::GetValue('e'));
    TEST(test[ExampleKey::GetKey(27)] == ExampleValue::GetValue('e'));
    TEST(test[ExampleKey::GetKey(28)] == ExampleValue::GetValue('d'));

    test.assign(ExampleKey::GetKey(20), ExampleKey::GetKey(30), ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(20)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(25)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(26)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(27)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(28)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(29)] == ExampleValue::GetValue('f'));
    TEST(test[ExampleKey::GetKey(30)] == ExampleValue::GetValue('a'));

    test.assign(ExampleKey::GetKey(-1), ExampleKey::GetKey(12), ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(-2)] == ExampleValue::GetValue('a'));
    TEST(test[ExampleKey::GetKey(-1)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(10)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(11)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(12)] == ExampleValue::GetValue('c'));

    test.assign(ExampleKey::GetKey(3), ExampleKey::GetKey(5), ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(-2)] == ExampleValue::GetValue('a'));
    TEST(test[ExampleKey::GetKey(-1)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(10)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(11)] == ExampleValue::GetValue('g'));
    TEST(test[ExampleKey::GetKey(12)] == ExampleValue::GetValue('c'));

    test.assign(ExampleKey::GetKey(10), ExampleKey::GetKey(13), ExampleValue::GetValue('c'));
    test.assign(ExampleKey::GetKey(3), ExampleKey::GetKey(28), ExampleValue::GetValue('x'));

    test.assign(ExampleKey::GetKey(5), ExampleKey::GetKey(20), ExampleValue::GetValue('c'));
    test.assign(ExampleKey::GetKey(5), ExampleKey::GetKey(40), ExampleValue::GetValue('x'));
    test.assign(ExampleKey::GetKey(40), ExampleKey::GetKey(42), ExampleValue::GetValue('x'));

    test.assign(ExampleKey::GetKey(50), ExampleKey::GetKey(110), ExampleValue::GetValue('a'));
    test.assign(ExampleKey::GetKey(-5), ExampleKey::GetKey(10), ExampleValue::GetValue('a'));
    std::cout << "Hello World!\n";
}
