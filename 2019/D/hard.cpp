#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cmath>

typedef long long ull;
using namespace std;

struct Spot {
    int index;
    ull pos;
    ull cost;
};

void heapify(vector<ull>& arr, int N, int p) {
    int largest = p;

    int left = (p<<1) + 1;
    int right = (p<<1) + 2;

    if (left < N && arr[left] > arr[p]) {
        largest = left;
    }
    if (right < N && arr[right] > arr[p]) {
        largest = arr[right] > arr[left] ? right : left;
    }
    if (largest != p) {
        swap(arr[p], arr[largest]);

        heapify(arr, N, largest);
    }
}

ull solve(int K, int N, vector<Spot>& spots) {
    sort(spots.begin(), spots.end(), [](const Spot& a, const Spot& b) {
        return a.pos < b.pos;
    });

    int left_K = K >> 1;
    int right_K = K - left_K;

    vector<ull> left_cost (N), right_cost (N);     // warehouse pos: [left_K, N-right_K)

    // make left heap
    // init warehouse pos
    int wi = left_K;
    vector<ull> max_cost_heap (left_K);
    ull bias = 0;

    if (left_K == 0) goto right;

    for (int i = 0; i < left_K; ++i) {
        max_cost_heap[i] = spots[i].cost + spots[wi].pos - spots[i].pos;
        left_cost[wi] += max_cost_heap[i];
    }
    make_heap(max_cost_heap.begin(), max_cost_heap.end());

    // move warehouse
    while (++wi < N-right_K) {
        ull new_cost = spots[wi-1].cost;
        ull max = max_cost_heap.front();

        ull delta_x = spots[wi].pos - spots[wi-1].pos;
        left_cost[wi] = left_cost[wi-1] + left_K * delta_x;

        if (new_cost < max + bias) {
            max_cost_heap[0] = new_cost - bias;
            heapify(max_cost_heap, left_K, 0);
            left_cost[wi] -= max - new_cost + bias;
        }

        bias += delta_x;
    }

right:
    // make right heap
    wi = N - right_K - 1;
    max_cost_heap.resize(right_K);
    bias = 0;
    for (int i = 0; i < right_K; ++i) {
        max_cost_heap[i] = spots[wi+1+i].cost + spots[wi+1+i].pos - spots[wi].pos;
        right_cost[wi] += max_cost_heap[i];
    }
    make_heap(max_cost_heap.begin(), max_cost_heap.end());

    // move warehouse
    while (--wi >= left_K) {
        ull new_cost = spots[wi+1].cost;
        ull max = max_cost_heap.front();

        ull delta_x = spots[wi+1].pos - spots[wi].pos;
        right_cost[wi] = right_cost[wi+1] + right_K * delta_x;

        if (new_cost < max + bias) {
            max_cost_heap[0] = new_cost - bias;
            heapify(max_cost_heap, right_K, 0);
            right_cost[wi] -= max - new_cost + bias;
        }

        bias += delta_x;
    }

    ull min_cost = LLONG_MAX;
    for (int i = left_K; i < N-right_K; ++i) {
        min_cost = min(min_cost, left_cost[i] + right_cost[i] + spots[i].cost);
    }

    return min_cost;
}

// ull solveVisible(int K, int N, vector<ull>& dis, vector<ull>& costs) {

//     ull res = ULLONG_MAX;

//     for (int i = 0; i < N; ++i) {
//         // try all possible pos for the warehouse
//         ull c = costs[i];
//         ull d = dis[i];

//         vector<ull> new_costs = costs;
//         for (int j = 0; j < N; ++j) {
//             if (i == j) {
//                 new_costs[j] = 0;
//             } else {
//                 new_costs[j] += dis[j] > d ? dis[j] - d : d - dis[j];
//             }
//         }

//         sort(new_costs.begin(), new_costs.end());

//         for (int j = 1; j <= K; ++j) {
//             c += new_costs[j];
//         }

//         res = min(c, res);
//     }

//     return res;
// }


int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i) {
        int K, N;
        cin >> K >> N;

        vector<Spot> spots (N);
        for (int j = 0; j < N; ++j) {
            spots[j].index = j;
            cin >> spots[j].pos;
        }

        for (int j = 0; j < N; ++j) {
            cin >> spots[j].cost;
        }

        cout << "Case #" << i << ": " << solve(K, N, spots);
        cout << endl;
    }

    return 0;
}