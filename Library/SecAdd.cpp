#include<bits/stdc++.h>
//#include<atcoder/all>
using namespace std;
//using namespace atcoder;
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
//using mint = modint998244353;


struct SecImos{
    vector<ll> imos;
    vector<ll> imos2;

    SecImos(int sz){
        imos.assign(sz + 1, 0);
        imos2.assign(sz + 1, 0);
    }
    
    // a[l]+=x, a[l+1]+=2x,.., a[r-1]+=(r-l)*x
    void add(int l, int r, ll x){
        if(r <= l) return;
        imos[l] += x;
        imos[r] -= x;
        imos2[r] -= (r - l) * x;
    }

    void run(){
        for (int i = 0; i + 1 < imos.size(); i++) {
            imos[i + 1] += imos[i];
        }
        for (int i = 0; i + 1 < imos.size(); i++) {
            imos[i + 1] += imos[i] + imos2[i + 1];
            imos[i + 1] += imos[i];
        }
    }

    ll get(int x){
        return imos[x];
    }

};



int main(){
    return 0;
}
