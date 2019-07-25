MOD = 1000000007

def read_int():
    return int(input())
    
def read_ints():
    return list(map(int, input().split()))
    
def load():
    N, K, x1, y1, C, D, E1, E2, F = read_ints()
    A = get_array(N, x1, y1, C, D, E1, E2, F)   # O(N)
    
    return N, K, A
    
def solve(case):
    N, K, A = case
    
    # POWER = SUM(POWER_i) = SUM(digit_sums[i-1] * (i^1 + i^2 + ... + i^K))
    # which can be simplified by the sum formula of equal-ratio series:
    # i^1 + ... + i^K = i*(i^K-1)/(i-1)
    
    digit_sum = 0
    power = 0
    for i in range(N):
        digit_sum = (digit_sum + A[N-1-i] * (i+1)) % MOD

        if i == N - 1:
            power = (power + digit_sum * K) % MOD
        else:
            power = (power + digit_sum * (N-i) * (pow(N-i, K, MOD) - 1) * pow(N-i-1, MOD-2, MOD)) % MOD
    
    return power
    
def get_array(N, x1, y1, C, D, E1, E2, F):
    X = [x1 % F]
    Y = [y1 % F]
    A = [(x1 + y1) % F]
    C %= F
    D %= F
    E1 %= F
    E2 %= F
    
    for i in range(1, N):
        x_next = (C * X[-1] + D * Y[-1] + E1) % F
        y_next = (D * X[-1] + C * Y[-1] + E2) % F
        X.append(x_next)
        Y.append(y_next)
        A.append((x_next + y_next) % F)
    
    return A

def get_sum(A):
    L = len(A)
    
    # denote f(i, j) as the total times appeared for A[i] in all contiguous subarrays at position j
    # therefore f(i, j) = 0, for i < j
    # and f(i, j) = L - i, otherwise
    
    # note that POWER_x is the summation of power of all contiguous subarrays
    # and power of each contiguous subarray is calculated in digit-wise fashion
    # so we can sum up each digits first,
    # and then apply the exponential multiplicants
    
    # sum of digit position j for all contiguous subarrays:
    # SUM(f(i, j) * A[i] for i >= j)
    
    # calculate in reverse order, to reuse the former result
    
    digit_sums = []
    s = 0
    for j in range(L-1, -1, -1):
        s += A[j] * (L - j)
        digit_sums.append(s)
    
    return list(reversed(digit_sums))

if __name__ == '__main__':
    T = read_int()
    
    for i in range(T):
        print('Case #{}: {}'.format(i+1, solve(load())))