#include "ArrayAndStrings.h"

#include <iostream>
#include <vector>
#include <unordered_map>

namespace ArrayAndStrings
{
    using namespace std;

    // Given a string s, find the length of the longest substring without repeating characters.
    //
    // s consists of English letters, digits, symbols and spaces.
    // Moving window method.
    int lengthOfLongestSubstring( string s )
    {
        int result = 0;
        // It is -1 because we scan from index 0. 0 - (-1) = 1, meaning the
        // 1st char in s.
        int left = -1;
        // <char c, that latest index of c in s>
        unordered_map<char, int> umap;
        for( int i = 0; i < s.size(); ++i )
        {
            if( umap.find( s[i] ) != umap.end() && umap[s[i]] > left )
            {
                left = umap[s[i]];
            }
            // Always update, so we get its latest index.
            umap[s[i]] = i;
            result = max( result, i - left );
        }
        return result;
    }

    // Moving window method without unodered_map.
    // Idea: If the elements are limited as such, we could use a integer array to
    // represent them, so we won't need a hash map.
    int lengthOfLongestSubstring_v2( string s )
    {
        vector<int> m( 128, -1 );
        int result = 0;
        int left = -1;
        for( int i = 0; i < s.size(); ++i )
        {
            left = max( left, m[s[i]] );
            m[s[i]] = i;
            result = max( result, i - left );
        }
        return result;
    }

    void test_lengthOfLongestSubstring()
    {
        cout << "\ntest_lengthOfLongestSubstring\n";
        string testData = "abcabcbb";
        cout << "Answer of " << testData << " is " << lengthOfLongestSubstring_v2(testData) << endl;
        testData = "bbbbb";
        cout << "Answer of " << testData << " is " << lengthOfLongestSubstring_v2( testData ) << endl;
        testData = "pwwkew";
        cout << "Answer of " << testData << " is " << lengthOfLongestSubstring_v2( testData ) << endl;
    }
}