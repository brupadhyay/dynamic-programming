#include "bits/stdc++.h"
using namespace std;

/**
 * TC - O(N x N)
 * SC - O(N) x 2
*/

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size();
    vector<int> hash(n, 0);
    vector<int> dp(n, 1);
    int maxi = 0;
    int lastIndex = 0;
    sort(begin(nums), end(nums));
    for(int i = 1; i < n; ++i){
        hash[i] = i;
        for(int prev = 0; prev < i; ++prev){
            if(nums[i] % nums[prev] == 0 &&
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
    vector<int> ans;
    while(lastIndex != hash[lastIndex]){
        ans.push_back(nums[lastIndex]);
        lastIndex = hash[lastIndex];
    }
    ans.push_back(nums[lastIndex]);
    return ans;
}

int main(){
    vector<int> nums = {1,16,7,8,4};
    vector<int> ans = largestDivisibleSubset(nums);
    reverse(ans.begin(), ans.end());
    // 1 4 8 16
    for(auto it: ans){
        cout << it << " ";
    }
}