#include "MorrisTraversal.h"
#include "LeetCodeUtil.h"
#include "BuildTree.h"

#include <stack>
#include <utility>

namespace TreesAndGraphs
{
    //-----------------------------------------------------------------------------------
    // 200. Number of Islands (Recursion)
    //-----------------------------------------------------------------------------------
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

    // Recursive DFS
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

    //-----------------------------------------------------------------------------------
    // 200. Number of Islands (Iterative)
    //-----------------------------------------------------------------------------------
    int numIslands_iterative(vector<vector<char>>& grid)
    {
        if (grid.empty() || grid[0].empty())
        {
            return 0;
        }

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != '1')
                {
                    continue;
                }
                // Let use DFS.
                stack<pair<int, int>> cellStack;
                cellStack.push({ i, j });

                while (!cellStack.empty())
                {
                    auto coord = cellStack.top();
                    cellStack.pop();

                    if (grid[coord.first][coord.second] == '1')
                    {
                        if (coord.first > 0)
                        {
                            cellStack.push({ coord.first - 1, coord.second });
                        }
                        if (coord.second > 0)
                        {
                            cellStack.push({ coord.first, coord.second - 1 });
                        }
                        if (coord.first < m - 1)
                        {
                            cellStack.push({ coord.first + 1, coord.second });
                        }
                        if (coord.second < n - 1)
                        {
                            cellStack.push({ coord.first, coord.second + 1 });
                        }

                        // The rule doesn't say that we cannot modify aGrid, so I am going to change
                        // '1' to '0' to mark it as visited.
                        grid[coord.first][coord.second] = '0';
                    }
                }

                result++;

            }
        }

        return result;
    }

    //-----------------------------------------------------------------------------------
    // 695. Max Area of Island
    //-----------------------------------------------------------------------------------
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
        {
            return 0;
        }

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != 1)
                {
                    continue;
                }
                // Let use DFS.
                stack<pair<int, int>> cellStack;
                cellStack.push({ i, j });

                int countOfLands = 0;
                while (!cellStack.empty())
                {
                    auto coord = cellStack.top();
                    cellStack.pop();

                    if (grid[coord.first][coord.second] == 1)
                    {
                        if (coord.first > 0)
                        {
                            cellStack.push({ coord.first - 1, coord.second });
                        }
                        if (coord.second > 0)
                        {
                            cellStack.push({ coord.first, coord.second - 1 });
                        }
                        if (coord.first < m - 1)
                        {
                            cellStack.push({ coord.first + 1, coord.second });
                        }
                        if (coord.second < n - 1)
                        {
                            cellStack.push({ coord.first, coord.second + 1 });
                        }

                        // The rule doesn't say that we cannot modify aGrid, so I am going to change
                        // '1' to '0' to mark it as visited.
                        grid[coord.first][coord.second] = 0;
                        countOfLands++;
                    }
                }
                result = max(result, countOfLands);
            }
        }

        return result;
    }

    //-----------------------------------------------------------------------------------
    // Test function
    //-----------------------------------------------------------------------------------
    void test_matrix_traversal()
    {
        cout << "\nTest matrix traversal!\n";

        // 200. Number of Islands
        vector<vector<char>> grid = {
            { '1', '1', '0', '0', '0' },
            { '1', '1', '0', '0', '0' },
            { '0', '0', '1', '0', '0' },
            { '0', '0', '0', '1', '1' }
        };

        cout << "Result of Number of Islands (recursion): " << numIslands(grid) << endl;

        grid = {
            { '1', '1', '0', '0', '0' },
            { '1', '1', '0', '0', '0' },
            { '0', '0', '1', '0', '0' },
            { '0', '0', '0', '1', '1' }
        };

        cout << "Result of Number of Islands (iteration): " << numIslands_iterative(grid) << endl;


        // 695. Max Area of Island
        // Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
        // Output: 6

        string gridString = "[[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],\
            [0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0], \
            [0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0], \
            [0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]";

        vector<vector<int>> gridInt;
        LeetCodeUtil::BuildIntMatrixFromString(gridString, &gridInt);

        cout << "Result of Max Area of Island: " << maxAreaOfIsland(gridInt) << endl;
        cout << endl;

    }
}