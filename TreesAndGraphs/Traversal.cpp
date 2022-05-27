#include "TreesAndGraphs.h"
#include "MorrisTraversal.h"

#include <stack>
#include <queue>

namespace TreesAndGraphs
{
    using namespace LeetCodeUtil;

    //---------------------------------------------------------------------------
    // 94. Binary Tree Inorder Traversal (Easy).
    // Follow up: Recursive solution is trivial, could you do it iteratively?
    // pre-order: 4213657
    // middle -> left -> right
    //---------------------------------------------------------------------------

    // Note that do inorder traversal for a binay search tree is to sort in ascending order.
    // Inorder = left -> middle -> right
    vector<int> inorderTraversal( TreeNode* root )
    {
        vector<int> result;
        stack<TreeNode*> nodeStack;

        if( root )
        {
            TreeNode* current = root;
            // Try to go left until we cannot. At that time current will be null, and we should process nodeStack.
            while( current || !nodeStack.empty() )
            {
                if( current )
                {
                    nodeStack.push( current );
                    current = current->left;
                }
                else
                {
                    result.push_back( nodeStack.top()->val );

                    current = nodeStack.top()->right;
                    nodeStack.pop();
                }
            }
        }

        return result;
    }

    void visitInorder( vector<int>& aResult, TreeNode* aRoot )
    {
        if( !aRoot )
        {
            return;
        }

        visitInorder( aResult, aRoot->left );

        aResult.push_back( aRoot->val );

        visitInorder( aResult, aRoot->right );
    }

    vector<int> inorderTraversal_recursive( TreeNode* root )
    {
        vector<int> result;
        visitInorder( result, root );
        return result;
    }

    //---------------------------------------------------------------------------
    // pre-order: 4213657
    // middle -> left -> right
    //---------------------------------------------------------------------------

    // Use the similar template as inorder/postorder.
    vector<int> preOrderTraversal( TreeNode* root )
    {
        vector<int> result;

        if( !root )
        {
            return result;
        }

        stack<TreeNode*> nodeStack;
        TreeNode* cur = root;

        while( cur || !nodeStack.empty() )
        {
            if( cur )
            {
                result.push_back( cur->val );
                nodeStack.push( cur );
                cur = cur->left;
            }
            else
            {
                cur = nodeStack.top()->right;
                nodeStack.pop();
            }
        }

        return result;
    }

    vector<int> preOrderTraversal_v2( TreeNode* root )
    {
        vector<int> result;

        if( !root )
        {
            return result;
        }

        stack<TreeNode*> nodeStack;
        nodeStack.push( root );

        while( !nodeStack.empty() )
        {
            TreeNode* cur = nodeStack.top();
            result.push_back( cur->val );
            nodeStack.pop();

            if( cur->right )
            {
                nodeStack.push( cur->right );
            }

            if( cur->left )
            {
                nodeStack.push( cur->left );
            }
        }

        return result;
    }

    // post-order: 1325764
    // left -> right -> middle
    // Postorder traversal can be used to delete the tree.
    // Several ways to do this:
    // 0. Template version but do not use stack.
    // 1. Modified from preOrderTraversal_v2. Change it to root -> right -> left, then reverse it to left -> right -> root.
    // 2. Push left/right node to stack and set left/right to nullptr of a node. If left/right are both nullptr, then visit the node.

    // Template version: idea: preorder is root -> left -> rigt.
    // We can change it to root -> right -> left, then reverse it to left -> right -> root.
    vector<int> postOrderTraversal( TreeNode* root )
    {
        vector<int> result;

        if( !root )
        {
            return result;
        }

        stack<TreeNode*> nodeStack;
        TreeNode* cur = root;

        while( cur || !nodeStack.empty() )
        {
            if( cur )
            {
                result.insert( result.begin(), cur->val );
                nodeStack.push( cur );
                cur = cur->right;
            }
            else
            {
                cur = nodeStack.top()->left;
                nodeStack.pop();
            }
        }

        return result;
    }

    vector<int> postOrderTraversal_v1( TreeNode* root )
    {
        vector<int> result;

        if( !root )
        {
            return result;
        }

        stack<TreeNode*> nodeStack1;
        //stack<TreeNode*> nodeStack2;

        nodeStack1.push( root );

        while( !nodeStack1.empty() )
        {
            TreeNode* cur = nodeStack1.top();
            // We use 'result' to simulate the 2nd stack since vector supports insert to the 1st position.
            result.insert( result.begin(), cur->val );
            nodeStack1.pop();

            if( cur->left )
            {
                nodeStack1.push( cur->left );
            }

            if( cur->right )
            {
                nodeStack1.push( cur->right );
            }

        }

        return result;
    }

    vector<vector<int>> levelOrderTraversal( TreeNode* root )
    {
        vector<vector<int>> result;

        if( !root )
        {
            return result;
        }

        queue<TreeNode*> q;
        q.push( root );
        while( !q.empty() )
        {
            int size = q.size();
            vector<int>v;
            for( int i = 0; i < size; i++ )
            {
                TreeNode* temp = q.front();
                q.pop();
                v.push_back( temp->val );

                if( temp->left )
                {
                    q.push( temp->left );
                }
                if( temp->right )
                {
                    q.push( temp->right );
                }

            }
            result.push_back( v );
        }

        return result;
    }

    //---------------------------------------------------------------------------
    // 671. Second Minimum Node In a Binary Tree (Easy).
    //---------------------------------------------------------------------------
    int findSecondMinimumValue( TreeNode* root )
    {
        if( !root->left )
        {
            return -1;
        }

        int secondMinOfLeft = root->left->val == root->val ? findSecondMinimumValue( root->left ) : root->left->val;
        int secondMinOfRight = root->right->val == root->val ? findSecondMinimumValue( root->right ) : root->right->val;

        if( secondMinOfLeft == -1 || secondMinOfRight == -1 )
        {
            // They could be both -1, but it won't affect the result.
            return max( secondMinOfLeft, secondMinOfRight );
        }
        else
        {
            return min( secondMinOfLeft, secondMinOfRight );
        }
    }

    //---------------------------------------------------------------------------
    // 99. Recover Binary Search Tree (Medium).
    // Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
    //---------------------------------------------------------------------------
    void recoverTree( TreeNode* root )
    {
        // To achieve O(1) space, we must use Morris inorder traversal.

        // 1 2 3 4 5 6 7. Assume 2 and 6 are swapped.
        // 1 6 3 4 5 2 7. We need to find the node of 6 and 2. At the end, swap them.
        //   ^       ^
        //  first    second
        TreeNode* current = root;
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        TreeNode* previous = nullptr;

        while( current )
        {
            if( !current->left )
            {
                // Visit
                if( previous && current->val < previous->val ) // error occurs.
                {
                    if( !first )
                    {
                        first = previous;
                    }
                    second = current;
                }
                previous = current;

                current = current->right;
            }
            else
            {
                // Find the predecessor.
                TreeNode* predecessor = current->left;
                while( predecessor->right &&
                    predecessor->right != current // This is important.
                    )
                {
                    predecessor = predecessor->right;
                }

                if( !predecessor->right )
                {
                    predecessor->right = current;
                    current = current->left;
                }
                else
                {
                    // Visit
                    if( previous && current->val < previous->val ) // error occurs.
                    {
                        if( !first )
                        {
                            first = predecessor;
                        }
                        second = current;
                    }
                    previous = current;

                    predecessor->right = nullptr;
                    current = current->right;
                }
            }
        }

        swap( first->val, second->val );
    }

    //---------------------------------------------------------------------------
    // 103 Binary Tree Zigzag Level Order Traversal
    // This is a variant of level order traversal.
    //---------------------------------------------------------------------------
    vector<vector<int>> zigzagLevelOrder( TreeNode* root )
    {
        vector<vector<int>> result;
        if( !root )
        {
            return result;
        }

        bool oddLevel = true;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( root );

        while( !nodeQueue.empty() )
        {
            const int len = nodeQueue.size(); // Size of this level.
            vector<int> levelResult( len );
            for( int i = 0; i < len; ++i )
            {
                TreeNode* current = nodeQueue.front();
                const int index = oddLevel ? i : len - i - 1;
                levelResult[index] = current->val;
                nodeQueue.pop();

                // Note that this will change nodeStack's size, so we cannot call nodeStack.size() in for-loop.
                // We must use 'len'.
                if( current->left )
                {
                    nodeQueue.push( current->left );
                }

                if( current->right )
                {
                    nodeQueue.push( current->right );
                }
            }

            result.push_back( levelResult );
            oddLevel = !oddLevel;
        }

        return result;
    }

    //---------------------------------------------------------------------------
    // 116. Populating Next Right Pointers in Each Node
    // You may only use constant extra space.
    // The recursive approach is fine.You may assume implicit stack space does not count as extra space for this problem.
    //
    // This could be a variant of level order traversal. However, it would take more than constant space if we use
    // iterative method. So, we will use the recursive method.
    //
    // There is also a tricky iterative method that only take constant space.
    // It use a pointer to mark each level's start point, and use another poiter to traverse the tree.
    //---------------------------------------------------------------------------

    TreeNode* connect( TreeNode* root )
    {
        if( !root )
        {
            return nullptr;
        }

        if( root->left )
        {
            root->left->next = root->right;
        }
        if( root->right )
        {
            root->right->next = !root->next ? nullptr : root->next->left;
        }

        connect( root->left );
        connect( root->right );

        return root;
    }

    // Non-recursion, constant space
    TreeNode* connect_iterative( TreeNode* root )
    {
        if( !root )
        {
            return nullptr;
        }

        TreeNode* start = root;
        TreeNode* cur = nullptr;

        while( start->left )
        {
            cur = start;
            while( cur )
            {
                cur->left->next = cur->right;

                if( cur->next )
                {
                    cur->right->next = cur->next->left;
                }

                cur = cur->next;
            }
            start = start->left;
        }
        return root;
    }

    //---------------------------------------------------------------------------
    // 117. Populating Next Right Pointers in Each Node II
    //
    // Contrary to 116, the input binary tree might be not perfect.
    //---------------------------------------------------------------------------

    TreeNode* findNextConnect( TreeNode* root )
    {
        TreeNode* target = nullptr;
        while( root && root->next )
        {
            if( root->next->left )
            {
                target = root->next->left;
                break;
            }
            if( root->next->right )
            {
                target = root->next->right;
                break;
            }
            root = root->next;
        }

        return target;
    }

    TreeNode* findNextStart( TreeNode* root )
    {
        do
        {
            if( root->left )
            {
                return root->left;
            }
            if( root->right )
            {
                return root->right;
            }

            root = root->next;
        } while( root );

        return nullptr;
    }

    TreeNode* connect_not_perfect( TreeNode* root )
    {
        if( !root )
        {
            return nullptr;
        }

        TreeNode* start = root;
        TreeNode* cur = nullptr;

        while( start )
        {
            cur = start;
            while( cur )
            {
                if( cur->left ) // Check because the tree might be not perfect.
                {
                    if( cur->right )
                    {
                        cur->left->next = cur->right;
                    }
                    else
                    {
                        cur->left->next = findNextConnect( cur );
                    }
                }

                if( cur->right )
                {
                    cur->right->next = findNextConnect( cur );
                }

                cur = cur->next;
            }

            // Find the start point in the next level.
            start = findNextStart( start );
        }
        return root;
    }

    void test_traversal()
    {
        // Input: root = [1,null,2,3]
        // Output: [1, 3, 2]
        #if 0
            //vector<string> testV = { "1", "null", "2", "null", "null", "3" };
        vector<string> testV = { "1", "null", "2", "3" };
        TreeNode* testData = levelOrderCreateTree( testV );
        #else
        /*
                4
             2     6
           1  3  5   7
        */
        vector<string> testV = { "4", "2", "6", "1", "3", "5", "7" };
        TreeNode* testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( testV );
        #endif

        vector<int> result = inorderTraversal( testData );

        // 1234567
        cout << "Result of inorderTraversal: ";
        PrintVector( result );
        cout << endl;

        result = preOrderTraversal( testData );

        // 4213657
        cout << "Result of preOrderTraversal: ";
        PrintVector( result );
        cout << endl;

        result = postOrderTraversal( testData );

        // 1325764
        cout << "Result of postOrderTraversal: ";
        PrintVector( result );
        cout << endl;

        auto resultVV = levelOrderTraversal( testData );

        // 4261357
        cout << "Result of levelOrderTraversal: ";
        PrintMatrix( resultVV );
        cout << endl;

        DeleteTree( testData );

        //vector<string> specialTree = { "2", "2", "5", "null", "null", "5", "7" }; // 5
        //vector<string> specialTree = { "2", "2", "2" }; // -1
        vector<string> specialTree = { "1", "1", "2", "1", "1", "2", "2" }; // 2
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( specialTree );
        int secondMinimum = findSecondMinimumValue( testData );
        cout << "Result of findSecondMinimumValue: " << secondMinimum << endl;
        DeleteTree( testData );

        specialTree = { "1", "1", "3", "1", "1", "3", "4", "3", "1", "1", "1", "3", "8", "4", "8", "3", "3", "1", "6", "2", "1" };
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( specialTree );
        secondMinimum = findSecondMinimumValue( testData );
        cout << "Result of findSecondMinimumValue: " << secondMinimum << endl; // 2
        DeleteTree( testData );

        cout << "\n";

        test_morrisTraversal();

        // 99. Recover Binary Search Tree
        // Input: root = [3,1,4,null,null,2]
        // Output: [2, 1, 4, null, null, 3]
        specialTree = { "3", "1", "4", "null", "null", "2" };
        //specialTree = { "1", "3", "null", "null", "2" };
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( specialTree );
        recoverTree( testData );
        cout << "Result of recoverTree: " << endl;
        PrintTreeLevelOrder( testData );
        DeleteTree( testData );

        cout << "\n";

        // 103 Binary Tree Zigzag Level Order Traversal
        // Input: root = [3,9,20,null,null,15,7]
        // Output: [[3], [20, 9], [15, 7]]
        testV = { "3", "9", "20", "null", "null", "15", "7" };
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( testV );
        resultVV = zigzagLevelOrder( testData );
        cout << "Result of zigzagLevelOrder: " << endl;
        PrintMatrix( resultVV );

        cout << "\n";

        testV = { "1", "2", "3", "4", "5", "6", "7" };
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( testV );
        TreeNode* nodeResult = connect_iterative( testData );
        // Use debugger to examine the result.
        cout << "Result of Populating Next Right Pointers in Each Node:";
        PrintTreeLevelOrder( nodeResult, true );
        DeleteTree( nodeResult );

        cout << "\n";

        //testV = { "1", "2", "3", "4", "5", "null", "7" };
        //testV = { "3", "9", "20", "null", "null", "15", "7" };
        testV = { "-1", "-7", "9", "null", "null", "-1", "-7", "null", "null", "null", "null", "null", "8", "-9" };
        testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( testV );
        nodeResult = connect_not_perfect( testData );
        cout << "Result of Populating Next Right Pointers in Each Node II:";
        // Use debugger to examine the result.
        PrintTreeLevelOrder( nodeResult, true );
        DeleteTree( nodeResult );
    }
}