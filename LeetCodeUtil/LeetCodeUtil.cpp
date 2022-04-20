// LeetCodeUtil.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include "LeetCodeUtil.h"

namespace LeetCodeUtil
{
	using namespace std;

	void printVectorOfVector
		(
		const vector<vector<int>>& aInput
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

}