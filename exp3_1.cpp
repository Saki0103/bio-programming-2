#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;

void LoadFile(string file_name, vector<string> &base){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    };

    string line;

    while(getline(ifs, line)){
        base.push_back(line);
        
        }
    }

    
void LoadSolubilityFile(string file_name, vector<string> &feature_name, vector<vector<double>> &dataset, vector<int> &labels){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    };
    string line;
    int line_num = 0;
    while(getline(ifs, line)){
        if(line_num == 0){
            int start = 0;
            int end = line.find(",");
            int feature_index = 0;
            while(end != string::npos){
                feature_name[feature_index] = line.substr(start, end - start);
                start = end + 1;
                end = line.find(",", start);
                feature_index++;
            }
            feature_name[feature_index] = line.substr(start);
        }else{
            int start = 0;
            int end = line.find(",");
            int feature_index = 0;
            while(end != string::npos){
                dataset[line_num - 1][feature_index] = stod(line.substr(start, end - start));
                start = end + 1;
                end = line.find(",", start);
                feature_index++;
            }
            dataset[line_num - 1][feature_index] = stod(line.substr(start, end - start));
            labels[line_num - 1] = static_cast<int>(dataset[line_num - 1][feature_index]);
        }
        line_num++;
    }
    ifs.close();
}

int main(void){
    vector<string> feature_name(NUM_FEATURES, "");
    vector<vector<double>> dataset(NUM_SEQS, vector<double>(NUM_FEATURES, 0.0));
    vector<int> labels(NUM_SEQS);

    LoadSolubilityFile("protein_solubility_data.txt", feature_name, dataset, labels);

    vector<vector<double>> training_dataset;
    vector<int> training_labels;
    vector<vector<double>> test_dataset;
    vector<int> test_labels;
    double test_ratio = 0.2;

    DivideDataset(dataset, labels, training_dataset, training_labels, test_dataset, test_labels, test_ratio);
}