#include <vector>
#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * Time Complexity: O(N*M)
 * Reason: There are two nested loops for memoization 
 * Space Complexity: O(N*M) + O(N + M)
 * Reason: We are using an external array of size (N*M) and recursive stack space.
*/

bool matchStrings(int i, int j, int n, int m, string pat, string txt, vector<vector<int>> &dp){
    if(i >= n && j >= m) return true;
    if(i >= n && j < m) return false;
    if(i < n && j >= m){
        for(int k = i; k < n; k++){
            if(pat[k] != '*') return false;
        }
        return true;
    }

    if(dp[i][j] != -1) return dp[i][j];

    if(pat[i] == txt[j] || pat[i] == '?'){
        return dp[i][j] = matchStrings(i + 1, j + 1, n, m, pat, txt, dp);
    }
    if(pat[i] == '*'){
        return dp[i][j] = matchStrings(i + 1, j, n, m, pat, txt, dp) || matchStrings(i, j+1, n, m, pat, txt, dp);
    }
    return dp[i][j] = false;
}

bool wildcardMatching1(string pattern, string text)
{
   int n = pattern.length();
   int m = text.length();
   vector<vector<int>> dp(n, vector<int> (m, -1));
   return matchStrings(0, 0, n, m, pattern, text, dp);
}

/**
 * Tabulation - Bottom-Up
 * Time Complexity: O(N*M) + O(M) { for pre-filling }
 * Reason: There are two nested loops for tabulation 
 * Space Complexity: O(N*M)
 * Reason: We are using an external array of size (N*M).
*/

bool wildcardMatching2(string pattern, string text)
{
    int n = pattern.length();
    int m = text.length();
    vector<vector<bool>> dp(n+1, vector<bool> (m+1, false));

    dp[n][m] = true;
    for(int i = 0; i < m; i++){
        dp[n][i] = false;
    }
    for(int i = 0; i < n; i++){
        bool flag = true;
        for(int k = i; k < n; k++){
            if(pattern[k] != '*'){
                flag = false;
                break;
            }
        }
        dp[i][m] = flag;
    }

    for(int i = n-1; i >= 0; i--){
        for(int j = m-1; j >= 0; j--){
            if(pattern[i] == text[j] || pattern[i] == '?'){
                dp[i][j] = dp[i+1][j+1];
            } else if(pattern[i] == '*'){
                dp[i][j] = dp[i+1][j] || dp[i][j+1];
            } else dp[i][j] =  false;
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - 2 x 1D Array
 * TC - O(N x M)
 * SC - O(M)
 * Reasong - using external array of m+1 size
*/

bool wildcardMatching3(string pattern, string text)
{
    int n = pattern.length();
    int m = text.length();
    vector<bool> front(m+1, false);
    vector<bool> curr(m+1, false);

    // i >= n && j >= m then true
    front[m] = true;
    // for nth row
    // fixing values of m columns
    for(int i = 0; i < m; i++){
        front[i] = false;
    }

    for(int i = n-1; i >= 0; i--){
        bool flag = true;
        for(int k = i; k < n; k++){
            if(pattern[k] != '*'){
                flag = false;
                break;
            }
        }
        // for every row
        // assigning mth column value
        curr[m] = flag;
        for(int j = m-1; j >= 0; j--){
            if(pattern[i] == text[j] || pattern[i] == '?'){
                curr[j] = front[j+1];
            } else if(pattern[i] == '*'){
                curr[j] = front[j] || curr[j+1];
            } else curr[j] =  false;
        }
        front = curr;
    }
    return front[0];
}

int main(){
    string pat = "*bc*da?*";
    string text = "abccdazzz";
    wildcardMatching3(pat, text) ? cout << "true" : cout << "false";
}