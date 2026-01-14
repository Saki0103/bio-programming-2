#include <iostream>
#include <vector>
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

long hash_s(vector<char>& a){
    long h = 0.0;
    for(int i = 0; i < a.size(); i++){
        h += static_cast<double>(a[i]) * pow(257, a.size()- i-1);
    }
    h /= 1000003;
    return h;
}

long hash_t(vector<char>& b, int start, int length){
    long h = 0.0;
    for(int i = 0; i < length; i++){
        h += static_cast<double>(b[start+i]) * pow(257, length-i-1);
    }
    h /= 1000003;
    return h;
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
        if(hash_s(s) == hash_t(bases, i, s.size())){
            if(Compare(a, s)){
                cout << i << endl;
            }
        }
    }

    return 0;

}