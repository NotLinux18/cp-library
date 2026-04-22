#define int long long
#define MAX_N (200'000 + 7)
struct Mint {
    static constexpr int mod = 1'000'000'007;
    int x;
    Mint(int x = 0) : x((x % mod + mod) % mod) {}
    explicit operator int()const{return x;}
    bool operator==(const Mint& rhs)const{return x == rhs.x;}
    bool operator!=(const Mint& rhs)const{return !(rhs == *this);}
    friend Mint operator+(const Mint& l, const Mint& r){return l.x + r.x;}
    Mint& operator+=(const Mint& o){return *this = *this + o;}
    friend Mint operator-(const Mint& l, const Mint& r){return l.x - r.x;}
    Mint operator-()const{return -x;}
    Mint& operator-=(const Mint& o){return *this = *this - o;}
    friend Mint operator*(const Mint& l, const Mint& r){return (int)l.x * r.x;}
    Mint& operator*=(const Mint& o){return *this = *this * o;}
    friend Mint fastpow(Mint a , int b){
        Mint ret = 1;
        while(b){
            if(b&1)ret = ret * a;
            a = a * a;
            b >>= 1;
        }
        return ret;
    }
    friend Mint fastpow(Mint a , Mint mb){
        long long b = mb.x;
        Mint ret = 1;
        while(b){
            if(b&1)ret = ret * a;
            a = a * a;
            b >>= 1;
        }
        return ret;
    }
    friend Mint operator/(const Mint& l, const Mint& r){return l * fastpow(r , mod-2);}
    Mint& operator/=(const Mint& o){return *this = *this / o;}
    friend ostream& operator<<(ostream& os, const Mint& o){return os << o.x;}
    friend istream& operator>>(istream& in, Mint& o){
        long long v;
        in >> v;
        o = Mint(v);
        return in;
    }
};
Mint fact[MAX_N] = {1}, invfact[MAX_N] = {1};
Mint ncr(int n, int r){return n < r || r < 0 ? 0 : fact[n] * invfact[r] * invfact[n - r];}
Mint bars(int balls , int baskets){return ncr(balls + baskets - 1 , baskets - 1);}
void precalc_math(){
    for(int i = 1; i < MAX_N; i++)fact[i] = fact[i - 1] * i;
    invfact[MAX_N - 1] = 1 / fact[MAX_N - 1];
    for(int i = MAX_N - 2; i >= 0; i--)invfact[i] = (i + 1) * invfact[i + 1];
}
