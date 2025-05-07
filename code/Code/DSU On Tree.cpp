void dfs(int u, int p) {
  node[t] = u, tin[u] = t++, sz[u] = 1, hc[u] = -1;
  for (auto v: adj[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (hc[u] == -1 or sz[hc[u]] < sz[v]) hc[u] = v;
    }
  }
  tout[u] = t - 1;
}
void dsu(int u, int p, int keep) {
  for (int v: adj[u]) {
    if (v != p and v != hc[u]) dsu(v, u, 0);
  }
  if (hc[u] != -1) dsu(hc[u], u, 1);
  for (auto v: adj[u]) {
    if (v != p and v != hc[u]) {
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = node[i];
        // Update ans if ans is related to path/pair
      }
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = node[i];
        // Add contribution of node w
      }

    }
  }
  // Add contribution of node u
  // Update ans if ans is related to subtree
  if (!keep) {
    for (int i = tin[u]; i <= tout[u]; ++i) {
      int w = node[i];
      // Remove contribution of node w
    }
    // Data structure is empty now
  }
}
dfs(0, 0);  dsu(0, 0, 0);