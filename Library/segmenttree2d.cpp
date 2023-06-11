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
int a[2000];
P A[2002][2002];



struct SegmentTree2D{

    int N, M;
    int KN, KM;
    int N2, M2;
    vector<vector<P>> dat;

    SegmentTree2D(int _N, int _M) : N(_N), M(_M) {
        _N--,_M--;
        KN = 0;
        while(_N){
            _N >>= 1;
            KN++;
        }
        N2 = 1 << KN;

        KM = 0;
        while(_M){
            _M >>= 1;
            KM++;
        }
        M2 = 1 << KM;

        dat.assign(2 * N2, vector<P> (2 * M2, {LONG_MIN,0,0}));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                dat[N2 + i][M2 + j] = A[i][j];
            }
        }
        build();
    }


    void build(){
        for (int j = 0; j < M; j++) {
            for (int i = N2 - 1; i > 0; i--) {
                dat[i][M2 + j] = max(dat[i << 1][M2 + j], dat[i << 1 | 1][M2 + j]);
            }
        }
        for (int i = 0; i < 2 * N2; i++) {
            for (int j = M2 - 1; j > 0; j--) {
                dat[i][j] = max(dat[i][j << 1], dat[i][j << 1 | 1]);
            }
        }
    }

    P leafvalue(int x, int y){
        return dat[x + N2][y + M2];
    }

    void update(int x, int y, P value){
        int i = x + N2;
        int j = y + M2;
        dat[i][j] = value;
        while(j > 1){
            j >>= 1;
            dat[i][j] = max(dat[i][j << 1], dat[i][j << 1 | 1]);
        }
        j = y + M2;
        while(i > 1){
            i >>= 1;
            dat[i][j] = max(dat[i << 1][j], dat[i << 1 | 1][j]);
            while(j > 1){
                j >>= 1;
                dat[i][j] = max(dat[i][j << 1], dat[i][j << 1 | 1]);
            }
            j = y + M2;
        }
    }

    P query(int Lx, int Rx, int Ly, int Ry){
        Lx += N2;
        Rx += N2;
        Ly += M2;
        Ry += M2;
        P vLx = def();
        P vRx = def();
        while(Lx < Rx){
            if(Lx & 1){
                P vLy = def();
                P vRy = def();
                ll Ly1 = Ly;
                ll Ry1 = Ry;
                while(Ly1 < Ry1){
                    if(Ly1 & 1){
                        vLy = max(vLy, dat[Lx][Ly1++]);
                    }
                    if(Ry1 & 1){
                        vRy = max(dat[Lx][--Ry1], vRy);
                    }
                    Ly1 >>= 1;
                    Ry1 >>= 1;
                }
                P vy = max(vLy, vRy);
                vLx = max(vLx,vy);
                Lx += 1;
            }
            if(Rx & 1){
                Rx -= 1;
                P vLy = def();
                P vRy = def();
                ll Ly1 = Ly;
                ll Ry1 = Ry;
                while(Ly1 < Ry1){
                    if(Ly1 & 1){
                        vLy = max(vLy, dat[Rx][Ly1++]);
                    }
                    if(Ry1 & 1){
                        vRy = max(dat[Rx][--Ry1], vRy);
                    }
                    Ly1 >>= 1;
                    Ry1 >>= 1;
                }
                P vy = max(vLy, vRy);
                vRx = max(vy, vRx);
            }
            Lx >>= 1;
            Rx >>= 1;
        }
        return max(vLx, vRx);
    }

    P def(){
        return {LONG_MIN, 0, 0};
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> a[i];
    vector<tuple<ll, int, int, int>> E(m);
    for(int i=0;i<m;i++) {
        int l,r;
        ll u;
        cin >> l >> r >> u;
        l--;
        E[i] = {u, l, r, i};
    }
    sort(RALL(E));

    for (int i = 0; i < n; i++) {
        ll S = 0;
        for (int j = 0; j < n; j++) {
            if(j < i) A[i][j] = {LONG_MIN, i, j};
            else{
                S += a[j];
                A[i][j] = {S, i, j};
            }
        }
    }

    SegmentTree2D seg(n, n);

    vector<ll> ans(m);
    for (int i = 0; i < m; i++) {
        auto [u, l, r, id] = E[i];
        auto [p, x, y] = seg.query(l, r, l, r);
        while(p > u){
            seg.update(x, y, {LONG_MIN,0,0});
            tie(p, x, y) = seg.query(l, r, l, r);
        }
        ans[id] = p;
    }
    for (int i = 0; i < m; i++) {
        if(ans[i] == LONG_MIN) cout << "NONE\n";
        else cout << ans[i] << "\n";
    }
    return 0;
}
