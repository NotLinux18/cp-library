mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l , int r){return rng() % (r-l+1) + l;}