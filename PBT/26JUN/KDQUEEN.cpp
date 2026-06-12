/*
Author: Nguyen Chi Thanh - High School for the Gifted - VNU.HCM (i2528)
*/
#include <bits/stdc++.h>
using namespace std;

// Name: Modint (based on jiangly's template)

template<int64_t _MOD>
struct Modint{
    static int64_t mod;
    int64_t v;

    static int64_t getMod() {
        if (_MOD != 0) return _MOD;
        return mod;
    }

    static void setMod(int64_t m) {
        mod = m;
    }

    Modint() : v(0) {}
    Modint(int64_t _v) {
        v = _v % getMod();
        if (v < 0) v += getMod();
    }

    Modint& operator += (const Modint &other) {
        v += other.v;
        if (v >= getMod()) v -= getMod();
        return *this;
    }

    Modint& operator -= (const Modint &other) {
        v -= other.v;
        if (v < 0) v += getMod();
        return *this;
    }

    Modint& operator *= (const Modint &other) {
        v = 1ll * v * other.v % getMod();
        return *this;
    }

    Modint pow(int64_t k) const {
        Modint res(1), base = *this;
        while (k) {
            if (k & 1) res *= base;
            base *= base;
            k >>= 1;
        }

        return res;
    }

    Modint inv() const {return pow(getMod() - 2);}

    Modint& operator /= (const Modint &other) {
        *this *= other.inv();
        return *this;
    }

    friend Modint operator + (Modint a, const Modint &b) {return a += b;}
    friend Modint operator - (Modint a, const Modint &b) {return a -= b;}
    friend Modint operator * (Modint a, const Modint &b) {return a *= b;}
    friend Modint operator / (Modint a, const Modint &b) {return a /= b;}

    Modint operator - () const {return Modint(0) - *this;}

    bool operator == (const Modint &t) const {return v == t.v;}
    bool operator != (const Modint &t) const {return v != t.v;}
    bool operator < (const Modint &t) const {return v < t.v;}

    friend istream& operator >> (istream &stream, Modint &other) {
        int64_t inp; stream >> inp;
        other = Modint(inp);
        return stream;
    } 

    friend ostream& operator << (ostream &stream, const Modint &other) {
        return stream << other.v;
    }

    // Long long casting
    operator int64_t() const {return v;} 
};

template<>
int64_t Modint<0>::mod = 1;

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

const int MOD  = (int)1e9 + 7;
const int MAXK = (int)1e5 + 5;
#define mint Modint<MOD>

int k, n[MAXK], x[MAXK];

void init() {
    cin >> k;
    for (int i = 1; i <= k; ++i) cin >> n[i];
    for (int i = 1; i <= k; ++i) cin >> x[i];
}
    
void solve() {
    mint res = 0;
    vector<int> evts(k + 5);
    int lim = (int)1e9 + 67;

    // Hang/cot
    for (int i = 1; i <= k; ++i) {
        res += mint(n[i]) - mint(1);

        int cl = x[i] - 1, cr = n[i] - x[i];
        evts[i] = min(cl, cr);
        minimize(lim, max(cl, cr));
    }

    if (k == 1) {
        cout << res;
        return;
    }

    // Duong cheo
    sort(begin(evts) + 1, begin(evts) + k + 1);
    int cur = 1, ptr = 1;
    while (cur <= lim) {
        while (ptr <= k && evts[ptr] < cur) ++ptr;
        int contrib = k - ptr + 1;
        int nxt = lim;
        if (ptr <= k) minimize(nxt, evts[ptr]);
        if (cur <= nxt) {
            res += mint(2).pow(contrib) * mint(nxt - cur + 1);
        }

        cur = nxt + 1;
    }

    cout << res;
}

signed main() {
    #ifdef NCTHANH
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    freopen("KDQUEEN.INP", "r", stdin);
    freopen("KDQUEEN.OUT", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);

    init();
    solve();

    return 0;
}