#pragma once

#include <vector>
#include <string>

namespace LeetCodeUtil
{
    class TreeNode;
}

namespace TreesAndGraphs
{
    using namespace std;
    using namespace LeetCodeUtil;

    TreeNode* createTree_omit_missing_children( const vector<int>& aNodeArray );

    TreeNode* levelOrderCreateTree
        (
        vector<string>& arr
        );

    // 105. Construct Binary Tree from Preorder and Inorder Traversal (Medium).
    TreeNode* buildTree( vector<int>& preorder, vector<int>& inorder );

    // 106. Construct Binary Tree from Inorder and Postorder Traversal (Medium).
    TreeNode* buildTree_in_post( vector<int>& inorder, vector<int>& postorder );

    // 889. Construct Binary Tree from Preorder and Postorder Traversal (Medium).
    // If there exist multiple answers, you can return any of them.
    TreeNode* constructFromPrePost( vector<int>& preorder, vector<int>& postorder );

    // 1008. Construct Binary Search Tree from Preorder Traversal (Medium).
    TreeNode* bstFromPreorder( vector<int>& preorder );

    void test_buildTree();
}