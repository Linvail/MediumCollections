#include "BuildTree.h"
#include "LeetCodeUtil.h"

#include <string>
#include <unordered_map>

namespace TreesAndGraphs
{
    using namespace std;

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

    //-----------------------------------------------------------------------------------------------------------------------
    // 105. Construct Binary Tree from Preorder and Inorder Traversal (Medium).
    //-----------------------------------------------------------------------------------------------------------------------

    unordered_map<int, int> mInorderIndex;

    TreeNode* buildTree_helper
        (
        const vector<int>& preorder,
        const int pLeft,
        const int pRight,
        const vector<int>& inorder,
        const int iLeft,
        const int iRight
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

        newRoot->left = buildTree_helper
            (
            preorder,
            pLeft + 1,
            pLeft + i - iLeft, // i - iLeft is the count of the left tree. We know this from inorder.
            inorder,
            iLeft,
            i - 1
            );


        newRoot->right = buildTree_helper
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
        // This make us able to find the root in inorder.
        for( int i = 0; i < inorder.size(); ++i )
        {
            mInorderIndex[inorder[i]] = i;
        }

        return buildTree_helper( preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1 );
    }

    //-----------------------------------------------------------------------------------------------------------------------
    // 106. Construct Binary Tree from Inorder and Postorder Traversal (Medium).
    //-----------------------------------------------------------------------------------------------------------------------

    TreeNode* buildTree_in_post_helper
        (
        vector<int>& inorder,
        int iLeft,
        int iRight,
        vector<int>& postorder,
        int pLeft,
        int pRight
        )
    {
        if( pLeft > pRight || iLeft > iRight )
        {
            return nullptr;
        }

        // The last node in postorder must be the root.
        // Find the root in inorder.
        int i = mInorderIndex[postorder[pRight]];

        TreeNode* newRoot = new TreeNode( postorder[pRight] );

        newRoot->left = buildTree_in_post_helper( inorder, iLeft, i - 1, postorder, pLeft, pLeft + i - iLeft - 1 );
        newRoot->right = buildTree_in_post_helper( inorder, i + 1, iRight, postorder, pLeft + i - iLeft, pRight - 1 );

        return newRoot;
    }

    TreeNode* buildTree_in_post( vector<int>& inorder, vector<int>& postorder )
    {
        for( int i = 0; i < inorder.size(); ++i )
        {
            mInorderIndex[inorder[i]] = i;
        }

        return buildTree_in_post_helper( inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1 );
    }

    //-----------------------------------------------------------------------------------------------------------------------
    // 889. Construct Binary Tree from Preorder and Postorder Traversal (Medium).
    // If there exist multiple answers, you can return any of them.
    //-----------------------------------------------------------------------------------------------------------------------

    unordered_map<int, int> mPostorderIndex;

    TreeNode* constructFromPrePost_helper
        (
        const vector<int>& preorder,
        const int prLeft,
        const int prRight,
        const vector<int>& postorder,
        const int poLeft,
        const int poRight
        )
    {
        // preorder -> [root] [left subtree] [right subtree]
        // postorder ->[left subtree][right substree][root]
        // preorder -> [1] [2, 4, 5] [3, 6, 7]
        // postorder ->[4, 5, 2][6, 7, 3][1]
        if( prLeft > prRight || poLeft > poRight )
        {
            return nullptr;
        }

        TreeNode* newRoot = new TreeNode( preorder[prLeft] );

        if( prRight != prLeft ) // We are build the same tree, if prLeft == prRight, this tree must only has root node.
        {
            // Construct the left subtree.
            // Now, locate '2' in postorder.
            int leftRootIdx = mPostorderIndex[preorder[prLeft + 1]];
            // With the index, we can get the number of the nodes in left subtree.
            int count = leftRootIdx - poLeft + 1;
            // With the count, we can get the right boundary of left subtree in preorder.
            newRoot->left = constructFromPrePost_helper
                (
                preorder,
                prLeft + 1,
                prLeft + count,
                postorder,
                poLeft,
                leftRootIdx
                );

            newRoot->right = constructFromPrePost_helper
                (
                preorder,
                prLeft + count + 1,
                prRight,
                postorder,
                leftRootIdx + 1,
                poRight - 1
                );
        }

        return newRoot;
    }

    TreeNode* constructFromPrePost( vector<int>& preorder, vector<int>& postorder )
    {
        for( int i = 0; i < postorder.size(); ++i )
        {
            mPostorderIndex[postorder[i]] = i;
        }

        return constructFromPrePost_helper( preorder, 0, preorder.size() - 1, postorder, 0, postorder.size() - 1 );
    }

    //-----------------------------------------------------------------------------------------------------------------------
    // 1008. Construct Binary Search Tree from Preorder Traversal (Medium).
    //-----------------------------------------------------------------------------------------------------------------------

    TreeNode* bstFromPreorder_helper
        (
        const vector<int>& preorder,
        const int aLeft,
        const int aRight
        )
    {
        if( aLeft > aRight )
        {
            return nullptr;
        }

        TreeNode* newRoot = new TreeNode( preorder[aLeft] );

        int i = aLeft + 1;
        for( ; i <= aRight; ++i )
        {
            if( preorder[i] > preorder[aLeft] )
            {
                break;
            }
        }

        newRoot->left = bstFromPreorder_helper( preorder, aLeft + 1, i - 1 );
        newRoot->right = bstFromPreorder_helper( preorder, i, aRight );

        return newRoot;
    }

    // Input: preorder = [8,5,1,7,10,12]
    // Output: [8, 5, 10, 1, 7, null, 12]
    TreeNode* bstFromPreorder( vector<int>& preorder )
    {
        return bstFromPreorder_helper( preorder, 0, preorder.size() - 1 );
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
        mInorderIndex.clear();

        // Input: inorder = [9, 3, 15, 20, 7], postorder = [9, 15, 7, 20, 3]
        // Output : [3, 9, 20, null, null, 15, 7]
        vector<int> postorder = { 9, 15, 7, 20, 3 };
        result = buildTree_in_post( inorder, postorder );

        cout << "Result of Construct Binary Tree from Inorder and Postorder Traversal:" << endl;
        printTreeLevelOrder( result );
        cleanUp( result );

        // 889. Construct Binary Tree from Preorder and Postorder Traversal
        // Input: preorder = [1, 2, 4, 5, 3, 6, 7], postorder = [4, 5, 2, 6, 7, 3, 1]
        // Output : [1, 2, 3, 4, 5, 6, 7]
        vector<int> preorder = { 1, 2, 4, 5, 3, 6, 7 };
        postorder = { 4, 5, 2, 6, 7, 3, 1 };
        result = constructFromPrePost( preorder, postorder );
        cout << "Construct Binary Tree from Preorder and Postorder Traversal:" << endl;
        printTreeLevelOrder( result );
        cleanUp( result );

        // Input: preorder = [8,5,1,7,10,12]
        // Output: [8, 5, 10, 1, 7, null, 12]
        preorder = { 8, 5, 1, 7, 10, 12 };
        result = bstFromPreorder( preorder );
        cout << "Construct Binary Search Tree from Preorder Traversal:" << endl;
        printTreeLevelOrder( result );
        cleanUp( result );

        cout << endl;
    }
}