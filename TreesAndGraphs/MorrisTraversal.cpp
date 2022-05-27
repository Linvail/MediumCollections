//-------------------------------------------------------------------------------------------
// Using Morris Traversal, we can traverse the tree without using stack and recursion.
// The idea of Morris Traversal is based on Threaded Binary Tree. In this traversal,
// we first create links to Inorder successor and print the data using these links,
// and finally revert the changes to restore original tree.
//
// Inorder and preorder is easier. Postorder is more tricky.
//-------------------------------------------------------------------------------------------

#include "MorrisTraversal.h"
#include "LeetCodeUtil.h"
#include "BuildTree.h"

namespace TreesAndGraphs
{
    using namespace LeetCodeUtil;
    using namespace std;

    // The most crucial problem of this algorithm is how to go back to the root after visiting the left subtree.
    //
    // Define predecessor: The predecessor of root is the node being visited before root in inorder traversal.
    vector<int> morrisTraversal_inorder( TreeNode* root )
    {
        vector<int> result;
        TreeNode* current = root;

        while( current )
        {
            if( !current->left )
            {
                // Visit this node and move the right subtree.
                result.push_back( current->val );
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

                // First time meet this predecessor.
                if( !predecessor->right )
                {
                    // Set predecessor's right child to current node. It makes us go back to current node when visiting this predecessor node.
                    predecessor->right = current;
                    // Move the left child.
                    current = current->left;
                }
                else
                {
                    // This is the 2nd time we found this predecessor. It means that we just went back to 'current' again.
                    // All left nodes of 'current' have been visited, it is time to visit 'current'.
                    result.push_back( current->val );
                    // Revert the 'thread' we made to predecessor.
                    predecessor->right = nullptr;
                    // Since we visited the middle, time to move to right child.
                    current = current->right;
                }
            }
        }

        return result;
    }

    // The implementation is very similar to inorder's. There is only one line difference.
    vector<int> morrisTraversal_preorder( TreeNode* root )
    {
        vector<int> result;
        TreeNode* current = root;

        while( current )
        {
            if( !current->left )
            {
                // Visit this node and move the right subtree.
                result.push_back( current->val );
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

                // First time meet this predecessor.
                if( !predecessor->right )
                {
                    // This is the only the only difference with inorder-traversal.
                    result.push_back( current->val );

                    // Set predecessor's right child to current node. It makes us go back to current node when visiting this predecessor node.
                    predecessor->right = current;
                    // Move the left child.
                    current = current->left;
                }
                else
                {
                    predecessor->right = nullptr;
                    // Since we visited the middle, time to move to right child.
                    current = current->right;
                }
            }
        }

        return result;
    }

    void reverse_right( TreeNode* aFrom, TreeNode* aTo )
    {
        if( aFrom == aTo )
        {
            return;
        }

        TreeNode* pre = aFrom;
        TreeNode* cur = aFrom->right;

        while( true )
        {
            TreeNode* next = cur->right;
            cur->right = pre;

            if( cur == aTo )
            {
                break;
            }

            pre = cur;
            cur = next;
        }
    }

    // Complex the tricky.
    vector<int> morrisTraversal_postorder( TreeNode* root )
    {
        vector<int> result;
        // We need a dummy node and let root be the left child of this dummy.
        TreeNode dummy( 0 );
        dummy.left = root;

        TreeNode* current = &dummy;
        while( current )
        {
            if( !current->left )
            {
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

                // First time meet this predecessor.
                if( !predecessor->right )
                {
                    // Set predecessor's right child to current node. It makes us go back to current node when visiting this predecessor node.
                    predecessor->right = current;
                    // Move the left child.
                    current = current->left;
                }
                else
                {
                    // Most tricky part. We need to visit from predecessor to curent->left, which is in reverse order.
                    // Because the idea of Morris traversal is to only use O(1) space, we cannot use the technique - add to a temp vector and reverse it.
                    // We have to add one by one.
                    reverse_right( current->left, predecessor );

                    for( TreeNode* p = predecessor; ; p = p->right )
                    {
                        result.push_back( p->val );
                        if( p == current->left )
                        {
                            break;
                        }
                    }

                    // Rollback
                    reverse_right( predecessor, current->left );

                    // This is the 2nd time we found this predecessor. It means that we just went back to 'current' again.
                    // Revert the 'thread' we made to predecessor.
                    predecessor->right = nullptr;
                    // Since we visited the middle, time to move to right child.
                    current = current->right;
                }
            }
        }

        return result;
    }

    void test_morrisTraversal()
    {
        cout << "\ntest_morrisTraversal\n";
        /*
                4
             2     6
           1  3  5   7

        */
        vector<string> testV = { "4", "2", "6", "1", "3", "5", "7" };
        TreeNode* testData = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( testV );

        vector<int> result = morrisTraversal_inorder( testData );

        // 1234567
        cout << "Result of morrisTraversal_inorder: ";
        PrintVector( result );
        cout << endl;

        // 4213657
        result = morrisTraversal_preorder( testData );
        cout << "Result of morrisTraversal_preorder: ";
        PrintVector( result );
        cout << endl;

        // 1325764
        result = morrisTraversal_postorder( testData );
        cout << "Result of morrisTraversal_postorder: ";
        PrintVector( result );
        cout << endl;
    }
}