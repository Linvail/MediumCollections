#include "TreesAndGraphs.h"
#include "BuildTree.h"
#include "LeetCodeUtil.h"

#include <stack>
#include <string>

namespace TreesAndGraphs
{
    using namespace std;

    //------------------------------------------------------------------------------------------------------------------------
    // 285. Inorder Successor in BST
    //
    // Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST.
    // If the given node has no in-order successor in the tree, return null.
    // The successor of a node p is the node with the smallest key greater than p.val.
    //
    // Let's try two solutions:
    // 1. Just do inorder travseral to find the successor.
    // 2. Take advantage of the properites of BST. Move the root to detect the successor.
    //------------------------------------------------------------------------------------------------------------------------

    TreeNode* inorderSuccessor( TreeNode* root, TreeNode* p )
    {
        stack<TreeNode*> nodeStack;
        TreeNode* current = root;
        bool visited = false;

        while( current || !nodeStack.empty() )
        {
            while( current )
            {
                nodeStack.push( current );
                current = current->left;
            }

            // Visit the node in the top of stack.
            current = nodeStack.top();
            nodeStack.pop();

            if( visited )
            {
                return current;
            }
            else if( current->val == p->val )
            {
                visited = true;
            }

            current = current->right;
        }

        return nullptr;
    }

    TreeNode* inorderSuccessor_BST( TreeNode* root, TreeNode* p )
    {
        TreeNode* result = nullptr;
        while( root )
        {
            // If p is equal to or greater than the root, the successor must be the right subtree.
            if( p->val >= root->val )
            {
                root = root->right;
            }
            else // p must be in the left subtree.
            {

                // The cuurent root is the in-order successor of the left subtree.
                result = root;
                root = root->left;
            }
        }

        return result;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 510. Inorder Successor in BST II
    //
    // You will have direct access to the node but not to the root of the tree. Each node will have a reference to its parent node.
    //
    // Follow up: Could you solve it without looking up any of the node's values?
    //------------------------------------------------------------------------------------------------------------------------

    // The crucial property is that if a node has right node, its in-order successor must be in the right tree (the smallest node in the subtree).
    // If a node doesn't has right node, its in-order successor be in the ancestors (first greater ancestor).
    TreeNode* inorderSuccessor( TreeNode* node )
    {
        if( !node )
        {
            return nullptr;
        }

        if( node->right )
        {
            // Find the the smallest node in the right subtree
            node = node->right;
            while( node && node->left )
            {
                node = node->left;
            }
            return node;
        }
        else
        {
            // Noving node to find the first greater ancestor
            while( node )
            {
                if( !node->parent )
                {
                    return nullptr;
                }

                // Check if this node is its parent's left child.
                // If yes, the parent is greater than this node.
                if( node->parent->left == node )
                {
                    return node->parent;
                }
                else
                {
                    node = node->parent;
                }
            }
        }

        return nullptr;
    }

    void test_inorderSuccessor()
    {
        cout << "\n";
        // Input: root = [2,1,3], p = 1
        // Output: 2
        vector<string> nodeVector = { "2", "1", "3" };
        TreeNode* root = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( nodeVector );
        TreeNode* p = root->left;
        TreeNode* result = inorderSuccessor_BST( root, p );
        cout << "Result of Inorder Successor in BST: " << ( ( result != nullptr ) ? to_string( result->val ) : string( "null" ) ) << endl;
        DeleteTree( root );

        // Input: root = [5,3,6,2,4,null,null,1], p = 6
        // Output: null
        nodeVector = { "5", "3", "6", "2", "4", "null", "null", "1" };
        root = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( nodeVector );
        p = root->right;
        result = inorderSuccessor_BST( root, p );
        cout << "Result of Inorder Successor in BST: " << ( ( result != nullptr ) ? to_string( result->val ) : string( "null" ) ) << endl;
        DeleteTree( root );

        nodeVector = { "2", "1", "3" };
        root = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( nodeVector );
        p = root->left;
        result = inorderSuccessor( p );
        cout << "Result of Inorder Successor in BST II: " << ( ( result != nullptr ) ? to_string( result->val ) : string( "null" ) ) << endl;
        DeleteTree( root );

        nodeVector = { "5", "3", "6", "2", "4", "null", "null", "1" };
        root = LeetCodeUtil::BuildTreeFromLevelOrderStringVector( nodeVector );
        p = root->right;
        result = inorderSuccessor( root, p );
        cout << "Result of Inorder Successor in BST: " << ( ( result != nullptr ) ? to_string( result->val ) : string( "null" ) ) << endl;
        DeleteTree( root );
    }
}