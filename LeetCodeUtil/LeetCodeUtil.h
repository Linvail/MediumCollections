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
}