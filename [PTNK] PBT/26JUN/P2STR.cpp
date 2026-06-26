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
string s;
bitset<MAXN> palind[MAXN];
ll prefL[MAXN][MAXN], prefR[MAXN][MAXN];
ll dp[2][MAXN];

void init() {
    cin >> s;
    n = SZ(s);
    s = ' ' + s;
}

void solve() {  
    ll res = 0;
    for (int i = n; i >= 1; --i) {
        palind[i][i] = 1;
        prefL[i][i] = 1; prefR[i][i] = 1;
        for (int j = 1; j <= n; ++j) dp[i & 1][j] = 0;

        for (int j = i + 1; j <= n; ++j) {
            if (j - i == 1) palind[i][j] = (s[i] == s[j]);
            else palind[i][j] = (s[i] == s[j] && palind[i + 1][j - 1]);
            prefL[i][j] = prefL[i][j - 1] + palind[i][j];
            prefR[i][j] = prefR[i + 1][j] + palind[i][j];

            if (s[i] == s[j])
                dp[i & 1][j] = dp[(i + 1) & 1][j - 1] + prefL[i + 1][j - 1] + prefR[i + 1][j - 1] + 1;
            res += dp[i & 1][j];
        }
    }

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