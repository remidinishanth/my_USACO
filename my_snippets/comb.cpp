// from kmjp
// source: https://kmjp.hatenablog.jp/entry/2021/03/29/0900

ll mo=1000000007;
ll comb(ll N_, ll C_) {
	const int NUM_=400001;
	static ll fact[NUM_+1],factr[NUM_+1],inv[NUM_+1];
	if (fact[0]==0) {
		inv[1]=fact[0]=factr[0]=1;
		for (int i=2;i<=NUM_;++i) inv[i] = inv[mo % i] * (mo - mo / i) % mo;
		for (int i=1;i<=NUM_;++i) fact[i]=fact[i-1]*i%mo, factr[i]=factr[i-1]*inv[i]%mo;
	}
	if(C_<0 || C_>N_) return 0;
	return factr[C_]*fact[N_]%mo*factr[N_-C_]%mo;
}

// Something noteworthy is you have to calculate binomial coefficients modulo 3, 
// but you can't do it naively since n! = 0 mod3, ∀ n ≥ 3. 
// To get around this, keep track of the power of 3 in 𝑛! (say 𝑝) and the value of 𝑛! without any powers of 3.
// Or use Lucas theorem
 
ll modpow(ll a, ll n) {
	ll r=1;
	while(n) r=r*((n%2)?a:1)%mo,a=a*a%mo,n>>=1;
	return r;
}
 
ll comb(int P_,int Q_) {
	if(P_<0 || Q_<0 || Q_>P_) return 0;
	ll p=1,q=1;
	Q_=min(Q_,P_-Q_);
	for(int i=1;i<=Q_;i++) p=p*P_%mo, q=q*i%mo,P_--;
	
	return p*modpow(q,mo-2)%mo;
}
 
void solve() {
	int i,j,k,l,r,x,y; string s;
	
	cin>>N>>M>>K;
	
	ll ret=0;
	FOR(i,N) {
		ll d=1LL*i*(i+1)/2%mo;
		d=d*M%mo*M%mo;
		ret+=d;
	}
	FOR(i,M) {
		ll d=1LL*i*(i+1)/2%mo;
		d=d*N%mo*N%mo;
		ret+=d;
	}
	
	cout<<ret%mo*comb(N*M-2,K-2)%mo<<endl;
	
	
}
