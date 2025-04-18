import random

def generate_sample_to_file(n, m, filename="sample_input.txt", seed=None):
    if seed is not None:
        random.seed(seed)

    edges = []
    nodes = list(range(2, n + 1))
    random.shuffle(nodes)

    # Step 1: Generate a spanning tree rooted at node 1 to ensure reachability
    for v in nodes:
        u = random.randint(1, v - 1)
        w = random.randint(1, 10**9)
        # w = random.randint(1, 100)
        edges.append((u, v, w))

    # Step 2: Add remaining m - (n - 1) random edges (can include self-loops and duplicates)
    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        w = random.randint(1, 10**9)
        # w = random.randint(1, 100)
        edges.append((u, v, w))

        # Output the input format
    print(f"{n} {m}")
    for u, v, w in edges:
        print(f"{u} {v} {w}")

    # print(f"Sample with n={n}, m={m} saved to {filename}")

# 示例：生成样例并保存
n = random.randint(1, 50000)
m = random.randint(1, 500000)
# generate_sample_to_file(n = 20 , m = 100, seed=42)
generate_sample_to_file(n  , m , seed=42)
