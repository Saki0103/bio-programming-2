#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

int board[20][20] = {0};
int next_board[20][20] = {0};

int main(void){
    board[0][1] = board[1][2] = board[2][0] = board[2][1] = board[2][2] = 1;

    for (int t = 0; t < 100; t++){
        system("clear");
        for (int i=0; i<20; i++){
            for (int j=0; j<20; j++){
                if(board[i][j] == 1){
                    cout << "M";
                }else{
                    cout << " ";
                }
            }
            cout << endl;
        }

        for(int i=0; i<20; i++) {
            for(int j=0; j<20; j++) {
                int live = 0;
                for(int x = i-1; x <= i + 1; x++){
                    for(int y = j-1; y<=j+1; y++){
                        if (x >= 0 && x < 20 && y >= 0 && y < 20){
                            live += board[x][y];
                        }
                    }
                }
                live -= board[i][j];

                if (board[i][j]==1 && (live==2 ||live==3)){
                    next_board[i][j] = 1;
                }else if(board[i][j]==0 && live==3){
                    next_board[i][j] = 1;
                }else{
                    next_board[i][j] = 0;
                }
            }
        }
        for(int i=0; i<20; i++){
            for(int j=0; j<20; j++){
                board[i][j] = next_board[i][j];
            }
        }
        
        usleep(100000);

    }
    return 0;
}
