#include<bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define ALL(A) A.begin(),A.end()
#define RALL(A) A.rbegin(),A.rend()
typedef long long ll;
typedef pair<ll,ll> P;
const ll mod=1e9+7;
const ll LINF=1LL<<62;

const int M_V=100001;
const int logV=21;

vector<int> G[M_V];

int parent[logV][M_V];
int depth[M_V];

void dfs(int v,int p,int d){
    parent[0][v]=p;
    depth[v]=d;
    for(int i=0;i<G[v].size();i++){
        if(G[v][i]!=p) dfs(G[v][i],v,d+1);
    }
}

void init(int V,int root){
    dfs(root,-1,0);
    for(int k=0;k<logV-1;k++){
        for(int v=0;v<V;v++){
            if(parent[k][v]<0) parent[k+1][v]=-1;
            else parent[k+1][v]=parent[k][parent[k][v]];
        }
    }
}

int lca(int u,int v){
    if(depth[u]>depth[v]) swap(u,v);
    for(int k=0;k<logV;k++){
        if((depth[v]-depth[u])>>k&1){
            v=parent[k][v];
        }
    }
    if(u==v) return u;
    for(int k=logV-1;k>=0;k--){
        if(parent[k][u]!=parent[k][v]){
            u=parent[k][u];
            v=parent[k][v];
        }
    }
    return parent[0][u];
}

int dist(int u, int v){
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}


int main(){
    int N;
    cin >> N;
    for(int i=0;i<N-1;i++){
        int x,y;
        cin >> x >> y;
        x--,y--;
        G[x].eb(y);
        G[y].eb(x);
    }
    init(N,0);
    int Q;
    cin >> Q;
    while(Q--){
        int a,b;
        cin >> a >> b;
        a--,b--;
        cout << depth[a]+depth[b]-2*depth[lca(a,b)] << endl;
    }
    return 0;
}
