// //
// // Created by laurie on 25-5-8.
// //
// #include <iostream>
// #include <vector>
// using namespace std;
// int answer =0;
// void divide(string& a,int k) {
//     if (a.size()<k) {
//         return;
//     }
//     int character[26]={0};
//     vector<string> v;
//     for (int i = 0;i<a.length();i++) {
//         character[a.at(i)-97]++;
//     }
//     int temp=0;
//     for (int i = 0;i<a.length();i++) {
//         if (character[a.at(i)-97]<k) {
//             string test =a.substr(temp,i);
//             if (!test.empty()) {
//                 v.push_back(test);
//             }
//             temp=i;
//         }
//     }
//     if (temp) {
//         string test = a.substr(temp+1,a.length()-1);
//         if (!test.empty()) {
//             v.push_back(test);
//         }
//     }
//     if (v.empty()) {
//         answer = max(answer, static_cast<int>(a.length()));
//         return;
//     }
//
//     for (int i = 0;i<v.size();i++) {
//         divide(v[i],k);
//     }
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);cout.tie(0);
//     string input;
//     cin >> input;
//     int k;
//     cin >> k;
//     divide(input,k);
//     cout << answer << endl;
// }


#include <iostream>
#include <vector>
#include <string>
using namespace std;
int global_answer = 0;
void divide_fixed(string current_string, int k) {
    if (current_string.empty()) {
        return;
    }
    int character_counts[26] = {0};
    for (char c : current_string) {
        character_counts[c - 'a']++;
    }
    bool current_string_is_candidate = true;
    for (char c : current_string) {
        if (character_counts[c - 'a'] < k) {
            current_string_is_candidate = false;
            break;
        }
    }
    if (current_string_is_candidate) {
        global_answer = max(global_answer, static_cast<int>(current_string.length()));
        return;
    }
    vector<string> sub_problems;
    int last_split_pos = 0;
    for (int i = 0; i < current_string.length(); ++i) {
        if (character_counts[current_string[i] - 'a'] < k) {
            if (i > last_split_pos) {
                sub_problems.push_back(current_string.substr(last_split_pos, i - last_split_pos));
            }
            last_split_pos = i + 1;
        }
    }
    if (last_split_pos < current_string.length()) {
        sub_problems.push_back(current_string.substr(last_split_pos, current_string.length() - last_split_pos));
    }
    for (const string& sub : sub_problems) {
        if (!sub.empty()) {
            divide_fixed(sub, k);
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string input;
    cin >> input;
    int k;
    cin >> k;
    if (k == 0) {
        cout << input.length() << endl;
        return 0;
    }
    if (input.empty() || k > input.length()) {
        cout << 0 << endl;
        return 0;
    }
    divide_fixed(input, k);
    cout << global_answer << endl;
    return 0;
}