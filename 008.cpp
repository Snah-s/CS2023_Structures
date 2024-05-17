#include <iostream>
#include <vector>
using namespace std;

const int M=5;

template<typename TK>
struct Node {
    TK *keys;
    Node** children;
    int count;//contador de llaves
    bool leaf;

    Node(initializer_list<TK> elements){
        this->leaf = true;
        this->keys = new TK[M-1];
        this->children = new Node<TK>*[M];    
        this->count = 0;
        for(auto elem : elements)  this->keys[this->count++] = elem;        
        for(int i=0;i<M;i++)    this->children[i] = nullptr;        
    }

    void link_child(int index_child, initializer_list<TK> elements){
        this->leaf = false;  
        this->children[index_child] = new Node<TK>(elements);
    }

    string toString(string sep){
        string cad = "";
        for(int i = 0; i<count;i++)
            cout<<keys[i]<<sep;
    }

    bool search(TK key){
        int i = 0;
        while(i < count && key > keys[i]){
            i++;
        }
        if(keys[i]==key){ return true;}
        if (leaf){ return false;}
        return children[i]->search(key);
    }

    vector<int> range_search(TK begin, TK end){
        vector<TK> res;
        int i = 0;
        while(i < count && keys[i] < begin){
            i++;
        }
        while(i < count && keys[i] <= end){
            if (!leaf){
                vector<TK> childRes = children[i]->range_search(begin, end);
                res.insert(res.end(), childRes.begin(), childRes.end());
            }
            res.push_back(keys[i]);
            i++;
        }

        if(!leaf && i < count){
            vector<TK> child_res = children[i]->range_search(begin, end);
            res.insert(res.end(), child_res.begin(), child_res.end());
        }

        return res;
    }
};

void test1(){
    Node<int>* root = new Node<int>({11,16,20,31});
    root->link_child(0, {3,5});
    root->link_child(1, {12,15});
    root->link_child(2, {17,19});
    root->link_child(3, {22,25,27,28});
    root->link_child(4, {32,36,37,38});

    cout<<"25:"<<root->search(25)<<endl; //25:1
    cout<<"16:"<<root->search(16)<<endl; //16:1
    cout<<"35:"<<root->search(35)<<endl; //35:0

    cout<<root->toString(",")<<endl;//3,5,11,12,15,16,17,19,20,22,25,27,28,31,32,36,37,38 
    
    vector<int> result = root->range_search(14, 20);
    for(auto elem : result) cout<<elem<<", "; //15,16,17,19,20
    cout<<endl; 
}

void test2(){
    Node<int>* root = new Node<int>({20});
    root->link_child(0, {11,16});
    root->link_child(1, {31,35});
    root->children[0]->link_child(0, {3,5});
    root->children[0]->link_child(1, {12,15});
    root->children[0]->link_child(2, {17,19});
    root->children[1]->link_child(0, {22,25,27,28});
    root->children[1]->link_child(1, {32,33});
    root->children[1]->link_child(2, {36,38});

    cout<<"25:"<<root->search(25)<<endl; //25:1
    cout<<"16:"<<root->search(16)<<endl; //16:1
    cout<<"37:"<<root->search(37)<<endl; //37:0

    cout<<root->toString(",")<<endl;//3,5,11,12,15,16,17,19,20,22,25,27,28,31,32,33,35,36,38  
    vector<int> result = root->range_search(14, 21);
    for(auto elem : result) cout<<elem<<", "; //15,16,17,19,20
    cout<<endl;     
}

int main()
{
    test1();
    //test2();
    return 0;
}