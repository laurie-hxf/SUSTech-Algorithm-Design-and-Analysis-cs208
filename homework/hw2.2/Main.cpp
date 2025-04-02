//
// Created by laurie on 25-3-29.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    int N,M,C,T;
    cin>>N>>M>>C>>T;
    vector<int> bunnies(N);
    vector<int> nest(M);
    for(int i=0;i<N;i++) {
        cin>>bunnies[i];
    }
    for(int i=0;i<M;i++) {
        cin>>nest[i];
    }
    vector<int> capacity(M,C);


    sort(bunnies.begin(),bunnies.end());
    sort(nest.begin(),nest.end());

    int i=0,j=0;


        while(i<M&&j<N) {
            if(bunnies[j]-nest[i]<-T) {
                j++;
            }
            if(bunnies[j]-nest[i]>=-T&&bunnies[j]-nest[i]<=T&&capacity[i]>0) {
                j++;
                capacity[i]--;
            }
            if(bunnies[j]-nest[i]>T||capacity[i]==0) {
                i++;
            }
        }

    int result =0;
    for(int k=0;k<M;k++) {
        result += C - capacity[k];
    }
    // result =N- result;
    cout<<result;



}