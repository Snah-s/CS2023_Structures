#include <iostream>
using namespace std;

template<typename T>
class Set{
private:
    struct Node{
        T key;
        Node* left;
        Node* right;
    };
    Node* root;

    static Node* newNode(T data){
        Node* node = new Node();
        node->key = data;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    void inorder(Node* root, Set<T>& result) const{
        if (root != nullptr){
            inorder(root->left, result);
            result.insert(root->key);
            inorder(root->right, result);
        }
    }


public:
    Set(){
        root = nullptr;
    }
    ~Set(){
        clear(root);
    }
    void insert(T data){
        root = insert(root, data);
    }
    bool find(T data){
        return find(root, data);
    }
    void display(){
        display(root);
        cout<<endl;
    }
    Set Union(const Set& other){
        Set result;
        inorder(root, result);
        inorder(other.root, result);
        return result;
    }

private:
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    Node* insert(Node *node, T data){
        if (node == nullptr){
            return newNode(data);
        }
        if (data < node ->key){
            node->left = insert(node->left, data);
        } else if (data > node->key){
            node->right = insert(node->right, data);
        }
        return node;
    }
    bool find(Node* node, T data){
        if(node == nullptr) return false;
        else if (data < node-> key) return find(node->left, data);
        else if (data > node-> key) return find(node->right, data);
        else return true;    
    }
    void display(Node* node){
        if (node){
            display(node->left);
            cout<<node->key<<", ";
            display(node->right);
        }
    }
};

int main(){
    Set<int> myset;
    myset.insert(10); myset.insert(5); myset.insert(8); myset.insert(10);
    myset.insert(2); myset.insert(5); myset.insert(15); myset.insert(3);
    myset.display();//2,3,5,8,10,15,
    cout<<myset.find(8)<<endl;//1
    cout<<myset.find(18)<<endl;//0
    Set<int> myset2;
    myset2.insert(9); myset2.insert(5); myset2.insert(15); myset2.insert(30);
    Set<int> myset3 = myset.Union(myset2);
    myset3.display();//2,3,5,8,9,10,15,30
    return 0;
}
