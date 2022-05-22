#include "Design.h"
#include "LeetCodeUtil.h"

#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

namespace Design
{
    using namespace std;
    using namespace LeetCodeUtil;

    //------------------------------------------------------------------------------------------------------------------------
    // 449. Serialize and Deserialize BST
    // The encoded string should be as compact as possible.
    // 0 <= Node.val <= 10^4
    //
    // BST is just a special case of binary tree. So the solution of 297 also works for this question.
    // However, serialization for BST can use less storage because we can use postorder instead of level order.
    // For BT, we need preorder/postorder AND inorder to constructed the tree (or level order).
    // However, for BST, we just need preorder or postorder because inorder can be obtained by sorting preorder or postorder.
    //
    //------------------------------------------------------------------------------------------------------------------------
    class Codec
    {
    public:

        class BuildBst
        {
            TreeNode* bstFromPreorder_helper
                (
                const vector<int>& preorder,
                const int aLeft,
                const int aRight
                )
            {
                if (aLeft > aRight)
                {
                    return nullptr;
                }

                TreeNode* newRoot = new TreeNode(preorder[aLeft]);

                // Try to find the first number that is greater than root.
                // It is the start point of the right tree.
                int i = aLeft + 1;
                for (; i <= aRight; ++i)
                {
                    if (preorder[i] > preorder[aLeft])
                    {
                        break;
                    }
                }

                newRoot->left = bstFromPreorder_helper(preorder, aLeft + 1, i - 1);
                newRoot->right = bstFromPreorder_helper(preorder, i, aRight);

                return newRoot;
            }

        public:
            // 1008. Construct Binary Search Tree from Preorder Traversal(Medium).
            TreeNode* bstFromPreorder(vector<int>& preorder)
            {
                return bstFromPreorder_helper(preorder, 0, preorder.size() - 1);
            }
        };

        // Encodes a tree to a single string.
        string serialize(TreeNode* root)
        {
            // Do preorder traversal.
            TreeNode* current = root;
            stack<TreeNode*> nodeStack;
            ostringstream os;

            while (current || !nodeStack.empty())
            {
                if (current)
                {
                    // Use space as the delimiter because we want to use istringstream to read it.
                    os << current->val << " ";
                    nodeStack.push(current);
                    current = current->left;
                }
                else
                {
                    current = nodeStack.top();
                    nodeStack.pop();
                    current = current->right;
                }
            }

            return os.str();
        }

        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data)
        {
            if (data.empty())
            {
                return nullptr;
            }
            vector<int> nodeValue;
            istringstream is(data);
            string val;
            while (( is >> val ))
            {
                nodeValue.push_back(stoi(val));
            }

            BuildBst builder;
            return builder.bstFromPreorder(nodeValue);
        }
    };

    //------------------------------------------------------------------------------------------------------------------------
    // 297. Serialize and Deserialize Binary Tree (Hard)
    //
    // Use level-order
    //------------------------------------------------------------------------------------------------------------------------
    static const int sInvalidValue = INT_MAX;

    // Encodes a tree to a single string.
    string serialize( TreeNode* aRoot )
    {
        vector<string> dataToPrint;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( aRoot );

        while( !nodeQueue.empty() )
        {
            TreeNode* cur = nodeQueue.front();
            nodeQueue.pop();

            string data = cur ? to_string( cur->val ) : "null";
            dataToPrint.push_back( data );

            if( cur )
            {
                nodeQueue.push(cur->left);
                nodeQueue.push(cur->right);
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

        vector<int> nodes;

        while( end <= string::npos )
        {
            string sub = data.substr( start, end - start );
            nodes.emplace_back( sub == "null" ? sInvalidValue : stoi( sub ) );

            if( end == string::npos )
            {
                break;
            }

            start = end + 1;
            end = data.find_first_of( ',', start);
        }

        TreeNode* root = new TreeNode(nodes[0]);
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        const size_t nodeSize = nodes.size();
        start = 1;

        while (!nodeQueue.empty() && start < nodeSize)
        {
            TreeNode* node = nodeQueue.front();
            nodeQueue.pop();

            if (start < nodeSize && nodes[start] != sInvalidValue)
            {
                node->left = new TreeNode(nodes[start]);
                nodeQueue.push(node->left);
            }
            start++;

            if (start < nodeSize && nodes[start] != sInvalidValue)
            {
                node->right = new TreeNode(nodes[start]);
                nodeQueue.push(node->right);
            }
            start++;
        }

        return root;
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

    //------------------------------------------------------------------------------------------------------------------------
    // 251. Flatten 2D Vector
    //
    // Follow up: As an added challenge, try to code it using only iterators in C++ or iterators in Java.
    //------------------------------------------------------------------------------------------------------------------------
    class Vector2D
    {
    public:
    public:
        Vector2D(vector<vector<int>>& vec) : inited(false)
        {
            for (const auto& v : vec)
            {
                m_internal.insert(m_internal.end(), v.begin(), v.end());
            }

        }

        int next()
        {
            if (!inited)
            {
                it = m_internal.begin();
                inited = true;
            }
            else
            {
                it++;
            }
            return *it;
        }

        bool hasNext()
        {
            if (!inited)
            {
                return !m_internal.empty();
            }
            else
            {
                return m_internal.end() != it && m_internal.end() != std::next(it);
            }
        }

    private:
        vector<int> m_internal;
        vector<int>::iterator it;
        bool inited;
    };

    //------------------------------------------------------------------------------------------------------------------------
    // 348. Design Tic-Tac-Toe
    //
    // Follow-up: Could you do better than O(n2) per move() operation?
    //
    // The straightfoward solution is to use a n*n table.
    // To achieve better space complex, we can take advantage of the fact that we don't really need to know the arrangement
    // of the marker made by players.  'O O X' and 'O X O' both stands for no-win. We only need to catch the cases of
    // 'O O O' and 'X X X'.
    // Therefore, we need rows[n] and columns[n] to record the situation of each row/column.
    // Let player 1's marker be 1 and player's marker be -1. When rows[i] of any i is 3 or -3, we have the winner.
    // And, we also need diagonal and antidiagonal.
    //------------------------------------------------------------------------------------------------------------------------

    class TicTacToe
    {
    public:
        TicTacToe(int n)
            : m_tableSize( n )
            , m_antidiagonal( 0 )
            , m_diagonal( 0 )
            , m_columns( n )
            , m_rows( n )
        {
        }

        int move(int row, int col, int player)
        {
            int marker = player == 1 ? 1 : -1;

            m_rows[row] += marker;
            m_columns[col] += marker;
            if (row == col)
            {
                m_diagonal += marker;
            }
            if (row == m_tableSize - col - 1)
            {
                m_antidiagonal += marker;
            }

            if (abs(m_rows[row]) == m_tableSize || abs(m_columns[col]) == m_tableSize ||
                abs(m_diagonal) == m_tableSize || abs(m_antidiagonal) == m_tableSize)
            {
                return player;
            }

            return 0;
        }

    private:
        size_t m_tableSize;

        int m_antidiagonal;
        int m_diagonal;

        vector<int> m_columns;
        vector<int> m_rows;
    };

    void test_design()
    {
        // Input: root = [1,2,3,null,null,4,5]
        // Output: [1, 2, 3, null, null, 4, 5]
        string testStr = "[1,2,3,null,null,4,5]";
        //string testStr = "[1,2,3,null,null,4,5,6,7]";
        //string testStr = "[1,2]";

        cout << "Call deserialize for: " << testStr << endl;
        TreeNode* newNode = deserialize( testStr );
        cout << "Result of serialize: " << serialize( newNode ) << endl;

        LeetCodeUtil::DeleteTree( newNode );

        RandomizedCollectionDup collectDup;

        bool ret = collectDup.insert( 5 );
        ret = collectDup.insert( 5 );
        ret = collectDup.insert( 6 );
        ret = collectDup.insert( 7 );
        ret = collectDup.remove( 5 );
        ret = collectDup.remove( 5 );
        ret = collectDup.remove( 5 );

        TicTacToe game(3);
        cout << "Move of TicTacToe: " << game.move(1, 1, 2) << endl;
        cout << "Move of TicTacToe: " << game.move(0, 2, 2) << endl;
        cout << "Move of TicTacToe: " << game.move(2, 0, 2) << endl;

        // 449. Serialize and Deserialize BST
        // Input: root = [2,1,3]
        // Output: [2, 1, 3]
        // Input: [8,5,1,7,10,12]
        // Output: [8, 5, 10, 1, 7, null, 12]
        TreeNode* root = LeetCodeUtil::BuildTreeFromLevelOrderString("[8, 5, 10, 1, 7, null, 12]");
        Codec codec;
        string resultStr = codec.serialize(root);
        cout << "Serialize BST: " << resultStr << endl;

        newNode = codec.deserialize(resultStr);
        cout << "Deserialize BST: " << endl;
        LeetCodeUtil::printTreeLevelOrder(newNode);

        LeetCodeUtil::DeleteTree(root);
        LeetCodeUtil::DeleteTree(newNode);
    }
}
