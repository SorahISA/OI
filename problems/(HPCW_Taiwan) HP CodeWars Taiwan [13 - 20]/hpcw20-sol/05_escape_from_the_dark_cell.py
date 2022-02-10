def solution(n):
    dp = [[0]*(n+1) for i in range(n+1)]
    for i in range(1,n+1):
        for j in range(1,n-i+1):
            start = j
            end = j+i
            res = float('inf')
            for k in range(start,end):
                res = min(res, k+max(dp[start][k-1],dp[k+1][end]))
            
            dp[start][end] = res
    return dp[1][n]

if __name__ == '__main__':
    ans = solution(int(raw_input()))
    print(ans)