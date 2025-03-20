//
// Created by purple on 25-3-13.
//
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
struct Folder;
struct File {
    string name;
    string content;
    Folder* father;
    File(string name,string content) :name(name),content(content),father(NULL){}
};
struct Folder {
    string name;
    Folder* father;
    map<string,Folder*> sub_folder;
    map<string,File*> files;
    Folder(string x) : name(x), father(NULL) {}
};
void search(vector<string>&search_out,Folder* path,string type,string name,string path_name) ;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    istringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}



Folder* find(Folder* root, string name,int offset) {
    Folder* current=root;
    vector<string> path = split(name, '/');
    for(int j = 0; j < path.size()+offset; j++) {
        string folder_name = path[j];
        if(folder_name == ".") {continue;}
        if(folder_name == "..") {
            current = current->father;
        }
        else {
            if(current->sub_folder.find(folder_name)!=current->sub_folder.end()) {
                current = current->sub_folder.at(folder_name);
            }
            else{return current;}
        }
    }
    return current;
}

void search(vector<string>&search_out,Folder* path,string type,string name,string path_name) {     //f is file ,d is folder
    for (pair<string,Folder*> p : path->sub_folder) {
        if(p.first == name|name.empty()) {
            if(type == "d"|type.empty()) {
                search_out.push_back(path_name+"/"+p.first);
            }
        }
        search(search_out,p.second,type,name,path_name+"/"+p.first);
    }

    if(type == "f"|type.empty()) {
        for (pair<string,File*> file : path->files) {
            if(file.first == name) {
                search_out.push_back(path_name+"/"+file.first);
            }
            else if(name.empty()) {
                search_out.push_back(path_name+"/"+file.first);
            }
        }
    }
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    Folder* root = new Folder(".");
    for(int i = 0; i < n; i++) {
        string command;
        cin >> command;

        if(command == "mkdir") {
            string name;
            cin >> name;
            vector<string> path = split(name, '/');
            string folder_name = path.back();
            Folder* current = find(root, name,-1);
            Folder* new_folder=new Folder(folder_name);
            current->sub_folder[folder_name] = new_folder;
            new_folder->father = current;
        }

        else if(command == "echo") {
            string content;
            cin >> content;
            string name;
            string arrow;
            if(content == ">") {
                content="";
                cin >> name;
            }else {
                cin >> arrow;
                cin >> name;
            }
            vector<string> path = split(name, '/');
            string file_name = path.back();
            Folder* current = find(root, name,-1);

            if(current->files.find(file_name) != current->files.end()) {
                current->files[file_name]->content = content;
            }else {
                File* new_file = new File(file_name,content);
                current->files[file_name] = new_file;
                new_file->father = current;
            }
        }

        else if(command == "rm") {
            string parameter;
            cin >> parameter;
            if(parameter=="-rf") {
                string name;
                cin >> name;
                vector<string> path = split(name, '/');
                string folder_name = path.back();
                Folder* current = find(root, name,-1);
                if(current->sub_folder.find(folder_name) != current->sub_folder.end()) {
                    delete current->sub_folder[folder_name];  // 释放动态内存
                    current->sub_folder.erase(folder_name);
                }
            }
            else {
                vector<string> path = split(parameter, '/');
                Folder* current = find(root,parameter,-1);
                string file_name = path.back();
                if(current->files.find(file_name) != current->files.end()) {
                    delete current->files[file_name];
                    current->files.erase(file_name);
                }
            }
        }

        else if(command == "mv") {
            string src_path_to_file, dst_path_to_file;
            cin >> src_path_to_file;
            cin >> dst_path_to_file;
            vector<string> path_1 = split(src_path_to_file, '/');
            vector<string> path_2 = split(dst_path_to_file, '/');
            string file_name = path_1.back();
            Folder* src = find(root, src_path_to_file,-1);
            Folder* dest = find(root, dst_path_to_file,0);
            if(src->files.find(file_name) != src->files.end()) {
                src->files[file_name]->father = dest;
                File* temp = src->files[file_name];
                src->files.erase(file_name);
                dest->files[file_name] = temp;

            }else if(src->sub_folder.find(file_name) != src->sub_folder.end()) {
                src->sub_folder[file_name]->father = dest;
                Folder* temp = src->sub_folder[file_name];
                src->sub_folder.erase(file_name);
                dest->sub_folder[file_name] = temp;
            }
        }
    }

    for(int i = 0; i < m; i++) {
        string command;
        cin >> command;
        if(command == "cat") {
            string name;
            cin >> name;
            vector<string> path = split(name, '/');
            string file_name = path.back();
            Folder* current = find(root, name,-1);
            if(current->files.find(file_name) != current->files.end()) {
                printf("%s\n", current->files[file_name]->content.c_str());
            }
        }
        else if(command == "find") {
            vector<string>search_out;
            string parameter;
            getline(cin, parameter);  // 读取整行输入
            vector<string> parameters = split(parameter, ' ');

            string path ;
            string type ;
            string name ;

            for(int j = 1; j < parameters.size(); j++) {
                string arguments = parameters[j];
                if(arguments == "-type") {
                    type = parameters[j+1];
                    j++;
                }
                else if(arguments == "-name") {
                    name = parameters[j+1];
                    j++;
                }
                else {
                    path = parameters[j];
                }
            }

            if(path.empty()) {
                search_out.push_back(".");
                search(search_out,root, type, name,".");
            }
            else {
                if (path.back() == '/') {
                    path.resize(path.size() - 1);  // 重新调整大小，去除最后一个字符
                }
                Folder* current = find(root, path,0);
                search(search_out,current, type, name,path);
            }
            cout<< search_out.size()<<endl;
            for(int j = 0; j < search_out.size(); j++) {
                cout<<search_out[j]<<endl;
            }

        }
    }

}
