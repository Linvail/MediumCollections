#include "MorrisTraversal.h"
#include "LeetCodeUtil.h"
#include "BuildTree.h"

namespace TreesAndGraphs
{
    void visitDFS
        (
        vector<vector<char>>& aGrid,
        const int aX,
        const int aY
        )
    {
        if( aX < 0 || aX >= aGrid.size() ||
            aY < 0 || aY >= aGrid[0].size() ||
            aGrid[aX][aY] == '0' // Reach the water or visited point
          )
        {
            return;
        }

        aGrid[aX][aY] = '0'; // The rule doesn't say that we cannot modify aGrid.
        visitDFS( aGrid, aX - 1, aY );
        visitDFS( aGrid, aX + 1, aY );
        visitDFS( aGrid, aX, aY - 1 );
        visitDFS( aGrid, aX, aY + 1 );
    }

    // 200. Number of Islands
    // Graph related problem. Can use DFS or BFS.
    int numIslands( vector<vector<char>>& grid )
    {
        if( grid.empty() || grid[0].empty() )
        {
            return 0;
        }

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;

        for( int i = 0; i < m; ++i )
        {
            for( int j = 0; j < n; ++j )
            {
                if( grid[i][j] == '1' )
                {
                    visitDFS( grid, i, j );
                    result++;
                }
            }
        }

        return result;
    }

    void test_numIslands()
    {
        cout << "\ntest_numIslands\n";

        vector<vector<char>> grid = {
            { '1', '1', '0', '0', '0' },
            { '1', '1', '0', '0', '0' },
            { '0', '0', '1', '0', '0' },
            { '0', '0', '0', '1', '1' }
        };

        cout << "Result: " << numIslands( grid ) << endl;
    }
}