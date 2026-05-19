#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;

#define NUM_FEATURES 53
#define NUM_SEQS 10000

struct TreeNode{
    int feature_id;
    double threshold;
    int left_class_id;
    int right_class_id;
};
    
void LoadSolubilityFile(string file_name, vector<string> &feature_name, vector<vector<double>> &dataset, vector<int> &labels){
    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    };

    string line;
    string header;
    int feature_index = 0;

    getline(ifs, line);
    int start = 0;
    int end = line.find(" ");
    header = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    while(feature_index < NUM_FEATURES && end != string::npos){
        feature_name[feature_index] = line.substr(start, end - start);
        start = end + 1;
        end = line.find(" ", start);
        feature_index++;
    }    
    double value;
    int label_value;

    for(int i = 0; i < NUM_SEQS; i++){
        ifs >> header;
        for(int j = 0; j < NUM_FEATURES; j++){
            ifs >> dataset[i][j];
        }
        ifs >> labels[i];
    }

    ifs.close();
}

void DivideDataset(const vector<vector<double>> &dataset, vector<int> &labels, vector<vector<double>> &training_dataset, vector<int> &training_labels, vector<vector<double>> &test_dataset, vector<int> &test_labels, double test_ratio){
    int num_seqs = dataset.size();
    int num_test_seqs = static_cast<int>(num_seqs * test_ratio);
    int num_training_seqs = num_seqs - num_test_seqs;

    vector<int> numbers(num_seqs);
    for(int i = 0; i < num_seqs; i++){
        numbers[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);

    training_dataset.resize(num_training_seqs);
    training_labels.resize(num_training_seqs);
    test_dataset.resize(num_test_seqs);
    test_labels.resize(num_test_seqs);

    for(int i = 0; i < num_training_seqs; i++){
        training_dataset[i] = dataset[numbers[i]];
        training_labels[i] = labels[numbers[i]];
    }
    for(int i = 0; i < num_test_seqs; i++){
        test_dataset[i] = dataset[numbers[num_training_seqs + i]];
        test_labels[i] = labels[numbers[num_training_seqs + i]];
    }
}

void TrainDecisionTree(vector<vector<double>> &training_dataset, vector<int> &training_labels, vector<TreeNode> &decision_tree){
    vector<vector<double>> training_dataset_sorted;
    training_dataset_sorted = training_dataset;
    for(int i = 0; i < training_dataset.size(); i++){
        sort(training_dataset_sorted[i].begin(), training_dataset_sorted[i].end());
    }

    double gini_left = 0.0;
    double gini_right = 0.0;
    double gini_left_number = 0.0;
    double gini_right_number = 0.0;
    double gini = 0.0;
    int num_left = 0;
    int num_right = 0;
    double gini_minimum = 1.0;
    int x_value;

    for(int i=0; i<NUM_FEATURES; i++){
        for(int x=0; x<99; x++){
            for(int j = 0; j<training_dataset.size(); j++){
                if(training_dataset[j][i] < training_dataset_sorted[(training_dataset.size())*(x+1)/100-1][i]){
                    num_left++;
                    if(training_labels[j] == 1){
                        gini_left += 1.0;
                        gini_left_number += 1.0;
                    }
                }else{
                    num_right++;
                    if(training_labels[j] == 1){
                        gini_right += 1.0;
                        gini_right_number += 1.0;
                    }
                }
            }
            gini_left = 2*(gini_left/num_left)*(1-(gini_left/num_left));
            gini_right = 2*(gini_right/num_right)*(1-(gini_right/num_right));
            gini = (num_left*gini_left + num_right*gini_right) / (num_left + num_right);
            if(gini < gini_minimum){
                gini_minimum = gini;
                decision_tree[0].feature_id = i;
                decision_tree[0].threshold = training_dataset_sorted[(training_dataset.size())*(x+1)/100-1][i];
                if(gini_left_number < 0.5*num_left){
                    decision_tree[0].left_class_id = 0;
                }else{
                    decision_tree[0].left_class_id = 1;
                }
                if(gini_right_number < 0.5*num_right){
                    decision_tree[0].right_class_id = 0;
                }else{
                    decision_tree[0].right_class_id = 1;
                }
                x_value = x;
            }
        }
    }

    training_dataset_sorted[(training_dataset.size())*(x_value+1)/100][decision_tree[0].feature_id];

    double gini_left1 = 0.0;
    double gini_right1 = 0.0;
    double gini_left_number1 = 0.0;
    double gini_right_number1 = 0.0;
    double gini1 = 0.0;
    int num_left1 = 0;
    int num_right1 = 0;
    double gini_minimum1 = 1.0;

    for(int i=0; i<num_left; i++){
        for(int x=0; x<99; x++){
            for(int j = 0; j<num_left; j++){
                if(training_dataset[j][i] < training_dataset_sorted[num_left*(x+1)/100][i]){
                    num_left1++;
                    if(training_labels[j] == 1){
                        gini_left1 += 1.0;
                        gini_left_number1 += 1.0;
                    }
                }else{
                    num_right1++;
                    if(training_labels[j] == 1){
                        gini_right1 += 1.0;
                        gini_right_number1 += 1.0;
                    }
                }
            }
            gini_left1 = 2*(gini_left1/num_left1)*(1-(gini_left1/num_left1));
            gini_right1 = 2*(gini_right1/num_right1)*(1-(gini_right1/num_right1));
            gini1 = (num_left1*gini_left1 + num_right1*gini_right1) / (num_left1 + num_right1);
            if(gini1 < gini_minimum1){
                gini_minimum1 = gini1;
                decision_tree[1].feature_id = i;
                decision_tree[1].threshold = training_dataset_sorted[num_left*(x+1)/100][i];
                if(gini_left_number1 < 0.5*num_left1){
                    decision_tree[1].left_class_id = 0;
                }else{
                    decision_tree[1].left_class_id = 1;
                }
                if(gini_right_number1 < 0.5*num_right1){
                    decision_tree[1].right_class_id = 0;
                }else{
                    decision_tree[1].right_class_id = 1;
                }
            }
        }
    }

    double gini_left2 = 0.0;
    double gini_right2 = 0.0;
    double gini_left_number2 = 0.0;
    double gini_right_number2 = 0.0;
    double gini2 = 0.0;
    int num_left2 = 0;
    int num_right2 = 0;
    double gini_minimum2 = 1.0;

    for(int i=0; i<num_right; i++){
        for(int x=0; x<99; x++){
            for(int j = 0; j<num_right; j++){
                if(training_dataset[j][i] < training_dataset_sorted[num_left*(x+1)/100][i]){
                    num_left2++;
                    if(training_labels[j] == 1){
                        gini_left2 += 1.0;
                        gini_left_number2 += 1.0;
                    }
                }else{
                    num_right2++;
                    if(training_labels[j] == 1){
                        gini_right2 += 1.0;
                        gini_right_number2 += 1.0;
                    }
                }
            }
            gini_left2 = 2*(gini_left2/num_left2)*(1-(gini_left2/num_left2));
            gini_right2 = 2*(gini_right2/num_right2)*(1-(gini_right2/num_right2));
            gini2 = (num_left2*gini_left2 + num_right2*gini_right2) / (num_left2 + num_right2);
            if(gini2 < gini_minimum2){
                gini_minimum2 = gini2;
                decision_tree[2].feature_id = i;
                decision_tree[2].threshold = training_dataset_sorted[num_left*(x+1)/100][i];
                if(gini_left_number2 < 0.5*num_left2){
                    decision_tree[2].left_class_id = 0;
                }else{
                    decision_tree[2].left_class_id = 1;
                }
                if(gini_right_number2 < 0.5*num_right2){
                    decision_tree[2].right_class_id = 0;
                }else{
                    decision_tree[2].right_class_id = 1;
                }
            }
        }
    }

    /*
    cout << "Feature ID: " << decision_tree.feature_id << endl;
    cout << "Threshold: " << decision_tree.threshold << endl;
    */
}

void Evaluation(vector<TreeNode> &decision_tree, vector<vector<double>> &test_dataset, vector<int> &test_labels){
    int num_test_seqs = test_dataset.size();
    int TP = 0;
    int FP = 0;
    int FN = 0;
    int TN = 0;

    /
    for(int i = 0; i < num_test_seqs; i++){
        if(test_dataset[i][decision_tree.feature_id] < decision_tree.threshold){
            if(test_labels[i] == decision_tree.left_class_id){
                if(test_labels[i] == 1){
                    TP++;
                }else{
                    TN++;
                }
            }else{
                if(test_labels[i] == 1){
                    FN++;
                }else{
                    FP++;
                }
            }
        }else{
            if(test_labels[i] == decision_tree.right_class_id){
                if(test_labels[i] == 1){
                    TP++;
                }else{
                    TN++;
                }
            }else{
                if(test_labels[i] == 1){
                    FN++;
                }else{
                    FP++;
                }
            }
        }

    }
    */

    double accuracy = static_cast<double>(TP) / num_test_seqs;
    
    cout << "Accuracy: " << accuracy << endl;
    cout << "Precision: " << static_cast<double>(TP) / (TP + FP) << endl;
    cout << "Recall: " << static_cast<double>(TP) / (TP + FN) << endl;
    cout << "F-score: " << (2.0 * TP) / (2.0 * TP + FP + FN) << endl;
    cout << "Confusion Matrix" << endl;
    cout << "TP: " << TP << " FP: " << FP << endl;
    cout << "FN: " << FN << " TN: " << TN << endl;
    
}

int main(void){
    vector<string> feature_name(NUM_FEATURES, "");
    vector<vector<double>> dataset(NUM_SEQS, vector<double>(NUM_FEATURES, 0.0));
    vector<int> labels(NUM_SEQS);

    LoadSolubilityFile("protein_solubility_dataset.txt", feature_name, dataset, labels);
    
    vector<vector<double>> training_dataset;
    vector<int> training_labels;
    vector<vector<double>> test_dataset;
    vector<int> test_labels;
    double test_ratio = 0.2;

    DivideDataset(dataset, labels, training_dataset, training_labels, test_dataset, test_labels, test_ratio);

    vector<TreeNode> decision_tree(3);
    TrainDecisionTree(training_dataset, training_labels, decision_tree);
    
    Evaluation(decision_tree, test_dataset, test_labels);
    
    return 0;
}