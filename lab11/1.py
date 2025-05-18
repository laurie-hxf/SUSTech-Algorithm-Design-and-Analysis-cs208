def fib(n, store={}):
    if n in store:  
        return store[n]
    if n <= 1:
        return n
    
    result = fib(n - 1, store) + fib(n - 2, store)
    store[n] = result
    return result
