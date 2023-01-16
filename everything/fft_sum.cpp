#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define yes cout << "Yes\n"
#define no cout << "No\n"
#define endl "\n"
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(),x.rend()
#define pb push_back
#define ll long long
#define debug(x) cout<<x<<" "
#define lld long double
#define lli long long int
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define INF 1e18
#define mod 998244353 
const int N = 2e5 + 5;
const int MAXN = 1000010;
const double PI = acos(-1);
ll fact[N], invfact[N];
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//

bool cmp(pair<ll,ll> & a,
         pair<ll,ll> & b){
    if(a.first > b.first){
        return true;
    }
    if(a.second == b.second){
        return a.first > b.first;
    }
    
    return false;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//

bool is_p(ll n){if (n == 1){return false;}ll i = 2;while (i * i <= n){if (n % i == 0){return false;}i += 1;}return true;}
bool is2(ll x){return __builtin_popcount(x)==1;}
ll pp(ll a, ll b, ll m){ll ans=1;while(b){if(b&1)ans=(ans*1LL* a % m)%m;b/=2, b%=m;a=(a*1LL* a % m)%m;}return ans % m;}
ll modinv(ll k){return pp(k, mod-2, mod);}
void precompute(){fact[0]=fact[1]=1;for(ll i=2;i<N;i++){fact[i]=fact[i-1]*i;fact[i]%=mod;}invfact[N-1]=modinv(fact[N-1]);for(ll i=N-2;i>=0;i--){invfact[i]=invfact[i+1]*(i+1);invfact[i]%=mod;}}
ll nCr(ll x, ll y){if(y>x){return 0;}ll num=fact[x];num*=invfact[y];num%=mod;num*=invfact[x-y];num%=mod;return num;}
string to_B(ll n){string r;while (n != 0){r = (n % 2 == 0 ? "0" : "1") + r;n /= 2;}return r;}
ll fib(ll n){ll a = 2, b = 3, c, i;if(n == 0){return a;}for(i = 2; i <= n; i++){c = 2*b - a + 2;a = b;b = c;}return b;}
set<ll> printDivisors(ll n){set<ll> v;for (ll i=1; i<=sqrt(n); i++){if (n%i == 0){if (n/i == i)v.insert(i);else{v.insert(i);v.insert(n/i);}}}return v;}
ll countDivisors(ll n){ll cnt = 0;for (ll i=1; i<=sqrt(n); i++){if (n%i == 0){if (n/i == i)cnt++;else{cnt+=2;} }}return cnt;}
ll nextPowerOf2(ll n) { ll p = 1; if (n && !(n & (n - 1))) {return n; }while (p < n) {p <<= 1; }return p; }
ll highestPowerof2(ll x){x |= x >> 1;x |= x >> 2;x |= x >> 4;x |= x >> 8;x |= x >> 16;return x ^ (x >> 1);}
bool isPerfectSquare(ll x){if (x >= 0) {ll sr = sqrt(x);return (sr * sr == x);}return false;}

//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------//

// function<void(ll,ll)> dfs = [&](ll u, ll pre){
     

// };

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (ll i = 0; i < n; i++){
        result[i] = round(fa[i].real());
    }
    ll carry = 0;
    for (ll i = 0; i < n; i++){
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    return result;
}

void solve(){
    ll a, b, c, d, n, m, k, i, j, cnt;

    cin >> n >> m;

    vector<ll> P(n);

    vector<ll> Q(m);
    
    for(i = 0; i < n; i++){
        cin >> P[i];
    }

    for(i = 0; i < m; i++){
        cin >> Q[i];
    }

    ll mx = max(*max_element(all(P)), *max_element(all(Q)));

    vector<ll> A(mx + 1), B(mx + 1);

    for(i = 0; i < max(n,m); i++){
        if(i < n){
            A[P[i]]++;
        }
        if(i < m){
            B[Q[i]]++;
        }
    }


    vector<ll> ans = multiply(A, B);


    for(i = 1; i <= 2*mx; i++){

        if(ans[i] > 0){
            cout << i << " -> " << ans[i] << endl;
        }
    }
    // cout << endl;
    


    
    
    
    
    

    
}

int main()
{
    FIO;
    ll t;
    // cin>>t;
    // precompute();
    t = 1;
    // ll test = 1;
    while(t--){
        // cout<<"Case #"<<test<<": ";
        solve();
        // test++;
    }
    
    return 0;

}
