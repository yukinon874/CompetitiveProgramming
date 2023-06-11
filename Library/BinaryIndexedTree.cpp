template< typename T >
struct BinaryIndexedTree{

    //0-indexed
    vector< T > bit;

    BinaryIndexedTree(int sz) : bit(sz, 0) {}

    //return a[0, k)
    T sum(int k){
        assert(0 <= k && k <= bit.size());
        T ret = 0;
        for (--k; k >= 0; k = (k&(k+1))-1) ret += bit[k];
        return ret;
    }

    //return a[l, r)
    T sum(int l, int r){
        return sum(r) - sum(l);
    }

    //a[k] += k
    void add(int k, T x){
        for (; k < bit.size(); k |= k+1) bit[k] += x;
    }

    //a[k] = x
    void update(int k, T x){
        add(k, x - sum(k, k + 1));
    }


    // return minimun i s.t. sum(i) >= x
    T lower_bound(T x) {
        if(x <= 0) return 0;
        T ret = 0;
        int i = 1;
        while((i<<1) < bit.size()) i <<= 1;
        for(;i;i>>=1){
            if(ret+i-1 < bit.size() && bit[ret+i-1] < x){
                x -= bit[ret + i - 1];
                ret += i;
            }
        }
        return ret;
    }
};


