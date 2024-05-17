#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    char init;
    char end;
    int weight;
    Edge(char i, char e, int w = 0){ init = i; end = e; weight = w;}
};

template <typename T>
class DisjoinSetArray{
    vector<char> parent;
    vector<int> rank;
public:
    DisjoinSetArray(vector<char> vertices){
        parent.resize(vertices.size());
        rank.resize(vertices.size());
        for (int i = 0; i < vertices.size(); i++){
            parent[i] = vertices[i];
            rank[i]=0;
        }
    }

    T find(T vertex){
        if (vertex == parent[vertex - 'A'])
            return vertex;
        return find(parent[vertex - 'A']);
    }

    void union_sets(char a, char b){
        char parentA = find(a);
        char parentB = find(b);
        if (rank[parentA - 'A'] > rank[parentB - 'A']) parent[parentB - 'A'] = parentA;
        else if(rank[parentA - 'A'] < rank[parentB - 'A']) parent[parentA - 'A'] = parentB;
        else{
            parent[parentB - 'A'] = parentA;
            rank[parentA - 'A']++;
        }
    }
};

bool compAristas(const Edge& a, const Edge& b){
    return a.weight < b.weight;
}


vector<Edge> kruskal(vector<char> vertices, vector<Edge> aristas){
    //usar el DisjointSets
    vector<Edge> solucion;
    DisjoinSetArray<char> ds(vertices);
    //1- ordenar las aristas en funcion del peso
    sort(aristas.begin(), aristas.end(), compAristas);
    //2- Recorrer todas las aristas y agregar al árbol solucion
    for (const Edge& ar : aristas){
        char initParent = ds.find(ar.init);
        char endParent = ds.find(ar.end);

        if (initParent != endParent){
            solucion.push_back(ar);
            ds.union_sets(ar.init, ar.end);
        }
    }
    return solucion;
}

void mostrar_ordenado(vector<Edge> result){
    for (Edge e : result){
        cout<<"'"<< e.init<< "','"<<e.end<<"', '"<<e.weight<<endl;
    }
}

int main(){
    vector<char> vertices = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    vector<Edge> aristas = {{'A','B',  1}, 
                            {'A', 'C', 3},
                            {'A', 'D', 5},
                            {'B', 'D', 6},
                            {'C', 'D', 4},
                            {'C', 'E', 7},
                            {'D', 'F', 2},
                            {'E', 'F', 9},
                            {'E', 'G', 4},
                            {'F', 'H', 3},
                            {'G', 'H', 8}};

    vector<Edge> result = kruskal(vertices, aristas);
    mostrar_ordenado(result);
    //'A','B', 1
    //'D','F', 2
    //'A','C', 3
    //'F','H', 3
    //'C','D', 4
    //'E','G', 4
    //'C','E', 7            
}