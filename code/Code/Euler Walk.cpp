/**
 * Author: nirjhor
 * Date: 2021-08-11
 * License: CC0
 * Source: folklore
 * Description: On directed graph, circuit (or edge disjoint directed cycles) exists iff each node satisfies in\_degree = out\_degree and the graph is strongly connected; path exists iff at most one vertex has in\_degree - out\_degree = 1 and at most one vertex has out\_degree - in\_degree = 1 and all other vertices have in\_degree = out\_degree, and graph is weakly connected. Push edge ID in circ if edges needed.
 * Time: O(V + E)
 * Status: tested
 */

// Directed graph
vector<int> euler_cycle(vector<int> *adj, int s = 0) {
  vector<int> cycle;
  function<void(int)> dfs = [&] (int u) {
    while (!adj[u].empty()) {
      int v = adj[u].back();
      adj[u].pop_back();
      dfs(v);
    }
    cycle.push_back(u);
  };

  dfs(s);
  reverse(cycle.begin(), cycle.end());
  return cycle;
}

// Undirected graph
vector<int> euler_cycle(vector<int> *adj, vector<int> *des_idx, vector<int> *done, int s = 0) {
  vector<int> cycle;

  function<void(int)> dfs = [&] (int u) {
    while (!adj[u].empty()) {
      int i = adj[u].size() - 1;
      if (done[u][i]) {
        adj[u].pop_back();
        continue;
      }
      int v = adj[u][i];
      adj[u].pop_back();
      done[u][i] = 1;
      done[v][des_idx[u][i]] = 1;
      dfs(v);

    }
    cycle.push_back(u);
  };

  dfs(s);
  return cycle;
}

int n, m;  cin >> n >> m;
vector<int> adj[n], des_idx[n], done[n];
vector<int> deg(n);
for (int e = 0; e < m; ++e) {
  int u, v;  cin >> u >> v;  u--, v--;
  des_idx[u].push_back(adj[v].size());
  des_idx[v].push_back(adj[u].size());
  adj[u].push_back(v);
  adj[v].push_back(u);
  done[u].push_back(0);
  done[v].push_back(0);
  deg[u]++, deg[v]++;
}
for (int u = 0; u < n; ++u) {
  if (deg[u] & 1) {
    cout << "IMPOSSIBLE\n";
    return ;
  }
}
vector<int> cycle = euler_cycle(adj, des_idx, done, 0);
if (cycle.size() != m + 1) {
  cout << "IMPOSSIBLE\n";
  return ;
}