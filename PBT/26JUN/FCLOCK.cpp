/*
Author: Nguyen Chi Thanh - High School for the Gifted - VNU.HCM (i2528)
*/
#include <bits/stdc++.h>
using namespace std;

/* START OF TEMPALTE */

#define int long long
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

const int MOD = 86400;

int extgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }

    int x1, y1;
    int g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;

    return g;
}

int inv(int a, int mod) {
    int x, y;
    extgcd(a, mod, x, y);
    x %= mod; if (x < 0) x += mod;
    return x;
}

bool crt(int &r1, int &m1, int r2, int m2) {
    int g = __gcd(m1, m2);
    if ((r1 - r2) % g != 0) return 0;

    int lcm = m1 / g * m2;
    int a = m1 / g, b = (r2 - r1) / g;
    int mod = m2 / g, k = 0;

    if (mod != 1) {
        a %= mod;
        if (a < 0) a += mod;
        b %= mod;
        if (b < 0) b += mod;
        k = b * inv(a, mod) % mod;
    }

    r1 = (r1 + m1 * k) % lcm;
    if (r1 < 0) r1 += lcm;
    m1 = lcm;

    return true;
}

void solve() {
    int n; cin >> n;

    int t1, d1; cin >> t1 >> d1;
    int cur_r = 0, cur_m = 1;

    for (int i = 2; i <= n; ++i) {
        int ti, di; cin >> ti >> di;
        // (Di - D1) * x = (T1 - Ti) (mod MOD)
        int a = (di - d1) % MOD; if (a < 0) a += MOD;
        int b = (t1 - ti) % MOD; if (b < 0) b += MOD;

        int g = __gcd(a, MOD);
        if (b % g != 0) {
            cout << 0 << '\n';
            return;
        }

        a /= g; b /= g; int m = MOD / g;
        int rhs = 0;
        if (m != 1) rhs = inv(a, m) * b % m;
        // cout << rhs << ' ' << m << '\n';
        if (!crt(cur_r, cur_m, rhs, m)) {
            cout << 0 << '\n';
            return;
        };
    }

    int res = 0;
    for (int x = 0; x < MOD; ++x) {
        if (x % cur_m == cur_r) ++res;
    }

    cout << res << '\n';
}

signed main() {
    #ifdef NCTHANH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}