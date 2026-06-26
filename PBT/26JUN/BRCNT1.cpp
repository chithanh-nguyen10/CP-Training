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
const ll CAP  = (ll)1e18 + 1;
ll dp[MAXN][MAXN][2];
int n, k; ll p;
string s;
vector<char> charList = {'(', '[', '{', ')', ']', '}'};
int order[256];

void init() {
    cin >> n >> k >> s >> p;
    for (int i = 0; i < 6; ++i) order[(int)charList[i]] = i;
}

bool isLess(char x, char y) {
    return order[(int)x] < order[(int)y];
}

bool isOpen(char x) {
    return (x == '(' || x == '[' || x == '{');
}

bool match(char x, char y) {
    if (x == '(' && y == ')') return 1;
    if (x == '[' && y == ']') return 1;
    if (x == '{' && y == '}') return 1;
    return 0;
}

void solve_part1() {
    int deg = 0; bool ok = 0; ll ans = 1;
    vector<char> st;

    for (int i = 0; i < n; ++i) {
        char cur = s[i];
        for (char pre : charList) {
            if (!isLess(pre, cur)) continue;
            if (isOpen(pre)) {
                if (deg < k) {
                    int nok = (ok | (deg + 1 == k));
                    ans += dp[n - i - 1][deg + 1][nok];
                }
            } else {
                if (!st.empty() && match(st.back(), pre)) {
                    ans += dp[n - i - 1][deg - 1][ok];
                }
            }
        }

        deg += (isOpen(s[i]) ? 1 : -1);
        ok = (ok | (deg == k));
        if (isOpen(s[i])) st.push_back(s[i]);
        else st.pop_back();
    }

    cout << ans << '\n';
}

void solve_part2() {
    int deg = 0; bool ok = 0;
    vector<char> st;

    for (int i = 0; i < n; ++i) {
        char chosen = '(';
        for (char cand : charList) {
            if (isOpen(cand)) {
                if (deg < k) {
                    int nok = (ok | (deg + 1 == k));
                    ll ways =  dp[n - i - 1][deg + 1][nok];
                    if (p <= ways) {
                        chosen = cand;
                        break;
                    } else p -= ways;
                }
            } else {
                if (!st.empty() && match(st.back(), cand)) {
                    ll ways = dp[n - i - 1][deg - 1][ok];
                    if (p <= ways) {
                        chosen = cand;
                        break;
                    } else p -= ways;
                }
            }
        }

        cout << chosen;

        deg += (isOpen(chosen) ? 1 : -1);
        ok = (ok | (deg == k));
        if (isOpen(chosen)) st.push_back(chosen);
        else st.pop_back();
    }
}

void solve() {
    /*
    dp[i][deg][ok]:
        - Need to fill i more places
        - Current (open - close) = deg
        - Has reach the deg = k?
    */

    dp[0][0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int deg = 0; deg <= k; ++deg) {
            for (int ok = 0; ok < 2; ++ok) {
                // Add open
                if (deg < k) {   
                    int nok = (ok | (deg + 1 == k));
                    ll add = min(CAP, 3ll * dp[i - 1][deg + 1][nok]);
                    dp[i][deg][ok] += add;
                    minimize(dp[i][deg][ok], CAP);
                }

                // Add close
                if (deg > 0) {
                    dp[i][deg][ok] += dp[i - 1][deg - 1][ok];
                    minimize(dp[i][deg][ok], CAP);
                }
            }
        }
    }

    solve_part1();
    solve_part2();
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