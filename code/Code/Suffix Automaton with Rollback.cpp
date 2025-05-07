int len[N], lnk[N], sz, last;
int nxt[N][A];
vector<pair<int*, int>> cng[N];
int R;
void update(int &x, int y) {
  cng[R].push_back({&x, x});
  x = y;
}
void rollback() {
  R--;
  while (!cng[R].empty()) {
    auto [x, y] = cng[R].back();  cng[R].pop_back();
    *x = y;
  }
}
void init (int n) {
  len[0] = 0, lnk[0] = -1, last = 0, sz = 1;
  for (int i = 0; i <= 2 * n; ++i) {
    memset(nxt[i], -1, sizeof nxt[i]);
  }
  while (R > 0)  rollback();
}
void add (int c) {
  int new_sz = sz;
  int cur = new_sz++;
  update(len[cur], len[last] + 1);
  int u = last;
  while (u != -1 and nxt[u][c] == -1) {
    update(nxt[u][c], cur);
    u = lnk[u];
  }
  if (u == -1) {
    update(lnk[cur], 0);
  }
  else {
    int v = nxt[u][c];
    if (len[u] + 1 == len[v]) {
      update(lnk[cur], v);
    }
    else {
      int w = new_sz++;
      update(len[w], len[u] + 1);
      update(lnk[w], lnk[v]);
      for (int a = 0; a < A; ++a) {
        update(nxt[w][a], nxt[v][a]);
      }
      while (u != -1 and nxt[u][c] == v) {
        update(nxt[u][c], w);
        u = lnk[u];
      }
      update(lnk[cur], w);
      update(lnk[v], w);
    }
  }
  update(last, cur);
  update(sz, new_sz);
}
