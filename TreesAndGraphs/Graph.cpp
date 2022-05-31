#include "Graph.h"
#include "LeetCodeUtil.h"

#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

namespace TreesAndGraphs
{
    using namespace std;
    using namespace LeetCodeUtil;

    //---------------------------------------------------------------------------------------
    // 323. Number of Connected Components in an Undirected Graph
    // Topic: Union Find, BFS/DFS
    //
    // This kind of question is not commonly seen.
    // Union Find is a very efficient algorithm for question like this, but I will not use
    // it in this. I will use it in 261 instead.
    //---------------------------------------------------------------------------------------

    // Use OOD method. It is slow but preserves a lot of information.
    class Solution323
    {
    public:
        struct Node
        {
            int value;
            int groupId;
        };

        class NodeManager
        {
        public:
            NodeManager(int n) : size(n)
            {
                groups.reserve(n);
                nodes.reserve(n);

                for (int i = 0; i < n; ++i)
                {
                    Node* node = new Node;
                    node->value = i;
                    node->groupId = i;

                    groups[i].push_back(node);
                    nodes[i] = node;
                }
            }

            ~NodeManager()
            {
                for (auto& node : nodes)
                {
                    delete node.second;
                }
            }

            void assignGroup(Node* node, int groupId)
            {
                const int oldGroupId = node->groupId;
                const auto& oldList = groups[oldGroupId];
                // Write new groupId for all nodes in the old group.
                for (auto& node : oldList)
                {
                    node->groupId = groupId;
                }
                // Copy all nodes into the new group.
                groups[groupId].insert(groups[groupId].end(), oldList.begin(), oldList.end());
                // Delete the old group.
                groups.erase(oldGroupId);
            }

            int size;
            unordered_map<int, list<Node*>> groups;
            unordered_map<int, Node*> nodes;
        };

        int countComponents(int n, vector<vector<int>>& edges)
        {
            NodeManager manager(n);

            for (const auto& edge : edges)
            {
                Node* node1 = manager.nodes[edge[0]];
                Node* node2 = manager.nodes[edge[1]];
                if (node1->groupId != node2->groupId)
                {
                    manager.assignGroup(node2, node1->groupId);
                }
            }

            return manager.groups.size();
        }
    };

    class Solution323DFS
    {
    public:
        void visitAdjacent(int node, vector<bool>& visited, vector<vector<int>>& adjacentList)
        {
            if (visited[node])
            {
                return;
            }

            visited[node] = true;
            for (int nearby : adjacentList[node])
            {
                visitAdjacent(nearby, visited, adjacentList);
            }
        }

        // Build adjacent list for every node, so that we can use DFS.
        int countComponents(int n, vector<vector<int>>& edges)
        {
            vector<vector<int>> adjacentList(n);
            vector<bool> visited(n, false);
            int result = 0;

            // Build adjacent list.
            for (const auto& edge : edges)
            {
                adjacentList[edge[0]].push_back(edge[1]);
                adjacentList[edge[1]].push_back(edge[0]);
            }

            for (int i = 0; i < n; ++i)
            {
                if (!visited[i])
                {
                    result++;
                    visitAdjacent(i, visited, adjacentList);
                }
            }

            return result;
        }
    };

    //---------------------------------------------------------------------------------------
    // 261. Graph Valid Tree
    // Topic: Union Find, BFS/DFS
    //
    //---------------------------------------------------------------------------------------
    class Solution261
    {
    public:
        bool validTree(int n, vector<vector<int>>& edges)
        {
            // A tree must meet the following conditions
            // 1. All nodes are connected.
            // 2. No cycle.
            // This question can be solved by
            // 1. Build adjacent list and use DFS to defect cycle and isolated node.
            // 2. Use union find to detect cycle. If there is no cycle and count of edge is
            // equal to n - 1, then there is no isolated node.
            vector<int> groups(n, -1);

            // We can build the groups and detect the cycle at the same time.
            for (const auto& edge : edges)
            {
                int root1 = unionFind(groups, edge[0]);
                int root2 = unionFind(groups, edge[1]);
                if (root1 == root2)
                {
                    return false;
                }
                else
                {
                    groups[root2] = root1;
                }
            }
            return edges.size() == n - 1;
        }

        // Find() of Union-Find Algorithm can be used find the root node of the given node
        // in the connected component.
        // If two nodes have the same root, then they are in the same connected component.
        // Time complexity: O(n)
        int unionFind(const vector<int>& groups, int node)
        {
            int root = node;

            // The root's group Id is itself. Iterate until we find the root.
            while (groups[root] != -1 && groups[root] != root)
            {
                root = groups[root];
            }

            return root;
        }
    };

    //---------------------------------------------------------------------------------------
    // 207. Course Schedule
    // Topic: Topological sorting
    // This is a question about directed graph category, which is seldom seen in LeetCode.
    //
    // There are two major approaches:
    // 1. Kahn's algorithm (BFS based)
    // 2. DFS
    //
    //---------------------------------------------------------------------------------------
    class Solution207
    {
    public:

        struct Node
        {
            list<unsigned short> outEdges;
            unsigned short inDegree = 0;
        };

        // Kahn's algorithm
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
        {
            vector<Node> courses(numCourses);
            // <ai, aj>  :  ai <--- aj
            for (const auto& edge : prerequisites)
            {
                courses[edge[1]].outEdges.push_back(edge[0]);
                courses[edge[0]].inDegree++;
            }

            // Put the node which has 0 indegree into queue.
            queue<int> zeroInDegree;
            for (int i = 0; i < numCourses; ++i)
            {
                if (courses[i].inDegree == 0)
                {
                    zeroInDegree.push(i);
                }
            }

            while (!zeroInDegree.empty())
            {
                int node = zeroInDegree.front();
                zeroInDegree.pop();
                for (const auto& dest : courses[node].outEdges)
                {
                    courses[dest].inDegree--;
                    if (courses[dest].inDegree == 0)
                    {
                        zeroInDegree.push(dest);
                    }
                }
            }

            // If there is cycle, all node should have 0 edge.
            for (int i = 0; i < numCourses; ++i)
            {
                if (courses[i].inDegree != 0)
                {
                    return false;
                }
            }

            return true;
        }

        struct NodeDfs
        {
            list<unsigned short> outEdges;
            // 0: unset mark, -1: temporal mark, 1: permanent mark.
            short state = 0;
        };

        // DFS. We need 3 special marks for the node - unset, permanent, temporal.
        bool canFinishDfs(int numCourses, vector<vector<int>>& prerequisites)
        {
            vector<NodeDfs> courses(numCourses);
            // <ai, aj>  :  ai <--- aj
            for (const auto& edge : prerequisites)
            {
                courses[edge[1]].outEdges.push_back(edge[0]);
            }

            for (int i = 0; i < numCourses; ++i)
            {
                if (!traverseDfs(i, courses))
                {
                    return false;
                }
            }

            return true;
        }

        bool traverseDfs(int node, vector<NodeDfs>& courses)
        {
            if (courses[node].state == 1) // Permanent state
            {
                return true;
            }
            else if (courses[node].state == -1) // Temporal state.
            {
                // Cycle detected.
                return false;
            }

            courses[node].state = -1;
            for (const auto& dest : courses[node].outEdges)
            {
                if (!traverseDfs(dest, courses))
                {
                    return false;
                }
            }
            courses[node].state = 1;
            return true;
        }
    };


    //---------------------------------------------------------------------------------------
    // Test function
    //---------------------------------------------------------------------------------------
    void TestGraphs()
    {
        cout << "\nTest Graphs\n";
        // 323. Number of Connected Components in an Undirected Graph
        // Input: n = 5, edges = [[0,1],[1,2],[3,4]]
        // Output: 2
        // n = 4, [[0,1],[2,3],[1,2]]
        // Output: 1
        Solution323 sol23;
        vector<vector<int>> edges;
        BuildIntMatrixFromString("[[0,1],[2,3],[1,2]]", &edges);
        int n = 4;
        cout << "\nResult of Number of Connected Components in an Undirected Graph: " << sol23.countComponents(n, edges) << endl;

        Solution323DFS sol323Dfs;
        cout << "\nResult of Number of Connected Components in an Undirected Graph (DFS): " << sol323Dfs.countComponents(n, edges) << endl;

        // 261. Graph Valid Tree
        // Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
        // Output: true
        // Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
        // Output: false
        Solution261 sol261;
        BuildIntMatrixFromString("[[0,1],[0,2],[0,3],[1,4]]", &edges);
        n = 5;
        cout << "\nResult of Graph Valid Tree: " << sol261.validTree(n, edges) << endl;

        // 207. Course Schedule
        // Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
        // Output: false
        BuildIntMatrixFromString("[[1,0],[2,1],[0,2]]", &edges);
        n = 3;
        Solution207 sol207;
        cout << "\nResult of Course Schedule: " << sol207.canFinishDfs(n, edges) << endl;
    }
}