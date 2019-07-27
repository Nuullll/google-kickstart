#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Stone {
    int second;
    int energy;
    int lose;
};

int solve(int N, vector<Stone>& stones) {
    // sort stones according to `a.second * b.lose` and `b.second * a.lose`
    sort(stones.begin(), stones.end(), [](const Stone& a, const Stone& b) {
        return a.second * b.lose < b.second * a.lose;
    });
    
    // 0/1 knapsack
    vector<unordered_map<int, int>> dp (N);
    
    // boundary
    dp[0][0] = 0;
    dp[0][stones[0].second] = stones[0].energy;
    
    for (int i = 1; i < N; ++i) {
        for (auto it = dp[i-1].begin(); it != dp[i-1].end(); ++it) {
            int t1 = it->first;
            dp[i][t1] = max(it->second, dp[i][t1]);
            
            int t2 = stones[i].second;
            dp[i][t1 + t2] = max(it->second + max(0, stones[i].energy - t1 * stones[i].lose), 
                                 dp[i][t1 + t2]);
        }
    }
    
    int res = 0;
    for (auto it = dp.back().begin(); it != dp.back().end(); ++it) {
        res = max(it->second, res);
    }
    
    return res;
}


int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int N;
        cin >> N;
        
        vector<Stone> stones(N);
        for (auto& stone : stones) {
            cin >> stone.second >> stone.energy >> stone.lose;
        }
        
        cout << "Case #" << i << ": " << solve(N, stones) << endl;
    }
    
    return 0;
}