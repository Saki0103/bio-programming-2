#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

void LoadSequenceFile(string file_name, vector<string>& sequences, vector<int>& labels){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }

    string seq;
    int label;

    while(ifs >> seq >> label){
        sequences.push_back(seq);
        labels.push_back(label);
    }

    ifs.close();
}

void BuildAaIndex(map<char, int>& aa_to_index){
    string aa_order = "ACDEFGHIKLMNPQRSTVWY";
    map<char, int> aa_to_index;
    for(int i = 0; i < 20; i++){
        aa_to_index[aa_order[i]] = i;
    }
}

void BuildFeatureMatrix(
    const vector<string>& sequences,
    vector<vector<double>>& feature_matrix
){
    int num_sequences = sequences.size();
    int aa_number = 20;
    feature_matrix.resize(num_sequences, vector<double>(aa_number, 0.0));

    map<char, int> aa_to_index;
    BuildAaIndex(aa_to_index);

    for(int i = 0; i < num_sequences; i++){
        const string& seq = sequences[i];
        for(int j = 0; j < seq.size(); j++){
            feature_matrix[i][aa_to_index[seq[j]]] += 1.0 / seq.size();
        }
    }
}

int main(void){
    int aa_number = 20;
    string aa_order = "ACDEFGHIKLMNPQRSTVWY";
    map<char, int> aa_to_index;
    for(int i = 0; i < 20; i++){
        aa_to_index[aa_order[i]] = i;
    }

string seq = "MAAWYYDP"
for(int i = 0; i < seq.size(); i++){
    aa_prob[aa_to_index[seq[i]]] += 1.0/seq.size();
}
}
