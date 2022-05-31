#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

#include <unordered_set>
#include <unordered_map>

namespace ArrayAndStrings
{
    //---------------------------------------------------------------------------------------
    // 128. Longest Consecutive Sequence (Medium)
    // Topic: Hash table, Union find.
    //
    // Break point: The element is int, and the question demands consecutive, so we should
    // seek the nearby int, i.e. n - 1, n + 1.
    //
    //---------------------------------------------------------------------------------------
    // Use Union find solution.
    int longestConsecutive(vector<int>& nums)
    {
        // Union find solution: Use a set to store all numbers = O(n)
        // Scan all numbers and do union-find's find approach on it (seek and remove n-1/n+1
        // from the set). This steps is also O(n). The maximum count of found numbers decides
        // the answer.

        unordered_set<int> fullSet(nums.begin(), nums.end());
        int result = 0;

        for (int number : nums)
        {
            if (fullSet.find(number) == fullSet.end())
            {
                // This number has been found as a consecutive number previously.
                continue;
            }

            fullSet.erase(number);
            int left = number - 1;
            int right = number + 1;

            // 0 1 2 3 4
            // %   ^   %
            while (fullSet.count(left) > 0)
            {
                fullSet.erase(left);
                left--;
            }
            while (fullSet.count(right) > 0)
            {
                fullSet.erase(right);
                right++;
            }

            result = max(result, right - left - 1);
        }

        return result;
    }

    // Use hash table solution.
    int longestConsecutive_hash(vector<int>& nums)
    {
        // Build a hash table
        // <number, the length of the consecutive sequence that this number belongs to>
        unordered_map<int, int> hashTable;
        int result = 0;

        for (int number : nums)
        {
            auto iter = hashTable.find(number);
            if (iter != hashTable.end())
            {
                // This number has been found as a consecutive number previously.
                continue;
            }

            iter = hashTable.find(number - 1);
            int leftLen = iter == hashTable.end() ? 0 : iter->second;

            iter = hashTable.find(number + 1);
            int rightLen = iter == hashTable.end() ? 0 : iter->second;

            int sumOfLen = leftLen + 1 + rightLen;
            hashTable[number] = sumOfLen;

            result = max(result, sumOfLen);

            // 0 1 2 3 4
            // %   ^   %
            // 5 2 5 2 5 <-- second in hashTable.
            // This is tricky. We just need to update the length value for the number on
            // the left/right boundaries (0 and 4).
            // It is because we just call continue if we encounter 0~4. If we encounter 5,
            // we will try to get the length of 4, which was updated.
            hashTable[number - leftLen] = sumOfLen;
            hashTable[number + rightLen] = sumOfLen;
        }

        return result;
    }

    // 128. Longest Consecutive Sequence (Medium)
    void TestLongestConsecutiveSequence()
    {
        // Input: nums = [100,4,200,1,3,2]
        // Output: 4
        // Input: nums = [0,3,7,2,5,8,4,6,0,1]
        // Output: 9
        vector<int> inputVI = { 100,4,200,1,3,2 };

        cout << "\n128. Longest Consecutive Sequence: " <<
            longestConsecutive_hash(inputVI) << endl;
    }
}