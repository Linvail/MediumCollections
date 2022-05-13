#include "Design.h"
#include "LeetCodeUtil.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace Design
{
    using namespace std;
    using namespace LeetCodeUtil;

    //------------------------------------------------------------------------------------------------------------------------
    // 297. Serialize and Deserialize Binary Tree (Hard)
    //------------------------------------------------------------------------------------------------------------------------
    static const int sInvalidValue = INT_MAX;

    TreeNode* createTree_omit_missing_children
        (
        const vector<int>& aNodeArray
        )
    {
        TreeNode* root = new TreeNode( aNodeArray[0] );
        int start = 1;

        vector<TreeNode*> prevLevel;
        prevLevel.push_back( root );

        while( !prevLevel.empty() && start < aNodeArray.size() )
        {
            vector<TreeNode*> thisLevel;
            for( auto node : prevLevel )
            {
                if( aNodeArray[start] != sInvalidValue )
                {
                    node->left = new TreeNode( aNodeArray[start] );
                    thisLevel.push_back( node->left );
                }
                start++;
                if( start >= aNodeArray.size() )
                {
                    break;
                }

                if( aNodeArray[start] != sInvalidValue )
                {
                    node->right = new TreeNode( aNodeArray[start] );
                    thisLevel.push_back( node->right );
                }
                start++;

                if( start >= aNodeArray.size() )
                {
                    break;
                }
            }
            swap( prevLevel, thisLevel );
        }

        return root;
    }

    // Encodes a tree to a single string.
    string serialize( TreeNode* aRoot )
    {
        vector<string> dataToPrint;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( aRoot );

        while( !nodeQueue.empty() )
        {
            const int len = nodeQueue.size();

            for( int i = 0; i < len; ++i )
            {
                TreeNode* cur = nodeQueue.front();
                nodeQueue.pop();

                string data = cur ? to_string( cur->val ) : "null";
                dataToPrint.push_back( data );

                if( !cur )
                {
                    continue;
                }

                if( cur->left )
                {
                    nodeQueue.push( cur->left );
                }
                else
                {
                    nodeQueue.push( nullptr );
                }

                if( cur->right )
                {
                    nodeQueue.push( cur->right );
                }
                else
                {
                    nodeQueue.push( nullptr );
                }
            }

        }

        // Remove "null" in the tail.
        int removeIndex = dataToPrint.size();
        auto rit = dataToPrint.rbegin();
        for( ; rit != dataToPrint.rend(); ++rit )
        {
            if( *rit != "null" )
            {
                break;
            }
            removeIndex--;
        }
        dataToPrint.erase( dataToPrint.begin() + removeIndex, dataToPrint.end() );

        string result( "[" );

        for( int i = 0; i < dataToPrint.size(); ++i )
        {
            result += dataToPrint[i];

            if( i != dataToPrint.size() - 1 )
            {
                result.push_back(',');
            }
        }

        result.push_back( ']' );;

        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize( string data )
    {
        if( data.empty() || data[0] != '[' || data.back() != ']' || data.length() < 3 )
        {
            return nullptr;
        }

        data.pop_back();

        size_t start = 1;
        size_t end = data.find_first_of( ',' );

        vector<int> nodeStrs;

        while( end <= string::npos )
        {
            string sub = data.substr( start, end - start );
            nodeStrs.emplace_back( sub == "null" ? sInvalidValue : stoi( sub ) );

            if( end == string::npos )
            {
                break;
            }

            start = end + 1;
            end = data.find_first_of( ',', start);
        }

        return createTree_omit_missing_children( nodeStrs );
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 380. Insert Delete GetRandom O(1)
    //------------------------------------------------------------------------------------------------------------------------

    class RandomizedSet
    {
    public:

        // <value, index of value in container>
        unordered_map<int, size_t> map;
        vector<int> container;

        RandomizedSet()
        {
        }

        bool insert( int val )
        {
            if( map.find( val ) != map.end() )
            {
                return false;
            }

            map[val] = container.size();
            container.push_back( val );
            return true;
        }

        bool remove( int val )
        {
            if( map.find( val ) == map.end() )
            {
                return false;
            }

            // Swap val and the last number in the container, then remove the last element.
            const int lastVal = container.back();
            const size_t indexOfVal = map[val];

            map[lastVal] = indexOfVal;
            container[indexOfVal] = lastVal;

            // Now the last element is useless, time to delete it.
            container.pop_back();
            map.erase( val );
            return true;
        }

        // unordered_set does not support accessing by index, so this issue cannot be simply resovled by
        // using a single unordered_set.
        int getRandom()
        {
            return container[rand() % container.size()];
        }
    };

    //------------------------------------------------------------------------------------------------------------------------
    // 381. Insert Delete GetRandom O(1) - Duplicates allowed (Hard)
    //------------------------------------------------------------------------------------------------------------------------

    class RandomizedCollectionDup
    {
    public:

        // <value, indexes of value in container>
        unordered_map<int, unordered_set<size_t>> map;
        vector<int> container;

        RandomizedCollectionDup()
        {

        }

        //  Inserts an item val into the multiset, even if the item is already present. Returns true if the item is not present, false otherwise.
        bool insert( int val )
        {
            map[val].insert( container.size() );
            container.push_back( val );
            return map[val].size() == 1;
        }

        // Removes an item val from the multiset if present. Returns true if the item is present, false otherwise.
        // Note that if val has multiple occurrences in the multiset, we only remove one of them.
        bool remove( int val )
        {
            if( map.find( val ) == map.end() )
            {
                return false;
            }

            // Pick one arbitrary index and remove it. Just pick the first one, it doesn't matter.
            const size_t index = *map[val].begin();
            map[val].erase( index );
            if( map[val].size() == 0 )
            {
                map.erase( val );
            }

            // If index is not the last, Swap the last element and container[index].
            if( index != container.size() - 1 )
            {
                int lastVal = container.back();
                container[index] = lastVal;

                // Update the information of lastVal in map.
                map[lastVal].erase( container.size() - 1 );
                map[lastVal].insert( index );
            }

            container.pop_back();
            return true;
        }

        // Returns a random element from the current multiset of elements.
        // The probability of each element being returned is linearly related to the number of same values the multiset contains.
        int getRandom()
        {
            return container[rand() % container.size()];
        }
    };

    void test_design()
    {
        // Input: root = [1,2,3,null,null,4,5]
        // Output: [1, 2, 3, null, null, 4, 5]
        //string testStr = "[1,2,3,null,null,4,5]";
        //string testStr = "[1,2,3,null,null,4,5,6,7]";
        string testStr = "[1,2]";

        cout << "Call deserialize for: " << testStr << endl;
        TreeNode* newNode = deserialize( testStr );
        cout << "Result of serialize: " << serialize( newNode ) << endl;

        LeetCodeUtil::cleanUp( newNode );

        RandomizedCollectionDup collectDup;

        bool ret = collectDup.insert( 5 );
        ret = collectDup.insert( 5 );
        ret = collectDup.insert( 6 );
        ret = collectDup.insert( 7 );
        ret = collectDup.remove( 5 );
        ret = collectDup.remove( 5 );
        ret = collectDup.remove( 5 );
    }
}
