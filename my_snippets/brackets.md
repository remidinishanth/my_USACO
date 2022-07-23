### Unique way of replacing ? in RBS
https://codeforces.com/contest/1709/problem/C There was an Regular Bracket Sequence. Some brackets have been replaced with question marks. Is it true that there is a unique way to replace question marks with brackets, so that the resulting sequence is an RBS?

Consider the segment between the last question mark replaced with an opening bracket, and the first question mark replaced by the closing bracket. If we try to change the order of characters corresponding to question marks, the balance on this segment will decrease at least by 2 (since at least one opening bracket to the left of it will become a closing bracket). Is there a way to affect only this segment, and change the balance on it only by 2? Yes — just swap the endpoints of this segment (i. e. the last opening bracket that was a question mark and the first closing bracket that was also a question mark). If it yields an RBS, then the answer is NO. Otherwise, the answer is YES since any other permutation of characters that were replacing question marks will also decrease the balance on this segment by at least 2.

```cpp
void solve() {
    string S; cin >> S;
    int N = sz(S);
    int remL = N/2, remR = N/2;
    trav(a, S) {
        if (a == '(') remL--;
        if (a == ')') remR--;
    }
    vector<char> rem;
    if (remL <= 0 || remR <= 0) {
        cout << "YES" << nl; return;
    }
    F0R(i, remL) rem.pb('(');
    F0R(i, remR) rem.pb(')');
    swap(rem[remL], rem[remL-1]);
    int p = 0;
    F0R(i, N) {
        if (S[i] == '?') {
            S[i] = rem[p]; p++;
        }
    }
    int cnt = 0;
    F0R(i, N) {
        if (S[i] == '(') {
            cnt++;
        } else {
            cnt--;
            if (cnt < 0) {
                cout << "YES" << nl; return;
            }
        }
    }
    cout << "NO" << nl;
 
}
```
