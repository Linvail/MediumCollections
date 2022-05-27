#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <vector>

using namespace LeetCodeUtil;

namespace ArrayAndStrings
{
    // Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.
    // Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
    bool increasingTriplet( vector<int>& nums )
    {
        int min = INT_MAX;
        int mid = INT_MAX;

        // nums[i] < min < nums[j] < mid < nums[k]
        for( int i : nums )
        {
            // Note that we use "<=" rather than "<" because the "return true" statement is put in the last.
            // "<=" can catch the case of consecutive identical number, like {1, 1, 1, ...}.
            if( i <= min )
            {
                // This is tricky. Consider { 2, 1, 5, 0, 6, 5 };
                // Even if we update min to 0, we don't need to modify mid (5).
                // The mid (5) means that there is a smaller number before 5, in this case, it is 1.
                // So, when we meet 6, we can return true because (1, 5, 6) meets the requirment.
                min = i;
            }
            else if( i <= mid )
            {
                mid = i;
            }
            else
            {
                return true;
            }

        }

        return false;
    }

    void test_increasingTriplet()
    {
        cout << "\ntest_increasingTriplet\n";

        vector<int> testData = { 1, 2, 3, 4, 5 };

        PrintVector( testData );
        cout << "Result is " << increasingTriplet( testData ) << endl;

        testData = { 5, 4, 3, 2, 1 };
        PrintVector( testData );
        cout << "Result is " << increasingTriplet( testData ) << endl;

        // The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
        testData = { 2, 1, 5, 0, 4, 6 };
        PrintVector( testData );
        cout << "Result is " << increasingTriplet( testData ) << endl;

        testData = { 2, 1, 5, 0, 6, 5 };
        PrintVector( testData );
        cout << "Result is " << increasingTriplet( testData ) << endl;

        testData = { 2, 4, -2, -3 };
        PrintVector( testData );
        cout << "Result is " << increasingTriplet( testData ) << endl;

        testData = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
            , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
            , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        cout << "Result is " << increasingTriplet( testData ) << endl;

    }
}