#include <bits/stdc++.h>
using namespace std;

/**
 * Tabulation - Bottom_Up
 * Time Complexity: O(N*M) + O(N + M)
 * Reason: There are two nested loops for tabulation and other linear is
 * for printing
 * Space Complexity: O(N*M)
 * Reason: We are using an external array of size (N*M).
*/

class Solution1 {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
        for(int i = n-1; i >= 0; --i){
            for(int j = m-1; j >= 0; --j){
                if(str1[i] == str2[j]){
                    dp[i][j] = 1 + dp[i+1][j+1];
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
                }
            }
        }
        int i = 0, j = 0;
        string ans;
        while( i < n && j < m ){
            if(str1[i] == str2[j]){
                ans += str1[i];
                i++;
                j++;
            } else if(dp[i+1][j] > dp[i][j+1]){
                ans += str1[i++];
            } else {
                ans += str2[j++];
            }
        }
        if(i < n) ans += str1.substr(i);
        if(j < m) ans += str2.substr(j);
        return ans;
    }
};


int main(){
    Solution1 obj;
    string s = "groot", t = "brute";
    cout << "shortest common supersequence is "<< obj.shortestCommonSupersequence(s,t);
}