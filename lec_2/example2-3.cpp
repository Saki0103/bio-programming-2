#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(void){
    ifstream ist("human_protein_interaction.txt");
    if(!ist){
        cerr << "Cannot open human_protein_interaction.txt." << endl;
        exit(1);
    }

    map<string, int> interaction;

    string line;

    while(getline(ist, line)){
        if(line.empty()) continue;

        unsigned int f = line.find(' ');

        string protein1 = line.substr(0,f);
        string protein2 = line.substr(f+1);

        interaction[protein1]++;
        interaction[protein2]++;
    }

    ist.close();

    string max_protein_interaction;
    int max_interaction = 0;
    for(const auto& p : interaction){
        if(p.second > max_interaction){
            max_interaction = p.second;
            max_protein_interaction = p.first;
        }
    }

    cout << "最も多くの相互作用を持つタンパク質: " << max_protein_interaction << endl;
    cout << "相互作用数: " << max_interaction << endl;

    
    return 0;
}