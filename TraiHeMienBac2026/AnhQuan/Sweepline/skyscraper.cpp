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

const int MAXN = (int)1e6 + 5;

struct DSU {
    int n; vector<int> par, sz;

    DSU(int _n) : n(_n), par(n + 5), sz(n + 5, 1) {
        iota(all(par), 0);
    }

    int findSet(int u) {
        while (u != par[u]) u = par[u] = par[par[u]];
        return u;
    }

    bool unite(int u, int v) {
        u = findSet(u); v = findSet(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);

        par[v] = u;
        sz[u] += sz[v];

        return 1;
    }
};

int n, q, h[MAXN], t[MAXN], ans[MAXN];
bool alive[MAXN];

void solve() {
    cin >> n >> q;

    vector<pii> order;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        order.push_back(pii{h[i], i});
        alive[i] = 0;
    }

    for (int i = 1; i <= q; ++i) cin >> t[i];

    sort(all(order), greater<pii>());
    int ptr = 0; DSU dsu(n);
    int numComp = 0;

    for (int i = q; i >= 1; --i) {
        while (ptr < n && order[ptr].fi > t[i]) {
            ++numComp; int pos = order[ptr].se;
            alive[pos] = 1;

            if (pos > 1 && alive[pos - 1] && dsu.unite(pos, pos - 1)) --numComp;
            if (pos < n && alive[pos + 1] && dsu.unite(pos, pos + 1)) --numComp;

            ++ptr;
        }

        ans[i] = numComp;
    }

    for (int i = 1; i <= q; ++i) cout << ans[i] << ' ';
    cout << '\n';
}

signed main() {
    #ifdef NCTHANH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {solve();}

    return 0;
}