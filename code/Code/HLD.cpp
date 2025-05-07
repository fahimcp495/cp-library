vector<int> adj[N];
int tin[N], tout[N], sz[N], dep[N], par[N][K], hc[N];
void dfs(int u) {
  tin[u] = t++;
  for (int k = 1; k < K; ++k)
    par[u][k] = par[par[u][k - 1]][k - 1];
  sz[u] = 1, hc[u] = -1;
  for (auto v: adj[u]) {
    if (v == par[u][0])  continue;
    par[v][0] = u;
    dep[v] = dep[u] + 1;
    dfs(v);
    sz[u] += sz[v];
    if (hc[u] == -1 or sz[v] > sz[hc[u]])
      hc[u] = v;
  }
  tout[u] = t++;
}
bool is_anc(int u, int v) {
  return tin[u]<=tin[v] and tout[v]<=tout[u];
}
int get_lca(int u, int v) {
  if (is_anc(u, v))  return u;
  if (is_anc(v, u))  return v;
  for (int k = K - 1; k >= 0; --k)
    if (!is_anc(par[u][k], v))
      u = par[u][k];
  return par[u][0];
}
int idx, in[N], out[N], hd[N];
void hld(int u) {
  in[u] = idx++;
  if (hd[u] == -1)  hd[u] = u;
  if (hc[u] != -1)  hd[hc[u]] = hd[u], hld(hc[u]);
  for (auto v: adj[u]) {
    if (v != par[u][0] and v != hc[u])  hld(v);
  }
  out[u] = ptr - 1;
}
void pupdate(int u, int v, int x) {
  while (hd[u] != hd[v]) {
    if(dep[hd[u]]>dep[hd[v]]) swap(u, v);
    add(in[hd[v]], in[v], x);
    v = par[hd[v]][0];
  }
  if (dep[u] > dep[v]) swap(u, v);
  add(in[u], in[v], x);
  // u is the lca
}
int psum(int u, int v) {
  int ret = 0;
  while (hd[u] != hd[v]) {
    if(dep[hd[u]]>dep[hd[v]]) swap(u, v);
    ret += rsum(in[hd[v]], in[v]);
    v = par[hd[v]][0];
  }
  if (dep[u] > dep[v]) swap(u, v);
  ret += rsum(in[u], in[v]);  // if weight in edges, then exclude lca, by query on (in[u] + 1, in[v])
  // u is the lca
  return ret;
}
// Query from u to root
ll query (int u) {
  ll ret = 0;
  while (1) {
    ret += rsum(pos[hd[u]], pos[u]);
    if (hd[u] == 0) break;
    u = par[hd[u]];
  }
  return ret;
}
void init(int n, int r) {
  par[r] = r;
  for (int u = 0; u < n; ++u) {
    par[u][0] = 0;
  }
  dfs(r);
  idx = 0;
  fill(hd, hd + n, -1);
  hld(r);
}