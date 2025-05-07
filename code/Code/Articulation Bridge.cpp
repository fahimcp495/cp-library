void dfs(int u, int p) {
  tin[u] = lo[u] = ++t; int cnt = 0;
  for (auto [v, f]: adj[u]) {
    if (v == p and ++cnt <= 1) continue;
    if (tin[v]) lo[u] = min(lo[u], tin[v]);
    else {
      dfs(v, u);
      lo[u] = min(lo[u], lo[v]);
      if (tin[u] < lo[v]) {
        ab.insert({u, v});
      }}}}
