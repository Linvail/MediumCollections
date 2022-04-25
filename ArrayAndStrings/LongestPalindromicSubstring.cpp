#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <vector>

using namespace LeetCodeUtil;

namespace ArrayAndStrings
{
    // Given a string s, return the longest palindromic substring in s.
    // The fastest algorithm is Manacher's Algorithm ( O(n) ).
    //

    inline int getIndex( int x, int y, int width )
    {
        return ( x * width ) + y;
    }

    // Use dynamic programming.
    string longestPalindrome( string s )
    {
        // dp[i][j] stands for whether s[i] ~ [j] is palindrome.
        // dp[i][i] is apparently true.
        // dp[i][j] is true when j = i + 1 (neighbor) and s[i] == s[j]. Like "aa".
        // dp[i][j] is true when j > i + 1 (not neighbor) and dp[i + 1][j - 1] = true and s[i] == s[j]. Like "baab", i = 0, b = 3.

        const size_t len = s.size();
        // Deal with specal cases.
        if( len <= 1 )
        {
            return s;
        }

        string result;

        bool* dp = new bool[len * len];
        memset( dp, 0, len * len );
        // dp[i][i] is apparently true.
        for( int i = 0; i < len; ++i )
        {
            dp[getIndex( i, i, len )] = true;
        }

        // Variables to remember the boundaries of substring.
        int maxLen = 1; // If we found nothing, this will make the result be the first character.
        int leftIndex = 0;
        // Let fill the table.
        // i should decrease because in dp[i + 1][j - 1] we need to refer i + 1. That position must be filled.
        // j should increase.
        for( int i = len - 2; i >= 0; --i )
        {
            for( int j = i + 1; j < len; ++j )
            {
                dp[getIndex( i, j, len )] = s[i] == s[j] && ( j == i + 1 || dp[getIndex( i + 1, j - 1, len )] );

                if( dp[getIndex( i, j, len )] )
                {
                    if( j - i + 1 > maxLen )
                    {
                        maxLen = j - i + 1;
                        leftIndex = i;
                    }
                }
            }
        }

        result = s.substr( leftIndex, maxLen );

        delete [] dp;

        return result;
    }

    void test_longestPalindrome()
    {
        cout << "\ntest_longestPalindrome\n";

        string testData = "ac";
        cout << "Answer of " << testData << " is " << longestPalindrome( testData ) << endl;
        testData = "cbbd";
        cout << "Answer of " << testData << " is " << longestPalindrome( testData ) << endl;
        testData = "aabaa";
        cout << "Answer of " << testData << " is " << longestPalindrome( testData ) << endl;
    }

}
