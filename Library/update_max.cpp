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

 
struct LazySegmentTree {
private:
    int n;
    vector<ll> node, lazy;
    vector<bool> lazyFlag;
 
public:
    LazySegmentTree(vector<ll> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.resize(2*n-1, 0);
        lazyFlag.resize(2*n-1, false);
 
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = max(node[i*2+1], node[i*2+2]);
    }
 
    void lazyEvaluate(int k, int l, int r) {
        if(lazyFlag[k]) {
            node[k] = lazy[k];
            if(r - l > 1) {
                lazy[k*2+1] = lazy[k*2+2] = lazy[k];
                lazyFlag[k*2+1] = lazyFlag[k*2+2] = true;
            }
            lazyFlag[k] = false;
        }
    }
 
    void update(int a, int b, ll x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = x;
            lazyFlag[k] = true;
            lazyEvaluate(k, l, r);
        }
        else {
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = max(node[2*k+1], node[2*k+2]);
        }
    }
 
    ll find(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return -1;
        if(a <= l && r <= b) return node[k];
        ll vl = find(a, b, 2*k+1, l, (l+r)/2);
        ll vr = find(a, b, 2*k+2, (l+r)/2, r);
        return max(vl, vr);
    }
};


int main(){
    int N;cin >> N;
    vector<ll> h(N),a(N);
    for (int i = 0; i < N; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    LazySegmentTree seg( vector<ll> (N+1,0) );
    for (int i = 0; i < N; i++) {
        seg.update(h[i],h[i]+1,seg.find(0,h[i])+a[i]);        
    }
    cout << seg.find(0,N+1) << endl;
    return 0;
}

