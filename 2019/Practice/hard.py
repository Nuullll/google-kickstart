REF = 1000000007
def mod(value):
    return value % REF

def read_int():
    return int(input())
    
def read_ints():
    return list(map(int, input().split()))
    
def load():
    N, K, x1, y1, C, D, E1, E2, F = read_ints()
    A = get_array(N, x1, y1, C, D, E1, E2, F)   # O(N)
    digit_sums = get_sum(A)                     # O(N)
    
    return N, K, A, digit_sums
    
def solve(case):
    N, K, A, digit_sums = case
    
    # POWER = SUM(POWER_i) = SUM(digit_sums[i-1] * (i^1 + i^2 + ... + i^K))
    # which can be simplified by the sum formula of equal-ratio series:
    # i^1 + ... + i^K = i*(i^K-1)/(i-1)
    
    # O(N)
    power = 0
    for i, digit_sum in enumerate(digit_sums):
        power += digit_sum * (i+1) * ((i+1) ** K - 1) // i if i > 0 else digit_sum * K
        power = mod(power)
    
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