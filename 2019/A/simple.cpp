#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;


int solve(int N, int P, vector<int>& scores) {
    sort(scores.begin(), scores.end());
    
    int psum = 0;
    for (int i = 0; i < P; ++i) {
        psum += scores[i];
    }
    
    int min_hour = P*scores[P-1] - psum;
    
    for (int i = 1; i <= N-P; ++i) {
        psum += scores[i+P-1] - scores[i-1];
        min_hour = min(min_hour, P*scores[i+P-1] - psum);
    }
    
    return min_hour;
}

int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i) {
        int N, P;
        cin >> N >> P;

        vector<int> scores (N);
        for (auto& v : scores) cin >> v;

        cout << "Case #" << i << ": " << solve(N, P, scores);
        cout << endl;
    }

    return 0;
}