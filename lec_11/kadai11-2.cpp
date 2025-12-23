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

    vector<double> expression_max(NUM_GENES, 0.0);

    double temp;
    for(int i = 0; i < NUM_TISSUES; i++){
        for(int j = i; j < NUM_TISSUES; j++){
            if(expression_max[j] > expression_max[i]){
                temp = expression_max[i];
                expression_max[i] = expression_matrix[i][j];
            }
        }
    }
    

    return 0;
}