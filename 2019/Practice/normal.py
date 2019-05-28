def read_int():
    return int(input())
    
def read_ints():
    return list(map(int, input().split()))
    
def load():
    N = read_int()
    scores = list(map(int, input()))
    
    return N, scores
    
def solve(case):
    N, scores = case
    
    # find largest sum of contiguous subarrays of length: (N+1)//2
    
    # Suppose the solution subarray starts from i to i+(N+1)//2-1
    # then the sections 0...i-1 and i+(N+1)//2...N-1 are to be destroyed
    # the solution is always achieveable if we start painting from section 2*i
    # we paint the next section depending on the section destroyed yesterday
    
    len_sub = (N+1) // 2
    s = None
    max_s = 0
    for i in range(N - len_sub + 1):
        
        if s is None:
            s = sum(scores[i:i+len_sub])
        else:
            s += scores[i+len_sub-1] - scores[i-1]
        
        max_s = max(max_s, s)
    
    return max_s
            
if __name__ == '__main__':
    T = read_int()
    
    for i in range(T):
        print('Case #{}: {}'.format(i+1, solve(load())))