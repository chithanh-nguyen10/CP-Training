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

const int MAXN = (int)1e4 + 5;
const ll INF = (ll)2e18 + 67;

struct Dinic {
    int n, m;
    vector<ll> flow, cap;
    vector<int> dist, head, work, nxt, point;
    
    Dinic(int _n) : n(_n), m(0), dist(n + 5, 0), head(n + 5, -1), work(n + 5) {}
 
    int addEdge(int u, int v, ll c) {
        int id = m;
        point.push_back(v); cap.push_back(c); flow.push_back(0);
        nxt.push_back(head[u]); head[u] = m++;
        point.push_back(u); cap.push_back(0); flow.push_back(0);
        nxt.push_back(head[v]); head[v] = m++;
        return id;
    }
 
    bool bfs(int s, int t) {
        for (int i = 1; i <= n; ++i) dist[i] = -1;
        dist[s] = 0; queue<int> q; q.push(s);
 
        while (!q.empty()) {
            int u = q.front(); q.pop();
 
            for (int i = head[u]; i >= 0; i = nxt[i]) {
                if (flow[i] < cap[i] && dist[point[i]] < 0) {
                    dist[point[i]] = dist[u] + 1;
                    q.push(point[i]);
                }
            }
        }
 
        return dist[t] >= 0;
    }
 
    ll dfs(int s, int t, ll f) {
        if (s == t) return f;
 
        for (int &i = work[s]; i >= 0; i = nxt[i]) {
            if (flow[i] < cap[i] && dist[point[i]] == dist[s] + 1) {
                ll d = dfs(point[i], t, min(f, cap[i] - flow[i]));
                if (d > 0) {
                    flow[i] += d;
                    flow[i ^ 1] -= d;
                    return d;
                }
            }
        }
 
        return 0;
    }
 
    ll maxflow(int s, int t) {
        ll res = 0;
 
        while (bfs(s, t)) {
            for (int i = 1; i <= n; ++i) work[i] = head[i];
            while (true) {
                ll d = dfs(s, t, INF);
                if (d == 0) break;
                res += d;
            }
        }
 
        return res;
    }
};

struct HeavyLightDecomposition {
    int n, curpos, curchain;
    vector<vector<int>> adj;
    vector<int> sz, parent, head, chain, pos;

    void dfs(int u, int par = 0) {
        sz[u] = 1; parent[u] = par;
        for (int v : adj[u]) {
            if (v == par) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }

    void hld(int u, int par = 0) {
        if (!head[curchain]) head[curchain] = u;
        chain[u] = curchain; pos[u] = curpos;
        ++curpos;

        int nxt = 0;
        for (int v : adj[u])
            if (v != par && (nxt == 0 || sz[v] > sz[nxt])) 
                nxt = v;
        
        if (nxt) hld(nxt, u);
        for (int v : adj[u]) if (v != par && v != nxt) {
            ++curchain;
            hld(v, u);
        }
    }

    void build() {
        curpos = 1; curchain = 1;
        dfs(1); hld(1);
    }

    vector<pii> query(int u, int v) {
        vector<pii> res;
        while (chain[u] != chain[v]) {
            if (chain[u] > chain[v]) {
                res.push_back({pos[head[chain[u]]], pos[u]});
                u = parent[head[chain[u]]];
            } else {
                res.push_back({pos[head[chain[v]]], pos[v]});
                v = parent[head[chain[v]]];
            }
        }

        if (sz[u] > sz[v]) res.push_back({pos[u], pos[v]});
        else res.push_back({pos[v], pos[u]});

        return res;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HeavyLightDecomposition() {}
    void init(int _n) {*this = HeavyLightDecomposition(_n);}
    HeavyLightDecomposition (int _n) : n(_n), adj(n + 5),
    sz(n + 5), parent(n + 5), head(n + 5), chain(n + 5),
    pos(n + 5) {}
};

struct Day {
    int a, b, c;
} info[MAXN];

int n, k, w[MAXN], arr[MAXN], seg[4 * MAXN];
HeavyLightDecomposition HLD;

void init() {
    cin >> n >> k;
    HLD.init(n);
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        HLD.addEdge(u, v);
    }

    HLD.build();
    for (int i = 1; i <= k; ++i) {
        int a, b, c; cin >> a >> b >> c;
        info[i] = {a, b, c};
    }

    for (int i = 1; i <= n; ++i) arr[HLD.pos[i]] = i;
}

void solve() {
    int numNode = 0;
    auto newNode = [&] () {return ++numNode;};

    vector<int> dayNode(k + 5), cityNode(n + 5);
    for (int i = 1; i <= k; ++i) dayNode[i] = newNode();
    for (int i = 1; i <= n; ++i) cityNode[i] = newNode();

    int s = newNode(), t = newNode();
    vector<array<ll, 3>> edges;

    for (int i = 1; i <= k; ++i)
        edges.push_back({s, dayNode[i], info[i].c});
        // cout << s << " -----> " << dayNode[i] << ": CAP = " << info[i].c << '\n';
    for (int i = 1; i <= n; ++i)
        edges.push_back({cityNode[i], t, w[i]});
        // cout << cityNode[i] << " -----> " << t << ": CAP = " << w[i] << '\n';

    function<int(int, int, int)> build = [&] (int id, int l, int r) {
        seg[id] = newNode();
        if (l == r) {
            // cout << seg[id] << " ------> " << cityNode[arr[l]] << '\n';
            edges.push_back({seg[id], cityNode[arr[l]], INF});
            return seg[id];
        }

        int mid = (l + r) >> 1;
        int left = build(id << 1, l, mid);
        int right = build(id << 1 | 1, mid + 1, r);

        edges.push_back({seg[id], left, INF});
        edges.push_back({seg[id], right, INF});
        // cout << seg[id] << " -----> " << left << '\n';
        // cout << seg[id] << " -----> " << right << '\n';
        return seg[id];
    };

    function<void(int, int, int, int, int, vector<int>&)> getNodes = 
    [&] (int id, int l, int r, int u, int v, vector<int> &nodes) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            nodes.push_back(seg[id]);
            return;
        }

        int mid = (l + r) >> 1;
        getNodes(id << 1, l, mid, u, v, nodes);
        getNodes(id << 1 | 1, mid + 1, r, u, v, nodes);
    };

    build(1, 1, n);

    vector<int> nodes;
    for (int i = 1; i <= k; ++i) {
        // cout << "PATH = " << info[i].a << ' ' << info[i].b << '\n';
        nodes.clear();
        vector<pii> ranges = HLD.query(info[i].a, info[i].b);
        for (auto &e : ranges)
            getNodes(1, 1, n, e.fi, e.se, nodes);
        for (int u : nodes) edges.push_back({dayNode[i], u, INF});
    }

    Dinic flow(numNode);
    for (auto &e : edges) flow.addEdge(e[0], e[1], e[2]);

    cout << flow.maxflow(s, t);
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