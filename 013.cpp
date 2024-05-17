#include <iostream>
#include <vector>
using namespace std;
int CONT = 0;

vector<vector<int>> validSubsets;

void printSubsets() {
    for (auto it = validSubsets.rbegin(); it != validSubsets.rend(); ++it) {
        for (int num : *it) {
            cout << num << " ";
        }
        cout << endl;
    }
    validSubsets.clear();
}

void displayAllSubsets(vector<int>& conjunto, int P, vector<int>& subset, int index, int currentSum) {
    if (index == conjunto.size()) {
        if (currentSum == P) {
            validSubsets.push_back(subset);
            CONT++;
        }
        return;
    }

    subset.push_back(conjunto[index]);
    displayAllSubsets(conjunto, P, subset, index + 1, currentSum + conjunto[index]);

    subset.pop_back();
    displayAllSubsets(conjunto, P, subset, index + 1, currentSum);

    if (index == 0) {
        printSubsets();
    }
}

void displayAllSubsets_pruning(vector<int>& conjunto, int P, vector<int>& subset, int index, int currentSum) {
    if (index == conjunto.size()) {
        if (currentSum == P) {
            validSubsets.push_back(subset);
            CONT++;
        }
        return;
    }

    subset.push_back(conjunto[index]);
    displayAllSubsets_pruning(conjunto, P, subset, index + 1, currentSum + conjunto[index]);

    subset.pop_back();
    displayAllSubsets_pruning(conjunto, P, subset, index + 1, currentSum);

    if (index == 0) {
        printSubsets();
    }
}


int main(){
    vector<int> conjunto = {1,2,3,4,5,6,7,8,9,10};
    int P = 5;
    vector<int> subset;
    CONT = 0;
    displayAllSubsets(conjunto, P, subset, 0, 0);
    cout<<"Sin optimizar:"<<CONT<<endl;
    //{5}
    //{2 3}
    //{1 4}
    CONT = 0;
    displayAllSubsets_pruning(conjunto, P, subset, 0, 0);
    //{5}
    //{2 3}
    //{1 4}
    cout<<"Optimizado:"<<CONT<<endl;
}