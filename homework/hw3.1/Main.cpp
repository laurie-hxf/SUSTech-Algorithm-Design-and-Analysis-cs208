//
// Created by laurie on 25-3-31.
//
#include <iostream>
#include <unordered_map>
using namespace std;


// 双向链表节点
class Node {
public:
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

// LRU Cache 类
class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache; // 哈希表，用于存储 key -> Node 的映射
    Node* head;  // 虚拟头节点
    Node* tail;  // 虚拟尾节点

    // 删除节点
    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 将节点插入到头部
    void insert(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    // 构造函数
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(0, 0); // 虚拟头节点
        tail = new Node(0, 0); // 虚拟尾节点
        head->next = tail;
        tail->prev = head;
    }

    // get 操作
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            insert(node); // 访问后将节点移到头部
            return node->value;
        }
        return -1;
    }

    // put 操作
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            remove(node);
            insert(node); // 更新后将节点移到头部
        } else {
            if (cache.size() >= capacity) {
                // 容量满了，删除尾部节点
                Node* tailNode = tail->prev;
                remove(tailNode);
                cache.erase(tailNode->key);
                delete tailNode;
            }
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            insert(newNode); // 新节点插入到头部
        }
    }

    //销毁缓存
    ~LRUCache() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int N,M;
    // scanf("%d %d", &N, &M);
    cin >> N >> M;
    LRUCache lru(N);
    for(int i = 0; i < M; i++) {
        string command;
        cin >> command;
        // char command[5];
        // scanf("%s", command);

        if(command == "put") {
            int key,value;
            cin >> key >> value;
            // scanf("%d %d", &key, &value);
            lru.put(key, value);
        }
        else if(command == "get") {
            int key;
            // scanf("%d", &key);
            cin >> key;
            int temp = lru.get(key);
            cout << temp << endl;
            // printf("%d\n", temp);
        }
    }
    return 0;
}
