#include "TreesAndGraphs.h"

#include <stack>
#include <queue>

using namespace LeetCodeUtil;

namespace TreesAndGraphs
{
    // 94. Binary Tree Inorder Traversal (Easy).
    // Follow up: Recursive solution is trivial, could you do it iteratively?
    //
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

    // pre-order: 4213657
    // middle -> left -> right
    vector<int> preOrderTraversal( TreeNode* root )
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
    // Two ways to do this:
    // 1. Use two stacks. This method will not break the tree's structure.
    // 2. Push left/right node to stack and set left/right to nullptr of a node. If left/right are both nullptr, then visit the node.
    vector<int> postOrderTraversal( TreeNode* root )
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

    vector<int> levelOrderTraversal( TreeNode* root )
    {
        vector<int> result;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( root );

        while( !nodeQueue.empty() )
        {
            for( int i = 0; i < nodeQueue.size(); ++i )
            {
                TreeNode* cur = nodeQueue.front();
                result.push_back( cur->val );
                nodeQueue.pop();

                if( cur->left )
                {
                    nodeQueue.push( cur->left );
                }

                if( cur->right )
                {
                    nodeQueue.push( cur->right );
                }
            }
        }

        return result;
    }

    // 671. Second Minimum Node In a Binary Tree (Easy).
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
        TreeNode* testData = levelOrderCreateTree( testV );
        #endif

        vector<int> result = inorderTraversal( testData );

        // 1234567
        cout << "Result of inorderTraversal: ";
        printVector( result );
        cout << endl;

        result = preOrderTraversal( testData );

        // 4213657
        cout << "Result of preOrderTraversal: ";
        printVector( result );
        cout << endl;

        result = postOrderTraversal( testData );

        // 1325764
        cout << "Result of postOrderTraversal: ";
        printVector( result );
        cout << endl;

        result = levelOrderTraversal( testData );

        // 4261357
        cout << "Result of levelOrderTraversal: ";
        printVector( result );
        cout << endl;

        cleanUp( testData );

        //vector<string> specialTree = { "2", "2", "5", "null", "null", "5", "7" }; // 5
        //vector<string> specialTree = { "2", "2", "2" }; // -1
        vector<string> specialTree = { "1", "1", "2", "1", "1", "2", "2" }; // 2
        testData = levelOrderCreateTree( specialTree );
        int secondMinimum = findSecondMinimumValue( testData );
        cout << "Result of findSecondMinimumValue: " << secondMinimum << endl;
        cleanUp( testData );

        specialTree = { "1", "1", "3", "1", "1", "3", "4", "3", "1", "1", "1", "3", "8", "4", "8", "3", "3", "1", "6", "2", "1" };
        testData = levelOrderCreateTree( specialTree );
        secondMinimum = findSecondMinimumValue( testData );
        cout << "Result of findSecondMinimumValue: " << secondMinimum << endl; // 2
        cleanUp( testData );

        cout << "\n";
    }
}