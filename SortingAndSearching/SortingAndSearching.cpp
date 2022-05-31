// SortingAndSearching.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SortingAndSearching.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <unordered_map>
#include <map>
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
    // The better way is to utilize the partition procedure of quick sort.
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

    //------------------------------------------------------------------------------------------------------------------------
    // 34. Find First and Last Position of Element in Sorted Array
    //
    // A.k.a Search for a Range
    // You must write an algorithm with O(log n) runtime complexity.
    //
    // Idea: Use binary search twice.
    //------------------------------------------------------------------------------------------------------------------------

    // A helper function to find the first element that is greater or equal to the target by using binary search.
    // If not found, return aEnd.
    int firstGreaterOrEqual
        (
        vector<int>& nums,
        int aStart,
        int aEnd,
        int target
        )
    {
        while( aStart < aEnd )
        {
            const int mid = aStart + ( aEnd - aStart ) / 2;

            if( nums[mid] < target )
            {
                aStart = mid + 1;
            }
            else
            {
                aEnd = mid;
            }
        }

        return aEnd;
    }

    vector<int> searchRange( vector<int>& nums, int target )
    {
        vector<int> result( 2, -1 );

        int start = firstGreaterOrEqual( nums, 0, nums.size(), target );
        if( start == nums.size() || nums[start] != target )
        {
            return result;
        }
        result[0] = start;

        int end = firstGreaterOrEqual( nums, start, nums.size(), target + 1 );
        result[1] = end - 1;

        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 57. Insert Interval
    //
    // Idea: Iterate the intervals. Insert if no overlap and increment the position for the newInterval.
    // If overlapped, update the newInterval.
    // After iterated all, insert the newInterval into the correct position.
    //------------------------------------------------------------------------------------------------------------------------
    vector<vector<int>> insert( vector<vector<int>>& intervals, vector<int>& newInterval )
    {
        vector<vector<int>> result;
        int newPosition = 0;
        for( int i = 0; i < intervals.size(); ++i )
        {
            if( intervals[i][0] > newInterval[1] ) // newInterval is on the left
            {
                // not overlap.
                result.push_back( intervals[i] );
            }
            else if( intervals[i][1] < newInterval[0] ) // newInterval is on the right
            {
                // not overlap.
                result.push_back( intervals[i] );
                newPosition++;
            }
            else
            {
                newInterval[0] = min( newInterval[0], intervals[i][0] );
                newInterval[1] = max( newInterval[1], intervals[i][1] );
            }
        }

        result.insert( result.begin() + newPosition, newInterval );

        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 56. Merge Intervals
    //------------------------------------------------------------------------------------------------------------------------

    // Compare function
    bool CompareTwoVector( const vector<int>& aInterval1, const vector<int>& aInterval2 )
    {
        if( aInterval1.empty() || aInterval2.empty() ) // This won't actually happen.
        {
            return false;
        }

        if( aInterval1[0] <= aInterval2[0] )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Idea: sort and merge.
    vector<vector<int>> merge( vector<vector<int>>& intervals )
    {
        vector<vector<int>> result;
        if( intervals.empty() )
        {
            return result;
        }

        sort( intervals.begin(), intervals.end(), CompareTwoVector );
        // Insert the 1st one directly.
        result.emplace_back( intervals[0] );

        for( int i = 1; i < intervals.size(); ++i )
        {
            if( intervals[i][0] <= result.back()[1] ) // overlap
            {
                // Merge
                result.back()[1] = max( result.back()[1], intervals[i][1] );
            }
            else
            {
                result.push_back( intervals[i] );
            }
        }

        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 33. Search in Rotated Sorted Array
    //
    // You must write an algorithm with O(log n) runtime complexity.
    // This problem is quite hard among the medium-level.
    //------------------------------------------------------------------------------------------------------------------------
    /*
    * Must use binary search. The crucial problem is how to determine which half we should keep.
    * Here are all permutations. When the right-most number is larger than the middle one, the right half array is sorted.
    * When it is not, the left half array is sorted.
    0�@�@1�@�@2�@ 4�@�@5�@�@6�@�@7
    7�@�@0�@�@1�@ 2�@�@4�@�@5�@�@6
    6�@�@7�@�@0�@ 1�@�@2�@�@4�@�@5
    5�@�@6�@�@7�@ 0�@�@1�@�@2�@�@4
    4�@�@5�@�@6�@ 7�@�@0�@�@1�@�@2
    2�@�@4�@�@5�@ 6�@�@7�@�@0�@�@1
    1�@�@2�@�@4�@ 5�@�@6�@�@7�@�@0
    */

    int search( vector<int>& nums, int target )
    {
        int left = 0;
        int right = nums.size() - 1;

        while( left <= right )
        {
            const int mid = left + ( right - left ) / 2;

            if( nums[mid] == target ) // termination condition
            {
                return mid;
            }
            else if( nums[mid] < nums[right] ) // right half array is sorted.
            {
                // check if target falls in the right half array.
                if( nums[mid] < target && target <= nums[right] )
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            else
            {
                // left half array is sorted.
                if( nums[left] <= target && target < nums[mid] )
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
        }

        return -1;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 81. Search in Rotated Sorted Array II
    //
    // Follow up: This problem is similar to Search in Rotated Sorted Array, but 'nums' may contain duplicates.
    // Would this affect the runtime complexity? How and why?
    //
    // Observe [3 1 1] and [1 1 3 1]. When middle is equal the right, the 3 could be on left or right.
    // Solution: Decrement right until we find a different value.
    //------------------------------------------------------------------------------------------------------------------------

    int search_with_dup( vector<int>& nums, int target )
    {
        int left = 0;
        int right = nums.size() - 1;

        while( left <= right )
        {
            const int mid = left + ( right - left ) / 2;

            if( nums[mid] == target ) // termination condition
            {
                return true;
            }
            else if( nums[mid] < nums[right] ) // right half array is sorted.
            {
                // check if target falls in the right half array.
                if( nums[mid] < target && target <= nums[right] )
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            else if( nums[mid] > nums[right] )
            {
                // left half array is sorted.
                if( nums[left] <= target && target < nums[mid] )
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            else
            {
                // nums[mid] == nums[right] and != target.
                // We know nums[right] != target, so we can safely ignore them.
                right--;
            }
        }
        return false;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 253. Meeting Rooms II
    //
    // Given an array of meeting time intervals where intervals[i] = [starti, endi], return the minimum number of
    // conference rooms required.
    // 1 <= intervals.length <= 10^4
    // 0 <= starti < endi <= 10^6
    //------------------------------------------------------------------------------------------------------------------------
    int minMeetingRooms(vector<vector<int>>& intervals)
    {
        // The CompareTwoVector is actually not necessary, the default comparison is fine.
        sort(intervals.begin(), intervals.end(), [](const vector<int>& aLeft, const vector<int>& aRight) { return aLeft[0] < aRight[0]; });

        // Keep the end time of an internal. The smallest is on top.
        priority_queue<int, vector<int>, greater<int>> rooms;

        for (const auto& interval : intervals)
        {
            if (!rooms.empty() && rooms.top() <= interval[0])
            {
                rooms.pop();
            }
            rooms.push(interval[1]);
        }

        return rooms.size();
    }

    // We use map (the ordered one) to store the start time and end time of all intervals.
    int minMeetingRooms_no_queue(vector<vector<int>>& intervals)
    {
        // <time, marker of enter or exit the room>
        map<int, int> times;

        // { {7, 10}, {2 ,4} } becomes 2(1) 4(-1) 7(1) 10(-1)
        for (const auto& interval : intervals)
        {
            times[interval[0]]++; // Meaning we need a room!
            times[interval[1]]--; // Meaning we don't need the room anymore.
        }

        int roomNeeded = 0;
        int maxRoomsEverNeeded = 0;

        for (const auto& time : times)
        {
            roomNeeded += time.second;
            maxRoomsEverNeeded = max(roomNeeded, maxRoomsEverNeeded);
        }

        return maxRoomsEverNeeded;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 240. Search a 2D Matrix II
    //------------------------------------------------------------------------------------------------------------------------

    // Implemented on Leetcode.

    //------------------------------------------------------------------------------------------------------------------------
    // 74. Search a 2D Matrix
    //------------------------------------------------------------------------------------------------------------------------

    // Implemented on Leetcode.

    //------------------------------------------------------------------------------------------------------------------------
    // 435. Non-overlapping Intervals
    // Topic: DP, Greedy
    //------------------------------------------------------------------------------------------------------------------------
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        // I don't know how to use DP to solve this, Greedy seems more understandable.
        const int cStart = 0;
        const int cEnd = 1;
        // Like other interval-related questions, we need to sort them first.
        sort(intervals.begin(), intervals.end(),
            [](const vector<int>& left, const vector<int>& right) { return left[0] < right[0]; }
            );

        // Idea: Iterate from left to right, starting with the 2nd item. Compare with the previous (if not being deleted)
        // item. If this's start < previous one's end, there is overlapping. We need to delete one, but which one?
        // Here is the greedy concept involves. We should delete the one whose end is greater.
        // That is how we can meet the requirement :　return minimum number of intervals.
        int result = 0;
        int prevIdx = 0;
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][cStart] < intervals[prevIdx][cEnd])
            {
                result++;
                // Deleting one interval needs a trick.
                if (intervals[i][cEnd] < intervals[prevIdx][cEnd])
                {
                    // Delete intervals[previousIdx]
                    prevIdx = i;
                }
                else
                {
                    // Delete intervals[i][cEnd]. Intentionally keep empty, we don't
                    // need to update previousIdx.
                    // 0    1     2
                    // ^          ^
                    // In the next iteration, prevIdx will be 0 and i will be 2.
                }
            }
            else
            {
                // Just update previousIdx to follow i, i will be incremented in the loop.
                prevIdx = i;
            }
        }

        return result;
    }


    void test_sorting_searching()
    {
        // Input: nums = [2, 0, 2, 1, 1, 0]
        // Output : [0, 0, 1, 1, 2, 2]
        //vector<int> testV = { 2, 0, 2, 1, 1, 0 };
        vector<int> testV = { 0, 0, 0, 0, 2, 0 };
        sortColors( testV );
        cout << "Result of Sort Colors:\n";
        LeetCodeUtil::PrintVector( testV );
        cout << endl;

        // Input: nums = [1,1,1,2,2,3], k = 2
        // Output: [1, 2]
        testV = { 1,1,1,2,2,3 };
        vector<int> resultV = topKFrequent( testV, 2 );
        cout << "Result of Top K Frequent Elements:\n";
        LeetCodeUtil::PrintVector( resultV );
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

        // Input: nums = [5,7,7,8,8,10], target = 8
        // Output: [3, 4]
        // Input: nums = [1], target = 1
        // Output : [0, 0]
        //testV = { 5, 7, 7, 8, 8, 10 };
        //int target = 8;
        testV = { 1 };
        int target = 1;

        resultV = searchRange( testV, target );
        cout << "Result of Find First and Last Position of Element in Sorted Array:\n";
        LeetCodeUtil::PrintVector( resultV );
        cout << endl;

        // Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
        // Output: [[1, 6], [8, 10], [15, 18]]
        #if( 1 )
            vector<vector<int>> testVV = {
                {8, 10},
                {2, 6},
                {15, 18},
                {1, 3}
            };
        #else
            vector<vector<int>> testVV = {
                {1, 4},
                {4, 5}
            };
        #endif

        vector<vector<int>> resultVV = merge( testVV );
        cout << "Result of Merge Intervals:\n";
        LeetCodeUtil::PrintMatrix( resultVV );
        cout << endl;

        // Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
        // Output: [[1, 2], [3, 10], [12, 16]]
        testVV =
        {
            {1, 2},
            {3, 5},
            {6, 7},
            {8, 10},
            {12,16}
        };
        vector<int> newInterval = { 4, 8 };

        resultVV = insert( testVV, newInterval );
        cout << "Result of Insert Interval:\n";
        LeetCodeUtil::PrintMatrix( resultVV );
        cout << endl;

        // Input: nums = [4,5,6,7,0,1,2], target = 0
        // Output: 4
        testV = { 4, 5, 6, 7, 0, 1, 2 };
        target = 0;
        cout << "Search in Rotated Sorted Array: " << search( testV, target ) << endl;
        cout << endl;

        // Input: nums = [2,5,6,0,0,1,2], target = 0
        // Output: true
        testV = { 2, 5, 6, 0, 0, 1, 2 };
        target = 0;
        cout << "Search in Rotated Sorted Array II: " << search_with_dup( testV, target ) << endl;
        cout << endl;

        // Input: intervals = [[0,30],[5,10],[15,20]]
        // Output: 2
        LeetCodeUtil::BuildIntMatrixFromString("[[0,30],[5,10],[15,20]]", &resultVV);
        //
        // Input: intervals = [[7,10],[2,4]]
        // Output: 1
        //resultVV = { {7, 10}, {2 ,4} };
        cout << "Result of Meeting Rooms II: " << minMeetingRooms_no_queue(resultVV) << endl;
        cout << endl;

        // 435. Non-overlapping Intervals
        // Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
        // Output: 1
        LeetCodeUtil::BuildIntMatrixFromString("[[1,2],[2,3]]", &testVV);
        cout << "Result of Non-overlapping Intervals: " << eraseOverlapIntervals(testVV) << endl;
        cout << endl;
    }
}
