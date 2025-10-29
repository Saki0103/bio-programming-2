#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

enum State{
    S=0,I,R
};

int board[50][50] = {0};
int next_board[50][50] = {0};

int main(void){
    ofstream file("output.txt");

    if(!file){
            cerr << "Cannot open the file." << endl;
            return 1;
        }
    
    random_device rnd;
    mt19937 mt(rnd());

    uniform_int_distribution<> dist(0, 49);

    int x = dist(mt);
    int y = dist(mt);
    board[x][y] = I;
    int z = dist(mt);
    int w= dist(mt);
    while(z == x && w == y){
        z = dist(mt);
        w = dist(mt);
    }
    board[z][w] = I;//初期状態設定終了

    int time = 0;
    int S_count_time = 0;
    int I_count_time = 0;
    int R_count_time = 0;


    while(true){
        time++;

        S_count_time = 0;
        I_count_time = 0;
        R_count_time = 0;
    
        file << "Time: " << time << endl;
        for(int i=0; i<50; i++){
            for(int j=0; j<50; j++){
                if(board[i][j] == S){
                    S_count_time++;
                }else if(board[i][j] == I){
                    I_count_time++;
                }else if(board[i][j] == R){
                    R_count_time++;
                }
            }
        }
        file << "S:" << S_count_time << " I:" << I_count_time << " R:" << R_count_time << endl;

        if(R_count_time == 2500){
            break;
        }

        for(int i=0; i<50; i++) {
            for(int j=0; j<50; j++) {
                int I_count = 0;
                for(int x = i-1; x <= i + 1; x++){
                    for(int y = j-1; y<=j+1; y++){
                        if (x >= 0 && x < 50 && y >= 0 && y < 50){
                            if(board[x][y] == I){
                                I_count++;
                            }
                        }
                    }
                }

                if (board[i][j]==S && I_count==1){
                    uniform_int_distribution<> dist2(0, 9);//0~9のうち0~2が選択される確率は0.3
                    int percent2 = dist2(mt);
                    if(percent2 <= 2){
                        next_board[i][j] = I;
                    }else{
                        next_board[i][j] = S;
                    }
                }else if (board[i][j]==S && I_count>=2){
                    uniform_int_distribution<> dist3(0, (int)(pow(10,I_count))-1);//0~(10^I_count-1)のうち0~(10^I_count-7^I_count-1)が選択される確率は1-0.7^I_count
                    int percent3 = dist3(mt);
                    if(percent3 <= (int)(pow(10,I_count)-pow(7,I_count)-1)){
                        next_board[i][j] = I;
                    }
                    else{
                        next_board[i][j] = S;
                    }
                }else if(board[i][j]==I){
                    uniform_int_distribution<> dist4(0, 99);//0~99のうち0~4が選択される確率は0.05
                    int percent4 = dist4(mt);
                    if(percent4 <= 4){
                        next_board[i][j] = R;
                    }else{
                        next_board[i][j] = I;
                    }
                }else{
                    next_board[i][j] = board[i][j];
                }
            }
        }
        for(int i=0; i<50; i++){
            for(int j=0; j<50; j++){
                board[i][j] = next_board[i][j];
            }
        }
    }
    file.close();
    return 0;
}
