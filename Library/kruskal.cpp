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
typedef pair<int,int> P;
const ll mod=998244353;
const ll LINF=1LL<<62;
const int INF=1<<20;


const int M_N=200001;

struct edge { int from;int to;int cost;
    bool operator<(const edge &right)const{ return right.cost<cost;}
};

struct UnionFind{
    int par[M_N];
    int rank[M_N];

    void init(int n){
        for(int i=0;i<n;i++){
            par[i]=i;
            rank[i]=0;
        }
    }

    int find(int x){
        if(par[x]==x){
            return x;
        }
        else{
            return par[x]=find(par[x]);
        }
    }

    void unite(int x,int y){
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(rank[x]<rank[y]){
            par[x]=y;
        }
        else{
            par[y]=x;
            if(rank[x]==rank[y]) rank[x]++;
        }
    }

    bool same(int x,int y){
        return find(x)==find(y);
    }
};


int main(){
    int n,m;
    cin >> n >> m
    UnionFind uf; 
    uf.init(n+1);
    vector<edge> v;
    for (int i = 0; i < m; i++) {
        int x,y,c;cin >> x >> y >> c;
        v.pb({x,y,c});
    }
    sort(ALL(v));
    int ans=0;
    for (int i = 0; i < m; i++) {
        edge e=v[i];
        if(uf.same(e.from,e.to)) continue;
        uf.unite(e.from,e.to);
        ans+=e.cost;
    }
    cout << ans << endl;
    return 0;
}

