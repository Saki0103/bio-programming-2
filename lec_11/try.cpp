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
    
    vector<double> ordered_cor(5, -1.0);
    vector<string> ordered_gene(5, " ");
    for(int i = 0; i < NUM_GENES; i++){
        for(int j = i+1; j < NUM_GENES; j++){
            double cor = 0.0;
            double dividend = 0.0;
            double divisor_i = 0.0;
            double divisor_j = 0.0;
            for(int k = 0; k < NUM_TISSUES; k++){
                dividend += (expression_matrix[i][k] - expression_average[i]) * (expression_matrix[j][k] - expression_average[j]);
                divisor_i += (expression_matrix[i][k] - expression_average[i]) * (expression_matrix[i][k] - expression_average[i]);
                divisor_j += (expression_matrix[j][k] - expression_average[j]) * (expression_matrix[j][k] - expression_average[j]);
            }
            cor = dividend / (sqrt(divisor_i) * sqrt(divisor_j));
            if(cor > ordered_cor[4]){
                ordered_cor[4] = cor;
                ordered_gene[4] = "(" + gene_names[i] + ", " + gene_names[j] + ")";
                for(int k = 4; k > 0; k--){
                    if(ordered_cor[k] > ordered_cor[k-1]){
                        swap(ordered_cor[k], ordered_cor[k-1]);
                        swap(ordered_gene[k], ordered_gene[k-1]);
                    }
                }
            }
        }
    }

    for(int i = 0; i < 5; i++){
        cout << i+1 << " " << ordered_gene[i] << " cor: " << ordered_cor[i] << endl;
    }
  
    return 0;
}