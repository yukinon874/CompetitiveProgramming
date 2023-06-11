#include<vector>
#include<tuple>
#include<algorithm>
#include<iostream>
#include<climits>
//#include<atcoder/all>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
//using namespace atcoder;
//using namespace boost::multiprecision;
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define ALL(A) A.begin(),A.end()
#define RALL(A) A.rbegin(),A.rend()
typedef long long ll;
//typedef pair<ll,ll> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template<typename T> T gcd(T a,T b){return b?gcd(b,a%b):a;}
const ll mod=998244353;
const ll LINF=1ll<<60;
const int INF=1<<30;
int dx[]={0,1,0,-1,0,1,-1,1,-1};
int dy[]={0,0,1,0,-1,1,-1,-1,1};

using P = tuple<ll, int, int>;
int a[2001];

template<typename T> class BIT {
private:
    int n,m; vector<vector<T> > bit;
public:
    void update(int i, int j, T val){
        for(int i_ = i+1; i_ < n; i_ += i_ & -i_)
            for(int j_ = j+1; j_ < m; j_ += j_ & -j_)
                chmax(bit[i_][j_], val);
    }
    T query(int i, int j){
        T s = -LINF;
        for(int i_ = i+1; i_ > 0; i_ -= i_ & -i_)
            for(int j_ = j+1; j_ > 0; j_ -= j_ & -j_)
                chmax(s, bit[i_][j_]);
        return s;
    }

    BIT(int sz1, int sz2){
        n = sz1 + 1, m = sz2 + 1;
        bit.resize(n, vector<T>(m, -LINF));
    }

    BIT(vector<vector<T> >& v){
        n = (int)v.size() + 1, m = (int)v[0].size() + 1;
        bit.resize(n, vector<T>(m, 0));
        for(int i = 0; i < n - 1; i++)
            for(int j = 0; j < m - 1; j++)
                update(i, j, v[i][j]);
    }
    void print(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout<< query(i-1, j-1) << " ";
            }
            cout << "\n";
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin >> n >> m;
    for(int i=0;i<n;i++) cin >> a[i];
    vector<tuple<ll, int, int, int>> E(m);
    for(int i=0;i<m;i++) {
        int l,r;cin >> l >> r;
        ll u;cin >> u;
        E[i] = {u, l - 1, r, i};
    }
    sort(ALL(E));

    vector<P> X;
    for (int i = 0; i < n; i++) {
        ll S = 0;
        for (int j = i; j < n; j++) {
            S += a[j];
            X.emplace_back(S, n - i - 1, j);
        }
    }
    sort(ALL(X));

    //SegmentTree2D seg(n, n);
    BIT<ll> seg(n, n);

    vector<ll> ans(m);

    int xid = 0;
    for (int i = 0; i < m; i++) {
        auto [u, l, r, id] = E[i];
        while(xid < X.size() and get<0>(X[xid]) <= u){
            auto [U, x, y] = X[xid++];
            seg.update(x, y, U);
        }
        ans[id] = seg.query(n - l - 1, r - 1);
    }
    for (int i = 0; i < m; i++) {
        if(ans[i] == -LINF) cout << "NONE\n";
        else cout << ans[i] << "\n";
    }
    return 0;
}
