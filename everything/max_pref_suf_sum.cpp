vector<ll> a(N), L(N), R(N);

ll n; 

struct Node {
    int sum = 0, pref = 0, suf = 0, best = 0;
    void merge(Node L, Node R) {
        sum = L.sum + R.sum;
        pref = max(L.pref, L.sum + R.pref);
        suf = max(R.suf, R.sum + L.suf);
        best = max({L.best, R.best, L.suf + R.pref});
    }
} seg[N << 2];
 
int getR(int i, int x) {
    return a[i] > x ? i: getR(R[i], x);
}
 
int getL(int i, int x) {
    return a[i] > x ? i: getL(L[i], x);
}
 
void build(int l = 1, int r = n, int root = 1) {
    if (l == r) {
        seg[root].sum = a[l], seg[root].pref = seg[root].suf = seg[root].best = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, root << 1), build(mid + 1, r, root << 1 | 1);
    seg[root].merge(seg[root << 1], seg[root << 1 | 1]);
}
 
Node get(int l, int r, int lv = 1, int rv = n, int root = 1) {
    Node res;
    if (l <= lv && r >= rv)
        return seg[root];
    int mid = lv + rv >> 1;
    if (l <= mid && r >= mid + 1) {
        res.merge(get(l, r, lv, mid, root << 1), get(l, r, mid + 1, rv, root << 1 | 1));
        return res;
    }
    if (l <= mid)
        return get(l, r, lv, mid, root << 1);
    return get(l, r, mid + 1, rv, root << 1 | 1);
}
