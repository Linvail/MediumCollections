#include "LinkedList.h"
#include "LeetCodeUtil.h"

#include <iostream>

using namespace std;
using namespace LeetCodeUtil;

namespace LinkedList
{
    /*
    Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.
    The first node is considered odd, and the second node is even, and so on.
    Note that the relative order inside both the even and odd groups should remain as it was in the input.
    You must solve the problem in O(1) extra space complexity and O(n) time complexity.

    Input: head = [2,1,3,5,6,4,7]
    Output: [2,3,6,7,1,5,4]
    */
    ListNode* oddEvenList( ListNode* head )
    {
        if( !head || !head->next || !head->next->next )
        {
            return head;
        }

        ListNode* headOfEven = nullptr;
        ListNode* tailOfEven = nullptr;
        ListNode* tailOfOdd = head;
        ListNode* current = head;

        ListNode* prev = current;
        // Move to next.
        current = current->next;
        bool even = true;

        while( current )
        {
            if( even )
            {
                // Prcoess the previous node.
                prev->next = current->next;

                if( !headOfEven )
                {
                    headOfEven = current;
                }
                else
                {
                    tailOfEven->next = current;
                }
                tailOfEven = current;
            }
            else
            {
                tailOfOdd = tailOfOdd->next;
            }

            prev = current;
            current = current->next;
            even = !even;
        }

        tailOfEven->next = nullptr;
        tailOfOdd->next = headOfEven;

        return head;
    }

    // Similiar to oddEvenList but uses less local variables.
    ListNode* oddEvenList_v2( ListNode* head )
    {
        if( !head || !head->next || !head->next->next )
        {
            return head;
        }

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* headOfEven = even;

        // 1 2 3 4
        while( even && even->next )
        {
            odd->next = even->next;
            odd = odd->next; // Keep odd point to the tail of odd list.

            even->next = odd->next;
            even = even->next; // Keep even point to the tail of even list.
        }
        // Connect odd and even list.
        odd->next = headOfEven;

        return head;
    }

    // This is more complicated.
    // 1     2     3     4     5     6     7
    // pre  cur
    //      tmp
    // 1 -> 3
    //       2 ->  4
    // 1 -> 3 -> tmp(2)
    //            pre
    //                  cur
    ListNode* oddEvenList_v3( ListNode* head )
    {
        if( !head || !head->next || !head->next->next )
        {
            return head;
        }

        ListNode* pre = head; // Point to the odd. pre always stays on odd node.
        ListNode* current = head->next; // Point to the even. even always stays on even node.

        while( current && current->next )
        {
            // We try to keep pre->next be the head of even list. This is the key of this algorithm.
            ListNode* temp = pre->next; // temp is the previous even node. In the 1st round, it is 2.

            pre->next = current->next; // pre connects to next odd node.
            current->next = current->next->next; // current connects to the next even node.

            pre->next->next = temp; // Establish the link between odd and even list.

            pre = pre->next; // jumps to next one.
            current = current->next; // jumps to next one.
        }

        return head;
    }

    void test_oddEvenList()
    {
        cout << "\ntest_oddEvenList\n";

        ListNode* result = nullptr;

        ListNode nn1( 2 );
        ListNode nn2( 1, &nn1 );
        PrintListNode( &nn2 );

        result = oddEvenList_v3( &nn2 );
        cout << "Result: " << endl;
        PrintListNode( result );

        ListNode n1( 7 );
        ListNode n2( 4, &n1 );
        ListNode n3( 6, &n2 );
        ListNode n4( 5, &n3 );
        ListNode n5( 3, &n4 );
        ListNode n6( 1, &n5 );
        ListNode n7( 2, &n6 );

        PrintListNode( &n7 );

        result = oddEvenList_v3( &n7 );
        cout << "Result: " << endl;
        PrintListNode( result );

        vector<int> testData = { 1, 2, 3, 4, 5, 6, 7, 8 };
        ListNode* newList = BuildLinkedListFromVector( testData );
        PrintListNode( newList );
        result = oddEvenList_v3( newList );
        cout << "Result: " << endl;
        PrintListNode( result );

        delete newList;
    }
}