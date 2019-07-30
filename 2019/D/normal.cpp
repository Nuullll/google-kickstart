#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Guest {
    int pos;
    bool clockwise;
};

vector<int> solve(int N, int G, int M, vector<Guest>& guests) {
    vector<pair<int, vector<int>>> mem (N);
    vector<int> res (G, 1);
    
    for (int i = 0; i < G; ++i) {
        auto g = guests[i];
        --g.pos;
        mem[g.pos].first = 0;
        mem[g.pos].second.push_back(i);
    }
    
    for (int t = 1; t <= M; ++t) {
        for (int i = 0; i < G; ++i) {
            auto& g = guests[i];

            if (g.clockwise) {
                g.pos = (g.pos + 1) % N;
            } else {
                g.pos = (g.pos + N - 1) % N;
            }
            
            if (mem[g.pos].first < t) {
                for (auto& v : mem[g.pos].second) {
                    --res[v];
                }
                mem[g.pos].second.clear();
                mem[g.pos].first = t;
            }
            ++res[i];
            mem[g.pos].second.push_back(i);
        }
    }
    
    return res;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 1; i <= T; ++i) {
        int N, G, M;
        cin >> N >> G >> M;
        
        vector<Guest> guests (G);
        for (auto& g : guests) {
            char c;
            cin >> g.pos >> c;
            
            if (c == 'C') g.clockwise = true;
            else g.clockwise = false;
        }
        
        cout << "Case #" << i << ": ";
        for (auto& v : solve(N, G, M, guests)) {
            cout << v << ' ';
        }
        cout << endl;
    }
    
    return 0;
}