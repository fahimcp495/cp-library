/**
 * Author: internet
 * Date: 2021-08-11
 * License: CC0
 * Source: nirjhor library
 * Description: Lower bound on capacity -- create a supersource, a supersink. If $u\rightarrow v$ has a lower bound of $L$, give an edge from supersource to $v$ with capacity $L$. Give an edge from $u$ to supersink with capacity $L$. Give an edge from normal sink to normal source with capacity infinity. If max flow here is equal to $L$, then the lower bound can be satisfied. For minimum flow satisfying lower bounds, binary search on the capacity from normal sink to normal source (instead of assigning inf). For maximum flow satisfying bounds, just add another source to normal source and binary search on capacity.
 * Time: $O(V^2 E)$, (on unit graphs $O(E\sqrt V)$)
 * Status: stress-tested
 */

// Effective flows are adj[u][3] where adj[u][3] > 0
ll get_max_flow(vector<array<int, 3>> edges, int n, int s, int t) {
  vector<array<ll, 4>> adj[n];
  for (auto [u, v, c]: edges) {
    adj[u].push_back({v, (int)adj[v].size(), c, 0});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
  } 

  ll max_flow = 0;
  while (true) {
    queue<int> q;  q.push(s);
    vector<int> dis(n, -1);  dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (auto [v, idx, c, f]: adj[u]) {
        if (dis[v] == -1 and c > f) {
          q.push(v);
          dis[v] = dis[u] + 1;
        }
      }
    }
    if (dis[t] == -1)  break;
    vector<int> next(n);
    function<ll(int, ll)> dfs = [&] (int u, ll flow) {
      if (u == t)  return flow;
      while (next[u] < adj[u].size()) {
        auto &[v, idx, c, f] = adj[u][next[u]++];
        if (c > f and dis[v] == dis[u] + 1) {
          ll bn = dfs(v, min(flow, c - f));
          if (bn > 0) {
            f += bn;
            adj[v][idx][3] -= bn;
            return bn;
          }
        }
      }
      return 0ll;
    };

    while (ll flow = dfs(s, LLONG_MAX)) {
      max_flow += flow;
    }
  }
  return max_flow;
}