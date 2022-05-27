#include "Others.h"
#include "LeetCodeUtil.h"

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <queue>

namespace Others
{
    using namespace std;

    //------------------------------------------------------------------------------------------------------------------------
    // 371. Sum of Two Integers
    //
    // Bit Manipulation is the only choice...
    //------------------------------------------------------------------------------------------------------------------------
    int getSum( int a, int b )
    {
        // To get A + B in decimal, we can ..
        // C = A' + B' ignoring carry.
        // D = ( A'' + B'' ) * 10  only considering carry.
        // A + B = C + D
        // For example, A = 15, B = 27. C will be 32. D will be 10. C + D = 42.

        // In binary world, this formula still works in similar way. The only difference is:
        // D = ( A'' + B'' ) * 2

        // Terminating condition of recursion.
        // Why b? It's because we use b as the carry part.
        if( b == 0 )
        {
            return a;
        }

        // To get C, we can use XOR.
        const int sumPart = a ^ b;
        // To get D, we can use AND.
        const int carryPart = a & b;

        // Some compiler won't allow left-shifting when the leading bit is 1, so we clear it manually.
        return getSum( sumPart, ( carryPart & 0x7fffffff ) << 1 );
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 150. Evaluate Reverse Polish Notation
    //
    // 1 <= tokens.length <= 10^4
    // Looks like a practice of stack or recursion
    // tokens seems long, let's use stack.
    //------------------------------------------------------------------------------------------------------------------------

    int evalRPN( vector<string>& tokens )
    {
        stack<int> operandStack;
        for( const auto& token : tokens )
        {
            if( token != "+" && token != "-" && token != "*" && token != "/" )
            {
                operandStack.push( std::stoi( token ) );
            }
            else
            {
                int operand1 = operandStack.top();
                operandStack.pop();
                int operand2 = operandStack.top();
                operandStack.pop();

                if( token == "+" )
                {
                    operandStack.push( operand1 + operand2 );
                }
                else if( token == "-" )
                {;
                    operandStack.push( operand2 - operand1 );
                }
                else if( token == "*" )
                {
                    operandStack.push( operand1 * operand2 );
                }
                else
                {
                    operandStack.push( operand2 / operand1 );
                }
            }
        }

        return operandStack.top();
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 169. Majority Element
    //
    // Follow-up: Could you solve the problem in linear time and in O(1) space?
    //
    // Using hash table can solve in O(n) time and space.
    // To achieve O(1) space, we have two options:
    // 1. Boyer�VMoore majority vote algorithm
    // 2. Bit manipulation - determine each bit of the result by checking whether there are more 1 than 0 in the same bit
    // among all numbers.
    //------------------------------------------------------------------------------------------------------------------------

    int majorityElement( vector<int>& nums )
    {
        int current = INT_MIN;
        int count = 0;

        for( const auto number : nums )
        {
            if( count == 0 )
            {
                current = number;
                count++;
            }
            else
            {
                if( current == number )
                {
                    count++;
                }
                else
                {
                    count--;
                }
            }
        }

        return current;
    }

    //------------------------------------------------------------------------------------------------------------------------
    // 621. Task Scheduler
    //
    // Use greedy or priority queue.
    //------------------------------------------------------------------------------------------------------------------------

    int leastInterval( vector<char>& tasks, int n )
    {
        unordered_map<char, size_t> countTable;
        // Accumulate the count of each tasks.
        for( char c : tasks )
        {
            countTable[c]++;
        }

        // The more tasks we need to do, the more high priority it is.
        // So, we can just put the number of remaining tasks into it.
        priority_queue<int> pQuque;
        for( auto& task : countTable )
        {
            pQuque.push( task.second );
        }

        // CPU can run n + 1 task in a cycle.
        const int cycleCapacity = n + 1;

        int totalTime = 0;
        // Take tasks out of priority queue and put them in one cycle.
        while( !pQuque.empty() )
        {
            int processedTasksCount = 0;
            vector<int> processedTasks;
            for( int i = 0; i < cycleCapacity; ++i )
            {
                if( !pQuque.empty() )
                {
                    processedTasks.push_back( pQuque.top() );
                    pQuque.pop();
                    processedTasksCount++;
                }
            }
            // We just consume one task, minus one and put the remaining back.
            for( auto p : processedTasks )
            {
                p--;
                if( p != 0 )
                {
                    pQuque.push( p );
                }
            }
            // Note that processedTasks might be smaller than cycleCapacity.
            // It means that we must idle. The idle intervals must be counted unless we have reached the end.
            totalTime += !pQuque.empty() ? cycleCapacity : processedTasksCount;
        }

        return totalTime;
    }


    //-----------------------------------------------------------------------------------
    // 277. Find the Celebrity
    //
    // Celebrity: Everyone knows it and it knows none.
    //
    // Follow up: If the maximum number of allowed calls to the API knows is 3 * n, could
    // you find a solution without exceeding the maximum number of calls?
    //
    // This is hard to test on my own.
    //-----------------------------------------------------------------------------------

    void test_others()
    {
        cout << "Result of Sum of Two Integers: " << getSum( 15, 27 ) << endl;

        vector<string> testStringArray = { "2","1","+","3","*" };

        cout << "Evaluate Reverse Polish Notation: " << evalRPN( testStringArray ) << endl;

        vector<int> testIntArray = { 4,4,1,1,1,4,4 };
        cout << "Result of Evaluate Majority Element: " << majorityElement( testIntArray ) << endl;

        // Input: tasks = ["A","A","A","B","B","B"], n = 2
        // Output: 8
       // vector<char> testCharArray = { 'A', 'A', 'A', 'B', 'B', 'B' };
        //int n = 2;
        // Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
        // Output: 16
        testStringArray = { "A","A","A","A","A","A","B","C","D","E","F","G" };
        vector<char> testCharArray;

        LeetCodeUtil::ConvertToVectorOfChar( testStringArray, testCharArray );
        int n = 2;
        cout << "Result of Task Scheduler: " << leastInterval( testCharArray, n ) << endl;

    }
}
