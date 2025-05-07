int n, l, dt[N];
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

bool cmp(int u,int v) {
    return tin[u] < tin[v];
}

vector<int>  g[N];

int virtual_tree(vector<int> vert){
    sort(vert.begin(),vert.end(),cmp);

    int k= vert.size();
    for(int i=0;i<k-1;i++){
        int nv= lca(vert[i],vert[i+1]);
        vert.push_back(nv);
    }

    sort(vert.begin(),vert.end(),cmp);
    vert.erase(unique(vert.begin(),vert.end()), vert.end());

    for(auto v:vert) g[v].clear();

    vector<int> stk;
    stk.push_back(vert[0]);

    for(int i=0;i<(int)vert.size();i++){
        int u= vert[i];

        while((int)stk.size() >=2 && !is_ancestor(stk.back(),u)){
            int sz= stk.size();
            g[stk[sz-2]].push_back(stk.back());
            stk.pop_back();
        }

        stk.push_back(u);
    }

    while((int)stk.size()>=2){
        int sz= stk.size();
        g[stk[sz-2]].push_back(stk.back());
        stk.pop_back();
    }

    return stk[0];
}