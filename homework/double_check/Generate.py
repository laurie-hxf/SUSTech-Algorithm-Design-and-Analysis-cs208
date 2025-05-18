import random

def generate_points(n, coord_range=1000):
    """
    在命令行中输出最近点对测试数据。
    第1行：点的数量 n
    接下来 n 行：每行一个点，格式为 x y，保留 4 位小数
    """
    print(n)
    for _ in range(n):
        x = round(random.uniform(0, coord_range), 4)
        y = round(random.uniform(0, coord_range), 4)
        print(f"{x} {y}")

# 示例：生成 1000 个点，坐标范围 [0, 1000)
if __name__ == "__main__":
    generate_points(1000)

