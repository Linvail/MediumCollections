#pragma once

#include <string>
#include <vector>

namespace ArrayAndStrings
{
    using namespace std;

    // 73. Set Matrix Zeroes
    void setZeroes( vector<vector<int>>& matrix );

    void test_setZeroes();

    // 49. Group Anagrams
    vector<vector<string>> groupAnagrams( vector<string>& strs );

    void test_groupAnagrams();

    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring( string s );

    void test_lengthOfLongestSubstring();

    // 5. Longest Palindromic Substring
    string longestPalindrome( string s );

    void test_longestPalindrome();

    // 334. Increasing Triplet Subsequence
    bool increasingTriplet( vector<int>& nums );

    void test_increasingTriplet();

    // 38. Count and Say
    string countAndSay( int n );

    void test_countAndSay();
}