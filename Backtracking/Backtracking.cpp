#include "Backtracking.h"
#include "LeetCodeUtil.h"

#include <algorithm>

namespace Backtracking
{
    using namespace std;
    //-----------------------------------------------------------------------------------------------
    // 17. Letter Combinations of a Phone Number
    //-----------------------------------------------------------------------------------------------
    vector<string> letterCombinations( string digits )
    {
        vector<string> result;
        if( digits.empty() )
        {
            return result;
        }

        result.push_back( "" ); // This is important. We must have an empty string to concatenate strings.
        vector<string> dict{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

        for( int i = 0; i < digits.length(); ++i )
        {
            const string& mappedStr = dict[digits[i] - '0'];
            vector<string> temp;
            temp.reserve( result.size() * mappedStr.length() );
            for( char c : mappedStr )
            {
                for( const string& str : result )
                {
                    temp.push_back( str + c );
                }
            }
            result.swap( temp );
        }

        return result;
    }

    //-----------------------------------------------------------------------------------------------
    // 22. Generate Parentheses
    //-----------------------------------------------------------------------------------------------
    void generateParenthesis_helper
        (
        vector<string>& aResult,
        const int aLeftCount,
        const int aRightCount,
        string aPartial
        )
    {
        if( aLeftCount > aRightCount ) // (()
        {
            return; // abort
        }

        if( aLeftCount == 0 && aRightCount == 0 ) // done
        {
            aResult.push_back( aPartial );
        }
        else
        {
            if( aLeftCount > 0 )
            {
                aPartial.push_back( '(' );
                generateParenthesis_helper( aResult, aLeftCount - 1, aRightCount, aPartial );
                aPartial.pop_back();
            }
            if( aRightCount > 0 )
            {
                aPartial.push_back( ')' );
                generateParenthesis_helper( aResult, aLeftCount, aRightCount - 1, aPartial );
            }
        }
    }

    vector<string> generateParenthesis( int n )
    {
        vector<string> result;

        generateParenthesis_helper( result, n, n, "" );

        return result;
    }

    //-----------------------------------------------------------------------------------------------
    // 46. Permutations
    //-----------------------------------------------------------------------------------------------

    void permuteDFS( vector<int>& aNums, int aStartIndex, vector<vector<int>>& aResult )
    {
        if( aStartIndex >= aNums.size() )
        {
            aResult.push_back( aNums );
        }

        for( int i = aStartIndex; i < aNums.size(); ++i )
        {
            // Iterate from aStartIndex to the end, so we can try all possible values on the aStartIndex.
            swap( aNums[aStartIndex], aNums[i] );
            permuteDFS( aNums, aStartIndex + 1, aResult );
            swap( aNums[aStartIndex], aNums[i] ); // Revert
        }
    }

    // Recursion solution 1
    vector<vector<int>> permute( vector<int>& nums )
    {
        // Idea:
        // Start with the 1st position, try all integer on it and call permute() recursively for the rest.
        vector<vector<int>> result;
        permuteDFS
            (
            nums,
            0,
            result
            );

        return result;
    }

    // Use next_permutation.
    vector<vector<int>> permute_STL( vector<int>& nums )
    {
        vector<vector<int>> res;
        sort( nums.begin(), nums.end() );
        res.push_back( nums );
        while( next_permutation( nums.begin(), nums.end() ) )
        {
            res.push_back( nums );
        }
        return res;
    }

    //-----------------------------------------------------------------------------------------------
    // 77. Combinations
    //-----------------------------------------------------------------------------------------------

    // Recursion method 1 - using math formula.
    vector<vector<int>> combine( int n, int k )
    {
        // Look at the formula : C(n, k) = C(n-1, k-1) + C(n-1, k).
        // Observe the their combinations.
        // C(4, 2) =
        // [2, 4],
        // [3, 4],
        // [2, 3],
        // [1, 2],
        // [1, 3],
        // [1, 4],
        //
        // C(3, 1) = [1], [2], [3]
        // C(3, 2) = [1, 2], [1, 3], [2, 3]
        // Note that C(3, 2) is contained in the C(4, 2). We just need to find out the missing part.
        // We can get the missing part by appending '4' to C(3, 1).

        if( k > n || k < 0 )
        {
            return {}; // no any combination.
        }
        if( k == 0 )
        {
            return { {} }; // One empty combiation. We need a empty vector here, so caller can append n to it.
        }

        auto part2 = combine( n - 1, k - 1 );

        for( auto& i : part2 )
        {
            i.push_back( n );
        }

        auto part1 = combine( n - 1, k );

        part2.insert( part2.begin(), part1.begin(), part1.end() );

        return part2;
    }

    // Recursion method 2 - traditional DFS
    void combine_DFS_helper( int n, int k, int aStartIndex, vector<vector<int>>& aResult, vector<int>& combination )
    {
        if( combination.size() == k )
        {
            aResult.push_back( combination );
            return;
        }

        for( int i = aStartIndex; i <= n; ++i )
        {
            combination.push_back( i );
            combine_DFS_helper( n, k, i + 1, aResult, combination );
            combination.pop_back(); // Remove the one we just added, so we can try another integer.
        }
    }

    //-----------------------------------------------------------------------------------------------
    // 78. Subsets
    //
    // There are recursive and iterative ways.
    //-----------------------------------------------------------------------------------------------

    // Iterative method
    vector<vector<int>> subsets( vector<int>& nums )
    {
        vector<vector<int>> result = { {} };
        for( int digit : nums )
        {
            const int len = result.size();
            for( int i = 0; i < len; ++i )
            {
                const auto& set = result[i];
                vector<int> copy( set );
                copy.push_back( digit );
                result.push_back( copy );
            }
        }

        return result;
    }

    /*
                            []
                       /          \
                      /            \
                     /              \
                  [1]                []
               /       \           /    \
              /         \         /      \
           [1 2]       [1]       [2]     []
          /     \     /   \     /   \    / \
      [1 2 3] [1 2] [1 3] [1] [2 3] [2] [3] []
    */
    // Recursive method.
    void subsets_recursive_helper( vector<int>& aNums, vector<vector<int>>& aResult, vector<int> aPartial, int aIndex )
    {
        aResult.push_back( aPartial );

        for( int i = aIndex; i < aNums.size(); ++i )
        {
            aPartial.push_back( aNums[i] );
            subsets_recursive_helper( aNums, aResult, aPartial, i + 1 );
            aPartial.pop_back();
        }
    }

    vector<vector<int>> subsets_recursive( vector<int>& nums )
    {
        vector<vector<int>> result;
        vector<int> partial;

        subsets_recursive_helper( nums, result, partial, 0 );

        return result;
    }

    vector<vector<int>> combine_DFS( int n, int k )
    {
        vector<vector<int>> result;
        vector<int> combination;

        combine_DFS_helper( n, k, 1, result, combination );

        return result;
    }

    //-----------------------------------------------------------------------------------------------
    // 79. Word Search
    //
    // Seems to be an application of graph DFS.
    //-----------------------------------------------------------------------------------------------

    int mBoardM;
    int mBoardN;

    bool searchWordDFS
        (
        vector<vector<char>>& aBoard,
        const string& aWord,
        const int aStartOfWord,
        const int aX,
        const int aY
        )
    {
        if( aStartOfWord == aWord.size() )
        {
            return true;
        }
        if( aX < 0 || aX >= mBoardM || aY < 0 || aY >= mBoardN || aBoard[aX][aY] != aWord[aStartOfWord] )
        {
            return false;
        }

        const char c = aBoard[aX][aY];
        // Mark the current cell as visited.
        aBoard[aX][aY] = '#';

        const bool res =
            searchWordDFS( aBoard, aWord, aStartOfWord + 1, aX + 1, aY ) ||
            searchWordDFS( aBoard, aWord, aStartOfWord + 1, aX - 1, aY ) ||
            searchWordDFS( aBoard, aWord, aStartOfWord + 1, aX, aY + 1 ) ||
            searchWordDFS( aBoard, aWord, aStartOfWord + 1, aX, aY - 1 );

        // Undo the mark
        aBoard[aX][aY] = c;

        return res;
    }

    bool exist( vector<vector<char>>& board, string word )
    {
        if( board.empty() || board[0].empty() )
        {
            return false;
        }

        mBoardM = board.size();
        mBoardN = board[0].size();

        for( int i = 0; i < mBoardM; ++i )
        {
            for( int j = 0; j < mBoardN; ++j )
            {
                if( searchWordDFS( board, word, 0, i, j ) )
                {
                    return true;
                }
            }
        }

        return false;
    }

    void test_Backtracking()
    {
        cout << "\test_Backtracking\n";
        // Input: "23"
        // Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"] .
        string testData = "23";

        vector<string> result = letterCombinations( testData );
        cout << "Result of letterCombinations: ";
        LeetCodeUtil::PrintVector( result );
        cout << endl;

        // Input: n = 3
        // Output: ["((()))", "(()())", "(())()", "()(())", "()()()"]
        result = generateParenthesis( 3 );
        cout << "Result of generateParenthesis: ";
        LeetCodeUtil::PrintVector( result );
        cout << endl;

        // Input: nums = [1, 2, 3]
        // Output : [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
        vector<int> testV = { 1, 2, 3 };
        auto resultV = permute( testV );
        cout << "Result of permute: ";
        LeetCodeUtil::printVectorOfVector( resultV );
        cout << endl;

        resultV = combine_DFS( 4, 2 );
        cout << "Result of combine(4 , 2): ";
        LeetCodeUtil::printVectorOfVector( resultV );
        cout << endl;

        // Input: nums = [1,2,3]
        // Output: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]
        vector<int> setDigits = { 1, 2, 3 };
        resultV = subsets_recursive( setDigits );
        cout << "Result of subsets: ";
        LeetCodeUtil::printVectorOfVector( resultV );
        cout << endl;

        // Input: board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], word = "ABCCED"
        // Output : true
        string word( "Z" );
        vector<vector<char>> charBoard = {
            { 'A', 'B', 'C', 'E'},
            { 'S', 'F', 'C', 'S'},
            { 'A', 'D', 'E', 'E'},
        };
        bool resultB = exist( charBoard, word );
        cout << "Result of Word Exist: " << resultB;
        cout << endl;
    }
}