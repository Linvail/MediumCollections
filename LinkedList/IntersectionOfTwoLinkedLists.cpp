#include "LinkedList.h"
#include "LeetCodeUtil.h"

#include <iostream>

using namespace std;
using namespace LeetCodeUtil;

namespace LinkedList
{
    int getLength( ListNode* aRoot )
    {
        int len = 0;
        while( aRoot )
        {
            aRoot = aRoot->next;
            len++;
        }
        return len;
    }

    // Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?


    //! Method 1:
    //! Get the length of two linked lists.
    //! For the longer one, move forward by N steps, where N is the difference of their length.
    //! Then, for both lists, move forward until two nodes are the same (could be both null).
    ListNode* getIntersectionNode( ListNode* headA, ListNode* headB )
    {
        const int lenA = getLength( headA );
        const int lenB = getLength( headB );

        if( lenA > lenB )
        {
            for( int i = 0; i < lenA - lenB; ++i )
            {
                headA = headA->next;
            }
        }
        else
        {
            for( int i = 0; i < lenB - lenA; ++i )
            {
                headB = headB->next;
            }
        }

        while( headA != headB )
        {
            headA = headA->next;
            headB = headB->next;
        }

        return headA;
    }

    // Method 2: Tricky one
    // For each list, move forward until the end. After reach the end, jump to the head of other list.
    // Eventually, two ndoe will become the same, either the intersection or nullptr at the same.
    // It is because they both move m+n+1 steps.
    ListNode* getIntersectionNode_v2( ListNode* headA, ListNode* headB )
    {
        ListNode* a = headA;
        ListNode* b = headB;

        while( a != b )
        {
            // If headA and headB are not intersected, a will be nullptr (end of list B), b will
            // be nullptr (end of list A).
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }

        return a;
    }

    void test_getIntersectionNode()
    {
        // Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
        // Output: Intersected at '8'

        ListNode n5( 5 );
        ListNode n4( 4, &n5 );
        ListNode n8( 8, &n4 );

        ListNode n1_1( 1, &n8 );
        ListNode n1_2( 1, &n8 );

        ListNode n4_1( 4, &n1_1 );
        ListNode n6_2( 6, &n1_2 );

        ListNode n5_2( 5, &n6_2 );

        cout << "\nList A:";
        PrintListNode( &n4_1 );
        cout << "\nList B:";
        PrintListNode( &n5_2 );
        cout << endl;

        ListNode* result = nullptr;
        /*result = getIntersectionNode(&n4_1, &n5_2);

        cout << "Result of getIntersectionNode:";
        PrintListNode( result );
        cout << endl;*/

        result = getIntersectionNode_v2( &n4_1, &n5_2 );

        cout << "Result of getIntersectionNode_v2:";
        PrintListNode( result );
        cout << endl;
    }
}