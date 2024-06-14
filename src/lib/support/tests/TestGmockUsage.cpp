#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;

// Define the interface
class Foo
{
public:
    virtual ~Foo()                 = default;
    virtual int DoSomething(int a) = 0;
};

// Create the mock class
class MockFoo : public Foo
{
public:
    MOCK_METHOD(int, DoSomething, (int a), (override));
};

// Test function that uses Foo
int UseFoo(Foo * foo, int value)
{
    return foo->DoSomething(value);
}

// Test case
TEST(GMockTest, BasicValidation)
{
    MockFoo mock_foo;

    // Set up the expectation
    EXPECT_CALL(mock_foo, DoSomething(5)).WillOnce(Return(10));

    // Call the function with the mock object
    int result = UseFoo(&mock_foo, 5);

    // Validate the result
    EXPECT_EQ(result, 11);
}
