#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top_Down
 * Time Complexity: O(N^2)
 * Reason: There are a total of N states and inside each state, 
 * a loop of size N(apparently) is running.
 * Space Complexity: O(N) + Auxiliary stack space O(N)
 * Reason: The first O(N) is for the dp array of size N.
*/

bool isPalindrome(int i, int j, string t){
    while(i < j){
        if(t[i] != t[j]) return false;
        i++;
        j--;
    }
    return true;
}

// Recursive function to find the minimum number of partitions to make palindromes.
int minPartitions(int i, int n, string &str, vector<int> &dp) {
    // Base case: If we've reached the end of the string.
    if (i == n) return 0;

    if (dp[i] != -1) return dp[i];
    int minCost = INT_MAX;
    // Consider all possible substrings starting from the current index.
    for (int j = i; j < n; j++) {
        if (isPalindrome(i, j, str)) {
            // If the substring is a palindrome, calculate the cost and minimize it.
            int cost = 1 + minPartitions(j + 1, n, str, dp);
            minCost = min(minCost, cost);
        }
    }
    return dp[i] = minCost;
}

// Main function to find the minimum number of partitions for palindrome partitioning.
int palindromePartitioning1(string str) {
    int n = str.size();
    vector<int> dp(n, -1);
    // Calling the recursive function and subtracting 1 as it counts partitions, not cuts.
    return minPartitions(0, n, str, dp) - 1;
}


/**
 * Tabulation - Bottom_Up
 * Time Complexity: O(N^2)
 * Reason: There are a total of N states and 
 * inside each state a loop of size N(apparently) is running.
 * Space Complexity: O(N)
 * Reason: O(N) is for the dp array we have used.
*/


int palindromePartitioning2(string s)
{
    int n = s.size();
    vector<int> dp(n+1, 0);
    for(int i = n-1; i >= 0; i--){
        int minCost = 1e9;
        for(int j = i; j < n; j++){
            if(isPalindrome(i, j, s)){
                int cost = 1 + dp[j+1];
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    return dp[0] - 1;
}

int main() {
    string str = "BABABCBADCEDE";
    int partitions = palindromePartitioning2(str);
    cout << "The minimum number of partitions: " << partitions << "\n";
    return 0;
}