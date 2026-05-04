// https://github.com/NotLinux18/cp-library/blob/main/treap.cpp
template<int32_t N>
struct Treap{
    int32_t rt=0,p=0,l[N],r[N],sz[N],cnt[N];
    uint32_t pri[N],sd=chrono::steady_clock::now().time_since_epoch().count();
    int key[N],sum[N];

    uint32_t rnd(){return sd^=sd<<13, sd^=sd>>17, sd^=sd<<5;}
    int32_t gs(int32_t x){return x?sz[x]:0;}
    int sm(int32_t x){return x?sum[x]:0;}

    int32_t nw(int x){
        ++p; l[p]=r[p]=0; sz[p]=cnt[p]=1;
        key[p]=sum[p]=x; pri[p]=rnd(); return p;
    }

    void pull(int32_t x){
        if(x)sz[x]=gs(l[x])+cnt[x]+gs(r[x]),
              sum[x]=sm(l[x])+key[x]*cnt[x]+sm(r[x]);
    }

    void spl(int32_t v,int x,int32_t& a,int32_t& b){ // < x , >= x
        if(!v)return void(a=b=0);
        if(key[v]<x)spl(r[v],x,r[v],b),a=v;
        else spl(l[v],x,a,l[v]),b=v;
        pull(v);
    }

    void sple(int32_t v,int x,int32_t& a,int32_t& b){ // <= x , > x
        if(!v)return void(a=b=0);
        if(key[v]<=x)sple(r[v],x,r[v],b),a=v;
        else sple(l[v],x,a,l[v]),b=v;
        pull(v);
    }

    int32_t mrg(int32_t a,int32_t b){
        if(!a||!b)return a?a:b;
        if(pri[a]>pri[b])return r[a]=mrg(r[a],b),pull(a),a;
        return l[b]=mrg(a,l[b]),pull(b),b;
    }

    int32_t fd(int x){
        int32_t v=rt;
        while(v&&key[v]!=x)v=x<key[v]?l[v]:r[v];
        return v;
    }

    bool find(int x){return fd(x);}
    int count(int x){int32_t v=fd(x); return v?cnt[v]:0;}
    int size(){return gs(rt);}
    bool empty(){return !rt;}

    void insert(int x){
        int32_t a,b,c;
        spl(rt,x,a,b); sple(b,x,b,c);
        if(b)cnt[b]++,pull(b); else b=nw(x);
        rt=mrg(a,mrg(b,c));
    }

    void insert_unique(int x){
        if(!find(x))insert(x);
    }

    void erase(int x){
        int32_t a,b,c;
        spl(rt,x,a,b); sple(b,x,b,c);
        if(b){
            if(cnt[b]>1)cnt[b]--,pull(b);
            else b=mrg(l[b],r[b]);
        }
        rt=mrg(a,mrg(b,c));
    }

    void erase_all(int x){
        int32_t a,b,c;
        spl(rt,x,a,b); sple(b,x,b,c);
        rt=mrg(a,c);
    }

    int kth(int32_t k){ // 0-indexed
        int32_t v=rt;
        while(v){
            if(k<gs(l[v]))v=l[v];
            else if(k<gs(l[v])+cnt[v])return key[v];
            else k-=gs(l[v])+cnt[v],v=r[v];
        }
        return -1;
    }

    int order_of_key(int x){ // < x
        int32_t v=rt; int ret=0;
        while(v){
            if(key[v]<x)ret+=gs(l[v])+cnt[v],v=r[v];
            else v=l[v];
        }
        return ret;
    }

    int order_of_key_le(int x){ // <= x
        int32_t v=rt; int ret=0;
        while(v){
            if(key[v]<=x)ret+=gs(l[v])+cnt[v],v=r[v];
            else v=l[v];
        }
        return ret;
    }

    int sum_less(int x){ // sum keys < x
        int32_t v=rt; int ret=0;
        while(v){
            if(key[v]<x)ret+=sm(l[v])+key[v]*cnt[v],v=r[v];
            else v=l[v];
        }
        return ret;
    }

    int sum_le(int x){ // sum keys <= x
        int32_t v=rt; int ret=0;
        while(v){
            if(key[v]<=x)ret+=sm(l[v])+key[v]*cnt[v],v=r[v];
            else v=l[v];
        }
        return ret;
    }

    int range_sum(int L,int R){
        return L>R?0:sum_le(R)-sum_less(L);
    }
};
/*
Treap<200005> tr;

tr.insert(5);
tr.insert(2);
tr.insert(5);
tr.insert(10);

cout << tr.size() << endl;            // 4
cout << tr.empty() << endl;           // 0

cout << tr.find(5) << endl;           // 1
cout << tr.count(5) << endl;          // 2

cout << tr.kth(0) << endl;            // 2
cout << tr.kth(1) << endl;            // 5
cout << tr.kth(3) << endl;            // 10

cout << tr.order_of_key(6) << endl;    // count < 6  -> 3
cout << tr.order_of_key_le(5) << endl; // count <= 5 -> 3

cout << tr.sum_less(6) << endl;        // 2+5+5 = 12
cout << tr.sum_le(5) << endl;          // 2+5+5 = 12
cout << tr.range_sum(3, 10) << endl;   // 5+5+10 = 20

tr.erase(5);                           // erase one 5
cout << tr.count(5) << endl;           // 1

tr.erase_all(5);                       // erase all 5s
cout << tr.count(5) << endl;           // 0
*/