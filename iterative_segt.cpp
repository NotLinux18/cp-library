// https://github.com/NotLinux18/cp-library/blob/main/iterative_segt.cpp
template<typename Info>
struct Iterative_Segt{
    int tree_size;
    vector<Info> t;
    void init(int n){
        tree_size = 1;
        while(tree_size < n) tree_size <<= 1;
        t.assign(2 * tree_size, Info());
    }
    template<typename T>
    void build(const vector<T>& a){
        init(sz(a));
        for(int i = 0; i < sz(a); i++)t[tree_size + i] = Info(a[i]);
        for(int i = tree_size - 1; i >= 1; i--)t[i] = merge(t[i<<1], t[i<<1|1]);
    }
    void set_modify(int p, const Info& value){
        p += tree_size;
        t[p] = value;
        for(p >>= 1; p >= 1; p >>= 1)t[p] = merge(t[p<<1], t[p<<1|1]);
    }
    void add_modify(int p, const Info& value){
        p += tree_size;
        t[p] = merge(t[p], value);
        for(p >>= 1; p >= 1; p >>= 1)t[p] = merge(t[p<<1], t[p<<1|1]);
    }
    Info query(int l, int r){ // [l, r]
        Info left = Info(), right = Info();
        for(l += tree_size, r += tree_size + 1; l < r; l >>= 1, r >>= 1){
            if(l & 1) left = merge(left, t[l++]);
            if(r & 1) right = merge(t[--r], right);
        }
        return merge(left, right);
    }
};