// LeetCodeUtil.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include <future>
#include <queue>
#include <string>

#include "LeetCodeUtil.h"

namespace LeetCodeUtil
{
    using namespace std;

    //! Insert aValue into aNums and keep ascending order.
    void insertAndSort( vector<int>& aNums, int aValue )
    {
        int i = 0;
        for( ; i < aNums.size(); ++i )
        {
            if( aNums[i] >= aValue )
            {
                aNums.insert( aNums.begin() + i, aValue );
                break;
            }
        }
        if( i == aNums.size() )
        {
            aNums.push_back( aValue );
        }
    }

    // It works like you pick a poker card from the table one by one, and sort them in hands.
    // We want to do in-place.
    void insertionSort( vector<int>& aInput )
    {
        for( int i = 1; i < aInput.size(); ++i )
        {
            int j = i;
            while( j > 0 && aInput[j] < aInput[j - 1] )
            {
                swap( aInput[j], aInput[j - 1] );
                j--;
            }
        }
    }

    //! Divide the input into two partitions, the left partition is less than the pivot,
    //! the right partition is greater than the pivot.
    //! Use Hoare partition scheme.
    //!
    //! @return The index of the last element on the smaller side.
    int partition_Hoare
        (
        vector<int>& aInput,
        int aBegin,
        int aEnd
        )
    {
        // Pick the pivot. There are many ways. Here we just pick the middle one.
        const size_t midIdx = aBegin + ( aEnd - aBegin ) / 2; // Equal to (aBegin + aEnd) / 2 but won't overflow when aBegin/aEnd are very very big.
        const int pivot = aInput[midIdx];

        // Note that they are out of bound.
        int i = aBegin - 1;
        int j = aEnd + 1;

        while( true )
        {
            do
            {
                i++;
            } while( aInput[i] < pivot );

            do
            {
                j--;
            } while( aInput[j] > pivot );

            if( i >= j )
            {
                // aInput[0 ~ j] are all less than pivot. aInput[j + 1 ~ aEnd] are all greater than pivot.
                return j;
            }

            swap( aInput[i], aInput[j] );
        }
    }

    //! Hoare is apparently faster than Lomuto, especially when there are many identical items.
    void quickSort_Hoare
        (
        vector<int>& aInput,
        int aBegin,
        int aEnd
        )
    {
        if( aBegin < aEnd )
        {
            int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

            quickSort_Hoare( aInput, aBegin, pivotIdx ); // Note that the pivot is included.
            quickSort_Hoare( aInput, pivotIdx + 1, aEnd );
        }
    }

    //! Based on quickSort_Hoare. When count is less than 8, just do the insertion sort.
    //! This is faster than quickSort_Hoare.
    void quickSort_with_insertionSort
        (
        vector<int>& aInput,
        int aBegin,
        int aEnd
        )
    {
        if( aBegin < aEnd )
        {
            if( aEnd - aBegin > 8 )
            {
                int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

                quickSort_Hoare( aInput, aBegin, pivotIdx ); // Note that the pivot is included.
                quickSort_Hoare( aInput, pivotIdx + 1, aEnd );
            }
            else
            {
                insertionSort( aInput );
            }
        }
    }

    //! Use std::async for the recursive calls.
    //! This is faster than all non-async functions.
    void quickSort_std_async
        (
        vector<int>& aInput,
        int aBegin,
        int aEnd
        )
    {
        if( aBegin < aEnd )
        {
            int pivotIdx = partition_Hoare( aInput, aBegin, aEnd );

            auto policy = std::launch::async;
            auto f1 = std::async( policy, [&aInput, aBegin, pivotIdx] { quickSort_with_insertionSort( aInput, aBegin, pivotIdx ); } );
            auto f2 = std::async( policy, [&aInput, pivotIdx, aEnd] { quickSort_with_insertionSort( aInput, pivotIdx + 1, aEnd ); } );
            f1.wait();
            f2.wait();
        }
    }

    ListNode* buildLinkedListFromVector( const vector<int>& aInput )
    {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        for( int i = 0; i < aInput.size(); ++i )
        {
            ListNode* newNode = new ListNode( aInput[i] );
            newNode->deleteNext = true;

            if( i == 0 )
            {
                head = newNode;
                tail = head;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }

        }

        return head;
    }

    void printTreeLevelOrder( TreeNode* aRoot, bool aPrintNext )
    {
        vector<string> dataToPrint;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( aRoot );

        while( !nodeQueue.empty() )
        {
            const int len = nodeQueue.size();

            for( int i = 0; i < len; ++i )
            {
                TreeNode* cur = nodeQueue.front();
                nodeQueue.pop();

                string data = cur ? to_string( cur->val ) : "null";
                dataToPrint.push_back( data );

                if( !cur )
                {
                    continue;
                }

                bool isLastNode = nodeQueue.size() == 0;
                bool isRoot = aRoot == cur;

                if( cur->left )
                {
                    nodeQueue.push( cur->left );
                }
                else if( !isLastNode || isRoot )
                {
                    nodeQueue.push( nullptr );
                }

                if( cur->right )
                {
                    nodeQueue.push( cur->right );
                }
                else if( !isLastNode || isRoot )
                {
                    nodeQueue.push( nullptr );
                }
            }

            if( aPrintNext )
            {
                dataToPrint.push_back( "#" );
            }
        }

        if( dataToPrint.size() > 1 && dataToPrint[dataToPrint.size() - 2] == "null" )
        {
            dataToPrint.pop_back(); // remove the last "#".
        }

        // Remove "null" in the tail.
        int removeIndex = dataToPrint.size();
        auto rit = dataToPrint.rbegin();
        for( ; rit != dataToPrint.rend(); ++rit )
        {
            if( *rit != "null" )
            {
                break;
            }
            removeIndex--;
        }
        dataToPrint.erase( dataToPrint.begin() + removeIndex, dataToPrint.end() );

        cout << "[";

        for( int i = 0; i < dataToPrint.size(); ++i )
        {
            cout << dataToPrint[i];

            if( i != dataToPrint.size() - 1 )
            {
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }

    void cleanUp( TreeNode* root )
    {
        if( root )
        {
            cleanUp( root->left );
            cleanUp( root->right );
        }
        delete root;
    }
}