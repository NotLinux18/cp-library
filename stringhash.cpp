#define int long long
struct StringHash{
    static const int mod1 = 1000000007;
    static const int mod2 = 1000000009;
    int base;

    vector<int> h1, h2, p1, p2;

    StringHash(){
        mt19937 rnghash(chrono::steady_clock::now().time_since_epoch().count());
        base = uniform_int_distribution<int>(256, StringHash::mod1 - 2)(rnghash);
    }

    void build(const string& s){
        int n = (int)s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 0; i < n; i++){
            p1[i + 1] = (1LL * p1[i] * base) % mod1;
            p2[i + 1] = (1LL * p2[i] * base) % mod2;

            h1[i + 1] = ( (1LL * h1[i] * base) + s[i] ) % mod1;
            h2[i + 1] = ( (1LL * h2[i] * base) + s[i] ) % mod2;
        }
    }

    pair<int,int> get(int l, int r){ // inclusive
        int x1 = (h1[r + 1] - 1LL * h1[l] * p1[r - l + 1]) % mod1;
        if (x1 < 0) x1 += mod1;

        int x2 = (h2[r + 1] - 1LL * h2[l] * p2[r - l + 1]) % mod2;
        if (x2 < 0) x2 += mod2;

        return {x1, x2};
    }
};