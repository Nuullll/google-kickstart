#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;

ull mod = 1000000007;

struct Case {
    ull N;
    ull K;
    vector<ull> A;
    vector<ull> digit_sums;
};

vector<ull> get_array(ull N, ull x1, ull y1, ull C, ull D, ull E1, ull E2, ull F) {
    x1 %= F, y1 %= F;
    C %= F, D %= F;
    E1 %= F, E2 %= F;
    
    vector<ull> X = {x1};
    vector<ull> Y = {y1};
    vector<ull> A = {(x1 + y1) % F};
    
    ull x, y;
    ull xb = x1, yb = y1;
    for (ull i = 0; i < N; ++i) {
        x = (C * xb + D * yb + E1) % F;
        y = (D * xb + C * yb + E2) % F;
        X.push_back(x);
        Y.push_back(y);
        A.push_back((x + y) % F);
        
        xb = x, yb = y;
    }
    
    return A;
}

vector<ull> get_sum(const vector<ull>& A, ull size) {
    vector<ull> digit_sums (size, 0);
    ull s = 0;
    
    for (ull i = 0; i < size; ++i) {
        s = (s + A[size-1-i] * (i + 1)) % mod;
        digit_sums[size-1-i] = s;
    }
    
    return digit_sums;
}

Case load() {
    Case cs;
    ull x1, y1;
    ull C, D, E1, E2, F;
    cin >> cs.N >> cs.K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
    
    cs.A = get_array(cs.N, x1, y1, C, D, E1, E2, F);
    cs.digit_sums = get_sum(cs.A, cs.N);
    
    return cs;
}

ull fast_pow(ull a, ull b, ull c=1000000007) {

    if (a == 1) {
        return a;
    }

    ull res = 1;
    
    while (b > 0) {
        if (b & 0x01) {
            res = (res * a) % c;
        }

        b >>= 1;
        a = (a * a) % c;
    }

    return res;
}

ull solve(Case cs) {
    ull power = (cs.digit_sums[0] * cs.K) % mod;
    ull t;

    for (ull i = 1; i < cs.N; ++i) {
        t = (cs.digit_sums[i] * (i+1)) % mod;
        t = (t * (fast_pow(i+1, cs.K) - 1)) % mod;
        t = (t * fast_pow(i, mod-2)) % mod;

        power += t;
        power %= mod;
    }
    
    return power;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; ++i) {
        cout << "Case #" << i+1 << ": " << solve(load()) << "\n";
    }
    
    return 0;
}