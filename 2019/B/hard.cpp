#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int start;
    int end;
    int sum;
    int max_psum;
};

void buildST(vector<int>& data, vector<Node>& tree, int ds, int de, int tp) {
    tree[tp].start = ds;
    tree[tp].end = de;

    if (ds == de) {
        // leaf node
        tree[tp].sum = data[ds];
        tree[tp].max_psum = data[ds];
        return;
    }

    // build left tree
    int mid = (de+ds) >> 1;
    buildST(data, tree, ds, mid, 2*tp+1);
    // build right tree
    buildST(data, tree, mid+1, de, 2*tp+2);

    // update this node
    tree[tp].sum = tree[2*tp+1].sum + tree[2*tp+2].sum;
    tree[tp].max_psum = max(tree[2*tp+1].max_psum,
                            tree[2*tp+1].sum + tree[2*tp+2].max_psum);
}

pair<int, int> queryST(vector<Node>& tree, int s, int e, int tp) {
    if (s == tree[tp].start && e == tree[tp].end) {
        return {tree[tp].sum, tree[tp].max_psum};
    }

    int mid = tree[2*tp+1].end;
    if (e <= mid) return queryST(tree, s, e, 2*tp+1);
    if (s >= mid+1) return queryST(tree, s, e, 2*tp+2);

    auto rl = queryST(tree, s, mid, 2*tp+1);
    auto rr = queryST(tree, mid+1, e, 2*tp+2);
    return {rl.first + rr.first, max(rl.second, rl.first + rr.second)};
}

void updateST(vector<Node>& tree, int pos, int val, int tp) {
    if (pos == tree[tp].start && pos == tree[tp].end) {
        tree[tp].sum = val;
        tree[tp].max_psum = val;
        return;
    }

    int mid = tree[2*tp+1].end;
    if (pos <= mid) updateST(tree, pos, val, 2*tp+1);
    else updateST(tree, pos, val, 2*tp+2);

    tree[tp].sum = tree[2*tp+1].sum + tree[2*tp+2].sum;
    tree[tp].max_psum = max(tree[2*tp+1].max_psum,
                            tree[2*tp+1].sum + tree[2*tp+2].max_psum);
}

int solve(int N, int S, vector<int> trinkets) {
    // 1. convert trinkets to count events {+1, -S, +0}
    // 2. record the first -S and all +0 events for all types of trinkets
    vector<int> events (N);
    
    unordered_map<int, list<int>> markers;
    unordered_map<int, int> count;

    for (int i = 0; i < N; ++i) {
        int t = trinkets[i];
        ++count[t];

        if (count[t] == S+1) {
            events[i] = -S;
            markers[t].push_back(i);
        } else if (count[t] > S+1) {
            events[i] = 0;
            markers[t].push_back(i);
        } else {
            events[i] = 1;
        }
    }

    // 3. build segment tree tracking range sum and range max prefix sum
    vector<Node> ST (4*N);
    buildST(events, ST, 0, N-1, 0);

    // 4. query all [i, N-1]
    int res = 0;
    for (int i = 0; i < N; ++i) {
        auto r = queryST(ST, i, N-1, 0);
        res = max(res, r.second);

        // update tree
        int type = trinkets[i];
        // -S event -> +1
        if (!markers[type].empty()) {
            updateST(ST, markers[type].front(), 1, 0);
            markers[type].pop_front();
        }
        // first +0 event -> -S
        if (!markers[type].empty()) {
            updateST(ST, markers[type].front(), -S, 0);
        }
    }

    return res;
}

int solveVisible(int N, int S, vector<int>& trinkets) {
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
        for (int j = 0; j < N; ++j) {
            cin >> trinkets[j];
        }

        cout << "Case #" << i << ": " << solve(N, S, trinkets) << endl;
    }

    return 0;
}