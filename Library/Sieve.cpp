//nまでの素数を求める(prime[i] == i => 素数)
vector<int> Sieve(int n){
    vector<int> ret(n + 1, 0);
    vector<int> pr;
    for (int i = 2; i <= n; i++) {
        if (ret[i] == 0) {
            ret[i] = i;
            pr.emplace_back(i);
        }
        for (int j = 0; j < pr.size() && pr[j] <= ret[i] && i*pr[j] <= n; j++) ret[i * pr[j]] = pr[j];
    }
    return ret;
}


int main(){
    return 0;
}
