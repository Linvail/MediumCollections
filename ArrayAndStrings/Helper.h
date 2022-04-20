#pragma once

#include <iostream>
#include <vector>
#include <map>

namespace ArrayAndStrings
{
    using namespace std;

    vector<int> twoSum( vector<int>& nums, int target )
    {
        vector<int> result;
        if( nums.size() == 0 )
        {
            return result;
        }

        // pair is <value, index>
        std::map<int, size_t> hashMap;
        hashMap[nums[0]] = 0;

        auto it = nums.begin() + 1;
        for( ; it != nums.end(); ++it )
        {
            auto foundIt = hashMap.find( target - *it );
            if( foundIt != hashMap.end() )
            {
                result.push_back( it - nums.begin() );
                result.push_back( foundIt->second );
            }
            hashMap[*it] = it - nums.begin();
        }

        return result;
    }
}