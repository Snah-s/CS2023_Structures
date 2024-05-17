#include <iostream>
#include <vector>
#include <limits>

using namespace std;
//std::numeric_limits<int>::max();

struct Edge
{
    char init;
    char end;
    float weight;    
};

vector<vector<int>> FloydWarshall(vector<char> vertices,vector<Edge> aristas)
{
    int V = vertices.size();
    vector<vector<float>> dists(V, vector<float>(V, numeric_limits<float>::max()));
    vector<vector<int>> tour(V, vector<int>(V, -1));    
    numeric_limits<float>::max();
    
    for (int i = 0; i < V; ++i){
        dists[i][i] = 0;
    }

    for (const Edge& edge : aristas){
        int u = edge.init - '1';
        int v = edge.end - '1';
        dists[u][v] = edge.weight;
        tour[u][v] = v;
    }

    for (int k = 0; k < V; ++k){
        for (int i = 0; i < V; ++i){
            for (int j = 0; j < V; ++j){
                if (dists[i][k] != numeric_limits<float>::max() && dists[k][j] != numeric_limits<float>::max() && dists[i][j] > dists[i][k] + dists[k][j]){
                    dists[i][j] = dists[i][k] + dists[k][j];
                    tour[i][j] = tour[i][k];
                }
            }
        }
    }

    return tour;
}   

void displayPath(vector<vector<int>> tour, char init, char end){
    int u = init - '1';
    int v = end - '1';

    if (tour[u][v] == -1){
        cout<<"Path doesn't exist"<<endl;
        return;
    }

    cout << init;
    while(u != v){
        u = tour[u][v];
        cout<<"->"<<static_cast<char>('1' + u);
    }
    cout<<endl;
}

void test1(){
    vector<char> vertices = {'1','2','3','4','5'};
    vector<Edge> aristas = 
        {{'1', '3', 6},
        {'1', '4', 3},
        {'2', '1', 3},
        {'3', '4', 2},
        {'4', '2', 1},
        {'4', '3', 1},
        {'5', '2', 4},
        {'5', '4', 2}
        };
    vector<vector<int>> tourMatrix = FloydWarshall(vertices, aristas);
    displayPath(tourMatrix, '5','1');//5->4->2->1
    displayPath(tourMatrix, '2','3');//2->1->4->3
    displayPath(tourMatrix, '5','3');//5->4->3
}

void test2(){
    vector<char> vertices = {'1','2','3','4'};
    vector<Edge> aristas = 
        {{'1', '3', -2},
        {'2', '1', 4},
        {'2', '3', 3},
        {'3', '4', 2},
        {'4', '2', -1}
        };
    vector<vector<int>> tourMatrix = FloydWarshall(vertices, aristas);
    displayPath(tourMatrix, '2','3');//2->1->3
    displayPath(tourMatrix, '4','3');//4->2->1->3
    displayPath(tourMatrix, '2','4');//2->1->3->4    
}

int main(){
    test1();
    cout<<endl;
    test2();
}