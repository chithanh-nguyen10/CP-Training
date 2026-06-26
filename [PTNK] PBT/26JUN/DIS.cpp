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

const int MAXN = 2005;
const int MOD  = (int)1e9 + 7;

void add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void sub(int &x, int y) {
    x -= y;
    if (x < 0) x += MOD;
}

struct FenwickTree {
    int n;
    vector<int> fen;

    FenwickTree() {}
    FenwickTree(int _n) : n(_n + 1), fen(n + 5) {}
    void init(int _n) {*this = FenwickTree(_n);}

    void update(int idx, int v) {
        ++idx;
        for (int i = idx; i <= n; i += i & -i)
            add(fen[i], v);
    }

    int get(int idx) {
        ++idx; int sum = 0;
        for (int i = idx; i; i -= i & -i)
            add(sum, fen[i]);
        return sum;
    }
};

int n, a[MAXN];

void init() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}

void solve() {
    int mx = *max_element(a + 1, a + n + 1);
    vector<FenwickTree> fen_row(mx + 5), fen_col(mx + 5);
    for (int i = 0; i <= mx; ++i) {
        fen_row[i].init(mx + 5);
        fen_col[i].init(mx + 5);
    }

    fen_row[0].update(0, 1); fen_col[0].update(0, 1);

    for (int i = 1; i <= n; ++i) {
        // a[i] > x
        vector<int> addRow(mx + 5, 0);
        for (int y = 0; y < a[i]; ++y)
            addRow[y] = fen_col[y].get(a[i] - 1);

        // y < a[i] <= x
        vector<int> addCol(mx + 5, 0);
        for (int x = a[i]; x <= mx; ++x)
            addCol[x] = fen_row[x].get(a[i] - 1);
        
        for (int y = 0; y < a[i]; ++y) {
            fen_row[a[i]].update(y, addRow[y]);
            fen_col[y].update(a[i], addRow[y]);
        }

        for (int x = a[i]; x <= mx; ++x) {
            fen_row[x].update(a[i], addCol[x]);
            fen_col[a[i]].update(x, addCol[x]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= mx; ++i) add(ans, fen_row[i].get(i));
    sub(ans, n + 1);
    cout << ans;

    // vector<vector<int>> dp(mx + 5, vector<int>(mx + 5, 0));
    // dp[0][0] = 1;

    // for (int i = 1; i <= n; ++i) {
    //     vector<vector<int>> ndp = dp;

    //     for (int x = 0; x <= mx; ++x) {
    //         for (int y = 0; y <= mx; ++y) {
    //             if (a[i] <= y || dp[x][y] == 0) continue;
    //             if (a[i] > x) add(ndp[a[i]][y], dp[x][y]);
    //             else add(ndp[x][a[i]], dp[x][y]);
    //         }
    //     }

    //     dp.swap(ndp);
    // }

    // int ans = 0;
    // for (int i = 0; i <= mx; ++i) for (int j = 0; j <= mx; ++j)
    //     add(ans, dp[i][j]);
    // sub(ans, n + 1);
    // cout << ans;
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