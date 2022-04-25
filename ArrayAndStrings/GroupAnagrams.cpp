#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

#include <unordered_map>

namespace ArrayAndStrings
{
    using namespace std;

    // Given an array of strings strs, group the anagrams together.You can return the answer in any order.
    // An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
    // 1 <= strs.length <= 104
    // 0 <= strs[i].length <= 100
    // strs[i] consists of lowercase English letters.

    // 242. Valid Anagram
    bool isAnagram( string s, string t )
    {
        if( s.length() != t.length() )
        {
            return false;
        }

        vector<int> charTableS( 26, 0 );
        vector<int> charTableT( 26, 0 );

        for( int i = 0; i < s.length(); ++i )
        {
            charTableS[s[i] - 'a']++;
            charTableT[t[i] - 'a']++;
        }

        return charTableS == charTableT;
    }

    //! Brutal method. This will exceed the time limit on Leetcode.
    vector<vector<string>> groupAnagrams( vector<string>& strs )
    {
        vector<vector<string>> result;
        vector<bool> isAnagramOfOthers( strs.size(), false );

        for( int i = 0; i < strs.size(); ++i )
        {
            if( isAnagramOfOthers[i] )
            {
                continue;
            }

            vector<string> group;
            for( int j = i + 1; j < strs.size(); ++j )
            {
                if( isAnagram( strs[i], strs[j] ) )
                {
                    if( group.empty() )
                    {
                        group.push_back( strs[i] );
                    }
                    group.push_back( strs[j] );
                    isAnagramOfOthers[j] = true;
                }
            }
            if( group.empty() )
            {
                group.push_back( strs[i] );
            }
            result.push_back( group );
        }

        return result;
    }

    string buildKey( string aInput )
    {
        string result;
        // Record the count of a-z.
        vector<int> cnt( 26, 0 );
        for( auto c : aInput )
        {
            cnt[c - 'a']++;
        }
        for( int i = 0; i < 26; ++i )
        {
            if( cnt[i] == 0 )
            {
                continue;
            }
            //result += string( 1, 'a' + i ) + to_string( cnt[i] );

            char buff[26 * 4];

            snprintf( buff, 26 * 4, "%s%c%d", result.c_str(), 'a' + i, cnt[i] );
            result = buff;
        }

        return result;
    }

    vector<vector<string>> groupAnagrams_v2( vector<string>& strs )
    {
        vector<vector<string>> res;
        // <key, index to res>.
        unordered_map<string, int> umap;
        for( string str : strs )
        {
            string key = buildKey( str );
            if( umap.find( key ) == umap.end() )
            {
                res.emplace_back( vector<string>() );
                umap[key] = res.size() - 1;
            }

            res[umap[key]].push_back( str );
        }

        return res;
    }

    void test_groupAnagrams()
    {
        cout << "\ntest_groupAnagrams" << endl;

        vector<string> data = { "eat", "tea", "tan", "ate", "nat", "bat" };

        auto result = groupAnagrams_v2( data );

        LeetCodeUtil::printVectorOfVector( result );
    }
}