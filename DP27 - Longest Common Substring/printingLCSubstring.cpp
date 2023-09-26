#include <bits/stdc++.h>
using namespace std;

int lcs1(string &str1, string &str2){
    int ans = 0;
    int n = str1.size(), m = str2.size();
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            string sub = str1.substr(i, j - i + 1);
            if(str2.find(sub) != string::npos){
                ans = max(ans, j - i + 1);
            }
        }
    }
    return ans;
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x M)
 * SC - O(N x M)
*/

int lcs2(string &str1, string &str2){
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
    int ans = 0;
    pair<int,int> lcspair;
    for(int i = n-1; i >= 0; --i){
        for(int j = m-1; j >= 0; --j){
            if(str1[i] == str2[j]){
                dp[i][j] = 1 + dp[i+1][j+1];
                if(dp[i][j] > ans){
                    ans = dp[i][j];
                    lcspair.first = i;
                    lcspair.second = j;
                }
            } else dp[i][j] = 0;
        }
    }
    int len = ans;
    string res;
    int i = lcspair.first;
    int j = lcspair.second;
    
    while(str1[i] == str2[j]){
        res += str1[i];
        i++;
        j++;
    }
    cout <<"lcs is "<< res << endl;

    return ans;
}

/**
 * Space Optimisation 
 * TC - O(N x M)
 * SC - O(2 x M)
*/

int lcs3(string &str1, string &str2){
    int n = str1.size();
    int m = str2.size();
    vector<int> front(m+1, 0);
    vector<int> curr(m+1, 0);
    int ans = 0;
    for(int i = n-1; i >= 0; --i){
        for(int j = m-1; j >= 0; --j){
            if(str1[i] == str2[j]){
                curr[j] = 1 + front[j+1];
                ans = max(ans, curr[j]);
            } else curr[j] = 0;
        }
        front = curr;
    }
    return ans;
}

int main(){
    string a = "abcjklp";
    string b = "acjkp";
    cout << "length of lcs is " << lcs3(a, b);
}