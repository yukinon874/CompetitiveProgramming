#include<bits/stdc++.h>
//#include<atcoder/all>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
//using namespace atcoder;
//using namespace boost::multiprecision;
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define ALL(A) A.begin(),A.end()
#define RALL(A) A.rbegin(),A.rend()
typedef long long ll;
//typedef pair<ll,ll> P;
//typedef pair<double,double> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template<typename T> T gcd(T a,T b){return b?gcd(b,a%b):a;}
const ll mod=1e9 + 7;
const ll LINF=1ll<<60;
const int INF=1<<30;
int dx[]={0,1,0,-1,0,1,-1,1,-1};
int dy[]={0,0,1,0,-1,1,-1,-1,1};
//int dx[]={0,0,1,-1};
//int dy[]={-1,1,0,0};

template< typename flow_t, typename cost_t >
struct PrimalDual {
  struct edge {
    int to;
    flow_t cap;
    cost_t cost;
    int rev;
    bool isrev;
  };

  vector< vector< edge > > graph;
  vector< cost_t > potential, min_cost;
  vector< int > prevv, preve;
  const cost_t INF;

  PrimalDual(int V) : graph(V), INF(numeric_limits< cost_t >::max()) {}

  void add_edge(int from, int to, flow_t cap, cost_t cost) {
    graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size() - 1, true});
  }

  cost_t min_cost_flow(int s, int t, flow_t f) {
    int V = (int) graph.size();
    cost_t ret = 0;
    using Pi = pair< cost_t, int >;
    priority_queue< Pi, vector< Pi >, greater< Pi > > que;
    potential.assign(V, 0);
    preve.assign(V, -1);
    prevv.assign(V, -1);

    while(f > 0) {
      min_cost.assign(V, INF);
      que.emplace(0, s);
      min_cost[s] = 0;
      while(!que.empty()) {
        Pi p = que.top();
        que.pop();
        if(min_cost[p.second] < p.first) continue;
        for(int i = 0; i < (int)graph[p.second].size(); i++) {
          edge &e = graph[p.second][i];
          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
          if(e.cap > 0 && min_cost[e.to] > nextCost) {
            min_cost[e.to] = nextCost;
            prevv[e.to] = p.second, preve[e.to] = i;
            que.emplace(min_cost[e.to], e.to);
          }
        }
      }
      if(min_cost[t] == INF) return -1;
      for(int v = 0; v < V; v++) potential[v] += min_cost[v];
      flow_t addflow = f;
      for(int v = t; v != s; v = prevv[v]) {
        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
      }
      f -= addflow;
      ret += addflow * potential[t];
      for(int v = t; v != s; v = prevv[v]) {
        edge &e = graph[prevv[v]][preve[v]];
        e.cap -= addflow;
        graph[v][e.rev].cap += addflow;
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << endl;
      }
    }
  }
};

int main(){
    ll n,c;cin >> n >> c;
    PrimalDual<int, ll> g(2 * n + 2);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int S = 0, G = 2 * n + 1;
    for (int i = 0; i < n; i++) {
        g.add_edge(S, i + 1, 1, c);
    }
    for (int i = 0; i < n; i++) {
        g.add_edge(i + 1, i + 1 + n, 1, -LINF);
        for (int j = i + 1; j < n; j++) {
            g.add_edge(i + 1 + n, j + 1, 1, abs(a[i] - a[j]));
        }
    }
    for (int i = 0; i < n; i++) {
        g.add_edge(n + i + 1, G, 1, 0);
    }
    g.add_edge(S, G, n, 0);
    auto res = g.min_cost_flow(S, G, n);
    cout << res + LINF * n << endl;
    return 0;
}
