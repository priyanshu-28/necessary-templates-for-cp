vector<vector<ll>> sparse(vector<ll> &v)
{
    ll n = v.size();
    ll k = log2(n)+1;
    vector<vector<ll>> s(n+5,vector<ll> (k+1, INT_MAX));
    for (ll i = 0; i < n; i++)
        s[i][0] = v[i];
 
    for (ll j = 1; j <= k; j++)
    {
        for (ll i = 0; i + (1 << j) <=n; i++)
        {
            s[i][j] = min(1LL*s[i][j-1], 1LL*s[i + (1 << (j - 1))][j - 1]);   
        }
    }
 
    return s;
 
}
 
ll range(vector<vector<ll>> &st,ll L,ll R)
{
    ll i = log2(R - L + 1);
    return min(1LL*st[L][i], 1LL*st[R - (1 << i) + 1][i]);
}
