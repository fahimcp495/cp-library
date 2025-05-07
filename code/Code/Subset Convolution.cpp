/**
 * Description: $c_i = \sum_{j\subseteq i} a_j b_{i\oplus j}$.  
 * Time: $O(n * \log^2(n))
 */

vector<int> subrset_conv (vector<int> a, vector<int> b) {
  int n = a.size();
  int lg = log2(n);
  vector<int> cnt(n);
  vector<vector<int>> fa(lg + 1, vector<int> (n)), fb(lg + 1, vector<int> (n)), g(lg + 1, vector<int> (n));
  for (int i = 0; i < n; ++i) {
    cnt[i] = cnt[i >> 1] + (i & 1);
    fa[cnt[i]][i] = a[i] % mod;
    fb[cnt[i]][i] = b[i] % mod;
  }
  for (int k = 0; k <= lg; ++k) {
    fwht(fa[k], 0, 1);  fwht(fb[k], 0, 1);
  }
  for (int k = 0; k <= lg; ++k) {
    for (int j = 0; j <= k; ++j) {
      for (int i = 0; i < n; ++i) {
        g[k][i] = addr(g[k][i], 1ll * fa[j][i] * fb[k - j][i] % mod);
      }
    }
  }
  for (int k = 0; k <= lg; ++k) {
    fwht(g[k], 1, 1);
  }
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    c[i] = g[cnt[i]][i];
  }
  return c;
}