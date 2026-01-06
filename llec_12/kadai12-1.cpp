#include "test_mitochondrion_cytoplasm_dataset.txt"
#include "train_mitochondrion_cytoplasm_dataset.txt"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

void LoadExpressionFile(string file_name, vector<string>& tissue_name, 
    vector<string>& gene_name, vector<vector<double>>& expression_matrix){

    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }
    string tmp;
    ifs >> tmp; 

    for(int i = 0; i < NUM_TISSUES; i++){
        ifs >> tissue_name[i];
    }

    for(int i = 0; i < NUM_GENES; i++){
        ifs >> gene_name[i];
        for(int j = 0; j < NUM_TISSUES; j++){
            ifs >> expression_matrix[i][j];
        }
    }
    ifs.close();
}

string aa_order = "ACDEFGHIKLMNPQRSTVWY";
map<char, int> aa_to_index;
for(int i = 0; i < 20; i++){
    aa_to_index[aa_order[i]] = i;
}

string seq = "MAAWYYDP"
for(int i = 0; i < seq.size(); i++){
    aa_prob[aa_to_index[seq[i]]] += 1.0/seq.size();
}
