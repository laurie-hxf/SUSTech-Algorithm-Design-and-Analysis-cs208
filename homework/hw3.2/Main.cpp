//
// Created by laurie on 25-4-3.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node {
    long l;
    long r;
    int type;
    Node() : l(0), r(0), type(0) {}
    Node(long l, long r, int type) {
        this->l = l;
        this->r = r;
        this->type = type;
    }
};
int main() {
    int n,m;
    cin>>n>>m;
    vector<Node> v(n+m);
    for(int i=0;i<n;i++) {  //task
        long l,r;
        cin>>l>>r;
        Node temp(l,r,1);
        v[i]=temp;
    }
    for(int i=0;i<m;i++) {  //slot
        long l,r;
        cin>>l>>r;
        Node temp(l,r,0);
        v[i+n]=temp;
    }

    std::sort(v.begin(), v.end(), [](const Node &a, const Node &b) {
        if (a.l != b.l) return a.l < b.l;      // 先按 l 升序
        if (a.r != b.r) return a.r > b.r;      // 然后按 r 降序
        return a.type < b.type;                // 最后按 type 升序
    });


    int ans=0,end=0;
    for(int i=0;i<v.size();i++) {
        if(v[i].type==0) {
            end = v[i].r;
        }else if(v[i].r<=end) {
            ans++;
        }
    }
    cout<<ans<<endl;

}