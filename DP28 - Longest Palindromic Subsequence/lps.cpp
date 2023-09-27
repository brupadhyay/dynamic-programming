#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top_Down
 * TC - O(N x N)
 * SC - O(N x N) + O(N + N)
*/

int solve(int l, int r, string &s, vector<vector<int>> &dp){
    if(r < 0 || l >= s.size()) return 0;
    if(dp[l][r] != -1) return dp[l][r];
    if(s[l] == s[r]){
        return dp[l][r] = 1 + solve(l+1, r-1, s, dp);
    }
    return dp[l][r] = max(solve(l+1, r, s, dp), solve(l, r-1, s, dp));
}

int longestPalindromeSubseq1(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int> (n, -1));
    return solve(0 , n-1, s, dp);
}




int findLCS(string s, string t){
    int n = s.length();
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
    for(int i = n-1;i>=0;i--){
        for(int j = n-1;j>=0;j--){
            if(s[i] == t[j]){
                dp[i][j] = 1 + dp[i+1][j+1];
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }
    int len = dp[0][0];

    int i = 0, j = 0;
    while(i < n && j < n){
        if(s[i] == t[j]){
            cout << s[i] << " ";
            i++;
            j++;
        } else if(dp[i+1][j] > dp[i][j+1]){
            i++;
        } else j++;
    }
    cout << "\n";

    return dp[0][0];
}
int longestPalindromeSubseq2(string s) {
    string t = s;
    // * important - reverse then LCS
    reverse(begin(t), end(t));
    return findLCS(s, t);
}

int findLCS1(string s, string t){
    int n = s.length();
    vector<int> front(n+1, 0);
    vector<int> curr(n+1, 0);
    for(int i = n-1;i>=0;i--){
        for(int j = n-1;j>=0;j--){
            if(s[i] == t[j]){
                curr[j] = 1 + front[j+1];
            } else {
                curr[j] = max(front[j], curr[j+1]);
            }
        }
        front = curr;
    }
    return front[0];
}
int longestPalindromeSubseq(string s) {
    string t = s;
    reverse(begin(t), end(t));
    return findLCS(s, t);
}


int main(){
    string s = "bbabcbcab";
    cout << "length of longest palindromic subs is "<< longestPalindromeSubseq2(s);
}