int trie[N * IDX][2], cnt[N * IDX], root[N], tot = 1;
void init() {
  cnt[tot]=0; root[0]=tot;
}
int add(int u, int x) {
  int uu = ++tot; int ret = uu;
  cnt[u] = cnt[uu];
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = x >> idx & 1;
    trie[uu][!f] = trie[u][!f];
    trie[uu][f] = ++tot;
    uu = trie[uu][f]; u = trie[u][f];
    cnt[uu] = cnt[u] + 1;
  }
  return ret;
}
int max_xor(int u, int x) {
  int ret = 0;
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = x >> idx & 1;
    if (cnt[trie[u][!f]])  ret |= 1 << idx, u = trie[u][!f];
    else  u = trie[u][f];
  }
  return ret;
}