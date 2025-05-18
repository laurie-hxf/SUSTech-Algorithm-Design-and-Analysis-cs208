//
// Created by laurie on 25-5-8.
//
#include <iostream>
#include <vector>

using namespace std;

struct rectangle {
    vector<pair<int, int>> points;
    rectangle() {}
    rectangle(vector<pair<int, int>> a) : points(a) {}
};

// 合并两个 skyline 的核心逻辑
rectangle conquer(rectangle &a, rectangle &b) {
    rectangle c;
    int i = 0, j = 0;
    int h1 = 0, h2 = 0;
    int prevHeight = 0;

    while (i < a.points.size() && j < b.points.size()) {
        int x;
        if (a.points[i].first < b.points[j].first) {
            x = a.points[i].first;
            h1 = a.points[i].second;
            i++;
        } else if (a.points[i].first > b.points[j].first) {
            x = b.points[j].first;
            h2 = b.points[j].second;
            j++;
        } else {
            x = a.points[i].first;
            h1 = a.points[i].second;
            h2 = b.points[j].second;
            i++;
            j++;
        }

        int currHeight = max(h1, h2);
        if (c.points.empty() || currHeight != prevHeight) {
            c.points.emplace_back(x, currHeight);
            prevHeight = currHeight;
        }
    }

    // 处理剩余部分
    while (i < a.points.size()) {
        if (c.points.empty() || a.points[i].second != prevHeight) {
            c.points.push_back(a.points[i]);
            prevHeight = a.points[i].second;
        }
        i++;
    }
    while (j < b.points.size()) {
        if (c.points.empty() || b.points[j].second != prevHeight) {
            c.points.push_back(b.points[j]);
            prevHeight = b.points[j].second;
        }
        j++;
    }

    return c;
}

// 分治主逻辑
rectangle divide(vector<rectangle> &v) {
    if (v.size() == 1) {
        return v[0];
    }
    size_t halfSize = v.size() / 2;
    vector<rectangle> left(v.begin(), v.begin() + halfSize);
    vector<rectangle> right(v.begin() + halfSize, v.end());
    rectangle t1 = divide(left);
    rectangle t2 = divide(right);
    return conquer(t1, t2);
}

int main() {
    int n;
    cin >> n;
    vector<rectangle> v(n);
    for (int i = 0; i < n; i++) {
        int l, r, h;
        cin >> l >> r >> h;
        v[i] = rectangle({{l, h}, {r, 0}});
    }

    rectangle result = divide(v);
    for (auto &pt : result.points) {
        cout << pt.first << " " << pt.second << endl;
    }

    return 0;
}
