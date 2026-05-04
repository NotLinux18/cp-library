// https://github.com/NotLinux18/cp-library/blob/main/rmq.cpp
template<class T,bool MX=0>
struct RMQ{
    int n,B,nb,K;
    vector<T>a;
    vector<unsigned long long> msk;
    vector<int> lg,bm;
    vector<vector<int>> st;

    bool bet(int i,int j){
        if(i<0)return 0;
        if(j<0)return 1;
        if constexpr(MX)return a[i]>=a[j]; // tie's prioritize left
        else return a[i]<=a[j];            // to make it right change >=/<= to >/<
    }
    int best(int i,int j){return bet(i,j)?i:j;}

    void build(const vector<T>& v){
        a=v,n=sz(a);
        B=max(1,__lg(max(1,n))/2), nb=(n+B-1)/B;
        msk.assign(n,0), bm.assign(nb,-1);

        for(int i=0;i<n;i++){
            int o=i%B,bs=i-o;
            unsigned long long m=msk[r]&(~0ULL<<(l%B));
            while(m){
                int p=63-__builtin_clzll(m), j=bs+p;
                if(bet(j,i))break;
                m^=1ULL<<p;
            }
            msk[i]=m|(1ULL<<o);
            bm[i/B]=best(bm[i/B],i);
        }

        lg.assign(nb+1,0);
        for(int i=2;i<=nb;i++)lg[i]=lg[i>>1]+1;

        K=nb?lg[nb]+1:0;
        st.assign(K,vector<int>(nb));
        if(nb)st[0]=bm;

        for(int k=1;k<K;k++){
            for(int i=0;i+(1<<k)<=nb;i++){
                st[k][i]=best(st[k-1][i],st[k-1][i+(1<<(k-1))]);
            }
        }
    }

    int in(int l,int r){
        unsigned int m=msk[r]&(~0ULL<<(l%B));
        return r-r%B+__builtin_ctzll(m);
    }

    int blocks(int l,int r){
        if(l>r)return -1;
        int k=lg[r-l+1];
        return best(st[k][l],st[k][r-(1<<k)+1]);
    }

    int idx(int l,int r){ // [l,r]
        int bl=l/B,br=r/B;
        if(bl==br)return in(l,r);
        return best(best(in(l,min(n-1,(bl+1)*B-1)),in(br*B,r)),blocks(bl+1,br-1));
    }

    T query(int l,int r){ // [l,r]
        return a[idx(l,r)];
    }
};
/*
vector<int> a = {5, 2, 7, 1, 9};

RMQ<int> rmq; // RMQ<int,1> for max
rmq.build(a);

cout << rmq.query(1, 3) << endl;
cout << rmq.idx(1, 3) << endl;// leftmost minimum
*/