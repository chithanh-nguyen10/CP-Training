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
bool state[MAXN];

void init() {
    cin >> n;
    string s; cin >> s;
    for (int i = 1; i <= n; ++i) state[i] = (s[i - 1] == '1');
}

void doMove(int x) {
    assert(state[abs(x)] == 1);
    if (x > 0) state[x] = 0;
    else {
        state[-x] = 0;
        state[-x - 1] ^= 1;
    }

    bool ok = 1;
    for (int i = 1; i <= n; ++i) {
        if (state[i]) {
            ok = 0;
            break;
        }
    }

    if (ok) exit(0);
}

void solve() {
    {
        int g = 0;
        for (int i = 1; i <= n; ++i)
            if (state[i]) g ^= ((i & 1) ? 1 : 2);
        if (g == 0) {
            cout << 0 << endl;
            int x; cin >> x;
            doMove(x);
        } else cout << 1 << endl;
    }

    while (true) {
        int g = 0;
        for (int i = 1; i <= n; ++i)
            if (state[i]) g ^= ((i & 1) ? 1 : 2);

        if (g == 1) {
            int target = 0;
            for (int i = 1; i <= n; ++i) {
                if (state[i] == 1 && i % 2 == 1) {
                    target = i;
                    break;
                }
            }

            cout << target << endl;
            doMove(target);
        } else if (g == 2) {
            int target = 0;
            for (int i = 1; i <= n; ++i) {
                if (state[i] == 1 && i % 2 == 0) {
                    target = i;
                    break;
                }
            }

            cout << target << endl;
            doMove(target);
        } else {
            int target = 0;
            for (int i = 2; i <= n; ++i) {
                if (state[i] == 1) {
                    target = i;
                    break;
                }
            }

            cout << -target << endl;
            doMove(-target);
        }

        int x; cin >> x;
        doMove(x);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    init();
    solve();

    return 0;
}