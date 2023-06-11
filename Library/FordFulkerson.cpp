#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const ll mod=1e9+7;
const ll LINF=1LL<<62;
const int INF=1<<17;

const int M_V=1001;
struct edge {int to,cap,rev;};

struct FordFulkerson{

    vector<edge> G[M_V];
    bool used[M_V];

    void add_edge(int from,int to,int cap){
        G[from].push_back({to,cap,G[to].size()});
        G[to].push_back({from,0,G[from].size()-1});
    }

    int dfs(int v,int t,int f){
        if(v==t) return f;
        used[v]=true;
        for(int i=0;i<G[v].size();i++){
            edge &e=G[v][i];
            if(!used[e.to]&&e.cap>0){
                int d=dfs(e.to,t,min(f,e.cap));
                if(d>0){
                    e.cap-=d;
                    G[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s,int t){
        int flow=0;
        for(;;){
            memset(used,0,sizeof(used));
            int f=dfs(s,t,INF);
            if(f==0) return flow;
            flow+=f;
        }
    }
};

int main(){
    int N,G,E;
    cin >> N >> G >> E;
    FordFulkerson FF;
    for(int i=0;i<G;i++){
        int p;
        cin >> p;
        FF.add_edge(p,N,1);
    }
    for(int i=0;i<E;i++){
        int u,v;
        cin >> u >> v;
        FF.add_edge(u,v,1);
        FF.add_edge(v,u,1);
    }
    cout << FF.max_flow(0,N) << endl;
    return 0;
}
