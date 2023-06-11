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
const ll mod=1000000007;
const ll LINF=1LL<<62;
const int INF=1<<17;

int M_N = 200000;

vector<ll> fact;
vector<ll> inver(M_N+1);
 
ll combi(int n,int r){
    if(n<r||n<0||r<0) return 0;
    return fact[n]%mod*inver[n-r]%mod*inver[r]%mod;
}
 
 
ll fpow(ll a, ll n){
    ll x = 1;
    while(n > 0){
        if(n&1){
            x=x*a%mod;
        }
        a=a*a%mod;
        n >>= 1;
    }
    return x;
}
 
void set_combi(){
    ll s=1;
    fact.push_back(1);
    for(int i=1;i<=M_N;i++){
        s*=i;
        s%=mod;
        fact.push_back(s);
    }
    inver[M_N]=fpow(fact[M_N],mod-2);
    for(int i=M_N-1;i>=0;i--){
        inver[i]=inver[i+1]*(i+1)%mod;
    }
}
 
ll hcombi(int n,int r){
    return combi(n+r-1,r); 
}

vector<ll> divi(ll K){
    vector<ll> v;
    for(ll i=1;i*i<=K;i++){
        if(K%i) continue;
        v.pb(i);
        v.pb(K/i);
    }
    sort(ALL(v));
    v.erase(unique(ALL(v)),v.end());
    return v;
}

vector<ll> pdivi(ll K){
    vector<ll> v;
    for(ll i=2;i*i<=K;i++){
        if(K%i) continue;
        v.pb(i);
        while(K%i==0){
            K/=i;
        }
    }
    if(K!=1) v.pb(K);
    return v;
}





int main(){
    ll N,M;
    cin >> N >> M;
    vector<ll> t;
    t=pdivi(M);
    set_combi();
    ll ans=1;
    for(int i=0;i<t.size();i++){
        ll p=0;
        while(M%t[i]==0){
            p++;
            M/=t[i];
        }
        ans*=hcombi(N,p);
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}
