// https://github.com/NotLinux18/cp-library/blob/main/mod_math.cpp
template<typename T, typename U>
T fastpow(T a, U b){
    T ret = 1;
    while(b){
        if(b & 1)ret *= a;
        a *= a;
        b >>= 1;
    }
    return ret;
}
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
    friend Mint operator/(const Mint& l, const Mint& r){return l * fastpow(r , mod-2);}
    Mint& operator/=(const Mint& o){return *this = *this / o;}
    friend ostream& operator<<(ostream& os, const Mint& o){return os << o.x;}
    friend istream& operator>>(istream& in, Mint& o){int v;in >> v;o = Mint(v);return in;}
};
Mint fact[MAX_N] = {1}, invfact[MAX_N] = {1};
Mint ncr(int n, int r){return n < r || r < 0 ? 0 : fact[n] * invfact[r] * invfact[n - r];}
Mint bars(int balls , int baskets){return ncr(balls + baskets - 1 , baskets - 1);}
void precalc_math(){
    for(int i = 1; i < MAX_N; i++)fact[i] = fact[i - 1] * i;
    invfact[MAX_N - 1] = 1 / fact[MAX_N - 1];
    for(int i = MAX_N - 2; i >= 0; i--)invfact[i] = (i + 1) * invfact[i + 1];
}
/*
precalc_math();

Mint a = 5, b = 3;

cout << a + b << endl;
cout << a * b << endl;
cout << a / b << endl;

cout << fastpow(2ll, 10) << endl;
cout << ncr(5, 2) << endl;
cout << bars(5, 3) << endl;
*/
