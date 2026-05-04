// https://github.com/NotLinux18/cp-library/blob/main/random.cpp
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}
// shuffle(all(arr) , rng)