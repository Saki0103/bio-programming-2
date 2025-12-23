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
    vector<double> ordered_average(NUM_GENES, 0.0);
    vector<double> expression_spread(NUM_GENES, 0.0);
    vector<double> ordered_spread(NUM_GENES, 0.0);

    for(int i = 0; i < NUM_GENES; i++){
        for(int j = 0; j < NUM_TISSUES; j++){
            expression_average[i] += expression_matrix[i][j];
        }
        expression_average[i] /= NUM_TISSUES;
    }
    ordered_average = expression_average; 
    
    double temp;
    for(int i = 0; i < NUM_GENES; i++){
        for(int j = i; j < NUM_GENES; j++){
            if(ordered_average[i] <= ordered_average[j]){
                temp = ordered_average[i];
                ordered_average[i] = ordered_average[j];
                ordered_average[j] = temp;
            }
        }
    }
    cout << "Average" << endl;
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < NUM_GENES; i++){
            if(ordered_average[j] == expression_average[i]){
                cout << j+1 << " " << ordered_average[j] << " " << gene_names[i] << endl;
                break;
            }
        }
    }

    for(int i = 0; i < NUM_GENES; i++){
        for(int j = 0; j < NUM_TISSUES; j++){
            expression_spread[i] += (expression_matrix[i][j] - expression_average[i])*(expression_matrix[i][j] - expression_average[i]);
        }
        expression_spread[i] /= NUM_TISSUES;
        expression_spread[i] = sqrt(expression_spread[i]) + 0.01;
        expression_spread[i] = expression_average[i] / expression_spread[i];
    }
    ordered_spread = expression_spread;

    for(int i = 0; i < NUM_GENES; i++){
        for(int j = i; j < NUM_GENES; j++){
            if(ordered_spread[i] <= ordered_spread[j]){
                temp = ordered_spread[i];
                ordered_spread[i] = ordered_spread[j];
                ordered_spread[j] = temp;
            }
        }
    }
    cout << "Spread" << endl;
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < NUM_GENES; i++){
            if(ordered_spread[j] == expression_spread[i]){
                cout << j+1 << " " << ordered_spread[j] << " " << gene_names[i] << endl;
                break;
            }
        }
    }

    return 0;
}