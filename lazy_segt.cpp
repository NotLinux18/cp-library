// https://github.com/NotLinux18/cp-library/blob/main/lazy_segt.cpp
template<typename Info, typename Tag>
struct Lazy_Segt{
    int tree_size;
    vector<Info> t;
    vector<Tag> lazy;
    void init(int n){
        tree_size = 1;
        while(tree_size < n) tree_size <<= 1;
        t.assign(2 * tree_size, Info());
        lazy.assign(2 * tree_size, Tag());
    }
    template<typename T>
    void build(const vector<T>& a){
        init(sz(a));
        for(int i = 0; i < sz(a); i++)t[tree_size + i] = Info(a[i]);
        for(int i = tree_size - 1; i >= 1; i--)t[i] = merge(t[i<<1], t[i<<1|1]);
    }
    void apply(int x, const Tag& v){
        t[x].apply(v);
        lazy[x].apply(v);
    }
    void push(int x){
        apply(x<<1, lazy[x]);
        apply(x<<1|1, lazy[x]);
        lazy[x] = Tag();
    }
    void pull(int x){
        t[x] = merge(t[x<<1], t[x<<1|1]);
    }
    void range_apply(int x, int lx, int rx, int l, int r, const Tag& v){
        if(l <= lx and rx <= r){
            apply(x, v);
            return;
        }
        push(x);
        int mid = (lx + rx) >> 1;
        if(l <= mid)range_apply(x<<1, lx, mid, l, r, v);
        if(mid < r)range_apply(x<<1|1, mid + 1, rx, l, r, v);
        pull(x);
    }
    void range_apply(int l, int r, const Tag& v){ // [l, r]
        if(l > r)return;
        range_apply(1, 0, tree_size - 1, l, r, v);
    }
    Info query(int x, int lx, int rx, int l, int r){
        if(l <= lx and rx <= r)return t[x];
        push(x);
        int mid = (lx + rx) >> 1;
        if(r <= mid)return query(x<<1, lx, mid, l, r);
        if(mid < l)return query(x<<1|1, mid + 1, rx, l, r);
        return merge(
            query(x<<1, lx, mid, l, r),
            query(x<<1|1, mid + 1, rx, l, r)
        );
    }
    Info query(int l, int r){ // [l, r]
        if(l > r)return Info();
        return query(1, 0, tree_size - 1, l, r);
    }
    void set_modify(int x, int lx, int rx, int p, const Info& v){
        if(lx == rx){
            t[x] = v;
            lazy[x] = Tag();
            return;
        }
        push(x);
        int mid = (lx + rx) >> 1;
        if(p <= mid)set_modify(x<<1, lx, mid, p, value);
        else set_modify(x<<1|1, mid + 1, rx, p, value);
        pull(x);
    }
    void set_modify(int p, const Info& v){
        set_modify(1, 0, tree_size - 1, p, v);
    }
};