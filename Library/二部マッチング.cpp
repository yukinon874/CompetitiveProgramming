#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const ll mod=1e9+7;
const ll LINF=1LL<<62;
const int INF=1<<17;


const int M_N=200; //最大頂点数

int V;
vector<int> G[M_N];
int match[M_N];
bool used[M_N];

void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v){
    used[v]=true;
    for(int i=0;i<G[v].size();i++){
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w)){
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}


int bipartie_matching(){
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=0;v<V;v++){
        if(match[v]<0){
            memset(used,false,sizeof(used));
            if(dfs(v)){
                res++;
            }
        }
    }
    return res;
}

int main(){
    int x,y,e;
    cin >> x >> y >> e;
    V=x+y; //頂点数
    for(int i=0;i<e;i++){
        int u,v;
        cin >> u >> v;
        add_edge(u,x+v);
    }
    cout << bipartie_matching() << endl;
    return 0;
}
