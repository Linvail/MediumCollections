#include "BuildTree.h"

#include <string>
#include <unordered_map>

using namespace std;

namespace TreesAndGraphs
{
    // { "4", "null", "6", "5", "7" };
    // { "4", "2", "6", "1", "3", "5", "7" };
    void createTree_omit_missing_children( TreeNode* node, size_t level, vector<string>& arr )
    {
        if( node != nullptr )
        {
            const size_t leftIndex = level * 2 + 1;
            const size_t rightIndex = leftIndex + 1;

            if( leftIndex < arr.size() )
            {
                node->left = arr[leftIndex] == "null" ? nullptr : new TreeNode( stoi( arr[leftIndex] ) );
            }

            if( rightIndex < arr.size() )
            {
                node->right = arr[rightIndex] == "null" ? nullptr : new TreeNode( stoi( arr[rightIndex] ) );
            }

            if( node->left )
            {
                createTree_omit_missing_children( node->left, leftIndex, arr );
            }
            if( node->right )
            {
                createTree_omit_missing_children(
                    node->right,
                    node->left ? rightIndex : rightIndex - 1,
                    arr );
            }

        }
    }

    void createTree( TreeNode* node, int i, vector<string>& arr )
    {
        if( node != nullptr )
        {
            if( 2 * i + 1 < arr.size() )
            {
                node->left = arr[2 * i + 1] == "null" ? nullptr : new TreeNode( stoi( arr[2 * i + 1] ) );
                createTree( node->left, 2 * i + 1, arr );
            }

            if( 2 * i + 2 < arr.size() )
            {
                node->right = arr[2 * i + 2] == "null" ? nullptr : new TreeNode( stoi( arr[2 * i + 2] ) );
                createTree( node->right, 2 * i + 2, arr );
            }
        }
    }

    //! Create a tree from level-order arrangement vector.
    TreeNode* levelOrderCreateTree
        (
        vector<string>& arr,
        bool aOmitMissingChildren
        )
    {
        if( arr.size() == 0 )
        {
            return nullptr;
        }

        TreeNode* head = new TreeNode( stoi( arr[0] ) );
        if( aOmitMissingChildren )
        {
            createTree_omit_missing_children( head, 0, arr );
        }
        else
        {
            createTree( head, 0, arr );
        }

        return head;
    }

    // Having preorder and postorder is not enough to build one unique binary tree.
    // We must have inorder.

    /****************************************************************
        1¡@¡@¡@¡@¡@¡@preorder:¡@¡@  1¡@¡@2¡@¡@3
       / \¡@¡@¡@¡@¡@ inorder:¡@     2¡@¡@1¡@¡@3
     2    3¡@¡@  ¡@ postorder:¡@¡@ 2¡@¡@3¡@¡@1



           1   ¡@¡@¡@¡@preorder:¡@¡@   1¡@¡@2¡@¡@3
          / ¡@¡@¡@¡@¡@ inorder:¡@¡@    3¡@¡@2¡@¡@1
        2 ¡@¡@¡@¡@     postorder: ¡@¡@3¡@¡@2¡@¡@1
       /
     3



       1¡@¡@¡@¡@    preorder:¡@¡@  1¡@¡@2¡@¡@3
      / ¡@¡@¡@¡@¡@  inorder:¡@¡@   2¡@¡@3¡@¡@1
    2 ¡@¡@¡@¡@¡@¡@  postorder:¡@¡@3¡@¡@2¡@¡@1
      \
       3



       1¡@¡@¡@¡@     preorder:¡@  1¡@¡@2¡@¡@3
         \ ¡@¡@¡@¡@  inorder:¡@    1¡@¡@3¡@¡@2
          2 ¡@¡@¡@¡@ postorder:¡@¡@3¡@¡@2¡@¡@1
         /
       3


       1¡@¡@¡@¡@     preorder:¡@   1¡@¡@2¡@¡@3
         \ ¡@¡@¡@¡@¡@inorder:¡@    1¡@¡@2¡@¡@3
          2 ¡@¡@¡@¡@ postorder:¡@¡@3¡@¡@2¡@¡@1
            \
¡@¡@¡@¡@		 3
    ******************************************************************/

    unordered_map<int, int> mInorderIndex;

    // Helper function for buildTree-105.
    TreeNode* buildTree
        (
        vector<int>& preorder,
        int pLeft,
        int pRight,
        vector<int>& inorder,
        int iLeft,
        int iRight
        )
    {
        if( pLeft > pRight || iLeft > iRight )
        {
            return nullptr;
        }

        // The first node in preorder must be the root.
        // Find the root in inorder.
        int i = mInorderIndex[preorder[pLeft]];

        TreeNode* newRoot = new TreeNode( preorder[pLeft] );

        newRoot->left = buildTree
            (
            preorder,
            pLeft + 1,
            pLeft + i - iLeft, // i - iLeft is the count of the left tree. We know this from inorder.
            inorder,
            iLeft, i - 1
            );


        newRoot->right = buildTree
            (
            preorder,
            pLeft + i - iLeft + 1,
            pRight,
            inorder,
            i + 1,
            iRight
            );

        return newRoot;
    }

    // 105. Construct Binary Tree from Preorder and Inorder Traversal (Medium).
    TreeNode* buildTree( vector<int>& preorder, vector<int>& inorder )
    {
        for( int i = 0; i < inorder.size(); ++i )
        {
            mInorderIndex[inorder[i]] = i;
        }

        return buildTree( preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1 );
    }

    TreeNode* buildTree_in_post( vector<int>& inorder, vector<int>& postorder )
    {
        return nullptr;
    }

    void test_buildTree()
    {
        cout << "\ntest_buildTree\n";
        /*
        *            3
        *           / \
        *          9  20
        *            /  \
        *           15   7
        */
        // Input: preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
        // Output : [3, 9, 20, null, null, 15, 7]

        vector<int> preoder = { 3, 9, 20, 15, 7 };
        vector<int> inorder = { 9, 3, 15, 20, 7 };

        TreeNode* result = buildTree( preoder, inorder );

        cout << "Result of Construct Binary Tree from Preorder and Inorder Traversal:" << endl;
        printTreeLevelOrder( result );
        cleanUp( result );


        // Input: inorder = [9, 3, 15, 20, 7], postorder = [9, 15, 7, 20, 3]
        // Output : [3, 9, 20, null, null, 15, 7]
        vector<int> postorder = { 9, 15, 7, 20, 3 };
        result = buildTree( inorder, postorder );

        cout << "Result of Construct Binary Tree from Inorder and Postorder Traversal:" << endl;
        printTreeLevelOrder( result );
        cleanUp( result );

        cout << endl;
    }
}