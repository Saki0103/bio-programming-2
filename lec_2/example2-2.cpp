#include <iostream>
#include <vector>
#include <string>
using namespace std;

double CalcGCContent(string seq){
    int count = 0;
    for(int i=0; i<seq.length(); i++){
        if(seq[i] == 'G' || seq[i] == 'C'){
            count++;
        }
    }
    double percent = (double)count / seq.length() *100;
    return percent;
}

int main(void){
    vector<string> sequences = {
        "ATGCGAT",
        "GCGCGCGC",
        "ATATATAC",
        "CCCGGGTT",
        "TTAACCGA"
    };

    //GC contentが50%以上の配列をhigh_gc_sequencesに格納する。
    vector<string> high_gc_sequences; 
    
    for(int i=0; i < sequences.size(); i++){
        double GCContent = CalcGCContent(sequences[i]);
        if(GCContent >= 50.0){
            high_gc_sequences.push_back(sequences[i]);
        }
    }

    //結果の出力
    cout << "GC含量が50%以上の配列：" << endl;
    for(int i = 0; i < high_gc_sequences.size();i++){
        cout << high_gc_sequences[i] << endl;
    }
    return 0;
}
