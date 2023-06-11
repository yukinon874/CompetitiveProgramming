
struct UnionFind{
    vector<int> data;

    UnionFind(int sz){
        data.assign(sz, -1);
    }

    int find(int k){
        if(data[k] < 0) return k;
        return data[k] = find(data[k]);
    }

    bool unite(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return false;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    int size(int k){
        return -data[find(k)];
    }

};

int main(){
    return 0;
}
