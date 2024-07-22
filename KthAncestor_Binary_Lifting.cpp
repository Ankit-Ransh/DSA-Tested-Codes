class KthAncestor {

private:
   vector<vector<int>> binaryLifting;
   vector<int> binaryLog;
   int n;

public:
   // Handle upto (2 << 20)
   const int LOG = 20;

   KthAncestor(vector<int> &v) {
      n = v.size();

      // 1 based indexing (1 -> root)
      binaryLifting = vector<vector<int>> (n + 5, vector<int> (LOG, -1));
      binaryLog = vector<int> (n + 5, 0);

      // efficiently calculate log
      for(int i = 2; i <= n; ++i) binaryLog[i] = binaryLog[i >> 1] + 1;

      // 1st parent of nodes
      for(int i = 2; i <= n; ++i) {
         binaryLifting[i][0] = v[i];
      }

      build();
   }

   void build() {

      // kth node parent
      for(int j = 1; j < LOG; ++j) {
         for(int i = 0; i < n; ++i) {
            int up1 = binaryLifting[i][j - 1];
            if(up1 == -1) {
               binaryLifting[i][j] = up1;
            }
            else {
               binaryLifting[i][j] = binaryLifting[up1][j - 1];
            }
         }
      }
   }

   int getKAncestor(int x, int k) {
      int ancestor = x;

      // k = binary representation and move upwards
      while(ancestor != -1 && k > 0) {
         int binLog = binaryLog[k];
         ancestor = binaryLifting[x][binLog];

         x = ancestor;
         k -= (1 << binLog);
      }  

      return ancestor;
   }
};