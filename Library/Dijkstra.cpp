#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const ll mod=1e9+7;
const ll LINF=1LL<<62;
string u="abcdefghijklmnopqrstuvwxyz";

struct edge {int to;ll cost;};

const int M_N=200000;

vector<edge> G[M_N+1];
struct Dijkstra{

    vector<ll> d;
    void init(int n){
        d.assign(n + 1, LINF);
    }

    void dijkstra(int s){
        priority_queue<P,vector<P>,greater<P>> que;
        que.push(P(0,s));
        d[s] = 0;
        while(!que.empty()){
            P p=que.top();
            que.pop();
            int v=p.second;
            if(d[v]<p.first) continue;
            for(int i=0;i<G[v].size();i++){
                edge e=G[v][i];
                if(d[e.to]>d[v]+e.cost){
                    d[e.to]=d[v]+e.cost;
                    que.push(P(d[e.to],e.to));
                }
            }
        }
    }

};

int main(){
    int N;
    cin >> N;
    Dijkstra Ds(N);
    int u,k,v,c;
    while(cin >> u >> k){
        for(int i=0;i<k;i++){
            cin >> v >> c;
            G[u].push_back({v,c});
        }
    }
    Ds.dijkstra(0);
    for(int i=0;i<N;i++){
        cout << i <<" "<< Ds.d[i] << endl;
    }
    return 0;
}
