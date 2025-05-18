//
// Created by laurie on 25-5-16.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;
struct points {
    double x;
    double y;
    points() : x(0), y(0) {}
    points(double x, double y) {
        this->x = x;
        this->y = y;
    }
};
double t = 1e18;


double closest_pair(vector<points> &v) {
    if (v.size() == 1) {
        return t;
    }
    int mid = v.size()/2;

    vector<points> left(v.begin(), v.begin()+mid);
    vector<points> right(v.begin()+mid, v.end());
    double t1 = closest_pair(left);
    double t2 = closest_pair(right);
    t = min(t, min(t1, t2));

    double L = (right[0].x+left.back().x)/2;
    vector<points> temp;
    for (size_t i = 0; i < v.size(); i++) {
        if (abs(v[i].x - L)<sqrt(t)) {
            temp.push_back(v[i]);
        }
    }
    std::sort(temp.begin(), temp.end(), [](const points& a, const points& b) {
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
    });

    size_t size = temp.size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i+1; j < i+11; j++) {
            if (j<size) {
                double dis = (temp[i].x - temp[j].x) * (temp[i].x - temp[j].x) +
                (temp[i].y - temp[j].y) * (temp[i].y - temp[j].y);
                if (dis < t) {
                    t = dis;
                }
            }
            else break;
        }

    }

    return t;


}
int main() {
    int n;
    cin >> n;
    vector<points> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].x;
        cin >> v[i].y;
    }
    std::sort(v.begin(), v.end(), [](const points& a, const points& b) {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
        });

    closest_pair(v);
    cout << fixed << setprecision(4) << sqrt(t) << endl;


}