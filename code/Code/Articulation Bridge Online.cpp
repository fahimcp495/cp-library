// O(n+m)*logn, Can be maintained 2ECC
vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
int ab, lca_itr;
vector<int> last_visit;
void init(int n) {
  par.resize(n);
  dsu_2ecc.resize(n);
  dsu_cc.resize(n);
  dsu_cc_size.resize(n);
  lca_itr = 0;
  last_visit.assign(n, 0);
  for (int i=0; i<n; ++i) {
    dsu_2ecc[i] = dsu_cc[i] = i;
    dsu_cc_size[i] = par[i] = -1;
  }
  ab = 0;
}
int find_2ecc(int v) {
  if (v == -1) return -1;
  return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}
int find_cc(int v) {
  v = find_2ecc(v);
  return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(dsu_cc[v]);
}
void make_root(int v) {
  v = find_2ecc(v);
  int root = v, child = -1;
  while (v != -1) {
    int p = find_2ecc(par[v]);
    par[v] = child; dsu_cc[v] = root;
    child = v; v = p;
  }
  dsu_cc_size[root] = dsu_cc_size[child];
}
void merge_path (int a, int b) {
  ++lca_itr;
  vector<int> path_a, path_b;
  int lca = -1;
  while (lca == -1) {
    if (a != -1) {
      a = find_2ecc(a);
      path_a.push_back(a);
      if (last_visit[a] == lca_itr){
        lca = a; break;
      }
      last_visit[a] = lca_itr;
      a = par[a];
    }
    if (b != -1) {
      b = find_2ecc(b);
      path_b.push_back(b);
      if (last_visit[b] == lca_itr){
        lca = b; break;
      }
      last_visit[b] = lca_itr;
      b = par[b];
    }
  }
  for (int v : path_a) {
    dsu_2ecc[v] = lca;
    if (v == lca) break;
    --ab;
  }
  for (int v : path_b) {
    dsu_2ecc[v] = lca;
    if (v == lca) break;
    --ab;
  }
}
void add_edge(int a, int b) {
  a = find_2ecc(a); b = find_2ecc(b);
  if (a == b) return;
  int ca = find_cc(a);
  int cb = find_cc(b);
  if (ca != cb) {
    ++ab;
    if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
      swap(a, b); swap(ca, cb);
    }
    make_root(a);
    par[a] = dsu_cc[a] = b;
    dsu_cc_size[cb] += dsu_cc_size[a];
  } else {
    merge_path(a, b);
  }
}