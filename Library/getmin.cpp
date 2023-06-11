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
typedef pair<char,ll> P;
const ll mod=998244353;
const ll LINF=1LL<<62;
const int INF=1<<30;


struct SegmentTree{
private:
    int n;
    vector<int> node;

public:
    SegmentTree(vector<int> v){
        int sz = v.size();
        n = 1;
        while(n < sz) n *= 2;
        node.resize(2*n-1,INF);
        for (int i = 0; i < sz; i++) node[i+n-1] = v[i];
        for (int i = n-2; i >= 0; i--) node[i] = min(node[2*i+1],node[2*i+2]);
    }

    void update(int x,int val){
        x += n-1;
        node[x] = val;
        while(x > 0){
            x = (x - 1) / 2;
            node[x] = min(node[2*x+1],node[2*x+2]);
        }
    }

    int getmin(int a, int b, int k=0, int l=0, int r=-1){
        if (r < 0) r = n;
        if(r <= a || b <= l) return INF;
        if(a <= l && r <= b) return node[k];
        int vl = getmin(a, b, 2*k+1, l , (l+r)/2);
        int vr = getmin(a, b, 2*k+2, (l+r)/2,r);
        return min(vl, vr);
    }
};





int main(){
    return 0;
}

