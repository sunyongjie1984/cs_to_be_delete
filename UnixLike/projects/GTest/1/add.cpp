#define private public
#define protect public

#include <iostream>
#include "gtest/gtest.h"
#include "add.h"

using::std::cout;
using::std::cin;
using::std::endl;
class MyTest {
public:
     int MyAdd(const int& x, const int& y) { return x + y; }
};

int add(const int& x, const int& y)
{
    return x + y;
}

class CMyTest_Test : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        cout << "CMyTest_Test Test case initialize" << endl;
    }

    static void TearDownTestCase()
    {
        cout << "CMyTest_Test test case cleanup" << endl;
    }

    virtual void SetUp()
    {
        cout << "CMyTest_Test Test initialize" << endl;
    }

    virtual void TearDown()
    {
        cout << "CMyTest_Test test cleanup" << endl;
    }
};

TEST_F(CMyTest_Test, MyAdd)
{
    MyTest a;
    EXPECT_EQ(3, a.MyAdd(1, 2));
}

TEST(Global_Add, add)
{
    EXPECT_EQ(3, add(1, 2));
}
