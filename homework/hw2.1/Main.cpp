//
// Created by laurie on 25-3-29.
//
#include <iostream>
#include <queue>
using namespace std;
int main() {
    int N,M;
    cin>>N>>M;

    vector<long long> number(N+1,0);
    vector<long long> number_inverse(N+1,0);

    vector<int> income(N+1,0);
    vector<int> income_inverse(N+1,0);

    vector<vector<int>> food_chain(N+1);
    vector<vector<int>> food_chain_inverse(N+1);
    for(int i=0;i<M;i++) {
        int x,y;
        cin>>x>>y;
        food_chain[x].push_back(y);
        income[y]++;
        food_chain_inverse[y].push_back(x);
        income_inverse[x]++;
    }

    queue<int> pq;
    queue<int> pq_inverse;

    for(int i=1;i<N+1;i++) {
        if(income[i]==0) {pq.push(i);number[i]=1;}
        if(income_inverse[i]==0) {pq_inverse.push(i);number_inverse[i]=1;}
    }

    while(!pq.empty()) {
        int x = pq.front();
        pq.pop();
        for(int y:food_chain[x]) {
            number[y]=(number[y]%1000000007+number[x]%1000000007)%1000000007;
            if(--income[y]==0) {
                pq.push(y);
            }
        }
    }

    while(!pq_inverse.empty()) {
        int x = pq_inverse.front();
        pq_inverse.pop();
        for(int y:food_chain_inverse[x]) {
            number_inverse[y]=(number_inverse[y]%1000000007+number_inverse[x]%1000000007)%1000000007;
            if(--income_inverse[y]==0) {
                pq_inverse.push(y);
            }

        }
    }

    for(int i = 1;i<N+1;i++) {
        cout<<(number[i]*number_inverse[i])%1000000007<<" ";
    }
}