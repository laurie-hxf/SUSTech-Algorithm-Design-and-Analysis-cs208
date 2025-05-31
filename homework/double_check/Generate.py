import random

def generate_points():
    n =random.randint(1, 5)
    m = random.randint(1, 10)
    print(n, m)


# 示例：生成 1000 个点，坐标范围 [0, 1000)
if __name__ == "__main__":
    generate_points()

