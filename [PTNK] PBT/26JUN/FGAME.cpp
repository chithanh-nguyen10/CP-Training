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

const int MAXN = 1005;
int n, m, grundy[MAXN][MAXN];
ll pref[MAXN][MAXN];
int colmask[3][MAXN];

void solve() {
    cin >> n >> m;
    memset(grundy, 0, sizeof grundy); memset(pref, 0, sizeof pref);
    memset(colmask, 0, sizeof colmask);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> pref[i][j];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];

    for (int j = 1; j <= m; ++j)
        colmask[0][j] |= MASK(0);

    for (int i = 1; i <= n; ++i) {
        vector<int> rowmask(3, 0);
        rowmask[0] |= MASK(0);

        for (int j = 1; j <= m; ++j) {
            // for (int delRow = 1; delRow <= i; ++delRow) {
            //     ll sum = query(i - delRow + 1, 1, i, j);
            //     if (sum % 3 != 1) continue;
            //     // cout << "TAKE GRUNDY AT (" << i - delRow << ", " << j << ")\n";
            //     vis[grundy[i - delRow][j]] = timer;
            // }

            // for (int delCol = 1; delCol <= j; ++delCol) {
            //     ll sum = query(1, j - delCol + 1, i, j);
            //     if (sum % 3 != 1) continue;
            //     // cout << "TAKE GRUNDY AT (" << i << ", " << j - delCol << ")\n";
            //     vis[grundy[i][j - delCol]] = timer;
            // }

            int mod = pref[i][j] % 3;
            int need = (mod + 2) % 3;

            int cur = rowmask[need] | colmask[need][j];
            int mex = 0;
            while (BIT(cur, mex)) ++mex;

            grundy[i][j] = mex;

            rowmask[mod] |= MASK(grundy[i][j]);
            colmask[mod][j] |= MASK(grundy[i][j]);
            // int mex = 0;
            // while (vis[mex] == timer) ++mex;
            // grundy[i][j] = mex;
        }
    }    

    // for (int i = 1; i <= n; ++i) debug(grundy[i], 1, m);
    // cout << '\n';
    cout << (grundy[n][m] != 0) << '\n';
}

signed main() {
    #ifdef NCTHANH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    int T = 5;
    while (T--) {
        solve();
    }

    return 0;
}