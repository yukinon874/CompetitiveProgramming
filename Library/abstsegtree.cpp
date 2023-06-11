#include<bits/stdc++.h>
using namespace std;
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
typedef long long ll;
typedef pair<double,double> P;
const ll mod=1000000007;
const ll LINF=1LL<<62;
const int INF=1<<30;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};


template <typename T>
struct SegmentTree{
    using F = function<T(T,T)>;
    int n;
    F f;
    T ti;
    vector<T> dat;
    SegmentTree(){};
    SegmentTree(F f,T ti):f(f),ti(ti){}
    void init(int n_){    
        n=1;
        while(n<n_) n<<=1;
        dat.assign(n<<1,ti);
    }
    void build(const vector<T> &v){
        int n_=v.size();
        init(n_);
        for(int i=0;i<n_;i++) dat[n+i]=v[i];
        for(int i=n-1;i;i--)
            dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
    }
    void set_val(int k,T x){
        dat[k+=n]=x;
        while(k>>=1)
            dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);    
    }
    T query(int a,int b){
        T vl=ti,vr=ti;
        for(int l=a+n,r=b+n;l<r;l>>=1,r>>=1) {
            if(l&1) vl=f(vl,dat[l++]);
            if(r&1) vr=f(dat[--r],vr);
        }
        return f(vl,vr);
    }
};


int main(){
    ll n,m;cin >> n >> m;
    vector<ll> x(m);
    vector<pair<ll,P>> v;
    for (int i = 0; i < m; i++) {
        ll t;cin >> t;
        double a,b;cin >> a >> b;
        v.pb(mp(t,mp(a,b)));
        x[i] = t;
    }
    sort(ALL(x));
    x.erase(unique(ALL(x)),x.end());
    for (int i = 0; i < m; i++) {
        v[i].fs = lower_bound(ALL(x),v[i].fs) - x.begin();
    }
    n = x.size();
    SegmentTree<P> seg([](P a, P b){
        return P(a.fs * b.fs, a.sc * b.fs + b.sc);
    }, P(1.0,0.0));
    seg.build(vector<P> (n+2,P(1.0,0.0)));
    double mi=1,mx=1;
    for (int i = 0; i < m; i++) {
        seg.set_val(v[i].fs, v[i].sc);
        P p = seg.query(0,n+1);
        mi = min(mi,p.fs+p.sc);
        mx = max(mx,p.fs+p.sc);
    }
    cout << setprecision(30) << fixed << mi << endl;
    cout << mx << endl;
    return 0;
}

