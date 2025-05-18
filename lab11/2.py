def lcs_memoization(s1, s2, m, n, memo=None):

    if memo is None:
        #初始化
        memo = [[-1 for _ in range(len(s2) + 1)] for _ in range(len(s1) + 1)]
    if m == 0 or n == 0:
        return 0
    if memo[m][n] != -1:
        return memo[m][n]
    if s1[m-1] == s2[n-1]:
        result = 1 + lcs_memoization(s1, s2, m-1, n-1, memo)
    else:
        result = max(lcs_memoization(s1, s2, m-1, n, memo),
                       lcs_memoization(s1, s2, m, n-1, memo))
    memo[m][n] = result
    return result



