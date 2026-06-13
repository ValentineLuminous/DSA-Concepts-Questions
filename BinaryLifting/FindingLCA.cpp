/*
Finding Lowest Common Ancestor (LCA) using Binary Lifting

Prerequisite:
If you are unfamiliar with Binary Lifting or how the ancestor table
(up[node][j] = 2^j-th ancestor of node) is built, refer to:

BinaryLifting/Finding-Kth-Ancestor.cpp

------------------------------------------------------------

Problem:
Given two nodes u and v in a tree, find their Lowest Common Ancestor.

Definition:
The Lowest Common Ancestor (LCA) of two nodes is the deepest node
that is an ancestor of both nodes.

Example:

        1
      /   \
     2     3
    / \   / \
   4   5 6   7
      /
     8

LCA(4, 5) = 2
LCA(4, 6) = 1
LCA(8, 5) = 5

------------------------------------------------------------

Approach:

Using the Binary Lifting table, we can answer LCA queries efficiently.

The process consists of three steps:

1) Bring both nodes to the same depth.

Suppose:

depth[u] = 10
depth[v] = 6

Then u is deeper.

We lift u upward by (10 - 6) = 4 levels using Binary Lifting.

------------------------------------------------------------

2) Check if they became the same node.

If after equalizing depths:

u == v

then one node was originally an ancestor of the other,
and that node itself is the LCA.

------------------------------------------------------------

3) Lift both nodes together.

Starting from the largest power of 2:

If:

up[u][j] != up[v][j]

then we can safely move both nodes upward by 2^j levels.

Why?

Because if their 2^j-th ancestors are different,
their LCA must lie above them.

Eventually, u and v become direct children of the LCA.

Hence:

LCA = up[u][0]

------------------------------------------------------------

Complexities:

Preprocessing:
O(N log N)

LCA Query:
O(log N)

Space Complexity:
O(N log N)

*/

class LCA {
private:
    int LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    void dfs(int node, int parent) {

        up[node][0] = parent;

        for (int j = 1; j < LOG; j++) {

            if (up[node][j - 1] != -1) {
                up[node][j] = up[up[node][j - 1]][j - 1];
            }
        }

        for (int child : adj[node]) {

            if (child == parent) continue;

            depth[child] = depth[node] + 1;

            dfs(child, node);
        }
    }

public:
    LCA(int n, vector<vector<int>>& edges, int root = 0) {

        LOG = ceil(log2(n)) + 1;

        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
        adj.assign(n, {});

        for (auto& edge : edges) {

            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(root, -1);
    }

    int getLCA(int u, int v) {

        // Ensure u is deeper
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        // Bring u to the same depth as v
        int diff = depth[u] - depth[v];


      // finding the (diff)th ancestor of node u
        for (int j = 0; j < LOG; j++) {

            if ((diff >> j) & 1) {
                u = up[u][j];
            }
        }

        // One node was ancestor of the other
        if (u == v) {
            return u;
        }

        // Lift both nodes together
        for (int j = LOG - 1; j >= 0; j--) {

            if (up[u][j] != up[v][j]) {

                u = up[u][j];
                v = up[v][j];
            }
        }

        // Immediate Parent of either node is the LCA
        return up[u][0];
    }
};
