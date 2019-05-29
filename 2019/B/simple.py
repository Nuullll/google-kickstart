from copy import copy

def read_int():
    return int(input())
    
def read_ints():
    return list(map(int, input().split()))
    
def load():
    N, Q = read_ints()
    
    letters = input()
    
    questions = []
    for _ in range(Q):
        questions.append(read_ints())
        
    return N, Q, letters, questions

def solve(case):
    N, Q, letters, questions = case

    psum = [0] * 26
    psums = [copy(psum)]
    
    for i in range(N):
        psum[ord(letters[i])-ord('A')] ^= 1
        psums.append(copy(psum))

    res = 0
    for q in questions:
        odd_count = 0
        for a, b in zip(psums[q[0]-1], psums[q[1]]):
            odd_count += a^b
            
            if odd_count > 1:
                break
        
        if odd_count <= 1 and odd_count ^ ((q[1]-q[0]) % 2):
            res += 1

    return res
    
if __name__ == '__main__':
    T = read_int()
    
    for i in range(T):
        print('Case #{}: {}'.format(i+1, solve(load())))