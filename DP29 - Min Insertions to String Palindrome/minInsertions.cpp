#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top _ Down
 * TC - O(N x N)
 * SC - O(N x N) { dp array } + O(N + N) { aux. stack space }
*/

int solve(int l, int r, string &s, vector<vector<int>> &dp){
    if(l >= s.size() || r < 0) return 0;
    if(dp[l][r] != -1) return dp[l][r];

    if(s[l] == s[r]){
        return dp[l][r] = 1 + solve(l+1, r-1, s, dp);
    }
    return dp[l][r] = max(solve(l+1,r,s, dp), solve(l, r-1, s, dp));
}

int minInsertions1(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int> (n, -1));
    int lps = solve(0, n-1, s, dp);
    return n - lps;
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x N)
 * SC - O(N x N) { dp array }
*/

int minInsertions2(string s) {
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
    string t = s;
    reverse(begin(t), end(t));
    for(int i = n-1; i >= 0; i--){
        for(int j = n-1; j >= 0; j--){
            if(s[i] == t[j]){
                dp[i][j] = 1 + dp[i+1][j+1];
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }
    return n - dp[0][0];
}

/**
 * Space Optimisation - Bottom-Up
 * TC - O(N x N)
 * SC - O(N) + O(N) { front/curr array }
*/

int minInsertions3(string s) {
    int n = s.size();
    vector<int> front(n+1, 0);
    vector<int> curr(n+1, 0);
    string t = s;
    reverse(begin(t), end(t));
    for(int i = n-1; i >= 0; i--){
        for(int j = n-1; j >= 0; j--){
            if(s[i] == t[j]){
                curr[j] = 1 + front[j+1];
            } else {
                curr[j] = max(front[j], curr[j+1]);
            }
        }
        front = curr;
    }
    return n - front[0];
}

int main(){
    string s = "bhavesh";
    cout << "min insertions are "<< minInsertions3(s);
}