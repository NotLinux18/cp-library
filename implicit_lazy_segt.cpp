// https://github.com/NotLinux18/cp-library/blob/main/implicit_lazy_segt.cpp
template<class T,class=void>
struct HasLen:false_type{};
template<class T>
struct HasLen<T,void_t<decltype(declval<T&>().len)>>:true_type{};

template<class Info,class Tag>
struct Implicit_Lazy_Segt{
    vector<int> lc,rc;
    vector<bool> bad;
    vector<Info> t;
    vector<Tag> lz;
    long long L,R;
    int rt;

    int nw(long long l,long long r){
        int x=sz(t);
        lc.push_back(0),rc.push_back(0),bad.push_back(0);
        t.push_back(Info()),lz.push_back(Tag());
        fix(x,l,r);
        return x;
    }

    void fix(int x,long long l,long long r){
        if constexpr(HasLen<Info>::value)t[x].len=r-l+1;
    }

    void init(long long l,long long r){
        L=l,R=r;
        lc={0},rc={0},bad={0},t={Info()},lz={Tag()}; // dummy 0
        rt=nw(L,R);
    }

    void app(int x,long long l,long long r,const Tag& v){
        fix(x,l,r);
        t[x].apply(v);
        lz[x].apply(v);
        bad[x]=1;
    }

    void push(int x,long long l,long long r){
        if(l==r)return;
        long long m=(l+r)>>1;
        if(!lc[x])lc[x]=nw(l,m);
        if(!rc[x])rc[x]=nw(m+1,r);
        if(bad[x]){
            app(lc[x],l,m,lz[x]);
            app(rc[x],m+1,r,lz[x]);
            lz[x]=Tag();
            bad[x]=0;
        }
    }

    void pull(int x){
        t[x]=merge(t[lc[x]],t[rc[x]]);
    }

    void upd(int x,long long l,long long r,long long ql,long long qr,const Tag& v){
        if(qr<l||r<ql)return;
        if(ql<=l&&r<=qr)return app(x,l,r,v);
        push(x,l,r);
        long long m=(l+r)>>1;
        upd(lc[x],l,m,ql,qr,v);
        upd(rc[x],m+1,r,ql,qr,v);
        pull(x);
    }

    void range_apply(long long l,long long r,const Tag& v){ // [l,r]
        if(l>r)return;
        upd(rt,L,R,l,r,v);
    }

    Info qry(int x,long long l,long long r,long long ql,long long qr){
        if(!x||qr<l||r<ql)return Info();
        if(ql<=l&&r<=qr)return t[x];
        if(bad[x])push(x,l,r);
        long long m=(l+r)>>1;
        return merge(qry(lc[x],l,m,ql,qr),qry(rc[x],m+1,r,ql,qr));
    }

    Info query(long long l,long long r){ // [l,r]
        if(l>r)return Info();
        return qry(rt,L,R,l,r);
    }

    void setm(int x,long long l,long long r,long long p,const Info& v){
        if(l==r){
            t[x]=v,lz[x]=Tag(),bad[x]=0;
            fix(x,l,r);
            return;
        }
        push(x,l,r);
        long long m=(l+r)>>1;
        if(p<=m)setm(lc[x],l,m,p,v);
        else setm(rc[x],m+1,r,p,v);
        pull(x);
    }

    void set_modify(long long p,const Info& v){
        setm(rt,L,R,p,v);
    }

    void set_modify(long long p,long long v){
        set_modify(p,Info(v));
    }

    int nodes(){
        return sz(t)-1;
    }
};
/*
Implicit_Lazy_Segt<SumInfo,AddTag> st;
st.init(0, 1000000000);              // coordinate range

st.range_apply(2, 10, AddTag(5));    // add 5 to [2,10]
st.range_apply(7, 20, AddTag(3));    // add 3 to [7,20]

cout << st.query(0, 100).x << endl;  // sum on [0,100]
cout << st.query(7, 7).x << endl;    // value at index 7

st.set_modify(7, SumInfo(100));      // a[7] = 100
cout << st.query(7, 7).x << endl;    // 100

cout << st.nodes() << endl;          // number of created nodes
*/