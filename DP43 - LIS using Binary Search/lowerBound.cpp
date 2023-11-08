#include <bits/stdc++.h>
using namespace std;

/**
 * Using lower_bound 
 * TC - O(NlogN)
 * SC - O(N)
*/

int lengthOfLIS(vector<int>& nums) {
    int len = 1;
    vector<int> temp;
    int n = nums.size();
    temp.push_back(nums[0]);
    for(int i = 1; i < nums.size(); i++){
        if(nums[i] > temp.back()){
            temp.push_back(nums[i]);
            len++;
        } else {
            int ind = lower_bound(begin(temp), end(temp), nums[i]) - begin(temp);
            temp[ind] = nums[i];
        }
    }
    return len;
}