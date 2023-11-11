#include "bits/stdc++.h"
using namespace std;

/**
 * TC - O(NlogN) + O(N x N)
 * SC - O(N) x 2
*/

bool isPossible(string s, string t){
    // checking if two strings differ by only one character
    if(s.size() != t.size() + 1) return false;
    int i = 0, j = 0;
    while(i < s.size()){
        if(j < t.size() && s[i] == t[j]){
            i++;
            j++;
        } else {
            i++;
        }
    }
    if(i == s.size() && j == t.size()) return true;
    return false;
}

bool static comp(string a, string b){
    return a.length() < b.length();
}

int longestStrChain(vector<string>& words) {
    int n = words.size();
    vector<int> hash(n, 0);
    vector<int> dp(n, 1);
    int maxi = dp[0];
    int lastIndex = 0;
    sort(begin(words), end(words), comp);
    for(int i = 1; i < n; ++i){
        hash[i] = i;
        for(int prev = 0; prev < i; ++prev){
            if(isPossible(words[i], words[prev]) &&
            dp[i] < 1 + dp[prev]){
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        }
        if(dp[i] > maxi){
            maxi = dp[i];
            lastIndex = i;
        }
    }
    vector<string> ans;
    while(lastIndex != hash[lastIndex]){
        ans.push_back(words[lastIndex]);
        lastIndex = hash[lastIndex];
    }
    ans.push_back(words[lastIndex]);
    reverse(ans.begin(), ans.end());
    for(auto it: ans) cout << it << " ";
    
    return maxi;
}

int main(){
    vector<string> words = {"xbc","pcxbcf","xb","cxbc","pcxbc"};
    cout << "\nlength of lsc is " << longestStrChain(words);
}