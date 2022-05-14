#include "MissingRanges.h"
#include "LeetCodeUtil.h"
#include <vector>
#include <string>

namespace ArrayAndStrings
{
    using namespace std;

    //------------------------------------------------------------------------------------------------------------------------
    // 163. Missing Ranges (Easy)
    //
    // Use greedy or priority queue.
    //------------------------------------------------------------------------------------------------------------------------

    vector<string> findMissingRanges
        (
        vector<int>& nums, //!< A sorted unique integer array.
        int lower,
        int upper
        )
    {
        // Let's deal a simple one [ 5,90 ]. We seek for "0->4", "6->89", and "91->99".

        vector<string> result;
        string range;
        for( int number : nums )
        {
            if( number > lower )
            {
                if( number - 1 > lower )
                {
                    range.append( to_string( lower ) );
                    range.append( "->" );
                    range.append( to_string( number - 1 ) );
                    result.push_back( range );
                }
                else
                {
                    // Need to deal with the special case [0, 1, ...]. We must not add '0' in that case.
                    range.append( to_string( lower ) );
                    result.push_back( range );
                }

                // Update the lower. Be careful of overflow.
                if( number == INT_MAX )
                {
                    break;
                }
                range.clear();
            }

            lower = number + 1;
        }

        if( nums.size() == 0 )
        {
            if( lower == upper )
            {
                result.push_back( to_string( lower ) );
            }
            else
            {
                range.append( to_string( lower ) );
                range.append( "->" );
                range.append( to_string( upper ) );
                result.push_back( range );
            }
        }
        else if( nums.back() < upper )
        {
            if( nums.back() < upper - 1 )
            {
                // Add one last range.
                range.append( to_string( nums.back() + 1 ) );
                range.append( "->" );
                range.append( to_string( upper ) );
                result.push_back( range );
            }
            else
            {
                range.append( to_string( upper ) );
                result.push_back( range );

            }
        }

        return result;
    }

    void test_missingRanges()
    {
        // Input: nums = [0,1,3,50,75], lower = 0, upper = 99
        // Output: ["2", "4->49", "51->74", "76->99"]
        vector<int> nums = { 0,1,3,50,75 };
        auto result = findMissingRanges( nums, 0, 99 );
        cout << "Missing Ranges of { 0,1,3,50,75 }. [0, 99]: " << endl;
        LeetCodeUtil::printVector( result );

        nums = { -1 };
        result = findMissingRanges( nums, -1, -1 );
        cout << "Missing Ranges of { -1 }. [-1, -1]: " << endl;
        LeetCodeUtil::printVector( result );

        nums = { INT_MAX };
        result = findMissingRanges( nums, INT_MAX - 2, INT_MAX );
        cout << "Missing Ranges of { INT_MAX }. [INT_MAX - 2, INT_MAX]: " << endl;
        LeetCodeUtil::printVector( result );

        nums = { };
        result = findMissingRanges( nums, 1, 3 );
        cout << "Missing Ranges of { }. [1, 3]: " << endl;
        LeetCodeUtil::printVector( result );

        nums = { -1 };
        result = findMissingRanges( nums, -1, 0 );
        cout << "Missing Ranges of { -1 }. [-1, 0]: " << endl;
        LeetCodeUtil::printVector( result );

        nums = { 1 };
        result = findMissingRanges( nums, 0, 9 );
        cout << "Missing Ranges of { 1 }. [0, 9]: " << endl;
        LeetCodeUtil::printVector( result );
    }
}