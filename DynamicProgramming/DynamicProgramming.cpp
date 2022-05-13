// DynamicProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DynamicProgramming.h"
#include "LeetCodeUtil.h"


namespace DynamicProgramming
{
    //------------------------------------------------------------------------------------------------------------------------
    // 55. Jump Game
    //
    // This can be resovled by dynamic programming or greedy algorithm. The later one seems easier
    //------------------------------------------------------------------------------------------------------------------------

    // Try dynamic programming. We must define the state-transition formula.
    // Let jumpPower[i] be the remaining jump power when rearch position i. If it's negative, it means that position is unreachable.
    // So, we have the formula: jumpPower[i] = max( jumpPower[i-1], nums[i-1] ) - 1.
    bool canJump( vector<int>& nums )
    {
        vector<int> jumpPower( nums.size(), 0 );

        for( int i = 1; i < nums.size(); ++i )
        {
            jumpPower[i] = max( jumpPower[i - 1], nums[i - 1] ) - 1;
            if( jumpPower[i] < 0 )
            {
                return false;
            }
        }

        return true;
    }

    // dynamic programming seems to occupy much space.
    // We don't really care about jump power of each position. We only care about whether we can reach the final position.
    // We can use a variable, reach, to record the farest position we can reach. If 'reach' is greater the nums.size() - 1, we
    // we can reach the final position.
    bool canJump_greedy( vector<int>& nums )
    {
        int reach = 0;
        const int n = nums.size();
        for( int i = 0; i < n; ++i )
        {
            // If i is greater than reach, i is not reachable.
            if( reach >= n - 1 || i > reach )
            {
                break;
            }

            reach = max( reach, i + nums[i] );
        }

        return reach >= n - 1;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 45. Jump Game II
    //------------------------------------------------------------------------------------------------------------------------

    // This is harder than Jump Game
    // Idea: Try to maintain the maximum reachable position of each position from left to right. If the maximum reachable
    // position is greater or equal to the n - 1, it means that we can reach the destination now.
    // We need to accumulate the steps we use.
    // The current the maximum reachable position is determined by the previous maximum reachable position of the current jump
    // power.
    int jump_game_II( vector<int>& nums )
    {
        int prevMaxDist = 0;
        int currMaxDist = 0;
        int steps = 0;
        const int n = nums.size() - 1;

        while( currMaxDist < n )
        {
            steps++;
            prevMaxDist = currMaxDist;
            for( int i = prevMaxDist; i >= 0; --i )
            {
                currMaxDist = max( currMaxDist, i + nums[i] );
            }
        }

        return steps;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 62. Unique Paths
    //
    // There are two ways to resolve this.
    // 1. dynamic programming.
    // 2. combination formula.
    //------------------------------------------------------------------------------------------------------------------------

    // Dynamic programming.
    // Formula: steps[i][j] = steps[i-1][j] + steps[i][j-1].
    // We only need to maintain one row (the row above) for the formula.
    int uniquePaths( int m, int n )
    {
        const int big = m >= n ? m : n;
        const int small = m < n ? m : n;

        vector<int> steps( small, 1 );
        for( int i = 1; i < big; ++i )
        {
            for( int j = 1; j < small; ++j )
            {
                steps[j] = steps[j] + steps[j - 1];
            }
        }

        return steps[small - 1];
    }

    inline uint32_t factorial( int k )
    {
        uint32_t result = 1;
        while( k > 1 )
        {
            result *= k;
            k--;
        }

        return result;
    }

    // We need to go down m - 1 steps and go right n - 1 steps.
    // Totally, we need ( m - 1 ) + ( n - 1 ) steps.
    //
    // The answer is equal to :
    // C(p, k) = p(p - 1)(p - 2)...(p - k + 1) / k!.
    // While p = ( m - 1 ) + ( n - 1 ), k = ( n - 1 ).
    int uniquePaths_math( int m, int n )
    {
        const int big = m >= n ? m - 1 : n - 1;
        const int small = m < n ? m - 1 : n - 1;

        const uint32_t totalSteps = big + small;

        uint32_t numerator = 1;
        uint32_t denominator = 1;
        // Calculate C(big, small).
        for( int i = 1; i <= small; ++i )
        {
            numerator *= ( totalSteps - i + 1 );
            denominator *= i;
        }

        return numerator / denominator;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 322. Coin Change
    //
    // Let count[i] be the minimum number of coins for amount i. count[amount] is the answer.
    // count[i] = min( count[i], count[i - conins[j]] + 1 ) for every j in conis
    // Calculate count[1] ~ count[amount].
    //------------------------------------------------------------------------------------------------------------------------
    int coinChange( vector<int>& coins, int amount )
    {
        const int InvalidCount = amount + 1;
        vector<int> count( amount + 1, InvalidCount );

        count[0] = 0;

        for( int i = 1; i <= amount; ++i )
        {
            for( const int coin : coins )
            {
                if( coin <= i )
                {
                    count[i] = min( count[i], count[i - coin] + 1 );
                }
            }
        }

        return count[amount] == InvalidCount ? -1 : count[amount];
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 300. Longest Increasing Subsequence
    //
    // Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
    //------------------------------------------------------------------------------------------------------------------------

    // The time complex of the straightforware dynmaic force is O(n^2)
    int lengthOfLIS_brutal( vector<int>& nums )
    {
        // n is size of nums.
        // Let dp[i] be the LIS of the sequence 0~i, where 0 <= i <= n - 1. The default value is 1.
        // dp[i] = max( dp[i], dp[j] + 1 ), where nums[j] < nums[i] and j < i.
        // The maximum value within dp is the answer.

        int result = 1;
        const int n = nums.size();
        vector<int> dp( n, 1 );

        for( int i = 0; i < n; ++i )
        {
            // This is a sequential search, making the time complex up to O(n^2).
            for( int j = 0; j < i; ++j )
            {
                if( nums[j] < nums[i] )
                {
                    dp[i] = max( dp[i], dp[j] + 1 );
                }
            }
            // Maintain the maximum value of dp[i].
            result = max( result, dp[i] );
        }

        return result;
    }

    // The achive O(n log(n)) time complex, we need to improve by binary search.
    // The whole algorithm is different.
    // Idea: We maintain a ordered list of numbers, whose length is the answer, but the numbers within are
    // not the LIS. Only its length is meaningfull.
    // To build the list:
    // For each number in nums, find the first element that is not less than it in the list (using binary search).
    // If that element doesn't exist, push back into the list.
    // If that element exist, overrite it with the current number.
    int lengthOfLIS( vector<int>& nums )
    {
        vector<int> list;

        for( int i : nums )
        {
            const int m = list.size();
            int left = 0;
            int right = m; // Note that this exceeds the boundary.

            // Binary search to find the 1st element that is not less than i.
            while( left < right )
            {
                const int mid = left + ( right - left ) / 2;
                if( list[mid] < i )
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid;
                }
            }

            if( right < m )
            {
                list[right] = i;
            }
            else
            {
                list.push_back( i );
            }
        }

        return list.size();
    }

    void test_dynamic_programming()
    {
        // Input: nums = [2,3,1,1,4]
        // Output: true
        // Input: nums = [3,2,1,0,4]
        // Output: false
        vector<int> testV = { 2,3,1,1,4 };
        cout << "Result of Jump Game: " << canJump_greedy( testV ) << endl;

        // Input: nums = [2,3,1,1,4]
        // Output: 2
        testV = { 2,3,0,1,4 };
        cout << "Result of Jump Game II: " << jump_game_II( testV ) << endl;

        // Input: m = 3, n = 7
        // Output: 28
        cout << "Result of Unique Paths: " << uniquePaths_math( 3, 7 ) << endl;

        // Input: coins = [1,2,5], amount = 11
        // Output: 3
        testV = { 1, 2, 5 };
        cout << "Result of Coin Change: " << coinChange( testV, 11 ) << endl;

        // Input: nums = [10,9,2,5,3,7,101,18]
        // Output: 4
        // Input: nums = [4, 2, 4, 5, 3, 7]
        // Output: 4
        testV = { 4, 2, 4, 5, 3, 7 };
        cout << "Result of Longest Increasing Subsequence: " << lengthOfLIS( testV ) << endl;
    }
}