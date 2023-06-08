struct unionfind{
  vector<int> p;
  vector<int> mx;
  unionfind(int N){
    p = vector<int>(N, -1);
    mx = vector<int>(N);
    for (int i = 0; i < N; i++){
      mx[i] = i;
    }
  };
  int root(int x){
    if (p[x] == -1){
      return x;
    } else {
      p[x] = root(p[x]);
      return p[x];
    }
  }
  bool same(int x, int y){
    return root(x) == root(y);
  }
  void unite(int x, int y){
    x = root(x);
    y = root(y);
    if (x != y){
      p[x] = y;
      mx[y] = max(mx[y], mx[x]);
    }
  }
  int max_id(int x){
    return mx[root(x)];
  }
};
unionfind UF(n);
