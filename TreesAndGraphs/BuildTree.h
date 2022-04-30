#pragma once

#include "LeetCodeUtil.h"

#include <vector>

using namespace std;
using namespace LeetCodeUtil;

namespace TreesAndGraphs
{
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

    void test_buildTree();
}