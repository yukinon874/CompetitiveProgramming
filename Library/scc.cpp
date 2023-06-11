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
const ll MOD=1000000007;
const ll LINF=1ll<<60;
const int INF=1<<30;
int dx[]={1,0,-1,0,1,-1,1,-1};
int dy[]={0,1,0,-1,1,-1,-1,1};


template< typename T = int >
struct Edge {
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1) : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template< typename T = int >
struct Graph {
    vector< vector< Edge< T > > > g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const {
        return g.size();
    }

    void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false, bool directed = false) {
        for(int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a += padding;
            b += padding;
            T c = T(1);
            if(weighted) cin >> c;
            if(directed) add_directed_edge(a, b, c);
            else add_edge(a, b, c);
        }
    }
};

template< typename T = int >
using Edges = vector< Edge< T > >;

template< typename T = int >
struct StronglyConnectedComponents : Graph< T > {
    public:
        using Graph< T >::Graph;
        using Graph< T >::g;
        vector< int > comp;
        Graph< T > dag;
        vector< vector< int > > group;

        void build() {
            rg = Graph< T >(g.size());
            for(int i = 0; i < g.size(); i++) {
                for(auto &e : g[i]) {
                    rg.add_directed_edge(e.to, e.from, e.cost);
                }
            }
            comp.assign(g.size(), -1);
            used.assign(g.size(), 0);
            for(int i = 0; i < g.size(); i++) dfs(i);
            reverse(begin(order), end(order));
            int ptr = 0;
            for(int i : order) if(comp[i] == -1) rdfs(i, ptr), ptr++;
            dag = Graph< T >(ptr);
            for(int i = 0; i < g.size(); i++) {
                for(auto &e : g[i]) {
                    int x = comp[e.from], y = comp[e.to];
                    if(x == y) continue;
                    dag.add_directed_edge(x, y, e.cost);
                }
            }
            group.resize(ptr);
            for(int i = 0; i < g.size(); i++) {
                group[comp[i]].emplace_back(i);
            }
        }

        int operator[](int k) const {
            return comp[k];
        }

    private:
        vector< int > order, used;
        Graph< T > rg;

        void dfs(int idx) {
            if(exchange(used[idx], true)) return;
            for(auto &to : g[idx]) dfs(to);
            order.push_back(idx);
        }

        void rdfs(int idx, int cnt) {
            if(comp[idx] != -1) return;
            comp[idx] = cnt;
            for(auto &to : rg.g[idx]) rdfs(to, cnt);
        }
};

int main(){
    int n,m;cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= m;
    }
    StronglyConnectedComponents<> G(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int t = i * a[j] % m;
            G.add_directed_edge(i, t);
        }
    }
    G.build();
    auto reG = G.dag.g;
    int sz = reG.size();
    vector<int> dp(sz, 0);
    for (int i = 0; i < sz; i++) {
        for(auto e:reG[i]){
            chmax(dp[e.to], dp[i] + 1);
        }
    }
    if(G[1] == 0 and dp[sz-1] == sz - 1) puts("Yes");
    else puts("No");
    return 0;
}


