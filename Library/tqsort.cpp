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
const ll mod=998244353;
const ll LINF=1LL<<60;
const int INF=1<<30;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};



typedef vector<vector<int>> UnWeightedGraph;


vector<int> tpsort(const UnWeightedGraph &g) {
    const int V = g.size();
    vector<int> indeg(V, 0);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            indeg[g[i][j]]++;
        }
    }
    vector<int> ret;
    priority_queue<int,vector<int>,greater<int>> pq;
    for (int i = 0; i < V; i++) {
        if(indeg[i] == 0) pq.push(i);
    }
    while(pq.size() > 0) {
        int u = pq.top(); pq.pop();
        ret.pb(u);
        for (int i = 0; i < g[u].size(); i++) {
            indeg[g[u][i]]--;
            if(indeg[g[u][i]] == 0) pq.push(g[u][i]);
        }
    }
    return ret;
}

int main(){
    int n;cin >> n;
    vector<string> a(n),b(n);
    UnWeightedGraph v(26);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        bool f = false;
        for (int j = 0; j < min(a[i].length(),b[i].length()); j++) {
            if(a[i][j] != b[i][j]){
                v[a[i][j] - 'a'].pb(b[i][j] - 'a');
                f = true;
                break;
            }
        }
        if(!f){
            if(a[i] > b[i]){
                puts("-1");
                return 0;
            }
        }
    }
    auto ans = tpsort(v);
    if(ans.size() == 26){
        for (int i = 0; i < ans.size(); i++) {
            cout << (char) ('a' + ans[i]);
        }
        cout << endl;
    }
    else{
        puts("-1");
    }
    return 0;
}

