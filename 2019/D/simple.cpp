#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int start;
    int end;
    int pe_ptr;     // max prefix xor even: [start, pe_ptr]; -1 if not exist
    int po_ptr;     // max prefix xor odd: [start, po_ptr]; -1 if not exist
    int se_ptr;     // max suffix xor even: [se_ptr, end]; INT_MAX if not exist
    int so_ptr;     // max suffix xor odd: [so_ptr, end]; INT_MAX if not exit
    bool even;      // xor sum even?

    Node() : pe_ptr(-1), po_ptr(-1), se_ptr(INT_MAX), so_ptr(INT_MAX) {};
};

void mergeNode(const Node& left, const Node& right, Node& parent) {
    // merge prefix
    if (left.even) {
        parent.pe_ptr = max(left.pe_ptr, right.pe_ptr);
        parent.po_ptr = max(left.po_ptr, right.po_ptr);
    } else {
        parent.pe_ptr = max(left.pe_ptr, right.po_ptr);
        parent.po_ptr = max(left.po_ptr, right.pe_ptr);
    }

    if (right.even) {
        parent.se_ptr = min(left.se_ptr, right.se_ptr);
        parent.so_ptr = min(left.so_ptr, right.so_ptr);
    } else {
        parent.se_ptr = min(left.so_ptr, right.se_ptr);
        parent.so_ptr = min(left.se_ptr, right.so_ptr);
    }

    parent.even = !(left.even ^ right.even);

    return;
}

void buildST(vector<int>& data, int start, int end, vector<Node>& tree, int ptr) {
    tree[ptr].start = start;
    tree[ptr].end = end;

    if (start == end) {

        if (__builtin_parity(data[start])) {
            tree[ptr].po_ptr = tree[ptr].so_ptr = start;
            tree[ptr].even = false;
        } else {
            tree[ptr].pe_ptr = tree[ptr].se_ptr = start;
            tree[ptr].even = true;
        }

        return;
    }

    int mid = (start + end) >> 1;
    buildST(data, start, mid, tree, 2*ptr+1);
    buildST(data, mid+1, end, tree, 2*ptr+2);

    mergeNode(tree[2*ptr+1], tree[2*ptr+2], tree[ptr]);
}

void updateST(vector<Node>& tree, int ptr, int pos, bool val) {
    if (pos == tree[ptr].start && pos == tree[ptr].end) {
        if (tree[ptr].even == val) return;
        tree[ptr].even = val;

        swap(tree[ptr].pe_ptr, tree[ptr].po_ptr);
        swap(tree[ptr].se_ptr, tree[ptr].so_ptr);
        return;
    }

    int mid = tree[2*ptr+1].end;
    if (pos <= mid) updateST(tree, 2*ptr+1, pos, val);
    else updateST(tree, 2*ptr+2, pos, val);

    mergeNode(tree[2*ptr+1], tree[2*ptr+2], tree[ptr]);
}

int queryAll(vector<Node>& tree) {
    return max(tree[0].pe_ptr - tree[0].start + 1, tree[0].end - tree[0].se_ptr + 1);
}

vector<int> solve(int N, vector<int>& nums, int Q, vector<pair<int, int>>& modifications) {
    vector<Node> ST (4*N);
    buildST(nums, 0, N-1, ST, 0);

    vector<bool> parity (N);
    for (int i = 0; i < N; ++i) {
        parity[i] = __builtin_parity(nums[i]);
    }

    vector<int> result (Q);
    for (int i = 0; i < Q; ++i) {
        auto m = modifications[i];
        bool odd = __builtin_parity(m.second);
        if (!(odd ^ parity[m.first])) {
            result[i] = queryAll(ST);
            continue;
        }

        parity[m.first] = odd;
        updateST(ST, 0, m.first, !odd);
        result[i] = queryAll(ST);
    }

    return result;
}

vector<int> solveVisible(int N, vector<int>& nums, int Q, vector<pair<int, int>>& modifications) {
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
        int orig = nums[m.first];
        nums[m.first] = m.second;
        int max_len = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                if (m.first >= i && m.first <= j) {
                    map[i][j] ^= orig ^ m.second;
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