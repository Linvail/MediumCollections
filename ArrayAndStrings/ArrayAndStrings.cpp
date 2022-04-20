// ArrayAndStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>

#include "LeetCodeUtil.h"
#include "ArrayAndStrings.h"

using namespace std;

int main()
{
    cout << "Calling threeSum..." << endl;
    // Output: [[-1,-1,2],[-1,0,1]]
    vector<int> testData = { -1, 0, 1, 2, -1, -4 };


    auto result = ArrayAndStrings::threeSum( testData );

    LeetCodeUtil::printVectorOfVector( result );
}
