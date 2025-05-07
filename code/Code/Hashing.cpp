const int mod = 1e9 + 7;
const ll P[] = {127, 1000003};
ll p[2][N], inv[2][N];
void init () {
  for (int it = 0; it < 2; ++it) {
    p[it][0] = inv[it][0] = 1;
    ll IP = poww(P[it], -1);
    for (int i = 1; i < N; ++i) {
      p[it][i] = p[it][i - 1] * P[it] % mod;
      inv[it][i] = inv[it][i - 1] * IP % mod;
    }
  }
}
struct RangeHash {
  vector <ll> h[2], rev[2];
  RangeHash (const string s, bool f = 0) {
    for (int it = 0; it < 2; ++it) {
      h[it].resize(s.size() + 1, 0);
      for (int i = 0; i < s.size(); ++i) {
        h[it][i + 1] = (h[it][i] + p[it][i + 1] * s[i]) % mod;
      }
      if (f) {
        rev[it].resize(s.size() + 1, 0);
        for (int i = 0; i < s.size(); ++i) {
          rev[it][i + 1] = (rev[it][i] + inv[it][i + 1] * s[i]) % mod;
        }
      }
    }
  }
  inline ll get (int l, int r) {
    ll z = (h[0][r + 1] - h[0][l] + mod) * inv[0][l + 1] % mod;
    ll o = (h[1][r + 1] - h[1][l] + mod) * inv[1][l + 1] % mod;
    return o << 31 | z;
  }
  inline ll getReverse (int l, int r) {
    ll z = (rev[0][r + 1] - rev[0][l] + mod) * p[0][r + 1] % mod;
    ll o = (rev[1][r + 1] - rev[1][l] + mod) * p[1][r + 1] % mod;
    return o << 31 | z;
  }
};
ll get (string &s) {
  int n = s.size();
  ll z = 0, o = 0;
  for (int i = 0; i < s.size(); ++i) {
    z = (z + p[0][i] * s[i]) % mod;
    o = (o + p[1][i] * s[i]) % mod;
  }
  return o << 31 | z;
}
// Point Update
void update (int i, int x, int u = 1, int s = 0, int e = n - 1) {
  if (s == e) {
    st[0][u] = x * p[0][i] % mod;
    st[1][u] = x * p[1][i] % mod;
    return ;
  }
  int v = u << 1, w = v | 1, m = (s + e) >> 1;
  if (i <= m) update(i, x, v, s, m);
  else update(i, x, w, m + 1, e);
  st[0][u] = addr(st[0][v], st[0][w]);
  st[1][u] = addr(st[1][v], st[1][w]);
}
array<ll, 2> query (int l, int r, int u = 1, int s = 0, int e = n - 1) {
  if (e < l or r < s) return {0, 0};
  if (l <= s and e <= r) return {st[0][u] * inv[0][l] % mod, st[1][u] * inv[1][l] % mod};
  int v = u << 1, w = v | 1, m = (s + e) >> 1;
  auto ql = query(l, r, v, s, m);
  auto qr = query(l, r, w, m + 1, e);
  ll ret0 = addr(ql[0], qr[0]);
  ll ret1 = addr(ql[1], qr[1]);
  return {ret0, ret1};
}