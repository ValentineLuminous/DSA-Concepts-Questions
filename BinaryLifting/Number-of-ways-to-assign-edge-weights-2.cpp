/*
This Question is really a good qustion it will teach you a lot of concepts like
  1. Binary Exponentiation
  2. Binary Lifting
  3. Lowest common ancestor in log(n) time complexity
  4. Finding Kth Ancestor in log(n) time complexity
  5. Finding depth of every node in a tree using dfs

  The simple solution of this question was that you need to find the distnace between the two nodes in a given query and if you have two choices
  to assign weights in the path (1, 2) there will always be 2^n ways to assign weights in a path and the total sum of weights in that path can be either
  even or odd nothing else and we want to find the number of ways in which total path sum is odd so that will be half of total number of ways.
  i.e. (2^n)/2 = 2^(n-1). (where n = number of edges between nodes or the distance between those two nodes)

  And for finding this 2 power n-1 we cannot use simple pow function we need to use binary exponentoation otherwise it will give integer overflow error

  But but but finding the distance between the two node in a log(n) time complexity with 2*10^5 size nodes tree is the main job.
  but for finding distance between two nodes we can use this simple formula -:
  
-----------------------------------------------------------
  distance(u,v) = depth(u) + depth(v) - 2*depth(LCA(u,v)) |
  ---------------------------------------------------------

  Finding LCA - : 
  FInding Kth Ancestor & Binary Lifting - : https://github.com/ValentineLuminous/DSA-Concepts-Questions/blob/main/BinaryLifting/Finding-Kth-Ancestor.cpp

*/


class Solution {
public:

    // Finding Depth of all nodes
    vector<int> depth;
    const int mod = 1e9+7;
    void findDepth(int node, int par, vector<int> adj[]){
        for(auto it: adj[node]){
            if(it==par) continue;

            depth[it] = depth[node]+1;

            findDepth(it,node,adj);
        }
    }

    // Binary Lifting nodes
    int binaryLift[100001][20];
    void binaryLifting(int node, int parent, vector<int> adj[]){
        binaryLift[node][0] = parent;

        for(int k=1;k<20;k++){

            if(binaryLift[node][k-1]!=-1) binaryLift[node][k] = binaryLift[binaryLift[node][k-1]][k-1];

        }

        for(auto it: adj[node]){
            if(it==parent) continue;
            binaryLifting(it,node,adj);
        }
    }

    //Finding Kth Ancestor
    int findKthAncestor(int node, int k){
        for(int i=0;i<20;i++){
            if((k>>i)&1){
                if(binaryLift[node][i]!=-1) node = binaryLift[node][i];
            }
        }
        return node;
    }

    //Finding LCA
    int findLca(int u, int v){
        if(depth[u]< depth[v]) swap(u,v);

        int depthDiff = depth[u] - depth[v];

        u = findKthAncestor(u, depthDiff);
        

        if(u==v){ 
            return u;
        }

        for(int i=19;i>=0;i--){
            
            if(binaryLift[u][i]==binaryLift[v][i]) continue;
            u = binaryLift[u][i];
            v = binaryLift[v][i];
        }

        return binaryLift[u][0];
    }
    
    //Bin Pow
    long long binPow(long long a, long b){
        long long res = 1;
        while(b>0){
            if(b&1) res = (res*a)%mod;

            a = (a*a)%mod;
            b = b>>1;
        }
        return res;
    }
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int m = 0;
        for(auto it: edges){
            m = max(m, max(it[0], it[1]));
        }
        
        vector<int> adj[m+1];
        for(auto it: edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        depth.resize(m+1, 0);
        findDepth(1,-1, adj);
       
        memset(binaryLift, -1, sizeof(binaryLift));
        binaryLifting(1,-1,adj);

        vector<int> ans;

        for(auto it: queries){
            int u = it[0];
            int v = it[1];

            if(u==v){
                ans.push_back(0);
                continue;
            }
            long long lca = findLca(u,v);

            long long distance = depth[u] + depth[v] - 2*(depth[lca]);

            int options = (int)binPow(2, distance-1);
            ans.push_back(options);
        }

        return ans;
    }
};
