#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;

void LoadSequenceFile(string file_name, vector<string>& sequences, vector<int>& labels){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }

    int N;
    ifs >> N;

    sequences.clear();
    labels.clear();
    sequences.reserve(N);
    labels.reserve(N);

    string seq;
    int label;

    while(ifs >> seq >> label){
        sequences.push_back(seq);
        labels.push_back(label);
    }

    ifs.close();
}

double Euclid(vector<double>& x, vector<double>& y){
    double sum = 0.0;
    for(int i = 0; i < 20; i++){
        double d = x[i] - y[i];
        sum += d * d;
    }
    return sqrt(sum);
}

int main(void){
    vector<string> train_sequences;
    vector<string> test_sequences;
    vector<int> train_labels;
    vector<int> test_labels;
    LoadSequenceFile("train_mitochondrion_cytoplasm_dataset.txt", train_sequences, train_labels);
    LoadSequenceFile("test_mitochondrion_cytoplasm_dataset.txt", test_sequences, test_labels);

    string aa_order = "ACDEFGHIKLMNPQRSTVWY";
    map<char, int> aa_to_index;
    for(int i = 0; i < 20; i++){
        aa_to_index[aa_order[i]] = i;
    }

    vector<vector<double>> train_features;
    for(int i = 0; i < train_sequences.size(); i++){
        vector<double> aa_prob(20, 0.0);
        for(int j = 0; j < train_sequences[i].size(); j++){
            aa_prob[aa_to_index[train_sequences[i][j]]] += 1.0/train_sequences[i].size();
        }
        train_features.push_back(aa_prob);
    }

    vector<vector<double>> test_features;
    for(int i = 0; i < test_sequences.size(); i++){
        vector<double> aa_prob(20, 0.0);
        for(int j = 0; j < test_sequences[i].size(); j++){
            aa_prob[aa_to_index[test_sequences[i][j]]] += 1.0 / test_sequences[i].size();
        }
        test_features.push_back(aa_prob);
    }

    int correct = 0;

    for(int i = 0; i < (int)test_features.size(); i++){
        int best_j = 0;
        double best_dist = Euclid(test_features[i], train_features[0]);

        for(int j = 1; j < (int)train_features.size(); j++){
            double d = Euclid(test_features[i], train_features[j]);
            if(d < best_dist){
                best_dist = d;
                best_j = j;
            }
        }

        int predict = train_labels[best_j];
        if(predict == test_labels[i]) correct++;
    }

    double accuracy = (double)correct / test_features.size();
    cout << "Balanced Accuracy: " << accuracy << endl;

    return 0;
}
