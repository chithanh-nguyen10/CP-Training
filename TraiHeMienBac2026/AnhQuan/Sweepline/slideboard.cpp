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

struct DSU {
    int n;
    vector<int> par, sz, mi, mx, cnt;
    vector<int> diff, lst; // For tracking result

    DSU(int _n) : n(_n), par(n + 5), sz(n + 5, 1), mi(n + 5), mx(n + 5), cnt(n + 5, 1), diff(n + 5, 0), lst(n + 5, 1) {
        iota(all(par), 0);
        iota(all(mi), 0);
        iota(all(mx), 0);
    }

    int findSet(int u) {
        while (u != par[u]) u = par[u] = par[par[u]];
        return u;
    }

    void pushDown(int u, int r) {
        int len = r - lst[u];
        if (cnt[u]) {
            int r = mx[u], l = r - cnt[u] + 1;
            diff[l] += len; diff[r + 1] -= len;
        }

        lst[u] = r;
    }

    bool unite(int u, int v, int r) {
        u = findSet(u); v = findSet(v);
        if (u == v) {
            pushDown(u, r);
            return 0;
        }
        pushDown(u, r); pushDown(v, r);
        if (sz[u] < sz[v]) swap(u, v);

        par[v] = u; sz[u] += sz[v];
        cnt[u] += cnt[v];
        minimize(mi[u], mi[v]);
        maximize(mx[u], mx[v]);

        return 1;
    }

    void removeBlock(int u, int r) {
        u = findSet(u);
        pushDown(u, r);
        cnt[u]--;
    }

    void gg() {
        for (int i = 1; i <= n; ++i)
            if (i == findSet(i)) pushDown(i, n + 1);
        for (int i = 1; i <= n; ++i) diff[i] += diff[i - 1];
    }
};

const int MAXN = (int)5e5 + 5;
int n, a[MAXN], h[MAXN];
vector<int> evtsBlock[MAXN], evtsBarrier[MAXN];

void init() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        evtsBlock[a[i] + 1].push_back(i);
    }

    for (int i = 1; i < n; ++i) {
        cin >> h[i];
        evtsBarrier[h[i] + 1].push_back(i);
    }
}

void solve() {
    DSU dsu(n);

    for (int i = 1; i <= n; ++i) {
        for (int pos : evtsBlock[i]) {
            dsu.removeBlock(pos, i);
        }
        for (int pos : evtsBarrier[i]) {
            dsu.unite(pos, pos + 1, i);
        }
    }

    dsu.gg();
    for (int i = 1; i <= n; ++i) cout << dsu.diff[i] << ' ';
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