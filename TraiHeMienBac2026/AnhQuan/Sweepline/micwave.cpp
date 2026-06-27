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

const int MAXN = (int)3e5 + 5;
int n, m, a[MAXN], nxt[MAXN];
set<int> vals;

struct FenwickTree {
    int n;
    vector<int> fen;

    FenwickTree(int _n) : n(_n), fen(n + 5, 0) {}

    void update(int idx, int v) {
        for (int i = idx; i <= n; i += i & -i)
            fen[i] += v;
    }

    int get(int idx) {
        int sum = 0;
        for (int i = idx; i; i -= i & -i)
            sum += fen[i];
        return sum;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
};

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vals.insert(a[i]);
    }
    fill(nxt, nxt + m + 1, n + 1);
}

void solve() {
    FenwickTree fen(n);

    ll ans = 0;
    for (int i = n; i >= 1; --i) {
        fen.update(i, 1); 
        if (nxt[a[i]] <= n) fen.update(nxt[a[i]], -1);
        ans += fen.query(i + 1, nxt[a[i]] - 1);
        nxt[a[i]] = i;
    }

    int d = SZ(vals);
    ans += 1ll * m * (m - 1) / 2;
    ans -= 1ll * (m - d) * (m - d - 1) / 2;

    cout << ans;
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