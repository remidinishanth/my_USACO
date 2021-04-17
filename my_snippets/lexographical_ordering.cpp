// Without duplicates
var W; //input string
var C[26];
var rank = 1;
for (var i = 0; i < W.length; i++) C[W[i] - 'a']++;
for (var i = 0; i < W.length; i++) {
   //How many characters which are not used, that come before current character
   var count = 0;
   for (var j = 0; j < 26; j++) {
       if (j == (W[i] - 'a')) break;
       if (C[j] > 0) count++;
   }
   C[W[i] - 'a'] = 0;
   rank += count * fact(W.length - i - 1);
}
// source: https://stackoverflow.com/questions/17600863/finding-the-rank-of-the-given-string-in-list-of-all-possible-permutations





using ll = long long;
const ll MOD = 1e9 + 7;

ll fexp(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll inv(ll x) {
    return fexp(x, MOD - 2);
}

// With duplicates: source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/
class Solution {
public:
    int makeStringSorted(string s) {
        ll ans = 0;
        int n = s.size();
        vector<int> cnt(26);
        for (char c : s)
            cnt[c - 'a']++;
        vector<ll> fac(n + 1), invfac(n + 1);
        fac[0] = invfac[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fac[i] = fac[i - 1] * i % MOD;
            invfac[i] = inv(fac[i]);
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < s[i] - 'a'; ++j) {
                if (cnt[j] == 0)
                    continue;
                cnt[j]--;
                ll tot = fac[n - 1 - i];
                for (int k = 0; k < 26; ++k)
                    tot = tot * invfac[cnt[k]] % MOD;
                ans = (ans + tot) % MOD;
                cnt[j]++;
            }
            cnt[s[i] - 'a']--;
        }
        
        return ans;
    }
};
