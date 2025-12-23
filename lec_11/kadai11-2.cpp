#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#define NUM_TISSUES 68
#define NUM_GENES 19594

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

int main(void){
    vector<string> tissue_names(NUM_TISSUES, "");
    vector<string> gene_names(NUM_GENES, "");
    vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
    LoadExpressionFile("gene_expression.txt", tissue_names, gene_names, expression_matrix);

    vector<double> expression_average(NUM_GENES, 0.0);
    for(int i = 0; i < NUM_GENES; i++){
        for(int j = 0; j < NUM_TISSUES; j++){
            expression_average[i] += expression_matrix[i][j];
        }
        expression_average[i] /= NUM_TISSUES;
    }

    vector<double> expression_max(NUM_GENES, 0.0);
    vector<int> expression_max_tissue(NUM_GENES, 0);
    for(int i = 0; i < NUM_GENES; i++){
        double max_value = expression_matrix[i][0];
        for(int j = 1; j < NUM_TISSUES; j++){
            if(expression_matrix[i][j] > max_value){
                max_value = expression_matrix[i][j];
                expression_max_tissue[i] = j;
            }
        }
        expression_max[i] = max_value;
    }
    
    cout << "組織特異的遺伝子数: " << endl;
    vector<double> tau(NUM_GENES, 0.0);
    vector<int> specific_genes(NUM_TISSUES, 0);
    vector<int> ordered_specific_genes(NUM_TISSUES, 0);
    for(int i = 0; i < NUM_GENES; i++){
        double sum = 0.0;
        for(int j = 0; j < NUM_TISSUES; j++){
            sum += (1.0 - (expression_matrix[i][j] / expression_max[i]));
        }
        tau[i] = sum / (NUM_TISSUES - 1);
        if(tau[i] > 0.85){
            specific_genes[expression_max_tissue[i]]++;
        }
    }
    
    ordered_specific_genes = specific_genes;
    for(int i = 0; i < NUM_TISSUES; i++){
        for(int j = i + 1; j < NUM_TISSUES; j++){
            if(ordered_specific_genes[i] < ordered_specific_genes[j]){
                swap(ordered_specific_genes[i], ordered_specific_genes[j]);
            }
        }
    }
    for(int i = 0; i < NUM_TISSUES; i++){
        for(int j = 0; j < NUM_TISSUES; j++){
            if(specific_genes[j] == ordered_specific_genes[i]){
                cout << tissue_names[j] << ": " << specific_genes[j] << endl;
                if(i==0){
                    for(int k = 0; k < NUM_GENES; k++){
                        if(tau[k] >=0.95 && expression_max_tissue[k] == j && expression_average[k] >= 30.0){
                            cout << "　特異性の高い遺伝子：" << gene_names[k] << endl;
                        }
                    }
                }
                
            }
        }
    }
    
    return 0;
}