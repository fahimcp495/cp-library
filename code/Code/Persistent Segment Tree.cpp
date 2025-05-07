const int N = 2e5+5, K = 4 + (1 + __lg(Q)); // Q for number of times add() is called
int n, a[N], L[K * N], R[K * N], cur;
ll st[K * N];
int copy(int u) {
  ++cur; st[cur] = st[u];
  L[cur] = L[u]; R[cur] = R[u];
  return cur;
}
int build(int s = 0, int e = n - 1) {
  int u = ++cur;
  if (s == e) { st[u] = a[s]; return u;}
  int m = s + e >> 1;
  L[u]=build(s, m); R[u]=build(m + 1, e);
  st[u] = st[L[u]] + st[R[u]]; return u;
}
int add(int i, ll x, int u, int s = 0, int e = n - 1) {
  u = copy(u);
  if (s == e) { st[u] += x; return u; }
  int &v = L[u], &w = R[u], m = s + e >> 1;
  if (i <= m) v = add(i, x, v, s, m);
  else w = add(i, x, w, m + 1, e);
  st[u] = st[v] + st[w]; return u;
}
ll rsum(int l, int r, int u, int s = 0, int e = n - 1) {
  if (e < l or r < s) return 0;
  if (l <= s and e <= r) return st[u];
  int v = L[u], w = R[u], m = s + e >> 1;
  return rsum(l, r, v, s, m) + rsum(l, r, w, m + 1, e);
}
// Return count of [l...r] in (ul...ur] subarray
int rcnt(int l, int r, int ul, int ur, int s = 0, int e = n - 1) {
  if (l > r or e < l or r < s) return 0;
  if (l <= s and e <= r) return st[ur] - st[ul];
  int m = s + e >> 1;
  return rcnt(l, r, L[ul], L[ur], s, m) + rcnt(l, r, R[ul], R[ur], m + 1, e);
}
// Return kth smallest number in [l...r] subarray
int kth(int k, int ul, int ur, int s = 0, int e = n - 1) {
  if (s == e) return s;
  int m = s + e >> 1;
  int x = st[L[ur]] - st[L[ul]];
  if (x >= k) return kth(k, L[ul], L[ur], s, m);
  else return kth(k - x, R[ul], R[ur], m + 1, e);
}
// while finding kth smallest number among union of some disjoint subarrays
// Specially, while finding kth smallest number in a path using HLD
int kth(int k, vector<array<int, 2>> u, int s = 0, int e = n - 1) {
  if (s == e) return s;
  int m = s + e >> 1;
  int sz = u.size(), x = 0;
  vector<array<int, 2>> v(sz), w(sz);
  for (int i = 0; i < sz; ++i) {
    v[i] = {L[u[i][0]], L[u[i][1]]};
    w[i] = {R[u[i][0]], R[u[i][1]]};
    x += st[v[i][1]] - st[v[i][0]];
  }
  if (x >= k) return kth(k, v, s, m);
  else return kth(k - x, w, m + 1, e);
}
// With Lazy
const int N = 1e5+5, K = 4 + 4 * (__lg(N) + 1);
int n, a[N], L[K * N], R[K * N], cur;
ll st[K * N], lz[K * N];
int copy(int u) {
  st[++cur] = st[u]; lz[cur] = lz[u];
  L[cur] = L[u]; R[cur] = R[u];
  return cur;
}
void push(int u, int s, int e) {
  if (!lz[u])  return ;
  int v = L[u], w = R[u], m = s + e >> 1;
  st[v] += (m - s + 1) * lz[u];
  st[w] += (e - m) * lz[u];
  lz[v]+=lz[u]; lz[w]+=lz[u]; lz[u]=0;
}
int build(int s = 0, int e = n - 1) {
  int u = ++cur;
  if (s == e) { st[u] = a[s]; return u;}
  int m = s + e >> 1;
  L[u] = build(s, m); R[u] = build(m + 1, e);
  st[u] = st[L[u]] + st[R[u]]; return u;
}
void add(int l, int r, ll x, int u, int s = 0, int e = n - 1) {
  if (e < l or r < s) return;
  if (l <= s and e <= r) {
    st[u] += (e - s + 1) * x;
    lz[u] += x; return; }
  int &v = L[u], &w = R[u], m = s + e >> 1;
  v = copy(v), w = copy(w);
  push(u, s, e); add(l,r,x,v,s,m);
  add(l,r,x,w,m+1,e); st[u]=st[v]+st[w];
}
ll rsum(int l, int r, int u, int s = 0, int e = n - 1) {
  if (e < l or r < s) return 0;
  if (l <= s and e <= r) return st[u];
  int &v = L[u], &w = R[u], m = s + e >> 1;
  if (lz[u]){ v=copy(v), w=copy(w);
    push(u, s, e); }
  return rsum(l, r, v, s, m) + rsum(l, r, w, m + 1, e);
}
cur = 0; root[0] = build();
root[i + 1] = copy(root[i]);
add(l, r, x, root[i + 1])
cout << rsum(l, r, ver[i]) << "\n";