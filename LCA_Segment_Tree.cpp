class LCA{
 
private:
   // first -> first time node appears in euler tour
   // height -> height of each node
   // euler -> visit all nodes with timer (each edge exactly once)
   // visited -> for dfs 
   // segmentTree -> min height among range l to r in euler tree
   vector<int> first, height, euler, vis, segmentTree;
 
public:
   LCA(int n, vector<int> adj[], int root = 1) {
      first = vector<int> (n, -1);
      height = vector<int> (n, 0);
      vis = vector<int> (n, 0);
 
      const int m = n << 3;
      // size -> (euler size * 4)
      segmentTree = vector<int> (m, 0);
 
      dfs(root, adj);
      build(root, 0, euler.size() - 1);
   }    
 
   void dfs(int node, vector<int> adj[], int h = 0) {
      vis[node] = 1;

      // first time node visited
      first[node] = euler.size();
      euler.pb(node);
 
      height[node] = h;
 
      for(auto nbr: adj[node]) {
         if(!vis[nbr]) {
            dfs(nbr, adj, h + 1);

            // go back to visit other nodes
            euler.pb(node);
         }
      }
   }
   
   // index will store lca from l to r
   void build(int index, int l, int r) {
      if(l == r) {
         segmentTree[index] = euler[l];
      }
      else {
         int mid = l + ((r - l) >> 1);
         build(index << 1, l, mid);
         build(index << 1 | 1, mid + 1, r);
 
         int left = segmentTree[index << 1], right = segmentTree[index << 1 | 1];
         segmentTree[index] = (height[left] <= height[right]) ? left : right;
      }     
   }
   
   // Query Range (i -> j) inclusive
   int query(int index, int l, int r, int i, int j) {
      // out of index
      if(j < l || i > r) return -1;
 
      // completely inside
      if(l >= i && r <= j) {
         return segmentTree[index];
      }
 
      int mid = l + ((r - l) >> 1);
      int left = query(index << 1, l, mid, i, j);
      int right = query(index << 1 | 1, mid + 1, r, i, j);
 
      if(left == -1) return right;
      if(right == -1) return left;
 
      return (height[left] <= height[right]) ? left : right;
   }
   
   // LCA of nodes u,v
   int getLca(int u, int v) {
      int left = first[u], right = first[v];
      if(left > right) swap(left, right);
 
      return query(1, 0, euler.size() - 1, left, right);
   }
};