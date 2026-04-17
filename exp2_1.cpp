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

    ifs.close();
}


int main(void){
    vector<string> base;
    string FileName;
    cout << "Motif: ";
    cin >> FileName;
    LoadFile(FileName, base);

    vector<vector<double>> matrix(4, vector<double>(base[0].size(), 0.0));

    //頻度表の作成
    for(int j=0; j<base[0].size(); j++){
        for(int i=0; i<base.size(); i++){
            if(base[i][j] == 'A') matrix[0][j]++;
            if(base[i][j] == 'C') matrix[1][j]++;
            if(base[i][j] == 'G') matrix[2][j]++;
            if(base[i][j] == 'T') matrix[3][j]++;
        }
    }

    //確率表の作成
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

    //バックグラウンドの確率表の作成
    vector<double> background = {7519429, 4637676, 4637676,7519429};
    double count = 0.0;
    for(int i=0; i<4; i++){
        count += background[i];
    }
    for(int i=0; i<4; i++){
        background[i] /= count;
    }

    //スコア表の作成
    vector<vector<double>> score(4, vector<double>(base[0].size(), 0.0));
    for(int j=0; j<base[0].size(); j++){
        for(int i=0; i<4; i++){
            score[i][j] = log(matrix[i][j] / background[i]);
        }
    }

    //プロモーター配列ファイルの取得
    vector<string> promoter;
    LoadFile("promoters", promoter);
    vector<string> promoter_name((promoter.size()/2));
    vector<string> promoter_base((promoter.size()/2));
    for(int j=0; j<(promoter.size()/2); j++){
        promoter_name[j] = promoter[2*j].substr(1, promoter[2*j].size()-1);
        promoter_base[j] = promoter[2*j+1];
    }

    //プロモーター配列のスコア計算
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
    }

    //ランダム配列の生成
    vector<string> random_base(3);
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> dist(1, 100);
    for(int x=0; x<3; x++){
        for(int i=0; i<promoter_base[0].size(); i++){
            int BaseNumber = dist(mt);
            if(BaseNumber <= 100*background[0]){
                random_base[x].push_back('A');
            }else if(BaseNumber <= 100*(background[0] + background[1])){
              random_base[x].push_back('C');
            }else if(BaseNumber <= 100*(background[0] + background[1] + background[2])){
              random_base[x].push_back('G');
            }else{
            random_base[x].push_back('T');
            }
        }
    }

    
    //ランダム配列のスコア計算
    vector<double> random_hit(3*(promoter_base[0].size()-base[0].size()+1), 0.0);
    for(int i=0; i<3; i++){
        for(int x=0; x<promoter_base[0].size()-base[0].size()+1; x++){
            for(int j=0; j<base[0].size(); j++){
                if(random_base[i][x+j] == 'A') random_hit[x+(i*(promoter_base[0].size()-base[0].size()+1))] += score[0][j];
                if(random_base[i][x+j] == 'C') random_hit[x+(i*(promoter_base[0].size()-base[0].size()+1))] += score[1][j];
                if(random_base[i][x+j] == 'G') random_hit[x+(i*(promoter_base[0].size()-base[0].size()+1))] += score[2][j];
                if(random_base[i][x+j] == 'T') random_hit[x+(i*(promoter_base[0].size()-base[0].size()+1))] += score[3][j];
            }
        }
    }

    //ランダム配列のスコアを降順化
    vector<double> random_hit_sorted(3*(promoter_base[0].size()-base[0].size()+1), 0.0);
    random_hit_sorted = random_hit;
    sort(random_hit_sorted.begin(), random_hit_sorted.end(), greater<double>());

    //p値を設定したときの閾値xの計算
    cout << endl << "p-value:" << endl;
    double p_value;
    cin >> p_value;
    double p_value_number = random_hit_sorted.size() * p_value;
    double x_value = random_hit_sorted[p_value_number];

    cout << "x:" << x_value << endl << endl;

    //閾値x以上のスコアを持つプロモーター配列
    for(int i=0; i<promoter_name.size(); i++){
        for(int x=0; x<promoter_base[0].size()-base[0].size()+1; x++){
            if(count_hit[i][x] >= x_value){
                cout << "pro:" << promoter_name[i] << endl;
                cout << "pos：" << x+1 << endl;
                cout << "hit(" << promoter_base[i].substr(x, base[0].size()) << ") = " << count_hit[i][x] << endl;
                cout << endl;
            }
        }
    }
    
    return 0;
}

