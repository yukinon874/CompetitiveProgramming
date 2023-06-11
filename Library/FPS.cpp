#include<bits/stdc++.h>
#include<atcoder/all>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;
//using namespace boost::multiprecision;
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
int dx[]={1,0,-1,0,1,-1,1,-1};
int dy[]={0,1,0,-1,1,-1,-1,1};


template<class T>
struct FormalPowerSeries : vector<T> {
    using vector<T>::vector;
    using vector<T>::operator=;
    using F = FormalPowerSeries;

    F operator-() const {
        F res(*this);
        for (auto &e : res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for (auto &e : *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (*this).size(), m = g.size();
        for (int i = 0; i < min(n, m); i++) (*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (*this).size(), m = g.size();
        for (int i = 0; i < min(n, m); i++) (*this)[i] -= g[i];
        return *this;
    }
    F &operator<<=(const int d) {
        int n = (*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
        return *this;
    }
    F &operator>>=(const int d) {
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + min(n, d));
        (*this).resize(n);
        return *this;
    }
    F inv(int d = -1) const {
        int n = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        if (d == -1) d = n;
        assert(d > 0);
        F res{(*this)[0].inv()};
        while (res.size() < d) {
            int m = size(res);
            F f(begin(*this), begin(*this) + min(n, 2*m));
            F r(res);
            f.resize(2*m), internal::butterfly(f);
            r.resize(2*m), internal::butterfly(r);
            for (int i = 0; i < 2 * m; i++) f[i] *= r[i];
            internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(2*m), internal::butterfly(f);
            for (int i = 0; i < 2 * m; i++) f[i] *= r[i];
            internal::butterfly_inv(f);
            T iz = T(2*m).inv(); iz *= -iz;
            for (int i = 0; i < m; i++) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        return {res.begin(), res.begin() + d};
    }

    // // fast: FMT-friendly modulus only O((N+M)log(N+M))
    // F &operator*=(const F &g) {
    //   int n = (*this).size();
    //   *this = convolution(*this, g);
    //   (*this).resize(n);
    //   return *this;
    // }
    // F &operator/=(const F &g) {
    //   int n = (*this).size();
    //   *this = convolution(*this, g.inv(n));
    //   (*this).resize(n); // dequeの畳み込み高速化をする場合はresizeを消してこれをコメントアウト
    //   return *this;
    // }


    // // naive O(NM)
    // F &operator*=(const F &g) {
    //   int n = (*this).size(), m = g.size();
    //   for (int i = n-1; i >= 0; i--) {
    //     (*this)[i] *= g[0];
    //     for (int j = 1; j < min(i + 1, m); j++) (*this)[i] += (*this)[i-j] * g[j];
    //   }
    //   return *this;
    // }
    // F &operator/=(const F &g) {
    //   assert(g[0] != T(0));
    //   T ig0 = g[0].inv();
    //   int n = (*this).size(), m = g.size();
    //   for (int i = n-1; i >= 0; i--) {
    //     for (int j = 1; j < min(i + 1, m); j++) (*this)[i] -= (*this)[i-j] * g[j];
    //     (*this)[i] *= ig0;
    //   }
    //   return *this;
    // }

    // sparse O(NK) Kはgの非ゼロの係数の数
    F &operator*=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if (d == 0) g.erase(g.begin());
        else c = 0;
        for (int i = n - 1; i >= 0; i--) {
            (*this)[i] *= c;
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] += (*this)[i-j] * b;
            }
        }
        return *this;
    }
    F &operator/=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(d == 0 && c != T(0));
        T ic = c.inv();
        g.erase(g.begin());
        for (int i = 0; i < n; i++) {
            for (auto &[j, b] : g) {
                if (j > i) break;
                (*this)[i] -= (*this)[i-j] * b;
            }
            (*this)[i] *= ic;
        }
        return *this;
    }

    // multiply and divide (1 + cz^d)
    void multiply(const int d, const T c) { 
        int n = (*this).size();
        if (c == T(1))
            for (int i = n-d-1; i >= 0; i--) (*this)[i+d] += (*this)[i];
        else if (c == T(-1)) for (int i = n-d-1; i >= 0; i--)  (*this)[i+d] -= (*this)[i];
        else for (int i = n-d-1; i >= 0; i--) (*this)[i+d] += (*this)[i] * c;
    }
    void divide(const int d, const T c) {
        int n = (*this).size();
        if (c == T(1)) for (int i = 0; i < n-d; i++) (*this)[i+d] -= (*this)[i];
        else if (c == T(-1)) for (int i = 0; i < n-d; i++) (*this)[i+d] += (*this)[i];
        else for (int i = 0; i < n-d; i++) (*this)[i+d] -= (*this)[i] * c;
    }

    T eval(const T &a) const {
        T x(1), res(0);
        for (auto e : *this) res += e * x, x *= a;
        return res;
    }

    F operator*(const T &g) const { return F(*this) *= g; }
    F operator/(const T &g) const { return F(*this) /= g; }
    F operator+(const F &g) const { return F(*this) += g; }
    F operator-(const F &g) const { return F(*this) -= g; }
    F operator<<(const int d) const { return F(*this) <<= d; }
    F operator>>(const int d) const { return F(*this) >>= d; }
    F operator*(const F &g) const { return F(*this) *= g; }
    F operator/(const F &g) const { return F(*this) /= g; }
    F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
    F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};

using mint = modint998244353;
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>; // {i, x} => a_i = x

int main(){
    int n,q;cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r, p;cin >> l >> r >> p;
        ll ans = 0;
        for (int k = l; k <= r; k++) {
            fps f = {1};
            f.resize(n + 1);
            for (int j = 0; j < n; j++) {
                if(a[j] >= k) f *= sfps{{0, a[j] - 1}, {1, 1}};
                else f *= sfps{{0, a[j]}};
            }
            ans = (ans ^ f[p].val())%mod;
        }
        cout << ans << endl;
    }
    return 0;
}
