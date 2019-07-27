#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

int solveVisible(int N, int S, vector<int> trinkets) {
    int res = 1;
    
    for (int i = 0; i < N; ++i) {
        unordered_map<int, int> count {{trinkets[i], 1}};
        int s = 1;
        
        for (int j = i+1; j < N; ++j) {
            int& c = count[trinkets[j]];
            ++c;
            ++s;
            
            if (c == S + 1) s -= c;
            else if (c > S + 1) --s;
            
            res = max(res, s);
        }
    }
    
    return res;
}


int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int N, S;
        cin >> N >> S;
        
        vector<int> trinkets (N);
        for (auto& v : trinkets) {
            cin >> v;
        }
        
        cout << "Case #" << i << ": " << solveVisible(N, S, trinkets) << endl;
    }
    
    return 0;
}