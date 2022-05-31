// TreesAndGraphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TreesAndGraphs.h"

int main()
{
    std::cout << "TreesAndGraphs\n";

	using namespace TreesAndGraphs;

    test_buildTree();

    test_traversal();

    test_kthSmallest();

    test_matrix_traversal();

    test_inorderSuccessor();

    TestGraphs();
}
