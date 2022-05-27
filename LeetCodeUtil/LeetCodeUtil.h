#pragma once

#include <iostream>
#include <vector>

namespace LeetCodeUtil
{
	using namespace std;

	//-----------------------------------------------------------------------------------
	// Vector
	//-----------------------------------------------------------------------------------

	//! Print a vector (1D array)
	template<typename T>
	void PrintVector
		(
		const vector<T>& aInput
		)
	{
		cout << "[";
		for (int i = 0; i < aInput.size(); ++i)
		{
			cout << aInput[i];
			if (i != aInput.size() - 1)
			{
				cout << ",";
			}
		}
		cout << "]" << endl;
	}

	//! Print a matrix  (vector of vector, 2d array)
	template<typename T>
	void PrintMatrix
		(
		const vector<vector<T>>& aInput
		)
	{
		cout << "[";
		for (int i = 0; i < aInput.size(); ++i)
		{
			cout << "[";
			for (int j = 0; j < aInput[i].size(); ++j)
			{
				cout << aInput[i][j];

				if (j != aInput[i].size() - 1)
				{
					cout << ",";
				}
			}

			cout << "]";
			if (i != aInput.size() - 1)
			{
				cout << ",";
			}
		}
		cout << "]" << endl;
	}

	//! Build vector<char> from a string.
	void BuildCharVectorFromString(const string& data, vector<char>* result);

	//! Build a matrix consists of char from a string.
	void BuildCharMatrixFromString(const string& data, vector<vector<char>>* matrix);

	//! Build vector<int> from a string.
	void BuildIntVectorFromString(const string& data, vector<int>* result);

	//! Build a matrix consists of int from a string.
	void BuildIntMatrixFromString(const string& data, vector<vector<int>>* matrix);

	//-----------------------------------------------------------------------------------
	// Linked list
	//-----------------------------------------------------------------------------------

	//! Definition for singly-linked list.
	struct ListNode
	{
		bool deleteNext;
		int val;
		ListNode* next;
		ListNode() : val( 0 ), next( nullptr ), deleteNext( false )  {}
		ListNode( int x ) : val( x ), next( nullptr ), deleteNext( false ) {}
		ListNode( int x, ListNode* next ) : val( x ), next( next ), deleteNext( false ) {}

		~ListNode()
		{
			if( deleteNext && next )
			{
				delete next;
			}
		}
	};

	//! Print all elements in the linked list.
	//! Assume that T has "val" and "next" data members.
	template<typename T>
	void PrintListNode(T* aListNode)
	{
		while (aListNode)
		{
			cout << "Node( " << aListNode->val << " )";
			if (aListNode->next)
			{
				cout << " -> ";
			}
			aListNode = aListNode->next;
		}
		cout << endl;
	}

	//! Build a linked list from a vector of int.
	ListNode* BuildLinkedListFromVector(const vector<int>& aInput);

	//-----------------------------------------------------------------------------------
	// Tree
	//-----------------------------------------------------------------------------------

	//! Definition for a binary tree node.
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
		TreeNode* next;
		TreeNode* parent; // Used in 510. Inorder Successor in BST II.

        TreeNode() : val( 0 ), left( nullptr ), right( nullptr ), next( nullptr ), parent( nullptr ) {}
        TreeNode( int x ) : val( x ), left( nullptr ), right( nullptr ), next( nullptr ), parent( nullptr ) {}
        TreeNode( int x, TreeNode* left, TreeNode* right ) : val( x ), left( left ), right( right ), next( nullptr ), parent( nullptr ) {}
    };

	//! Build a tree from a vector of string, which represents each node of a tree in level order.
	TreeNode* BuildTreeFromLevelOrderStringVector(const vector<string>& aNodeArray);

	//! Build a tree from a string, which represent a tree in level order.
	TreeNode* BuildTreeFromLevelOrderString(const string& data);

	//! Print a tree in level order.
	void PrintTreeLevelOrder( TreeNode* aRoot, bool aPrintNext = false );

	//! Delete a tree, including all its children.
	void DeleteTree( TreeNode* root );

	//! Convert vector<string> to vector<char>.
	bool ConvertToVectorOfChar
		(
		const vector<string>& aInput,
		vector<char>& aOutput
		);
}