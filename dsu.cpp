struct DSU{
	vector<int> par , sz;
	void init(int x){
		x += 3;
		par.resize(x);
		iota(par.begin() , par.end() , 0);
		sz.assign(x , 1);
	}
	int find(int a){
		if(par[a] == a)return a;
		return par[a] = find(par[a]);
	}
	void merge(int a , int b){
		a = find(a) , b = find(b);
		if(a == b)return;
		if(sz[a] > sz[b])swap(a,b);
		sz[b] += sz[a];
		par[a] = b;
	}
};