vector<int> adj[N];
int sz[N], cen[N];
void dfs_sz(int u, int p) {
  sz[u] = 1;
  for (auto v: adj[u]) {
    if (v != p and !cen[v]) {
      dfs_sz(v, u); sz[u] += sz[v];
    }
  }
}
int get(int u, int p, int k) {
  for (auto v: adj[u]) {
    if (v != p and !cen[v] and sz[v] > k) return get(v, u, k);
  }
  cen[u] = 1; return u;
}
int cpar[N], cdep[N], dis[N][K];
vector<int> cnt[N], cntp[N];
void dfs(int u, int p, int d) {
  for (auto v: adj[u]) {
    if (v != p and !cen[v]) {
      dis[v][d] = dis[u][d] + 1; dfs(v, u, d);
    }
  }
}
int go(int u, int d) {
  dfs_sz(u, u);
  int tot = sz[u];
  u = get(u, u, sz[u] >> 1);
  cdep[u] = d, dis[u][d] = 0;
  dfs(u, u, d);
  cnt[u].resize(tot);
  cntp[u].resize(tot + 1);
  for (auto v: adj[u]) {
    if (!cen[v]) {
      int w = go(v, d + 1);
      cpar[w] = u;
    }
  }
  return u;
}
int n, k;
ll ans = 0;
void add(int u) {
  int pv = -1, v = u;
  while (v != -1) {
    int rem = k - dis[u][cdep[v]];
    if (rem >= 0 and rem < cnt[v].size()) {
      ans += cnt[v][rem];
    }
    if (pv != -1) {
      if (rem >= 0 and rem < cntp[pv].size()) {
        ans -= cntp[pv][rem];
      }
    }
    pv = v;
    v = cpar[v];
  }
  pv = -1, v = u;
  while (v != -1) {
    int d = dis[u][cdep[v]];
    cnt[v][d]++;
    if (pv != -1) {
      cntp[pv][d]++;
    }
    pv = v;
    v = cpar[v];
  }
}