#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const ll mod=1e9+7;
const ll LINF=1LL<<62;

typedef vector<vector<ll>> mat;

mat mul(mat A,mat B){
    mat C(A.size(),vector<ll> (B[0].size()));
    for(int i=0;i<A.size();i++){
        for(int k=0;k<B.size();k++){
            for(int j=0;j<B[0].size();j++){
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%mod;
            }
        }
    }
    return C;
}

mat pow(mat A,ll n){
    mat B(A.size(),vector<ll> (A.size()));
    for(int i=0;i<A.size();i++){
        B[i][i]=1;
    }
    while(n>0){
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}


int main(){
    ll H;
    int R;
    cin >> H >> R;
    bool g[R][R];
    for(int i=0;i<R;i++){
        for(int j=0;j<R;j++){
            cin >> g[i][j];
        }
    }
    mat dp(R,vector<ll> (R));
    for(int i=0;i<R;i++){
        for(int j=0;j<R;j++){
            if(i==j) dp[i][j]=1;
            else dp[i][j]=0;
        }
    }
    for(int i=0;i<R;i++){
        ll t[1<<R][R];
        memset(t,0,sizeof(t));
        t[1<<i][i]=1LL;
        for(int S=0;S<1<<R;S++){
            for(int j=0;j<R;j++){
                if(t[S][j]==0) continue;
                for(int k=0;k<R;k++){
                    if(S>>k&1||g[j][k]==0) continue;
                    t[S|(1<<k)][k]=(t[S|(1<<k)][k]+t[S][j])%mod;
                    dp[i][k]=(dp[i][k]+t[S][j])%mod;
                }
            }
        }
    }
    mat t=pow(dp,H-1);
    ll ans=0;
    for(int i=0;i<R;i++){
        ans=(ans+t[0][i]*dp[i][0])%mod;
    }
    cout << ans << endl;
    return 0;
}
