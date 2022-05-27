// LeetCodeUtil.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include <future>
#include <queue>
#include <string>
#include <sstream>

#include "LeetCodeUtil.h"

namespace LeetCodeUtil
{
    using namespace std;

    void BuildCharVectorFromString(const string& data, vector<char>* result)
    {
        if (!result)
        {
            return;
        }

        string raw = data.substr(1, data.size() - 2);
        istringstream is(raw);
        string sub;
        while (getline(is, sub, ','))
        {
            while (sub[0] == ' ')
            {
                sub = sub.substr(1, sub.size() - 1);
            }
            while (sub[sub.size() - 1] == ' ')
            {
                sub.pop_back();
            }
            result->push_back(sub.back());
        }
    }

    void BuildCharMatrixFromString(const string& data, vector<vector<char>>* matrix)
    {
        if (!matrix)
        {
            return;
        }

        matrix->clear();

        string raw = data.substr(1, data.size() - 2);
        istringstream is(raw);
        string sub;
        while (getline(is, sub, ']'))
        {
            while (sub.front() == ' ' || sub.front() == ',')
            {
                sub.erase(0, 1);
            }
            while (sub.back() == ' ')
            {
                sub.pop_back();
            }
            sub.push_back(']');

            vector<char> row;
            BuildCharVectorFromString(sub, &row);
            matrix->push_back(row);
        }
    }

    // Input: [1, 2], or [1,2,3]
    // Output: vector<int> with content 1, 2.
    void BuildIntVectorFromString(const string& data, vector<int>* result)
    {
        if (!result)
        {
            return;
        }

        string raw = data.substr(1, data.size() - 2);
        istringstream is(raw);
        string sub;
        while (getline(is, sub, ','))
        {
            while (sub[0] == ' ')
            {
                sub = sub.substr(1, sub.size() - 1);
            }
            while (sub[sub.size() - 1] == ' ')
            {
                sub.pop_back();
            }
            result->push_back(stoi(sub));
        }
    }

    // Input: [[0,0],[2,0],[1,1],[2,1],[2,2]]
    // vector<vector<int>>
    void BuildIntMatrixFromString(const string& data, vector<vector<int>>* matrix)
    {
        if (!matrix)
        {
            return;
        }

        matrix->clear();

        string raw = data.substr(1, data.size() - 2);
        istringstream is(raw);
        string sub;
        while (getline(is, sub, ']'))
        {
            while (sub.front() == ' ' || sub.front() == ',')
            {
                sub.erase(0, 1);
            }
            while (sub.back() == ' ')
            {
                sub.pop_back();
            }
            sub.push_back(']');

            vector<int> row;
            BuildIntVectorFromString(sub, &row);
            matrix->push_back(row);
        }
    }

    ListNode* BuildLinkedListFromVector(const vector<int>& aInput)
    {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        for (int i = 0; i < aInput.size(); ++i)
        {
            ListNode* newNode = new ListNode(aInput[i]);
            newNode->deleteNext = true;

            if (i == 0)
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

    TreeNode* BuildTreeFromLevelOrderStringVector
        (
        const vector<string>& aNodeArray
        )
    {
        TreeNode* root = new TreeNode(stoi(aNodeArray[0]));
        int start = 1;

        vector<TreeNode*> prevLevel;
        prevLevel.push_back(root);

        while (!prevLevel.empty() && start < aNodeArray.size())
        {
            vector<TreeNode*> thisLevel;
            for (auto node : prevLevel)
            {
                if (aNodeArray[start] != "null")
                {
                    node->left = new TreeNode(stoi(aNodeArray[start]));
                    thisLevel.push_back(node->left);
                }
                start++;
                if (start >= aNodeArray.size())
                {
                    break;
                }

                if (aNodeArray[start] != "null")
                {
                    node->right = new TreeNode(stoi(aNodeArray[start]));
                    thisLevel.push_back(node->right);
                }
                start++;

                if (start >= aNodeArray.size())
                {
                    break;
                }
            }
            swap(prevLevel, thisLevel);
        }

        return root;
    }

    TreeNode* BuildTreeFromLevelOrderString(const string& data)
    {
        if (data.empty() || data[0] != '[' || data.back() != ']' || data.length() < 3)
        {
            return nullptr;
        }

        size_t start = 1;
        size_t end = data.find_first_of(',');

        vector<string> nodes;

        while (end <= string::npos)
        {
            string sub = data.substr(start, end - start);

            while (sub[0] == ' ')
            {
                sub = sub.substr(1, sub.size() - 1);
            }
            if (sub[sub.size() - 1] == ']')
            {
                sub.pop_back();
            }
            while (sub[sub.size() - 1] == ' ')
            {
                sub.pop_back();
            }

            nodes.emplace_back(sub);

            if (end == string::npos)
            {
                break;
            }

            start = end + 1;
            end = data.find_first_of(',', start);
        }

        return BuildTreeFromLevelOrderStringVector(nodes);
    }

    void PrintTreeLevelOrder( TreeNode* aRoot, bool aPrintNext )
    {
        vector<string> dataToPrint;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push( aRoot );

        while( !nodeQueue.empty() )
        {
            const int len = static_cast<int>(nodeQueue.size());

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
        int removeIndex = static_cast<int>(dataToPrint.size());
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

    void DeleteTree( TreeNode* root )
    {
        if( root )
        {
            DeleteTree( root->left );
            DeleteTree( root->right );
        }
        delete root;
    }

    bool ConvertToVectorOfChar
        (
        const vector<string>& aInput,
        vector<char>& aOutput
        )
    {
        aOutput.clear();

        for( auto& str : aInput )
        {
            aOutput.push_back( str[0] );
        }

        return aOutput.size() > 0;
    }
}