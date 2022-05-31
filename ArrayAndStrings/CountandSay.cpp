#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <vector>
#include <string>

namespace ArrayAndStrings
{
    using namespace LeetCodeUtil;

    // 38. Count and Say
    // 1 <= n <= 30
    // To generate the nth term, just count and say the n-1th term.
    // Input: n = 4
    // Output: "1211"
    // Explanation :
    // countAndSay( 1 ) = "1"
    // countAndSay( 2 ) = say "1" = one 1 = "11"
    // countAndSay( 3 ) = say "11" = two 1's = "21"
    // countAndSay( 4 ) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
    // countAndSay( 5 ) = say "1211" = one 1 + one 2 + two 1 = "12" + "11" = "111221"

    string countAndSay( int n )
    {
        string result = "1";
        while( --n )
        {
            string newStr;
            for( int i = 0; i < result.size(); ++i )
            {
                int countOfChar = 1;
                while( i + 1 < result.size() && result[i] == result[i + 1] )
                {
                    countOfChar++;
                    i++;
                }
                // Assume strings concatenating is expensive.
                //newStr += to_string( countOfChar ) + result[i];
                newStr.push_back( '0' + countOfChar );
                newStr.push_back( result[i] );
            }
            result = newStr;
        }

        return result;
    }

    void test_countAndSay()
    {
        cout << "\n38. Count and Say\n";

        int n = 4;

        cout << "Result of " << n << " is " << countAndSay( n ) << endl;
    }
}