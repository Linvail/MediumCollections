// SortingAndSearching.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SortingAndSearching.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <unordered_map>
#include <queue>

namespace SortingAndSearching
{
    using namespace std;

    enum Color
    {
        ColorRed = 0,
        ColorWhite = 1,
        ColorBlue = 2
    };

    //------------------------------------------------------------------------------------------------------------------------
    // 75. Sort Colors
    //
    // We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
    // Follow up: Could you come up with a one-pass algorithm using only constant extra space?
    //------------------------------------------------------------------------------------------------------------------------
    void sortColors( vector<int>& nums )
    {
        int redIndex = 0;
        int blueIndex = nums.size() - 1;

        for( int i = 0; i <= blueIndex; ++i )
        {
            if( ColorRed == nums[i] )
            {
                swap( nums[i], nums[redIndex] );
                redIndex++;
            }
            else if( ColorBlue == nums[i] )
            {
                swap( nums[i], nums[blueIndex] );
                i--;
                blueIndex--;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 347. Top K Frequent Elements
    //
    // Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
    //------------------------------------------------------------------------------------------------------------------------

    // Use a hash map (record the count of presence) and a max heap (sort the count presence).
    vector<int> topKFrequent( vector<int>& nums, int k )
    {
        vector<int> res;

        if( nums.size() == 0 || k == 0 )
        {
            return res;
        }

        // <element, count of presence>
        unordered_map<int, size_t> hashMap;
        // <count of presence, element>
        priority_queue<pair<size_t, int>> maxHeap;

        for( int digit : nums )
        {
            hashMap[digit]++;
        }

        for( const auto& it : hashMap )
        {
            maxHeap.push( { it.second, it.first } );
        }

        for( int i = 0; i < k; ++i )
        {
            res.push_back( maxHeap.top().second );
            maxHeap.pop();
        }

        return res;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // Kth Largest Element in an Array
    //
    // Using sort or priority_queue is easy but not smart.
    // The better way is to utilize the parition precedure of quick sort.
    //
    //
    //------------------------------------------------------------------------------------------------------------------------

    int partition_Lomuto
        (
        vector<int>& aInput,
        int aBegin,
        int aEnd
        )
    {
        const int pivot = aInput[aEnd];
        int low = aBegin;

        for( int i = aBegin; i < aEnd; ++i )
        {
            if( aInput[i] >= pivot )
            {
                swap( aInput[i], aInput[low] );
                low++;
            }
        }

        swap( aInput[low], aInput[aEnd] );
        return low;
    }

    int findKthLargest( vector<int>& nums, int k )
    {
        int left = 0;
        int right = nums.size() - 1;

        // k is 1-based.
        while( true )
        {
            const int pivot = partition_Lomuto( nums, left, right );
            if( pivot == k - 1 )
            {
                return nums[pivot];
            }
            else if( pivot > k - 1 ) // search the left
            {
                right = pivot - 1;
            }
            else
            {
                left = pivot + 1;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 162. Find Peak Element
    //
    // !! If the array contains multiple peaks, return the index to any of the peaks.
    // You must write an algorithm that runs in O(log n) time.
    //------------------------------------------------------------------------------------------------------------------------

    int findPeakElement( vector<int>& nums )
    {
        // When it comes to O(log n), binary search might be the solution.
        int left = 0;
        int right = nums.size() - 1;
        // { 0, 1 ,0 }
        while( left < right )
        {
            int mid = left + ( right - left ) / 2;
            if( nums[mid] < nums[mid + 1] )
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return right;
    }

    void test_sorting_searching()
    {
        // Input: nums = [2, 0, 2, 1, 1, 0]
        // Output : [0, 0, 1, 1, 2, 2]
        //vector<int> testV = { 2, 0, 2, 1, 1, 0 };
        vector<int> testV = { 0, 0, 0, 0, 2, 0 };
        sortColors( testV );
        cout << "Result of Sort Colors:\n";
        LeetCodeUtil::printVector( testV );
        cout << endl;

        // Input: nums = [1,1,1,2,2,3], k = 2
        // Output: [1, 2]
        testV = { 1,1,1,2,2,3 };
        vector<int> resultV = topKFrequent( testV, 2 );
        cout << "Result of Top K Frequent Elements:\n";
        LeetCodeUtil::printVector( resultV );
        cout << endl;

        // Input: nums = [3,2,1,5,6,4], k = 2
        // Output: 5
        // Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
        // Output: 4
        // Input: nums = [5,2,4,1,3,6,0], k = 4
        // Output: 3
        //
        #define TEST_CASE 3

        #if( TEST_CASE == 1 )
            testV = { 3, 2, 1, 5, 6, 4 };
            int k = 2; // output: 5
        #elif( TEST_CASE == 2 )
            testV = { 5, 2, 4, 1, 3, 6, 0 };
            int k = 4; // output: 3
        #elif( TEST_CASE == 3 )
            testV = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };
            int k = 4; // output 4
        #endif

        cout << "Result of Kth Largest Element in an Array: " << findKthLargest( testV, k ) << endl;

        // Input: nums = [1,2,3,1]
        // Output: 2
        testV = { 1, 2, 3, 1 };
        cout << "Result of Find Peak Element: " << findPeakElement( testV ) << endl;

    }
}
