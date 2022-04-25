#pragma once

#include <iostream>
#include <vector>

namespace LeetCodeUtil
{
	using namespace std;

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
}