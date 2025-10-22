#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
int rule_number;
vector<int> rules(8,0);
int rule(int left, int center, int right){
    int index = left *4 + center *2 + right *1;
    return rules[index];
}

int main(void){
    cout << "ルール番号を 0~255 から選択してください：" << endl;
    cin >> rule_number;
    if(rule_number<0 || rule_number>255){
        cout << "ルール番号は 0~255 の範囲で指定してください。" << endl;
        return 1;
    }
    int number = rule_number;
    for(int i=0; i<8; i++){
        rules[i] = number % 2;
        number = number / 2;
    }

    vector<int> cell(401, 0);
    cell[200] = 1;
    for(int t=0; t<=200; t++){
        vector<int> new_cell(401,0);
        for(int i=0; i<=400; i++){
            if(i==0){
                new_cell[i] = rule(cell[400], cell[0], cell[1]);
                continue;
            }
            else if(i==400){
                new_cell[i] = rule(cell[399], cell[400], cell[0]);
                continue;
            }
            else{new_cell[i] = rule(cell[i-1], cell[i], cell[i+1]);}
            if(new_cell[i] == 1){
                cout << "█";
            }else{
                cout << " ";
            }
        }
        cell = new_cell;
        cout<< endl;
    }
    return 0;
}