#include "TwoSumSorted.h"
#include "LeetCodeUtil.h"

namespace ArrayAndStrings
{
    using namespace std;

    //! 167. Two Sum II - Input Array Is Sorted
    //! Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number.
    //!  Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
    //!
    //! Return the indexes of the two numbers, index1and index2, added by one as an integer array[index1, index2] of length 2.
    //!
    //! The tests are generated such that there is exactly one solution.You may not use the same element twice.
    //!
    //! Your solution must use only constant extra space.
    vector<int> twoSum_sorted( vector<int>& numbers, int target )
    {
        int i = 0;
        int j = numbers.size() - 1;
        vector<int> ans( 2 );
        while( i < j )
        {
            const int sum = numbers[i] + numbers[j];
            if( sum == target )
            {
                ans[0] = i + 1;
                ans[1] = j + 1;

                return ans;
            }
            else if( sum > target )
            {
                j--;
            }
            else
            {
                i++;
            }
        }

        return ans;
    }

    void test_twoSum_sorted()
    {
        // Input: numbers = [2,7,11,15], target = 9
        // Output: [1, 2]

        vector<int> input = { 2,7,11,15 };
        int target = 9;

        cout << "\ntest_twoSum_sorted: " << endl;
        LeetCodeUtil::PrintVector( twoSum_sorted( input, target ) );
    }

}