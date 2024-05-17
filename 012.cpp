#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <unistd.h>

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   ";

string generarTexto(size_t N){    
    string resultado = "";
    for (size_t i = 0; i < N; i++)
        resultado += alfabeto[rand() %  alfabeto.size()];
    return resultado;
}

vector<int> testInocente(string Texto, string Patron)
{    
    auto start = std::chrono::steady_clock::now();

    vector<int> result;
    int n = Texto.size();
    int m = Patron.size();
    for(int j=0; j<=n-m; j++){
        int i = 0;
        while(i<m && Patron[i] == Texto[i+j]){
            i++;
        }
        if(i == m){
            result.push_back(j);
        }
    }

    auto end = std::chrono::steady_clock::now();
    cout << "Inocente time in milliseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " ms" << endl;
    return result;
}

vector<int> testBoyerMoore(string Texto, string Patron)
{    
    auto start = std::chrono::steady_clock::now();

    //execute the algorithm
    int n = Texto.size();
    int m = Patron.size();
    vector<int> positions(256, -1);
    for(int i=0; i<m; i++){
        positions[Patron[i]] = i;
    }
    vector<int> result;
    int i = 0;
    while(i <= n-m){
        int j = m-1;
        while(j >= 0 && Patron[j] == Texto[i+j]){
            j--;
        }
        if(j < 0){
            result.push_back(i);
            i += m;
        }else{
            i += max(1, j - positions[Texto[i+j]]);
        }
    }

    auto end = std::chrono::steady_clock::now();
    cout << "BoyerMoore time in milliseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " ms" << endl;
    return result;
}

void verificarResultado(vector<int> result1, vector<int> result2)
{
    if(result1.size() != result2.size())
        cerr <<"Error!! el resultado no es el mismo\n";
    for(int i=0;i<result1.size();i++)
        if(result1[i] != result2[i])
            cerr <<"Error!! el resultado no es el mismo\n";
}

int main()
{    
    srand(time(NULL));    
    size_t N = 1000000;//100,1000,10000,100000,1000000
    int m = 10;
    string Texto = "AABACAABABACAA";
    string Patron = "AABA";    
    
    vector<int> result1 = testInocente(Texto, Patron); //0,9,12
    vector<int> result2 = testBoyerMoore(Texto, Patron); //0,9,12
    verificarResultado(result1, result2);

    return 0;
}