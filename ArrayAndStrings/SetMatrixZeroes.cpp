#include "ArrayAndStrings.h"
#include "LeetCodeUtil.h"

namespace ArrayAndStrings
{
    using namespace std;

    //! Basic idea: We cannot make changes to the matix while we are still scanning it because we will make un-scaned cells dirty.
    //! O( m * n ) Space complexity : Straightforward solution: Create a matrix with the same size( m * n ).
    //!             Mark each cell to 0 according the input matrix.
    //! O( m + n ) Space complexity : A little improve. Create a vector(m) to record if certain row should be cleared.
    //!              And create a vector(n) to record if certain column should be cleared.
    //! O( 1 ) Space complexity : For each row/column, execpt the 1st row and 1 column, use the 1st element of the row/column to record if
    //! this row/column should be cleared. Use another variables for handle the 1st row/column.
    void setZeroes( vector<vector<int>>& matrix )
    {
        bool clearFirstColumn = false;
        const int m = matrix.size();
        const int n = matrix[0].size();

        // Mark matrix[0][0] to 0 if the 1st row should be cleared.
        for( int i = 0; i < n; ++i )
        {
            if( matrix[0][i] == 0 )
            {
                if( i == 0 )
                {
                    clearFirstColumn = true;
                }
                else
                {
                    matrix[0][0] = 0;
                }
                break;
            }
        }

        if( !clearFirstColumn )
        {
            for( int i = 1; i < m; ++i )
            {
                if( matrix[i][0] == 0 )
                {
                    clearFirstColumn = true;
                    break;
                }
            }
        }

        for( int i = 1; i < m; ++i )
        {
            for( int j = 1; j < n; ++j )
            {
                if( matrix[i][j] == 0 )
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for( int i = 1; i < m; ++i )
        {
            for( int j = 1; j < n; ++j )
            {
                if( matrix[i][0] == 0 || matrix[0][j] == 0 )
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // Clear 1st row.
        if( matrix[0][0] == 0 )
        {
            for( int j = 1; j < n; ++j )
            {
                matrix[0][j] = 0;
            }
        }

        // Clear 1st colmun.
        if( clearFirstColumn )
        {
            for( int i = 0; i < m; ++i )
            {
                matrix[i][0] = 0;
            }
        }
    }

    void test_setZeroes()
    {
        cout << "\nTesting setZeroes..." << endl;

        // Input:  [[1,1,1],[1,0,1],[1,1,1]]
        // Output: [[1,0,1],[0,0,0],[1,0,1]]
        /*vector<vector<int>> testData = {
            { 1, 1, 1 },
            { 1, 0, 1 },
            { 1, 1, 1 }
        };*/

        // Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
        // Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
        vector<vector<int>> testData = {
            { 0,1,2,0 },
            { 3,4,5,2 },
            { 1,3,1,5 }
        };

        // Input: [[1], [0]]
        // Output: [[0],[0]]
        /*vector<vector<int>> testData = {
            { 1 },
            { 0 }
        };*/

        setZeroes( testData );

        LeetCodeUtil::PrintMatrix( testData );
    }
}