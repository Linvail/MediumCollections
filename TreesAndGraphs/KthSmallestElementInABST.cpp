#include "TreesAndGraphs.h"

#include <stack>

namespace TreesAndGraphs
{
    // 230. Kth Smallest Element in a BST (Medium).
    //
    // The straightforward method is to use inorder traversal becasue it gives us the list in ascending order.
    // We just need to stop when we get the kth element.
    //
    // Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
    // Extend the structure of TreeNode. We need a data member to record the count of nodes of a subtree (including all subtrees and root).
    // Compare k and the count, then we know which subtree we should look into.

    int kthSmallest( TreeNode* root, int k )
    {
        int result = 0;
        TreeNode* current = root;
        stack<TreeNode*> nodeStack;

        while( current || !nodeStack.empty() )
        {
            if( current )
            {
                nodeStack.push( current );
                current = current->left;
            }
            else
            {
                k--;
                if( k == 0 )
                {
                    result = nodeStack.top()->val;
                    break;
                }

                current = nodeStack.top()->right;
                nodeStack.pop();
            }
        }

        return result;
    }

    int kthSmallest_recursive_helper( TreeNode* root, int& k )
    {
        if( !root )
        {
            return -1;
        }

        int ret = kthSmallest_recursive_helper( root->left, k );
        if( k == 0 )
        {
            return ret;
        }

        // Visit this node.
        k--;
        if( k == 0 )
        {
            return root->val;
        }

        return kthSmallest_recursive_helper( root->right, k );

    }

    int kthSmallest_recursive( TreeNode* root, int k )
    {
        return kthSmallest_recursive_helper( root, k );
    }

    void test_kthSmallest()
    {
        cout << "\ntest_kthSmallest\n";

        // Input: root = [5,3,6,2,4,null,null,1], k = 3
        // Output: 3
        vector<string> testV = { "5", "3", "6", "2", "4", "null", "null", "1" };
        TreeNode* testData = levelOrderCreateTree( testV );

        cout << "Result of kthSmallest: " << kthSmallest_recursive( testData, 3 ) << endl;
    }
}