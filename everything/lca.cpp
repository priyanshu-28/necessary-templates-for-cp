struct data {
    int sum;
    data(): sum(1e9) {};
    data(int _sum): sum(_sum) {};
};

struct SegmentTree {
    int sz = 1;
    vector<struct data> arr;
    void init(int n) {
        while (sz < n)
            sz *= 2;
        arr.resize(sz * 2 + 1);
    }

    struct data merge(struct data& d1, struct data& d2) {
        struct data res;
        res.sum = min(d1.sum, d2.sum);
        return res;
    }

    void build(vector<int>& a, int x, int l, int r){
        if (r - l == 0){
            if (l < (int)a.size()) {
                arr[x].sum = a[l];
            }
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * x + 1, l, mid);
        build(a, 2 * x + 2, mid + 1, r);
        arr[x] = merge(arr[2 * x + 1], arr[2 * x + 2]);
    }
    void build(vector<int>& a){
        build(a, 0, 0, sz);
    }
 
 
    void update(int i, int v, int x, int l, int r){
        if (r - l == 0) {
            arr[x].sum = v;
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid)
            update(i, v, 2 * x + 1, l, mid);
        else
            update(i, v, 2 * x + 2, mid + 1, r);
        arr[x] = merge(arr[2 * x + 1], arr[2 * x + 2]);
    }
 
    void update(int ind, int v) {
        update(ind, v, 0, 0, sz);
    }

    struct data query(int l, int r, int x, int lx, int rx) {
        if (rx < l || r < lx || lx > rx) {
            struct data temp;
            return temp;
        }
        if (l <= lx && rx <= r) {
            return arr[x];
        }
        int mid = (lx + rx) / 2;
        struct data d1 = query(l, r, 2 * x + 1, lx, mid);
        struct data d2 = query(l, r, 2 * x + 2, mid + 1, rx);
        return merge(d1, d2);
    }
    struct data query(int l, int r) {
        return query(l, r, 0, 0, sz);
    }
};

class LCA {
    int n, N;
    vector<vector<int>> graph, LCA;
    vector<int> depth, up, subtree, ind;
    map<pair<int, int>, int> mp;
    vector<SegmentTree> segs;

public:
    void init(int _n) {
        n = _n;
        N = log2(_n) + 2;

        LCA.assign(n + 1, vector<int> (N + 1, -1));
        graph.resize(n + 1);
        up.resize(n + 1);
        subtree.resize(n + 1);
        ind.resize(n + 1);
        segs.resize(n + 1);
        depth.assign(n + 1, 0);
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void calculateLCA() {
        dfs(1, -1, 0);
        dfs_down(1, -1, 0);
        up[1] = 1;
        dfs_up(1, -1, 0);
        for(int i = 1; i <= N; i++) {
            for(int node = 1; node <= n; node++) {
                if(LCA[node][i - 1] != -1) {
                    LCA[node][i] = LCA[ LCA[node][i-1] ][i-1];
                }
            }
        }
    }


    void dfs(int node, int parent, int curDepth) {
        depth[node] = curDepth;
        subtree[node] = node;
        LCA[node][0] = parent;

        for(int child: graph[node]) {
            if (child != parent) {
                dfs(child, node, curDepth + 1);
                subtree[node] = min(subtree[node], subtree[child]);
            }
        }
    }
    void dfs_down(int node, int parent, int curDepth) {
        vector<pair<int, int>> v;
        vector<int> childs;
        for(int child: graph[node]) {
            if (child != parent) {
                v.push_back({child, subtree[child]});
                childs.push_back(subtree[child]);
            }
        }

        int sz = (int)v.size();
        vector<int> suff_mn(sz + 1, 1e9);
        for (int i = sz - 1; i >= 0; i--) {
            suff_mn[i] = min(suff_mn[i + 1], v[i].second);
        }
        int pref = 1e9;
        // cerr << node << ' ' << segs.size() << ' ';
        segs[node].init(sz + 1);
        segs[node].build(childs);
        for (int i = 0; i < sz; i++) {
            int child = v[i].first;
            mp[{node, child}] = min({node, pref, suff_mn[i + 1]});
            pref = min(pref, v[i].second);
            ind[child] = 1;
        }


        for(int child: graph[node]) {
            if (child != parent) {
                dfs_down(child, node, curDepth + 1);
            }
        }
    }
    void dfs_up(int node, int parent, int curDepth) {
        vector<pair<int, int>> v;
        for(int child: graph[node]) {
            if (child != parent) {
                v.push_back({child, subtree[child]});
            }
        }

        int sz = (int)v.size();
        vector<int> suff_mn(sz + 1, 1e9);
        for (int i = sz - 1; i >= 0; i--) {
            suff_mn[i] = min(suff_mn[i + 1], v[i].second);
        }
        int pref = 1e9;
        for (int i = 0; i < sz; i++) {
            int child = v[i].first;
            up[child] = min({up[node], pref, suff_mn[i + 1]});
            pref = min(pref, v[i].second);
        }


        for(int child: graph[node]) {
            if (child != parent) {
                dfs_up(child, node, curDepth + 1);
            }
        }
    }
    int getPar(int u, int diff) {
        while (diff > 0) {
            int jump = log2(diff);
            u = LCA[u][jump];
            diff -= (1 << jump);
        }
        return u;
    }

    int getLCA(int node1, int node2) {
        if(depth[node2] < depth[node1]) {
            swap(node1, node2);
        }

        int diff = depth[node2] - depth[node1];
        while (diff > 0) {
            int jump = log2(diff);
            node2 = LCA[node2][jump];

            diff -= (1 << jump);
        }

        if(node1 == node2) {
            return node1;
        }

        for (int i = N; i >= 0; i--) {
            if (LCA[node1][i] != -1 && LCA[node1][i] != LCA[node2][i]) {
                node1 = LCA[node1][i];
                node2 = LCA[node2][i];
            }
        }
        return LCA[node1][0];
    }
    int getDepth(int u) {
        return depth[u];
    }
    int getAns(int u, int v) {
        return mp[{u, v}];
    }
    int getUp(int u) {
        return up[u];
    }

    int get2Down(int par, int c1, int c2) {
        int i1 = ind[c1];
        int i2 = ind[c2];
        int mn = 1e9;
        if (i1 - 1 >= 0) {
            mn = min(mn, segs[par].query(0, i1 - 1 + 1).sum);
        }
        if (i1 + 1 <= i2 - 1) {
            mn = min(mn, segs[par].query(i1 + 1, i2 - 1 + 1).sum);
        }
        int sz = graph[par].size() - (par != 1);
        if (i2 + 1 < sz) {
            mn = min(mn, segs[par].query(i2 + 1, sz + 1).sum);
        }
        return mn;
    }
};
