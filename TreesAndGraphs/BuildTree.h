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

    void createTree_omit_missing_children( TreeNode* node, size_t level, vector<string>& arr );

    TreeNode* levelOrderCreateTree
        (
        vector<string>& arr,
        //! true if we allow not to put two "null" in the arr when its parent is null.
        //! For example, if true, we accept [1,null,2,3], if false, it must be provided as [1,null,2,null,null,3].
        bool aOmitMissingChildren = false
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