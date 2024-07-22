class LCA{

private:
   // first -> first time node appears in euler tour
   // height -> height of each node
   // euler -> visit all nodes with timer (each edge exactly once)
   // visited -> for dfs 
   // sparseTable -> min height among range l to r in euler tree
   vector<int> first, euler, height;
   vector<bool> vis;
   vector<vector<int>> sparseTable;

public:
   const int LOG = 20;
   LCA(int n, vector<int> adj[], int root = 1) {
      first = vector<int> (n, 0);
      height = vector<int> (n, 0);
      vis = vector<bool> (n, false);

      dfs(root, adj);
      sparseTable = vector<vector<int>> (euler.size() + 1, vector<int> (LOG, 0));
      build();
   }   

   void dfs(int node, vector<int> adj[], int h = 0) {
      vis[node] = true;
      height[node] = h;

      // first time node visited
      first[node] = euler.size();
      euler.pb(node);

      for(auto nbr: adj[node]) {
         if(!vis[nbr]) {
            dfs(nbr, adj, h + 1);

            // go back to visit other nodes
            euler.pb(node);
         }
      }
   }  

   void build() {
      const int n = euler.size();

      // 0th col will store elements of euler tour
      for(int i = 0; i < n; ++i) {
         sparseTable[i][0] = euler[i];
      }

      // lca of elements of size j from (i, i + (1 << j))
      for(int j = 1; j < LOG; ++j) {
         for(int i = 0; i + (1 << j) - 1 < n; ++i) {
            int left = sparseTable[i][j - 1];
            int right = sparseTable[i + (1 << (j - 1))][j - 1];

            sparseTable[i][j] = height[left] <= height[right] ? left : right;
         }
      }
   }

   // idempotent function -> therefore overlapping ignored
   int query(int u, int v) {
      int length = v - u + 1;
      int k = 0;
      while((1 << (k + 1)) <= length) k++;

      int left = sparseTable[u][k];
      int right = sparseTable[v - (1 << k) + 1][k];

      return height[left] <= height[right] ? left : right;
   }

   // LCA of node u, v
   int getLca(int u, int v) {
      int left = first[u], right = first[v];
      if(left > right) swap(left, right);

      return query(left, right);
   }
};