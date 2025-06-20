

#### **(1)**

**证明：**  
假设存在三个d维盒子A, B, C，满足A嵌套于B，B嵌套于C。根据定义：
- 存在排列$\pi_1$，使得$A$的每个维度满足$x_{\pi_1(i)} < y_i$。
- 存在排列$\pi_2$，使得$B$的每个维度满足$y_{\pi_2(j)} < z_j$。

构造排列$\pi = \pi_2 \circ \pi_1$（先应用$\pi_1$，再应用$\pi_2$），则对任意$i$：
$$
x_{\pi(i)} = x_{\pi_2(\pi_1(i))} < y_{\pi_2(i)} < z_i.
$$
因此，$A$可嵌套于$C$，证明嵌套关系具有传递性。

---

#### **(2)**


1. ：将$X$和$Y$的坐标分别升序排序，得到$X' = (x_{(1)}, \dots, x_{(d)})$和$Y' = (y_{(1)}, \dots, y_{(d)})$。
2. **比较**：检查是否对所有$i \in \{1, \dots, d\}$，满足$x_{(i)} < y_{(i)}$。若成立，则$X$可嵌套于$Y$；否则不可。

**时间复杂度：**  
- 排序时间：$O(d \log d)$（每盒）。
- 比较时间：$O(d)$。
- **总计**：$O(d \log d)$。

**正确性证明：**  

假设有一个我们排完序之后X中有一个元素$x_i$大于Y中对应的元素$y_i$，然后假设这种排序结果满足嵌套关系，那么则对于i后面的元素而言$y_i$始终不能大于$x_k$(k>i)，所以假设不成立。

---

#### **(3)**


1. 
   - 对每个盒子$B_i$，将其坐标升序排序，得到$B_i'$。
   - 将所有盒子按$B_i'$的字典序升序排列。
2. 
   - 初始化数组$L[1..n]$，$L[i]$表示以$B_i$结尾的最长序列长度，初始$L[i] = 1$。
   - 对每个$i$从2到$n$，遍历$j$从1到$i-1$：
     - 若$B_j$可嵌套于$B_i$，则更新$L[i] = \max(L[i], L[j] + 1)$。
   - 最终结果为$\max(L[1..n])$。

**时间复杂度：**  
- ：$O(n d \log d)$。
- ：共$O(n^2)$次嵌套检查，每次耗时$O(d)$。
- **总计**：$O(n^2 d)$。
