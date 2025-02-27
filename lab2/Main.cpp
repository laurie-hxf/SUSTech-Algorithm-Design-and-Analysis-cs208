//
// Created by purple on 25-2-27.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main() {
    int N = 0;
    cin >> N;
    unordered_map<string, int> boys_s2i;    //男孩名字对应编号
    unordered_map<int, string> boys_i2s;    //男孩编号对应名字
    unordered_map<string, int> girls_s2i;   //女孩名字对应编号
    unordered_map<int, string> girls_i2s;   //女孩编号对应名字
    int boys_prefer[N][N];                  //男孩对女孩的心动值
    int girls_prefer_inverse[N][N];         //女孩对男孩的心动值取反

    int girl_fiancé[N];                     //女孩的未婚夫
    int boy_fiancée[N];                     //男孩的未婚妻

    queue<int>boy_free;                     //男孩是否free
    vector<int> boys_propose(N, 0);       //男孩求婚对象

    for (int i = 0; i < N; i++) {           //给男孩名字配对编号
        string s ;
        cin >> s;
        boys_s2i[s]=i;
        boys_i2s[i]=s;
    }
    for (int i = 0; i < N; i++) {           //给女孩名字配对编号
        string s ;
        cin >> s;
        girls_s2i[s]=i;
        girls_i2s[i]=s;
    }

    for (int i = 0; i < N; i++) {           //记录男孩对女孩心动值
        for (int j = 0; j < N; j++) {
            string s;
            cin >>  s;
            boys_prefer[i][j]=girls_s2i[s];
        }
    }
    for (int i = 0; i < N; i++) {           //记录女孩对男孩心动值取反
        for (int j = 0; j < N; j++) {
            string s;
            cin >>  s;
            girls_prefer_inverse[i][boys_s2i[s]]=j;
        }
    }

    for (int i = 0; i < N; i++) {           //初始化男女未婚夫/妻的值，以及队列
        girl_fiancé[i] = -1;
        boy_fiancée[i] = -1;
        boy_free.push(i);
    }

    while (boy_free.size() > 0) {
        int b = boy_free.front();
        int g = boys_prefer[b][boys_propose[b]];
        int g_fiancé = girl_fiancé[g];
        if(g_fiancé==-1) {
            girl_fiancé[g]=b;
            boy_fiancée[b]= g;
            boy_free.pop();
            boys_propose[b]++;
        }
        else if(girls_prefer_inverse[g][b]<girls_prefer_inverse[g][g_fiancé]) {
            girl_fiancé[g]=b;
            boy_fiancée[b]= g;
            boy_free.pop();
            boys_propose[b]++;

            boy_fiancée[g_fiancé]= -1;
            boy_free.push(g_fiancé);
        }
        else {
            boys_propose[b]++;
        }
    }

    for(int i = 0; i < N; i++) {
        printf("%s %s\n",boys_i2s[i].c_str(),girls_i2s[boy_fiancée[i]].c_str());
    }


    return 0;
}