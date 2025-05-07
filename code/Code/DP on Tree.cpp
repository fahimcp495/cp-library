// Rerooting Technique

int down[N], dp[N];
// This dfs is supposed to calculate down[u] from its childs down value
void dfs(int u, int p) {
  for (auto v: adj[u]) {
    if (v != p) {
      dfs(v, u);
      // down[u] <- down[v]
    }
  }
}
// This dfs is supposed to calculate its childs up value
// Assuming up[u] is already calculated
void dfs2(int u, int p) {
  // Add contribution of down[siblings] to up[v]
  ll pref = ?;
  for (auto v: adj[u]) {
    // up[v] <- pref
    // Update pref
  }
  reverse(adj[u].begin(), adj[u].end());
  ll suf = ?;
  for (auto v: adj[u]) {
    // up[v] <- suf
    // Update suf
  }
  for (auto v: adj[u]) {
    // Add contribution of up[u] to up[v]
    // up[v] <- up[u]
    dfs2(v, u);
  }
}