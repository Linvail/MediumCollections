#include "LinkedList.h"
#include "LeetCodeUtil.h"

#include <iostream>

using namespace std;
using namespace LeetCodeUtil;

namespace LinkedList
{
    //-----------------------------------------------------------------------------------
    // 2. Add Two Numbers
    //-----------------------------------------------------------------------------------
    //
    // Need to consider the case that two list do not have the same length.
    ListNode* addTwoNumbers( ListNode* l1, ListNode* l2 )
    {
        ListNode* result = new ListNode( -1 ); // This should not change.
        ListNode* current = result; // Used to point to the last node.
        bool carry = false;
        while( l1 || l2 )
        {
            const int val1 = l1 ? l1->val : 0;
            const int val2 = l2 ? l2->val : 0;
            const int sum = val1 + val2 + ( carry ? 1 : 0 );
            carry = sum >= 10;

            current->next = new ListNode( carry ? sum - 10 : sum );
            current = current->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        if( carry )
        {
            current->next = new ListNode( 1 );
        }

        return result->next;
    }

    void test_addTwoNumbers()
    {
        cout << "\ntest_addTwoNumbers\n";

        // [2, 4, 3, 9]
        // [5, 6, 7]

        ListNode list1_n( 9 );
        ListNode list1_n3( 3, &list1_n );
        ListNode list1_n2( 4, &list1_n3 );
        ListNode list1_n1( 2, &list1_n2 );

        ListNode list2_n3( 7 );
        ListNode list2_n2( 6, &list2_n3 );
        ListNode list2_n1( 5, &list2_n2 );

        ListNode* result = addTwoNumbers( &list1_n1, &list2_n1 );
        PrintListNode( result );

        delete result;
    }
}