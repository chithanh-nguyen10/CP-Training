/*
Author: Nguyen Chi Thanh - High School for the Gifted - VNU.HCM (i2528)
*/
#include <bits/stdc++.h>
using namespace std;

/* START OF TEMPALTE */

// #define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define popcount __builtin_popcountll
#define all(x) (x).begin(), (x).end()
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(x) (1ll << (x))
#define SZ(a) ((int32_t)a.size())

#define debug(a, l, r) {for (int _i = (l); _i <= (r); ++_i) cout << (a)[_i] << ' '; cout << '\n';}

template<class X, class Y>
bool minimize(X &x, const Y &y) {
    if (x > y) {
        x = y;
        return true;
    } else return false;
}

template<class X, class Y>
bool maximize(X &x, const Y &y) {
    if (x < y) {
        x = y;
        return true;
    } else return false;
}

/* END OF TEMPALTE */

const int MAXN = 5005;
int n;
vector<int> adj[MAXN];

void init() {
    cin >> n;
    for (int i = 1; i < n; ++i)  {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int numhash = 0;
map<vector<int>, int> mp;
int id[MAXN];

void solve() {
    function<void(int, int)> dfs = [&] (int u, int par) {
        vector<int> info;

        for (int v : adj[u]) {
            if (v == par) continue;
            dfs(v, u);
            info.push_back(id[v]);
        }

        sort(all(info));
        if (!mp.count(info))
            mp[info] = ++numhash;
        id[u] = mp[info];
    };

    dfs(1, 0);

    map<int, int> cnt;
    for (int i = 1; i <= n; ++i) cnt[id[i]]++;
    ll res = 0;
    for (auto &e : cnt)
        res += 1ll * e.se * (e.se - 1) / 2;
    cout << res;
}

signed main() {
    #ifdef NCTHANH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    init();
    solve();

    return 0;
}