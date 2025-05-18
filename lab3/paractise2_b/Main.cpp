//
// Created by laurie on 25-3-20.
//

/*3
a 1 3
b 2 4
c 4 6
 */

/*
 5
 a 1 2
 b 2 5
 c 3 4
 d 4 6
 e 5 6
 */



#include <iostream>
#include <set>
using namespace std;
struct job {
    string name;
    int start;
    int end;
    job(string name,int s, int e) {
        this->name = name;
        start = s;
        end = e;
    }
};

int main() {
    vector<job> jobs;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        int start, end;
        cin >> name>>start >> end;
        job* temp=new job(name,start, end);
        jobs.push_back(*temp);
    }
    sort(jobs.begin(), jobs.end(), [](const job &a, const job &b) {
        return a.end < b.end; // 小的在前
    });
    int current = jobs[0].end;
    vector<string> results;
    results.push_back(jobs[0].name);
    for (int i = 1; i < jobs.size(); i++) {
        if(jobs[i].start<current) {
            continue;
        }
        current = jobs[i].end;
        results.push_back(jobs[i].name);
    }
    for (int i = 0; i < results.size(); i++) {
        cout << results[i] << endl;
    }
}