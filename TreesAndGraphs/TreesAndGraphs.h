#pragma once

#include "LeetCodeUtil.h"
#include "BuildTree.h"

#include <vector>

using namespace std;
using namespace LeetCodeUtil;

namespace TreesAndGraphs
{
    // 94. Binary Tree Inorder Traversal (Easy).
    vector<int> inorderTraversal( TreeNode* root );

    // 671. Second Minimum Node In a Binary Tree (Easy).
    int findSecondMinimumValue( TreeNode* root );

    // 230. Kth Smallest Element in a BST (Medium).
    int kthSmallest( TreeNode* root, int k );

    void test_kthSmallest();

    void test_traversal();
}