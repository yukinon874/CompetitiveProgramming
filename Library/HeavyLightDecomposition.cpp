#include<bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define ALL(A) A.begin(),A.end()
#define RALL(A) A.rbegin(),A.rend()
typedef long long ll;
typedef pair<ll,ll> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template<typename T> T gcd(T a,T b){return b?gcd(b,a%b):a;}
const ll mod=1000000007;
const ll LINF=1LL<<62;
const int INF=1<<30;
int dx[]={1,0,-1,0,1,-1,1,-1};
int dy[]={0,1,0,-1,1,-1,-1,1};



struct edge {int from;int to;int cost;int idx;
    bool operator<(const edge &right)const{ return cost < right.cost;}
};

struct UnionFind{
    vector<int> data;

    UnionFind(int sz){
        data.assign(sz, -1);
    }

    int find(int k){
        if(data[k] < 0) return k;
        return data[k] = find(data[k]);
    }

    bool unite(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    int size(int k){
        return -data[find(k)];
    }

};


template< typename G >
struct HeavyLightDecomposition {
    G &g;
    vector< int > sz, in, out, head, rev, par;

    HeavyLightDecomposition(G &g) :
        g(g), sz(g.size()), in(g.size()), out(g.size()), head(g.size()), rev(g.size()), par(g.size()) {}

    void dfs_sz(int idx, int p) {
        par[idx] = p;
        sz[idx] = 1;
        if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
        for(auto &to : g[idx]) {
            if(to == p) continue;
            dfs_sz(to, idx);
            sz[idx] += sz[to];
            if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
        }
    }

    void dfs_hld(int idx, int par, int &times) {
        in[idx] = times++;
        rev[in[idx]] = idx;
        for(auto &to : g[idx]) {
            if(to == par) continue;
            head[to] = (g[idx][0] == to ? head[idx] : to);
            dfs_hld(to, idx, times);
        }
        out[idx] = times;
    }

    void build() {
        dfs_sz(0, -1);
        int t = 0;
        dfs_hld(0, -1, t);
    }

    int la(int v, int k) {
        while(1) {
            int u = head[v];
            if(in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) {
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v);
            if(head[u] == head[v]) return u;
        }
    }

    template< typename T, typename Q, typename F >
        T query(int u, int v, const T &ti, const Q &q, const F &f, bool edge = false) {
            T l = ti, r = ti;
            for(;; v = par[head[v]]) {
                if(in[u] > in[v]) swap(u, v), swap(l, r);
                if(head[u] == head[v]) break;
                l = f(q(in[head[v]], in[v] + 1), l);
            }
            return f(f(q(in[u] + edge, in[v] + 1), l), r);
            //  return {f(q(in[u] + edge, in[v] + 1), l), r};
        }

    template< typename Q >
        void add(int u, int v, const Q &q, bool edge = false) {
            for(;; v = par[head[v]]) {
                if(in[u] > in[v]) swap(u, v);
                if(head[u] == head[v]) break;
                q(in[head[v]], in[v] + 1);
            }
            q(in[u] + edge, in[v] + 1);
        }
};

template< typename T >
struct SegmentTree{
    private:
        int n;
        vector<T> segMax;
        vector<T> segAdd;

    public:
        SegmentTree(int sz){
            n = 1;
            while(n < sz) n *= 2;
            segMax.resize(2*n-1, 0);
            segAdd.resize(2*n-1, 0);
        }

        void add(int a, int b, T x, int k, int l, int r) {
            if (r <= a || b <= l) return;
            if (a <= l && r <= b){
                segAdd[k] += x;
                return;
            }
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);
            segMax[k] = max(segMax[k * 2 + 1] + segAdd[k * 2 + 1], segMax[k * 2 + 2] + segAdd[k * 2 + 2]);
        }

        void add(int a,int b, T x) {
            add(a, b, x, 0, 0, n);
        }

        T getMax(int a, int b, int k, int l, int r) {
            if (r <= a || b <= l) return 0;
            if (a <= l && r <= b) return (segMax[k] + segAdd[k]);
            T left = getMax(a, b, k * 2 + 1, l, (l + r) / 2);
            T right = getMax(a, b, k * 2 + 2, (l + r) / 2, r);
            return (max(left, right) + segAdd[k]);
        }

        T getMax(int a,int b){
            return getMax(a, b, 0, 0, n);
        }
};

vector<P> sub_G[1<<17];
vector<ll> s(1<<17,0);
void dfs(int u,int v,ll c){
    if(u != 0) s[u] = c;
    for(auto g:sub_G[u]){
        if(g.fs == v) continue;
        dfs(g.fs, u, g.sc);
    }
}

int main(){
    int n,m;cin >> n >> m;
    vector<edge> E(m);
    for (int i = 0; i < m; i++) {
        cin >> E[i].from >> E[i].to >> E[i].cost;
        E[i].from--, E[i].to--;
        E[i].idx = i;
    }
    sort(ALL(E));
    UnionFind uf(n);
    ll sum = 0;
    SegmentTree<ll> seg(n);
    vector<vector<int>> G(n);
    HeavyLightDecomposition<vector<vector<int>>> hld(G);
    vector<edge> v;
    for (int i = 0; i < m; i++) {
        if(uf.unite(E[i].from, E[i].to)){
            G[E[i].from].pb(E[i].to);
            G[E[i].to].pb(E[i].from);
            v.pb(E[i]);
            sum += E[i].cost;
        }
    }
    hld.build();
    for (int i = 0; i < v.size(); i++) {
        hld.add(v[i].from, v[i].to, [&](int l, int r){seg.add(l, r, v[i].cost);}, true);
    }
    vector<ll> ans(m);
    for (int i = 0; i < m; i++) {
        ll res = hld.query(E[i].from, E[i].to, -1, [&](int l, int r){ return seg.getMax(l, r);}, [&](ll l, ll r){ return max(l, r); }, true);
        ans[E[i].idx] = sum - res + E[i].cost;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
