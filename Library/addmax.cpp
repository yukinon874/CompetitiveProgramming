template< typename T >
struct SegmentTree{
    private:
        int n;
        vector<T> segMax;
        vector<T> segAdd;
 
    public:
        SegmentTree(int sz){
            n = 1;
            while(n < sz) n *= 2;
            segMax.resize(2*n-1, 0);
            segAdd.resize(2*n-1, 0);
        }
 
        void add(int a, int b, T x, int k, int l, int r) {
            if (r <= a || b <= l) return;
            if (a <= l && r <= b){
                segAdd[k] += x;
                return;
            }
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);
            segMax[k] = max(segMax[k * 2 + 1] + segAdd[k * 2 + 1], segMax[k * 2 + 2] + segAdd[k * 2 + 2]);
        }
 
        void add(int a,int b, T x) {
            add(a, b, x, 0, 0, n);
        }
 
        T getMax(int a, int b, int k, int l, int r) {
            if (r <= a || b <= l) return -LINF;
            if (a <= l && r <= b) return (segMax[k] + segAdd[k]);
            T left = getMax(a, b, k * 2 + 1, l, (l + r) / 2);
            T right = getMax(a, b, k * 2 + 2, (l + r) / 2, r);
            return (max(left, right) + segAdd[k]);
        }
 
        T getMax(int a,int b){
            return getMax(a, b, 0, 0, n);
        }
};


int main(){
    return 0;
}
