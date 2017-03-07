#include <iostream>

#include <unistd.h>

#include "gtest/gtest.h"

using namespace std;

//Test Environment initialize and cleanup
class TestSuiteEnvironment : public testing::Environment
{
public:
    virtual void SetUp()
    {
        cout << "Test environment initialize" << endl;
    }

    virtual void TearDown()
    {
        cout << "test environment cleanup" << endl;
    }
};

int main(int argc, char* argv[])
{
    testing::AddGlobalTestEnvironment(new TestSuiteEnvironment);
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
