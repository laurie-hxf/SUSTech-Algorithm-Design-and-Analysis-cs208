//
// Created by laurie on 25-4-24.
//
#include <iostream>
#include <vector>

using namespace std;
long long number=0;

// 合并两个有序数组的辅助函数
void merge(vector<int>& arr, int left, int mid, int right) {
    // 创建临时数组来存储两个子数组
    vector<int> temp(right - left + 1);
    int i = left;     // 左边子数组的起始索引
    int j = mid + 1;  // 右边子数组的起始索引
    int k = 0;        // 临时数组的索引

    // 合并两个子数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            number+=(mid-i+1);
        }
    }

    // 复制剩余的元素（如果有的话）
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // 把排序好的临时数组复制回原数组
    for (int t = 0; t < temp.size(); ++t)
        arr[left + t] = temp[t];
}

// 归并排序的递归函数
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);        // 排序左半部分
    mergeSort(arr, mid + 1, right);   // 排序右半部分
    merge(arr, left, mid, right);     // 合并两个部分
}

// 示例主函数
int main() {
    int n ;
    cin >> n ;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    mergeSort(arr, 0, n - 1);
    cout << number << endl;
    return 0;
}
