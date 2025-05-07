int to[N][A], len[N], lnk[N], u, cnt;
int node[N], occ[N], dep[N];
void init() {
  while (cnt >= 0) {
    memset(to[cnt], 0, sizeof(to[cnt]));
    occ[cnt] = 0; cnt--;
  }
  len[1] = -1; lnk[1] = lnk[2] = 1;
  u = cnt = 2;
}
void add(int i) {
  while (s[i-1-len[u]] != s[i]) u=lnk[u];
  int c = s[i] - 'a', v = lnk[u];
  while (s[i-1-len[v]] != s[i]) v=lnk[v];
  if (!to[u][c]) {
    to[u][c] = ++cnt;
    len[cnt] = len[u] + 2;
    lnk[cnt] = len[cnt] == 1? 2: to[v][c];
    dep[cnt] = dep[lnk[cnt]] + 1;
  }
  u = to[u][c]; node[i] = u; occ[u]++;
}
s = " " + s;
init();
for (int i = 1; i < s.size(); ++i) add(i);
for (int u = cnt; u > 2; --cnt) {
  occ[lnk[u]] += occ[u];
}
// The number of palindromic substrings end at i-th position = dep[node[i]]