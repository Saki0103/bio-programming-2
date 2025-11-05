#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
using namespace std;

#define PI 3.141592653589793

enum State{
    S=0,I,R
};

class Agent{
    public:
    double x;
    double y;
    int state;
};

class Place{
    public:
    double x;
    double y;
    int risk;
};


int N = 500;


int main(void){
    ofstream file("output_kadai2.txt");

    if(!file){
            cerr << "Cannot open the file." << endl;
            return 1;
        }
    
    random_device rnd;
    mt19937 mt(rnd());

    uniform_real_distribution<> distance1(0.0, 100.0);

    Agent agents[N];
    for(int i=0; i<N; i++){
        agents[i].x = distance1(mt);
        agents[i].y = distance1(mt);
        agents[i].state = S;
    }

    Agent next_agents[N];
    for(int i=0; i<N; i++){
        next_agents[i] = agents[i];
    }

    Place next_place[6];

    uniform_int_distribution<> agnt(0, N-1);

    for(int i=0; i<5; i++){
        int c = agnt(mt);
        if(agents[c].state == I){
            i--;
        }else{
            agents[c].state = I;
        }
    }

    int time = 0;
    int S_count_time = 0;
    int I_count_time = 0;
    int R_count_time = 0;
    
    double doublePI = 2 * PI;
    uniform_real_distribution<> rad(0.0 ,doublePI);
    uniform_real_distribution<> prb(0.0, 1.0);


    while(true){
        time++;

        S_count_time = 0;
        I_count_time = 0;
        R_count_time = 0;
    
        file << "Time: " << time << endl;

        for(int i=0; i<N; i++){
           if(agents[i].state == S){
                S_count_time++;
            }else if(agents[i].state == I){
                I_count_time++;
            }else if(agents[i].state == R){
                R_count_time++;
            }
        }
        file << "S:" << S_count_time << " I:" << I_count_time << " R:" << R_count_time << endl;

        if(I_count_time == 0){
            break;
        }

        if(I_count_time >= N*0.1){
            //エージェントの移動
            for(int i=0; i<N; i++){
                double theta = rad(mt);
                //感染者は行動制限あり。0.1の速さで移動。
                if(agents[i].state == I){
                    next_agents[i].x = agents[i].x + 0.1*cos(theta);
                    next_agents[i].y = agents[i].y + 0.1*sin(theta);
                }
                //未感染者はできるだけ感染者を避けて移動する。
                if(agents[i].state == S){
                    for(int  a=0; a<5; a++){
                        double theta_random = rad(mt);
                        next_place[a].x = agents[i].x + 1.0*cos(theta_random);
                        next_place[a].y = agents[i].y + 1.0*sin(theta_random);
                        next_place[a].risk = 0;
                        if(next_place[a].x < 0.0){
                            next_place[a].x += 100.0;
                        }else if(next_place[a].x >= 100.0){
                            next_place[a].x -= 100.0;
                        }
                        if(next_place[a].y < 0.0){
                            next_place[a].y += 100.0;
                        }else if(next_place[a].y >= 100.0){
                            next_place[a].y -= 100.0;
                        }
                        for(int j=0; j<N; j++){
                            double distance = sqrt(pow(next_place[a].x - agents[j].x, 2) + pow(next_place[a].y - agents[j].y, 2));
                        if(i != j && distance <= 6.0 && agents[j].state == I){
                            next_place[a].risk++;
                        }
                    }
                    if(a==0){
                        next_place[5] = next_place[a];
                    }else if(next_place[a].risk <= next_place[5].risk){
                        next_place[5] = next_place[a];
                    }
                    next_agents[i].x = next_place[5].x;
                    next_agents[i].y = next_place[5].y;
                }

                //Rはランダム移動。
                if(agents[i].state == R){
                    next_agents[i].x = agents[i].x + 1.0*cos(theta);
                    next_agents[i].y = agents[i].y + 1.0*sin(theta);;
                }
                //座標調整
                if(next_agents[i].x < 0.0){
                    next_agents[i].x += 100.0;
                }else if(next_agents[i].x >= 100.0){
                next_agents[i].x -= 100.0;
                }
                if(next_agents[i].y < 0.0){
                    next_agents[i].y += 100.0;
                }else if(next_agents[i].y >= 100.0){
                   next_agents[i].y -= 100.0;
                }
                agents[i] = next_agents[i];
            }
        }else{
            for(int i=0; i<N; i++){
                double theta = rad(mt);
                agents[i].x += 1.0*cos(theta);
                agents[i].y += 1.0*sin(theta);
                if(agents[i].x < 0.0){
                    agents[i].x += 100.0;
                }else if(agents[i].x >= 100.0){
                    agents[i].x -= 100.0;
                }
                if(agents[i].y < 0.0){
                    agents[i].y += 100.0;
                }else if(agents[i].y >= 100.0){
                   agents[i].y -= 100.0;
               }
               next_agents[i] = agents[i];
            }
        }

        

        //感染の状態遷移
        for(int i=0; i<N; i++){
            int I_count = 0;
            if(agents[i].state == S){
                for(int j=0; j<N; j++){
                    double distance = sqrt(pow(agents[i].x - agents[j].x, 2) + pow(agents[i].y - agents[j].y, 2));
                    if(i != j && distance <= 6.0 && agents[j].state == I){
                        I_count++;
                    }
                }
                double probability = 1 - pow(0.7, I_count);
                double occur_SI = prb(mt);
                if(occur_SI<=probability){
                    next_agents[i].state = I;
                }else{
                    next_agents[i].state = S;
                }
            }
            if(agents[i].state == I){
                double occur_IR = prb(mt);
                if(occur_IR <= 0.05){
                    next_agents[i].state = R;
                }else{
                    next_agents[i].state = I;
                }
            }
            if(agents[i].state == R){
                next_agents[i].state = R;
            }
        }
        
        for(int i=0; i<N; i++){
            agents[i] = next_agents[i];
        }
    }
    file.close();
    return 0;
}