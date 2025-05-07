using Basis = array<ll, D>;
bool add(Basis &b, ll x) {
  for (int i = D - 1; i >= 0; --i) {
    if (x >> i & 1 ^ 1) continue;
    if (!b[i]) return b[i] = x, true;
    x ^= b[i];
  } return false;
}
void reduce(Basis &b, ll &x) {
  for (int d = D - 1; d >= 0; --d) {
    x = min(x, x ^ b[d]);
  }
}
bool exist(Basis &b, ll x) {
  return reduce(b, x), x == 0;
}
ll max_xor(Basis &b, ll x = 0) {
  for (int i = D - 1; i >= 0; --i) {
    x = max(x, x ^ b[i]);
  } return x;
}
ll kth(Basis &b, ll k) {
  ll ret = 0, rem = rnk;
  for (int i = D - 1; i >= 0; --i) {
    if (!b[i]) continue;
    rem--;
    if (ret >> i & 1) ret ^= b[i];
    if ((1ll << rem) >= k) continue;
    ret ^= b[i]; k -= 1 << rem;
  } return ret;
}
int cnt_supermask(Basis &b, int x) {
  Basis c{0}; int rnk = 0;
  for (auto bi: b) {
    bi &= x, rnk += add(c, bi);
  }
  int ret = 0;
  if (exist(c, x)) {
    ret = two[n - rnk]; // 2^(n-rnk)
    if (x == 0) sub(ret, 1);  // When counting non-empty subsets
  } return ret;
}
Basis b{0};
## Static Range XOR-basis Query
Basis b[N], idx[N];
void build () {
  b[0] = idx[0] = Basis{0};
  for (int i = 0; i < n; ++i) {
    if (i) b[i] = b[i - 1], idx[i] = idx[i - 1];
    ll x = a[i], j = i;
    for (int d = D - 1; d >= 0; --d) {
      if (x >> d & 1 ^ 1)  continue;
      if (!b[i][d]) b[i][d] = x, idx[i][d] = j;
      if (idx[i][d] < j) swap(b[i][d], x), swap(idx[i][d], j);
      x ^= b[i][d];
    }
  }
}
Basis rbasis (int l, int r) {
  Basis ret{0};
  for (int d = D - 1; d >= 0; --d) {
    if (b[r][d] and l <= idx[r][d]) ret[d] = b[r][d];
  }
  return ret;
}
## Maximum XOR Subset Printing
Basis b{0};
vector<int> idx[D];
bool add(ll x, int i) {
  vector<int> cur = {i};
  for (int i = D - 1; i >= 0; --i) {
    if (x >> i & 1 ^ 1) continue;
    if (!b[i]) return b[i] = x, idx[i] = cur, true;
    x ^= b[i], cur.push_back(i);
  } return false;
}
pair<ll, vector<int>> max_xor(ll x = 0) {
  vector<int> ret, cnt(D);
  for (int i = D - 1; i >= 0; --i) {
    if ((x ^ b[i]) > x) {
      x ^= b[i];
      cnt[i] ^= 1;
    }
  }
  for (int i = 0; i < D; ++i) {
    if (cnt[i]) {
      ret.push_back(idx[i][0]);
      for (int j = 1; j < idx[i].size(); ++j) {
        cnt[idx[i][j]] ^= 1;
      }
    }
  }
  return make_pair(x, ret);
}
## Reduced row echelon form (unique).
void reduce(vector<ll> &b, ll &x) {
  for (auto bi: b) x = min(x, x ^ bi);
}
void add(vector<ll> &b, ll x) {
  reduce(b, x);
  if (x) { for (auto &bi: b) {
      bi = min(bi, bi ^ x);
    }
    b.push_back(x);
  }
}
## Previous of upper bound of k with initial value = x
ll ub(vector<ll> &b, ll k, ll x = 0) {
  reduce(b, x);
  sort(b.rbegin(), b.rend());
  for (auto bi: b) {
    if (x > k) x = min(x, x ^ bi);
    else if ((x ^ bi) <= k) x ^= bi;
  }
  if (x > k) x = 0;
  return x;
}