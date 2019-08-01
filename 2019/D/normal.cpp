#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

inline int mod(int x, int m) {
    // return range [0, m-1]
    return (m + (x%m)) % m;
}

int getNext(vector<vector<int>>& poles, int N, int ptr, int direction = 1) {
    int p = mod(ptr+direction, N);
    
    while (poles[p].empty()) {
        if (p == ptr) return -1;
        p = mod(p+direction, N);
    }
    
    return p;
}

vector<int> solve(int N, int G, int M, vector<vector<int>>& cpoles, vector<vector<int>>& apoles, int c_count, int a_count) {
    bool period = false;
    if (M >= N) {
        M %= N;
        period = true;
    }
    
    vector<int> result (G);
    vector<int> last_seen (N, INT_MAX);
    vector<int> orig (N, -1);
    if (c_count) {
        int next = getNext(cpoles, N, N-M-1, 1);
        for (int i = 0; i < N; ++i) {
            int d = mod(i-next, N);
            
            if (d <= M || period) {
                last_seen[i] = mod(M-d, N);
                orig[i] = next;
            }
            
            if (d == M) next = getNext(cpoles, N, next, 1);
        }
    }
    
    if (a_count) {
        int next = getNext(apoles, N, M, -1);
        for (int i = N-1; i >= 0; --i) {
            int d = mod(next-i, N);
            
            if (d <= M || period) {
                int t = mod(M-d, N);
                if (t < last_seen[i]) {
                    for (auto& v : apoles[next]) ++result[v];
                } else if (t == last_seen[i]) {
                    for (auto& v : apoles[next]) ++result[v];
                    for (auto& v : cpoles[orig[i]]) ++result[v];
                } else {
                    for (auto& v : cpoles[orig[i]]) ++result[v];
                }
            } else {
                if (orig[i] != -1) {
                    for (auto& v : cpoles[orig[i]]) ++result[v];
                }
            }
            
            if (d == M) next = getNext(apoles, N, next, -1);
        }
    } else {
        // update result
        for (int i = 0; i < N; ++i) {
            if (orig[i] == -1) continue;
            for (auto& v : cpoles[orig[i]]) ++result[v];
        }
    }
    
    return result;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int N, G, M;
        cin >> N >> G >> M;
        
        vector<vector<int>> cpoles (N), apoles (N);
        int c_count = 0, a_count = 0;
        for (int j = 0; j < G; ++j) {
            int pos;
            char c;
            cin >> pos >> c;
            --pos;
            
            if (c == 'C') {
                cpoles[pos].push_back(j);
                ++c_count;
            } else {
                apoles[pos].push_back(j);
                ++a_count;
            }
        }
        
        cout << "Case #" << i << ": ";
        for (auto& v : solve(N, G, M, cpoles, apoles, c_count, a_count)) {
            cout << v << ' ';
        }
        cout << endl;
    }
    
    return 0;
}