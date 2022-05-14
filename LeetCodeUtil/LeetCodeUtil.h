#pragma once

#include <iostream>
#include <vector>

namespace LeetCodeUtil
{
	using namespace std;

	/**
	 * Definition for singly-linked list.
	 */
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

	/**
	* Definition for a binary tree node.
	*/
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


	template<typename T>
	void printVector
		(
		const vector<T>& aInput
		)
	{
		cout << "[";
		for( int i = 0; i < aInput.size(); ++i )
		{
			cout << aInput[i];
			if( i != aInput.size() - 1 )
			{
				cout << ",";
			}
		}
		cout << "]" << endl;
	}

	template<typename T>
	void printVectorOfVector
		(
		const vector<vector<T>>& aInput
		)
	{
		cout << "[";
		for( int i = 0; i < aInput.size(); ++i )
		{
			cout << "[";
			for( int j = 0; j < aInput[i].size(); ++j )
			{
				cout << aInput[i][j];

				if( j != aInput[i].size() - 1 )
				{
					cout << ",";
				}
			}

			cout << "]";
			if( i != aInput.size() - 1 )
			{
				cout << ",";
			}
		}
		cout << "]" << endl;
	}

	void quickSort_std_async
		(
		vector<int>& aInput,
		int aBegin,
		int aEnd
		);

	// Assume that T has "val" and "next" data members.
	template<typename T>
	void printListNode( T* aListNode )
	{
		while( aListNode )
		{
			cout << "Node( " << aListNode->val << " )";
			if( aListNode->next )
			{
				cout << " -> ";
			}
			aListNode = aListNode->next;
		}
		cout << endl;
	}

	ListNode* buildLinkedListFromVector( const vector<int>& aInput );

	void printTreeLevelOrder( TreeNode* aRoot, bool aPrintNext = false );

	void DeleteTree( TreeNode* root );

	bool convertToVectorOfChar
		(
		const vector<string>& aInput,
		vector<char>& aOutput
		);
}