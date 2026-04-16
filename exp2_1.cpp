#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
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

    ifs.close();
}


int main(void){
    vector<string> base;
    string FileName;
    cout << "enter file name: ";
    cin >> FileName;
    //LoadFile("MATa1", base);
    LoadFile(FileName, base);
    vector<vector<double>> matrix(4, vector<double>(base[0].size(), 0.0));
    vector<vector<double>> score(4, vector<double>(base[0].size(), 0.0));
    vector<double> background = {7519429, 4637676, 4637676,7519429};


    for(int j=0; j<base[0].size(); j++){
        for(int i=0; i<base.size(); i++){
            if(base[i][j] == 'A') matrix[0][j]++;
            if(base[i][j] == 'C') matrix[1][j]++;
            if(base[i][j] == 'G') matrix[2][j]++;
            if(base[i][j] == 'T') matrix[3][j]++;
        }
    }

    for(int j=0; j<base[0].size(); j++){
        double count = 0.0;
        for(int i=0; i<4; i++){
            matrix[i][j]++;
            count += matrix[i][j];
        }
        for(int i=0; i<4; i++){
            matrix[i][j] /= count;
        }
    }

    double count = 0.0;
    for(int i=0; i<4; i++){
        count += background[i];
    }
    for(int i=0; i<4; i++){
        background[i] /= count;
    }

    for(int j=0; j<base[0].size(); j++){
        for(int i=0; i<4; i++){
            score[i][j] = log(matrix[i][j] / background[i]);
        }
    }
    /*
    for(int j=0; j<base[0].size(); j++){
        for(int i=0; i<4; i++){
            cout << score[i][j] << " ";
        }
        cout << "\n";
    }
    */
    vector<string> promoter;
    LoadFile("promoters", promoter);
    vector<string> promoter_name((promoter.size()/2));
    vector<string> promoter_base((promoter.size()/2));
    for(int j=0; j<(promoter.size()/2); j++){
        promoter_name[j] = promoter[2*j].substr(1, promoter[2*j].size()-1);
        promoter_base[j] = promoter[2*j+1];
    }

    vector<vector<double>> count_hit(promoter_name.size(), vector<double>(promoter_base[0].size()-base[0].size()+1, 0.0));
    for(int i=0; i<promoter_name.size(); i++){
        for(int x=0; x<promoter_base[0].size()-base[0].size()+1; x++){
            for(int j=0; j<base[0].size(); j++){
                if(promoter_base[i][x+j] == 'A') count_hit[i][x] += score[0][j];
                if(promoter_base[i][x+j] == 'C') count_hit[i][x] += score[1][j];
                if(promoter_base[i][x+j] == 'G') count_hit[i][x] += score[2][j];
                if(promoter_base[i][x+j] == 'T') count_hit[i][x] += score[3][j];
            }
        }
        cout << promoter_name[i] << endl;
        for(int x=0; x<promoter_base[0].size()-base[0].size()+1; x++){
            cout << count_hit[i][x] << " ";
        }
        cout << endl << endl;
    }

    return 0;
}