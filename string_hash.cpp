// https://github.com/NotLinux18/cp-library/blob/main/string_hash.cpp
struct StringHash{
    static const int mod1 = 1000000007;
    static const int mod2 = 1000000009;
    static int base1 , base2;
    vector<int> h1, h2, p1, p2;
    StringHash(){}
    StringHash(const string& s){build(s);}
    void build(const string& s){
        int n = (int)s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        for(int i = 0; i < n; i++){
            p1[i + 1] = (1LL * p1[i] * base1) % mod1;
            p2[i + 1] = (1LL * p2[i] * base2) % mod2;
            h1[i + 1] = ( (1LL * h1[i] * base1) + s[i] ) % mod1;
            h2[i + 1] = ( (1LL * h2[i] * base2) + s[i] ) % mod2;
        }
    }
    pair<int,int> get(int l, int r){ // inclusive
        if(l > r)return {0 , 0};
        int x1 = (h1[r + 1] - 1LL * h1[l] * p1[r - l + 1]) % mod1;
        if(x1 < 0)x1 += mod1;
        int x2 = (h2[r + 1] - 1LL * h2[l] * p2[r - l + 1]) % mod2;
        if(x2 < 0)x2 += mod2;
        return {x1, x2};
    }
};
mt19937 rnghash(chrono::steady_clock::now().time_since_epoch().count());
int StringHash::base1 = uniform_int_distribution<int>(256, StringHash::mod1 - 2)(rnghash);
int StringHash::base2 = uniform_int_distribution<int>(256, StringHash::mod2 - 2)(rnghash);
bool hash_less(const string& a,const string& b){ // a < b lexicographically
    StringHash A(a),B(b);
    int l=0,r=min(sz(a),sz(b));
    while(l<r){
        int m=(l+r+1)>>1;
        if(A.get(0,m-1)==B.get(0,m-1))l=m;
        else r=m-1;
    }
    if(l==min(sz(a),sz(b)))return sz(a)<sz(b);
    return a[l]<b[l];
}
/*
string s = "abacaba";

StringHash sh(s);

cout << (sh.get(0, 2) == sh.get(4, 6)) << endl;
cout << (sh.get(0, 1) == sh.get(2, 3)) << endl;

auto h = sh.get(1, 3);

vector<string> v = {"banana","apple","band"};
sort(all(v),hash_less);
*/