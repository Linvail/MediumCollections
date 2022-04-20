#include <algorithm>    // std::sort
#include <map>

#include "ArrayAndStrings.h"

namespace ArrayAndStrings
{
    using namespace std;

    //! Two Sum.
    //! @return The vector of all pairs that contains two indices x and y, which aNums[x] + aNums[y] is aSum.
    vector<vector<int>> twoSum
        (
        const vector<int>& aNums,
        const int aSum,
        multimap<int, size_t> aHashMap, //!< For <x, y>, it means that the index of value - x in aNums is y.
        const int excludedIndex //<! The value in this index cannot be used.
        )
    {
        vector<vector<int>> result;

        for( int i = 0; i != aNums.size(); ++i )
        {
            if( i == excludedIndex )
            {
                continue;
            }

            auto matches = aHashMap.equal_range( aSum - aNums[i] );
            for( auto it = matches.first; it != matches.second; ++it )
            {
                if( excludedIndex != it->second && i != it->second )
                {
                    vector<int> match( 2 );
                    match[0] = i;
                    match[1] = static_cast<int>( it->second );
                    result.push_back( match );
                }
            }
        }

        return result;
    }

    //! Recalling the twosum algorithm, we have a hash of value to index, which tell us the index of certain value.
    vector<vector<int>> threeSum( vector<int>& nums )
    {
        vector<vector<int>> result;

        if( nums.size() < 3 )
        {
            return result;
        }

        multimap<int, size_t> hashMap;
        for( int i = 0; i < nums.size(); ++i )
        {
            hashMap.insert( pair<int, size_t>( nums[i], i ) );
        }

        for( int i = 0; i < nums.size(); ++i )
        {
            vector<vector<int>> twoSums = twoSum
            (
                nums,
                0 - nums[i],
                hashMap,
                i
            );

            for( auto matchTwo : twoSums )
            {
                vector<int> matchThree( 3 );
                matchThree[0] = nums[i];
                matchThree[1] = nums[matchTwo[0]];
                matchThree[2] = nums[matchTwo[1]];

                std::sort( matchThree.begin(), matchThree.end() );
                if( std::find( result.begin(), result.end(), matchThree ) == result.end() )
                {
                    result.push_back( matchThree );
                }
            }
        }

        std::sort( result.begin(), result.end() );

        return result;
    }
}