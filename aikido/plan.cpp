#include <iostream>
#include <cmath>
using namespace std;

int main(void){
    int num_graduates;
    int num_alcohol;
    int num_non_alcohol = 21;
    int num_order;
    cout << "卒業生人数：" << endl;
    cin >> num_graduates;
    num_alcohol = num_graduates+6;
    cout << "料理注文人数：" << endl;
    cin >> num_order;
    cout << "アルコール人数：" << num_alcohol << endl; //現役6名＋卒業生全員
    cout << "ソフドリ人数：" << num_non_alcohol << endl; //現役20名＋師範
    cout << endl;
    cout << "[料金]" << endl;
    cout << "総額：" << num_order*3500+num_alcohol*2000+num_non_alcohol*1200 << "円" << endl << endl;
    cout << "卒業生支払い6500円の場合：" << endl;
    cout << "卒業生集金総額：" << num_graduates*6500 << "円" << endl;
    cout << "現役集金総額：" << (num_order*3500+num_alcohol*2000+num_non_alcohol*1200 - num_graduates*6500) << "円" << endl;
    double money;
    money = (num_order*3500+num_alcohol*2000+num_non_alcohol*1200 - num_graduates*6500) / 16.0;
    cout << "現役一人当たり(平均)：" << money << "円" << endl;
    cout << "卒業生支払い7000円の場合：" << endl;
    cout << "卒業生集金総額：" << num_graduates*7000 << "円" << endl;
    cout << "現役集金総額：" << (num_order*3500+num_alcohol*2000+num_non_alcohol*1200 - num_graduates*7000) << "円" << endl;
    money = (num_order*3500+num_alcohol*2000+num_non_alcohol*1200 - num_graduates*7000) / 16.0;
    cout << "現役一人当たり(平均)：" << money << "円" << endl;
    return 0;
}   