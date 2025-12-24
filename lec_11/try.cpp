#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

#define NUM_TISSUES 68
#define NUM_GENES 19594

using namespace std;

void LoadExpressionFile(const string& file_name, vector<string>& tissue_name,
    vector<string>& gene_name, vector<vector<double>>& expression_matrix){

    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }

    string tmp;
    if(!(ifs >> tmp)){
        cerr << "Error: header read failed\n";
        exit(1);
    }

    for(int i = 0; i < NUM_TISSUES; i++){
        if(!(ifs >> tissue_name[i])){
            cerr << "Error: tissue name read failed at i=" << i << "\n";
            exit(1);
        }
    }

    for(int i = 0; i < NUM_GENES; i++){
        if(!(ifs >> gene_name[i])){
            cerr << "Error: gene name read failed at i=" << i << "\n";
            exit(1);
        }
        for(int j = 0; j < NUM_TISSUES; j++){
            if(!(ifs >> expression_matrix[i][j])){
                cerr << "Error: expression read failed at gene i=" << i
                     << ", tissue j=" << j << "\n";
                exit(1);
            }
        }
    }
}

int main(){
    vector<string> tissue_names(NUM_TISSUES, "");
    vector<string> gene_names(NUM_GENES, "");
    vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
    LoadExpressionFile("gene_expression.txt", tissue_names, gene_names, expression_matrix);

    vector<double> expression_average(NUM_GENES, 0.0);
    for(int i = 0; i < NUM_GENES; i++){
        double s = 0.0;
        for(int j = 0; j < NUM_TISSUES; j++) s += expression_matrix[i][j];
        expression_average[i] = s / NUM_TISSUES;
    }

    vector<double> ordered_cor(5, -numeric_limits<double>::infinity());
    vector<string> ordered_gene(5, "");

    for(int i = 0; i < NUM_GENES; i++){
        for(int j = i+1; j < NUM_GENES; j++){
            double dividend = 0.0, divisor_i = 0.0, divisor_j = 0.0;

            for(int k = 0; k < NUM_TISSUES; k++){
                double di = expression_matrix[i][k] - expression_average[i];
                double dj = expression_matrix[j][k] - expression_average[j];
                dividend += di * dj;
                divisor_i += di * di;
                divisor_j += dj * dj;
            }

            double denom = sqrt(divisor_i) * sqrt(divisor_j);
            if(denom == 0.0) continue;

            double cor = dividend / denom;
            if(std::isnan(cor) || std::isinf(cor)) continue;

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
        cout << i+1 << " " << ordered_gene[i] << " cor: " << ordered_cor[i] << "\n";
    }
    return 0;
}
