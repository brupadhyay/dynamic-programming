#include <bits/stdc++.h> 
using namespace std;

/**
 * Space Optimised - 
 * TC - O(N) + O(N) ~ O(N)
 * SC - O(1)
*/

long long int leaveFirst(vector<int> valueInHouse, bool isFirst){
    if(isFirst){
        valueInHouse.erase(valueInHouse.begin());
    } else {
        valueInHouse.pop_back();        
    }
    
    int n = valueInHouse.size();
    long long int prev2 = 0;
    long long int prev1 = valueInHouse[0];
    for(int i = 1;i<n;i++){
        long long int pick = valueInHouse[i] + prev2;
        long long int nonpick = 0 + prev1;
        long long int curi = max(pick, nonpick);
        prev2 = prev1;
        prev1 = curi;
    }
    return prev1;
}


long long int houseRobber(vector<int>& valueInHouse)
{
    long long int ans1 = leaveFirst(valueInHouse, true);
    long long int ans2 = leaveFirst(valueInHouse, false);
    return max(ans1, ans2);
}


int main(){
    vector<int> valueInHouse = {1,3,2,1};
    cout << "maximum robbery is "<< houseRobber(valueInHouse);
}