#define MAX_N (200'000 + 7)
vector<int>primes , lp(MAX_N);
void precalc_primes(){
	// lienar sieve
	for(int i=2; i < MAX_N; i++) {
	    if(lp[i] == 0) {
	        lp[i] = i;
	        primes.push_back(i);
	    }
	    for(int j = 0; i * primes[j] < MAX_N; j++){
	        lp[i * primes[j]] = primes[j];
	        if(primes[j] == lp[i]){
	            break;
	        }
	    }
	}
}