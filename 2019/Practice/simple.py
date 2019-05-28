def read_int():
    return int(input())

def read_ints():
    return list(map(int, input().split()))

def solve():
    # read A, B
    A, B = read_ints()
    N = read_int()
    
    # binary search, exclusive A, inclusive B
    left, right = A, B
    count = 0
    while left < right:
        mid = (left + right + 1) // 2     # python int is safe, will not overflow
        print(mid)
        count += 1
        
        # get feedback
        feedback = input()
        if feedback == 'CORRECT':
            return True
        elif feedback == 'TOO_BIG':
            right = mid - 1
        elif feedback == 'TOO_SMALL':
            left = mid
        else:
            return False
        
        if count > N:
            # unexpected
            return False
    
    return False

if __name__ == '__main__':
    T = read_int()
    
    for _ in range(T):
        if not solve():
            break
