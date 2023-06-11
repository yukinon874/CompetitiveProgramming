#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;
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
const ll mod=998244353;
const ll LINF=1ll<<60;
const int INF=1<<30;
int dx[]={0,1,0,-1,0,1,-1,1,-1};
int dy[]={0,0,1,0,-1,1,-1,-1,1};


struct S{
    int value;
    int size;
};
using F = int;
const F ID = -1;
S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){
    return (f == ID ? x : S{x.size * f, x.size});
}
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }



int main(){
    int n,q,x;cin >> n >> q >> x;
    x--;
    int now = -1;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        if(p[i] == x) now = i;
    }
    vector<S> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = {p[i] >= x, 1};
    }
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(c);
    for (int i = 0; i < q; i++) {
        int c,l,r;cin >> c >> l >> r;
        l--;
        if(c == 1){
            int s1 = seg.prod(l, r).value;
            int s0 = r - l - s1;
            seg.apply(l, l + s0, 0);
            seg.apply(l + s0, r, 1);
            if(l <= now and now < r){
                now = l + s0;
            }
        }
        else{
            int s1 = seg.prod(l, r).value;
            int s0 = r - l - s1;
            seg.apply(l, l + s1, 1);
            seg.apply(l + s1, r, 0);
            if(l <= now and now < r){
                now = l + s1 - 1;
            }
        }
    }
    cout << now + 1 << endl;
    return 0;
}
