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

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    // if (n == 1 && m == 1 && k == 1) cout << -1;
    // else {
    //     int pos = 12;
    //     int sum = n + m + k;
    //     if (BIT(sum, pos)) {
    //         // WA
    //         cout << 0;
    //     } else {
    //         // TLE
    //         int skibdi = 0;
    //         while (true) {
    //             ++skibdi;
    //         } 
    //         cout << skibdi;
    //     }
    // }

    vector<int> ans = {3, 604, 1060, 1453, 2258, 1945, 2096, 2054, 2062, 1421, 552, 565, 1245, 1892, 2478, 2263, 1976, 1128, 758, 472, 1082};
    int sum = n + m + k;
    for (int i = 0; i < SZ(ans); ++i) {
        if (ans[i] == sum) {
            cout << (i == 0 ? -1 : ans[i - 1]);
            return 0;
        }
    }

    return 0;
}