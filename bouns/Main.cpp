//
// Created by purple on 25-3-13.
//
#include <iostream>
using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 前序遍历（根 -> 左 -> 右）
void preOrder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// 中序遍历（左 -> 根 -> 右）
void inOrder(TreeNode* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// 后序遍历（左 -> 右 -> 根）
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

//     1
//    / \
//   2   3
//  / \
// 4   5


int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "前序遍历: ";
    preOrder(root);
    cout << "\n";

    cout << "中序遍历: ";
    inOrder(root);
    cout << "\n";

    cout << "后序遍历: ";
    postOrder(root);
    cout << "\n";

    // 释放内存
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}