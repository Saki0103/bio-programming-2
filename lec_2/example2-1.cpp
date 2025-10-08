#include <iostream>
#include <string>
using namespace std;

int HammingDistance(string x, string y){
    if(x.length() != y.length()){
        return -1;
    }

    int distance = 0;

    for(int i=0; i<x.length(); i++){
        if(x[i] != y[i]){
            distance++;
        }
    }
    return distance;
}

int main() {
    string a = "AACCGT";
    string b = "AATCAT";
    string c = "AACCG";

    int dist1 = HammingDistance(a, b);
    if (dist1 != -1) {
        cout << "Hamming Distance: " << dist1 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }
    int dist2 = HammingDistance(a, c);
    if (dist2 != -1) {
        cout << "Hamming Distance: " << dist2 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }

    return 0;
}