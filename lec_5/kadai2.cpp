#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

enum State{
    S=0,I,R,D,V,VI
};

int board[50][50] = {0};
int next_board[50][50] = {0};

int main(void){
    ofstream file("output_kadai2.txt");

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
    int S_count_time;
    int I_count_time;
    int R_count_time;
    int D_count_time;
    int V_count_time;
    int VI_count_time;


    while(true){
        time++;

        S_count_time = 0;
        I_count_time = 0;
        R_count_time = 0;
        D_count_time = 0;
        V_count_time = 0;
        VI_count_time = 0;
    
        file << "Time: " << time << endl;
        for(int i=0; i<50; i++){
            for(int j=0; j<50; j++){
                if(board[i][j] == S){
                    S_count_time++;
                }else if(board[i][j] == I){
                    I_count_time++;
                }else if(board[i][j] == R){
                    R_count_time++;
                }else if(board[i][j] == D){
                    D_count_time++;
                }else if(board[i][j] == V){
                    V_count_time++;
                }else if(board[i][j] == VI){
                    VI_count_time++;
                }
            }
        }
        file << "S:" << S_count_time << " I:" << I_count_time << " R:" << R_count_time << " D:" << D_count_time << " V:" << V_count_time << " VI" << VI_count_time << endl;

        if(I_count_time == 0){
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

                
                if(board[i][j]==S && I_count==1){
                    uniform_int_distribution<> dist2(0, 9);//0~9のうち0~2が選択される確率は0.3
                    int percent2 = dist2(mt);
                    if(percent2 <= 2){
                        next_board[i][j] = I;//0.3の確率で状態SはIに移行
                    }else{
                        next_board[i][j] = S;
                    }
                }else if(board[i][j]==S && I_count>=2){
                    uniform_int_distribution<> dist3(0, (int)(pow(10,I_count))-1);//0~(10^I_count-1)のうち0~(10^I_count-7^I_count-1)が選択される確率は1-0.7^I_count
                    int percent3 = dist3(mt);
                    if(percent3 <= (int)(pow(10,I_count)-pow(7,I_count)-1)){
                        next_board[i][j] = I;
                    }
                    else{
                        next_board[i][j] = S;
                    }
                }else if(board[i][j]==S){
                    uniform_int_distribution<> dist1(0, 4);//0~4のうち0が選択される確率は0.2
                    int percent1 = dist1(mt);
                    if(percent1 == 0){
                        next_board[i][j] = V;//0.2の確率で状態SはVに移行
                    }else{
                        next_board[i][j] = S;
                    }
                }
                if(board[i][j]==I){
                    uniform_int_distribution<> dist4(0, 99);//0~99のうち0~4が選択される確率は0.05
                    int percent4 = dist4(mt);
                    uniform_int_distribution<> dist5(0, 99);//0~99のうち0が選択される確率は0.01
                    int percent5 = dist5(mt);
                    if(percent4 <= 4){
                        next_board[i][j] = R;//0.05の確率で状態IはRに移行
                    }else if(percent5 == 0){
                        next_board[i][j] = D;//0.01の確率で状態IはDに移行
                    }else{
                        next_board[i][j] = I;
                    }
                }else{
                    next_board[i][j] = board[i][j];
                }
                if(board[i][j]==R){
                    uniform_int_distribution<> dist6(0, 99);//0~99のうち0が選択される確率は0.01
                    int percent6 = dist6(mt);
                    if(percent6 == 0){
                        next_board[i][j] = S;//0.01の確率で状態RはSになる
                    }else{
                        next_board[i][j] = R;
                    }
                }
                if(board[i][j]==D){
                    next_board[i][j] = D;
                }
                if(board[i][j]==V){
                    uniform_int_distribution<> dist7(0, 99);//0~99のうち0が選択される確率は0.01
                    int percent7 = dist7(mt);
                    if(percent7 == 0){
                        next_board[i][j] = VI;//0.01の確率で状態VはVIになる
                    }
                }else{
                    next_board[i][j] = V;
                }
                if(board[i][j]==VI){
                    uniform_int_distribution<> dist8(0, 9);//0~9のうち0が選択される確率は0.1
                    int percent8 = dist8(mt);
                    uniform_int_distribution<> dist9(0, 199);//0~199のうち0が選択される確率は0.005
                    int percent9 = dist9(mt);
                    if(percent8 == 0){
                        next_board[i][j] = R;//0.1の確率で状態VIはRになる
                    }else if(percent9 == 0){
                        next_board[i][j] = D;//0.005の確率で状態VIはDになる
                    }else{
                    next_board[i][j] = VI;
                    }
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
