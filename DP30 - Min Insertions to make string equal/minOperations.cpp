#include <bits/stdc++.h>
using namespace std;

/**
 * Space Optimisation - Bottom-Up
 * TC - O(N x M)
 * SC - O(M) + O(M) { front/curr array }
*/

int minDistance(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();
    vector<int> front(m+1, 0);
    vector<int> curr(m+1, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = m-1; j >= 0; j--){
            if(word1[i] == word2[j]){
                curr[j] = 1 + front[j+1];
            } else {
                curr[j] = max(front[j], curr[j+1]);
            }
        }
        front = curr;
    }
    return n + m - 2*front[0];
}

int main(){
    string word1 = "leetcode";
    string word2 = "etco";
    cout << "min. operations are "<< minDistance(word1, word2);
}