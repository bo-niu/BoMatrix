#include <iostream>
#include <time.h>
#include<istream>
#include <string>
#include "BoMatrix.h"
#include "gtest/gtest.h"
#include <omp.h>


// The fixture for testing class Foo.
class BoMatrixTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    BoMatrixTest() {
        // You can do set-up work for each test here.
    }

    ~BoMatrixTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

TEST_F(BoMatrixTest, testOpenMPWorking) {

//    int target_thread_num = 4;
//    omp_set_num_threads(target_thread_num);
//    int a, b=0;
//    #pragma omp parallel for private(a) shared(b)
//    for(a=1; a<2; ++a)
//    {
//        #pragma omp atomic
//        b += a;
//    }

    int a, b=0;
    #pragma omp parallel private(a) shared(b) num_threads(4)
    {
        a = 1;
        #pragma omp atomic
        b += a;
    }
    printf("b = %d\n", b);
    ASSERT_TRUE(b==4);
}


TEST_F(BoMatrixTest, testMultiplication) {

    BoMatrixXd m1(3, 2), m2(2, 3);
    m1 <<
    1.0, 2.0,
    3.0, 4.0,
    5.0, 6.0;

    //    std::cout << "m1 = \n" << m1 << std::endl;

    m2 <<
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0;

    //    std::cout << "m2 = \n" << m2 << std::endl;


    BoMatrixXd m3(3, 3);
    m3 <<
    9, 12, 15,
    19, 26, 33,
    29, 40, 51;

    //    std::cout << "m3 = \n" << m3 << std::endl;

    ASSERT_TRUE(m3 == (m1 * m2));

    BoMatrixXd m1_2(3, 2);
    m1_2 <<
    2.0, 4.0,
    6.0, 8.0,
    10.0, 12.0;

//    assert(m1_2 == (m1 * 2));
    ASSERT_TRUE(m1_2 == (m1 * 2));
//    assert(m1_2 == (2 * m1));
    ASSERT_TRUE(m1_2 == (2 * m1));


}


#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}