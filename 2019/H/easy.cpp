/*
 * Kick Start 2019 - H
 * H-index (5, 16)
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


void dynamicHIndex(int n) {
    map<int, int> count;

    int h = 0;
    int right = 0;
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;

        ++count[v];

        if (v > h) ++right;

        auto it = count.upper_bound(h);
        int h_next = min(it->first, right);

        if (h_next > h) {
            if (h_next == it->first) {
                right -= it->second;
            }

            ++h;
        }

        cout << h << " ";
    }
}


int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i) {
        int n;
        cin >> n;

        cout << "Case #" << i << ": ";
        dynamicHIndex(n);
        cout << endl;
    }

    return 0;
}