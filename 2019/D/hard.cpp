#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cmath>

typedef unsigned long long ull;
using namespace std;

ull solve(int K, int N, vector<ull>& dis, vector<ull>& costs) {
    
    ull res = ULLONG_MAX;
    
    for (int i = 0; i < N; ++i) {
        // try all possible pos for the warehouse
        ull c = costs[i];
        ull d = dis[i];
        
        vector<ull> new_costs = costs;
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                new_costs[j] = 0;
            } else {
                new_costs[j] += dis[j] > d ? dis[j] - d : d - dis[j];
            }
        }
        
        sort(new_costs.begin(), new_costs.end());
        
        for (int j = 1; j <= K; ++j) {
            c += new_costs[j];
        }
        
        res = min(c, res);
    }
    
    return res;
}


int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int K, N;
        cin >> K >> N;
        
        vector<ull> dis (N);
        for (auto& v : dis) {
            cin >> v;
        }
        
        vector<ull> costs (N);
        for (auto& v : costs) {
            cin >> v;
        }
        
        cout << "Case #" << i << ": " << solve(K, N, dis, costs);
        cout << endl;
    }
    
    return 0;
}