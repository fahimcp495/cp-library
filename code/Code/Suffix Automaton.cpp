int len[2 * N], lnk[2 * N], last, sz = 1;
unordered_map<char, int> to[2 * N]; // Use map during finding kth substring
int deg[2 * N], focc[2 * N];  // First Occurrence
ll cnt[2 * N], dp[2 * N];
void init(int n) {
  fill(deg, deg + sz, 0);
  fill(cnt, cnt + sz, 0);
  while (sz) to[--sz].clear();
  lnk[0] = -1, last = 0, sz = 1;
}
void add (char c, int i) {
  int cur = sz++;
  len[cur] = len[last] + 1;
  cnt[cur] = 1; dp[cur] = i;
  focc[cur] = i;
  int u = last;
  last = cur;
  while (u != -1 and !to[u].count(c)) {
    to[u][c] = cur;
    u = lnk[u];
  }
  if (u == -1) {
    lnk[cur] = 0;
  }
  else {
    int v = to[u][c];
    if (len[u] + 1 == len[v]) {
      lnk[cur] = v;
    }
    else {
      int w = sz++;
      len[w] = len[u] + 1, lnk[w] = lnk[v], to[w] = to[v];
      focc[w] = focc[v];
      while (u != -1 and to[u][c] == v) {
        to[u][c] = w, u = lnk[u];
      }
      lnk[cur] = lnk[v] = w;
    }
  }
}
bool exist (string &p) {
  int u = 0;
  for (auto c: p) {
    if (!to[u].count(c)) return false;
    u = to[u][c];
  }
  return true;
}
void build() {
  deg[0] = 1;
  for (int u = 1; u < sz; ++u) {
    deg[lnk[u]]++;
  }
  queue<int> q;
  for (int u = 0; u < sz; ++u) {
    if (!deg[u]) q.push(u);
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    int v = lnk[u];
    cnt[v] += cnt[u]; // DP on suffix link tree
    for (auto [c, v]: to[u]) { // DP on DAG
      dp[u] = max(dp[u], dp[v]);
    }
    deg[v]--;
    if (!deg[v]) q.push(v);
  }
}
## Count number of occurrence for each k length substring of s in SA
ll count (string s, int k) {
  ll ret = 0;
  int u = 0, L = 0;
  for (auto c: s) {
    while (u and !to[u].count(c)) u = lnk[u], L = len[u];
    if (!to[u].count(c)) continue;
    u = to[u][c], L++;
    while (len[lnk[u]] >= k) u = lnk[u], L = len[u];
    if (L >= k) ret += cnt[u];
  }
  return ret;
}
## Kth substring (not distinct)
ll dp[2 * N];
ll dfs (int u) {
  if (dp[u] != -1) return dp[u];
  dp[u] = cnt[u]; // For distinct dp[u] = 1
  for (auto [c, v]: to[u]) {
    dp[u] += dfs(v);
  }
  return dp[u];
}
void yo (int u, ll k, string &s) {
  if (k <= 0) return ;
  for (auto [c, v]: to[u]) {
    if (k > dfs(v)) k -= dfs(v);
    else {
      s += c;
      k -= cnt[v];  // For distinct k -= 1
      yo(v, k, s);
      return ;
    }
  }
}