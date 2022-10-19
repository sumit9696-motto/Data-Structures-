#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3 + 14, mod = 1e9 + 7;

int n, m, dp[maxn], fac[maxn] = {1}, rfac[maxn] = {1};
int po(int a, int b){
	int ans = 1;
	for(; b; b >>= 1, a = (ll) a * a % mod)
		if(b & 1)
			ans = (ll) ans * a % mod;
	return ans;
}
int p(int n, int r){
	return (ll) fac[n] * rfac[n - r] % mod;
}
int c(int n, int r){
	return (ll) p(n, r) * rfac[r] % mod;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	for(int i = 1; i < maxn; i++){
		fac[i] = (ll) fac[i - 1] * i % mod;
		rfac[i] = po(fac[i], mod - 2);
	}
	int t;
	cin >> t;
	while(t--){
		cin >> n >> m;
		fill(dp, dp + m + 1, 0);
		dp[0] = 1;
		map<string, int> all;
		for(int i = 0; i < n; i++){
			string s;
			cin >> s;
			all[s]++;
		}
		while(all.size()){
			string s = all.begin() -> first;
			int cnt = all.begin() -> second;
			all.erase(all.begin());
			string cop = string(s.rbegin(), s.rend());
			if(cop == s){
				for(int i = m; i >= 0; i--){
					for(int j = 2; j <= cnt && i + j <= m; j += 2)
						dp[i + j] = (dp[i + j] + (ll) p(cnt, j) * c((i + j) / 2, j / 2) % mod * dp[i]) % mod;
					if(i % 2 == 0)
						for(int j = 1; j <= cnt && i + j <= m; j += 2)
							dp[i + j] = (dp[i + j] + (ll) p(cnt, j) * c((i + j) / 2, j / 2) % mod * dp[i]) % mod;
				}
			}
			else{
				int c2 = all[cop];
				all.erase(cop);
				cerr << c2 << '\n';
				for(int i = m; i >= 0; i--)
					for(int j = 2; j / 2 <= min(cnt, c2) && i + j <= m; j += 2){
						dp[i + j] = (dp[i + j] + (ll) p(cnt, j / 2) * p(c2, j / 2) % mod * po(2, j / 2) % mod * c((i + j) / 2, j / 2) % mod * dp[i]) % mod;
					}
			}
		}
		cout << accumulate(dp + 1, dp + m + 1, 0ll) % mod << '\n';
	}
}
