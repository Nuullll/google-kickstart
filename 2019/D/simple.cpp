#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> solve(int N, vector<int>& nums, int Q, vector<pair<int, int>>& modifications) {
    vector<vector<int>> map (N, vector<int> (N));
    
    for (int i = 0; i < N; ++i) {
        int x = nums[i];
        map[i][i] = x;
        
        for (int j = i+1; j < N; ++j) {
            x ^= nums[j];
            map[i][j] = x;
        }
    }
    
    vector<int> res;
    
    for (auto& m : modifications) {
        int max_len = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                if (m.first >= i && m.first <= j) {
                    map[i][j] ^= nums[m.first] ^ m.second;
                }
                
                if (!__builtin_parity(map[i][j])) max_len = max(max_len, j-i+1);
            }
        }
        
        res.push_back(max_len);
    }
    
    return res;
}


int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int N, Q;
        cin >> N >> Q;
        
        vector<int> nums (N);
        for (auto& v : nums) {
            cin >> v;
        }
        
        vector<pair<int, int>> modifications (Q);
        for (auto& v : modifications) {
            cin >> v.first >> v.second;
        }
        
        cout << "Case #" << i << ": ";
        for (auto& v : solve(N, nums, Q, modifications)) {
            cout << v << ' ';
        }
        cout << endl;
    }
    
    return 0;
}