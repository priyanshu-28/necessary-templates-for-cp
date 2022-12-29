vector<ll> parent(200010);
vector<ll> siz(200010);

ll find_set(ll v)
{
    if (v == parent[v])
        return v;

    return parent[v] = find_set(parent[v]);

}

void make_set(ll n)
{
    for(int i = 0; i < n; i++)
    {
        parent[i] = i;
        siz[i] = 1;

    }

}

void union_sets(ll a, ll b)
{
    a = find_set(a);
    b = find_set(b);

    if (a != b)
    {
        if (siz[a] < siz[b])
            swap(a, b);

        parent[b] = a;
        siz[a] += siz[b];

    }

}
