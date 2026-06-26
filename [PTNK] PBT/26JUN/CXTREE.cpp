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
const int MOD  = (int)1e9 + 7;
int fact[MAXN], ifact[MAXN];

int bpow(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
        k >>= 1;
    }

    return res;
}

int binom(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1ll * (1ll * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD; 
}

int n, k, numTree[MAXN], dp[MAXN];

void init() {
    cin >> n >> k;

    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    ifact[MAXN - 1] = bpow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; --i)
        ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;

    numTree[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        for (int take = 1; take < i; ++take) {
            int ways = numTree[i - take];
            int label = binom(i - 2, take - 1);
            int cnt = 1ll * numTree[take] * take % MOD;
            numTree[i] += (1ll * cnt * label % MOD) * ways % MOD;
            if (numTree[i] >= MOD) numTree[i] -= MOD;
        }
    }
}

void solve() {
    int threshold = 0;
    for (int i = 1; i <= n / 2; ++i)
        if (i * (n - i) <= k) threshold = i;
    if (threshold == n / 2) {
        cout << numTree[n];
        return;
    }

    dp[0] = 1;
    for (int i = 1; i <= n - 1; ++i) {
        for (int take = 1; take <= min(i, threshold); ++take) {
            int pre = dp[i - take];
            int cur = numTree[take];
            int label = binom(i - 1, take - 1);
            dp[i] += ((1ll * pre * cur % MOD) * label % MOD * take) % MOD;
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
    }
    
    int res = 1ll * dp[n - 1] * n % MOD;
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