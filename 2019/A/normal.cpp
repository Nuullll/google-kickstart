#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

struct Site {
    int t;      // delivery time
    int r;
    int c;
};

struct Info {
    int xpy_max;
    int xpy_min;
    int xmy_max;
    int xmy_min;

    Info() : xpy_max(INT_MIN), xpy_min(INT_MAX), xmy_max(INT_MIN), xmy_min(INT_MAX) {};
    void update(const Site& site) {
        xpy_max = max(xpy_max, site.r + site.c);
        xpy_min = min(xpy_min, site.r + site.c);
        xmy_max = max(xmy_max, site.r - site.c);
        xmy_min = min(xmy_min, site.r - site.c);
    };

    void update(const Info& info) {
        xpy_max = max(xpy_max, info.xpy_max);
        xpy_min = min(xpy_min, info.xpy_min);
        xmy_max = max(xmy_max, info.xmy_max);
        xmy_min = min(xmy_min, info.xmy_min);
    };
};

int solve(int R, int C, vector<string>& grids) {
    unordered_map<int, Info> dict;
    // BFS: overall delivery time
    vector<vector<bool>> visited (R, vector<bool> (C, false));
    queue<Site> bfs;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grids[i][j] == '1') {
                bfs.push({0, i, j});
                visited[i][j] = true;
            }
        }
    }

    int r, c;
    int max_time;
    while (!bfs.empty()) {
        Site& current = bfs.front();
        max_time = current.t;
        dict[max_time].update(current);

        for (int dr = -1; dr <= 1; dr += 2) {
            r = current.r + dr;
            c = current.c;
            if (r >= 0 && r < R) {
                if (!visited[r][c]) {
                    bfs.push({max_time + 1, r, c});
                    visited[r][c] = true;
                }
            }
        }
        for (int dc = -1; dc <= 1; dc += 2) {
            r = current.r;
            c = current.c + dc;
            if (c >= 0 && c < C) {
                if (!visited[r][c]) {
                    bfs.push({max_time + 1, r, c});
                    visited[r][c] = true;
                }
            }
        }

        bfs.pop();
    }

    vector<Info> psum (max_time+1);
    psum[max_time] = dict[max_time];

    for (int i = max_time - 1; i >= 1; --i) {
        // query x-y minmax of sites whose delivery time >= i
        psum[i] = psum[i+1];
        psum[i].update(dict[i]);
    }

    // bi-search possible minimum
    int left = 0, right = max_time;
    while (left < right) {
        int mid = (left + right) >> 1;

        // is mid possible?
        // time > mid should be covered by a 45deg square whose diag length is 2*mid
        auto info = psum[mid+1];
        int x2_lower = info.xpy_max + info.xmy_max - 2*mid;     // lower bound of 2*x
        int x2_upper = info.xpy_min + info.xmy_min + 2*mid;
        int y2_lower = info.xpy_max - info.xmy_min - 2*mid;
        int y2_upper = info.xpy_min - info.xmy_max + 2*mid;
        if (info.xpy_max - info.xpy_min <= 2*mid && info.xmy_max - info.xmy_min <= 2*mid
            && x2_upper >= x2_lower && y2_upper >= y2_lower) {
            if (x2_upper == x2_lower && x2_upper % 2 != 0) {
                left = mid+1;
                continue;
            }
            if (y2_upper == y2_lower && y2_upper % 2 != 0) {
                left = mid+1;
                continue;
            }
            right = mid;
        } else {
            left = mid+1;
        }
    }
    return right;

//    int res;
//    for (res = max_time - 1; res >= 0; --res) {
//        auto info = psum[res+1];
//        if (info.xpy_max - info.xpy_min <= 2*res && info.xmy_max - info.xmy_min <= 2*res) {
//            continue;
//        } else {
//            return res + 1;
//        }
//    }
//
//    return 0;
}

int solveVisible(int R, int C, vector<string>& grids) {
    vector<vector<int>> time_map (R, vector<int> (C, INT_MAX));

    // BFS: overall delivery time
    vector<vector<bool>> visited (R, vector<bool> (C, false));
    queue<Site> bfs;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grids[i][j] == '1') {
                bfs.push({0, i, j});
                visited[i][j] = true;
            }
        }
    }

    int r, c;
    int max_time;
    while (!bfs.empty()) {
        Site& current = bfs.front();
        max_time = current.t;
        time_map[current.r][current.c] = max_time;

        for (int dr = -1; dr <= 1; dr += 2) {
            r = current.r + dr;
            c = current.c;
            if (r >= 0 && r < R) {
                if (!visited[r][c]) {
                    bfs.push({max_time + 1, r, c});
                    visited[r][c] = true;
                }
            }
        }
        for (int dc = -1; dc <= 1; dc += 2) {
            r = current.r;
            c = current.c + dc;
            if (c >= 0 && c < C) {
                if (!visited[r][c]) {
                    bfs.push({max_time + 1, r, c});
                    visited[r][c] = true;
                }
            }
        }

        bfs.pop();
    }

    int res = max_time;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grids[i][j] == '1') continue;

            int overall_time = 0;
            for (int x = 0; x < R; ++x) {
                for (int y = 0; y < C; ++y) {
                    overall_time = max(overall_time, min(time_map[x][y], abs(i-x)+abs(j-y)));
                }
            }
            res = min(res, overall_time);
        }
    }

    return res;
}

int main() {
    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i) {
        int R, C;
        cin >> R >> C;

        vector<string> grids (R);
        for (auto& v : grids) cin >> v;

        cout << "Case #" << i << ": " << solve(R, C, grids);
        cout << endl;
    }

    return 0;
}