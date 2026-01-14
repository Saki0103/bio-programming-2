#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;

void LoadFile(string file_name, vector<char>& bases){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }


    bases.clear();

    char base;

    while(ifs >> base){
        bases.push_back(base);
    }

    ifs.close();
}

bool Compare(vector<char>& a, vector<char>& b){
    if(a.size() != b.size()) return false;
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

int main(void){
    vector<char> bases;
    LoadFile("genome.txt", bases);

    vector<char> s;

    char c;
    while (cin >> c){
        s.push_back(c);
        if(cin.peek() == '\n'){
            break;
        }
    }
    
    for(int i = 0; i < bases.size(); i++){
        vector<char> a = vector<char>(bases.begin() + i, bases.begin() + i + s.size());
        if(Compare(a, s)){
            cout << i << endl;
        }
    }

    return 0;

}