#pragma once

#include <vector>

namespace LeetCodeUtil
{
    class TreeNode;
}

namespace TreesAndGraphs
{
    std::vector<int> morrisTraversal_inorder( LeetCodeUtil::TreeNode* root );

    std::vector<int> morrisTraversal_preorder( LeetCodeUtil::TreeNode* root );

    std::vector<int> morrisTraversal_postorder( LeetCodeUtil::TreeNode* root );

    void test_morrisTraversal();
}