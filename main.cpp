#include <iostream>
#include <time.h>
#include<istream>
#include <string>
#include "BoMatrix.h"


void testMultiplication(){
    clock_t start, end;
    start = clock();

    BoMatrixXd m1(3, 2), m2(2, 3);
    m1 <<
       1.0, 2.0,
       3.0, 4.0,
       5.0, 6.0;

    std::cout << "m1 = \n" << m1 << std::endl;

    m2 <<
       1.0, 2.0, 3.0,
       4.0, 5.0, 6.0;

    std::cout << "m2 = \n" << m2 << std::endl;


    BoMatrixXd m3(3, 3);
    m3 <<
       9, 12, 15,
       19, 26, 33,
       29, 40, 51;

    std::cout << "m3 = \n" << m3 << std::endl;

    assert(m3 == (m1 * m2));

    end = clock();
    printf("total time=%fs\n", (float)(end - start) / CLOCKS_PER_SEC);

    printf("testMultiplication PASSED!\n");

}

void testTranspose(){

    clock_t start, end;
    start = clock();

    BoMatrixXd m1(3, 2), m2(2, 3);
    m1 <<
    1.0, 2.0,
    3.0, 4.0,
    5.0, 6.0;

    std::cout << "m1 = \n" << m1 << std::endl;

    BoMatrixXd m1t(2, 3);
    m1t <<
    1, 3, 5,
    2, 4, 6;
    assert(m1t == m1.transpose());

    end = clock();
    printf("total time=%fs\n", (float)(end - start) / CLOCKS_PER_SEC);
    printf("testTranspose PASSED!\n");

}



int main(void){

    testTranspose();
    testMultiplication();

}