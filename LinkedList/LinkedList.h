#pragma once

#include "LeetCodeUtil.h"

namespace LinkedList
{
    using namespace LeetCodeUtil;

    //           head
    //            1 -> 2 -> 3 -> nullptr
    // nullptr < -1 < -2 < -3
    //                    head
    inline ListNode* reverseList( ListNode* aList )
    {
        ListNode* prev = nullptr;

        while( aList )
        {
            ListNode* originalNext = aList->next;
            aList->next = prev;

            prev = aList;
            aList = originalNext;
        }

        return prev;
    }

    // 2. Add Two Numbers
    ListNode* addTwoNumbers( ListNode* l1, ListNode* l2 );

    void test_addTwoNumbers();

    // 328. Odd Even Linked List
    ListNode* oddEvenList( ListNode* head );

    void test_oddEvenList();

    // 160. Intersection of Two Linked Lists (Easy)
    ListNode* getIntersectionNode( ListNode* headA, ListNode* headB );

    void test_getIntersectionNode();
}