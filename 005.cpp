#include <iostream>
using namespace std;

template <typename T>
struct NodeBT {
    T data;
    int height;
    NodeBT* left; 
    NodeBT* right;        
    NodeBT() : left(nullptr), right(nullptr), height(0) {}   
    NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0) {}   

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};

template <typename T>
class BSTree
{
private:
    NodeBT<T> *root;

    int getHeight(NodeBT<T>* node) {
        if(node) return node->height;
        else return -1;
    }

public:
    BSTree() : root(nullptr) {}

    ~BSTree() {
        if (root)
            root->killSelf();
    }

    void insert(T value)
    {
        insert(this->root, value);
    }

    void displayPreOrder(){
        displayPreOrder(this->root);
    }   
    
    int getHeight(){
        return getHeight(root);
    }

    void displayPretty(){
        displayPretty(root, 1);
    }

private:
    void insert(NodeBT<T> *&node, T value)
    {
        if (node == nullptr){
            node = new NodeBT<T>(value);
            return;
        }
        else if (value < node->data)
            insert(node->left, value);
        else
            insert(node->right, value);
        
        updateHeight(node);
        balance(node);
    }

    void updateHeight(NodeBT<T>* node){
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(NodeBT<T>* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    NodeBT<T>* leftRotate(NodeBT<T>* x) {
        NodeBT<T>* y = x->right;
        NodeBT<T>* z = y->left;
        y->left = x;
        x->right = z;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    NodeBT<T>* rightRotate(NodeBT<T>* y) {
        NodeBT<T>* x = y->left;
        NodeBT<T>* z = x->right;
        x->right = y;
        y->left = z;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    void balance(NodeBT<T>*& node) {
        int balanceFactor = getBalance(node);
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            node = rightRotate(node);
        } else if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            node = leftRotate(node);
        }
    }

    void displayPreOrder(NodeBT<T>* &node){
        if(node == nullptr) return;
        cout << node->data << ",";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
    
    void displayPretty(NodeBT<T> *node, int level)
    {
        if (node == nullptr)
            return;
        displayPretty(node->right, level + 1);
        cout << endl;
        if (node == this->root)
            cout << "Root->:  ";
        else
        {
            for (int i = 0; i < level; i++)
                cout << "      ";
        }
        cout << node->data << "(" << node->height << ")";
        displayPretty(node->left, level + 1);
    }
};

int main(){
    BSTree<int> *avl = new BSTree<int>();

    avl->insert(35);
    avl->insert(30);
    avl->insert(27);
    avl->insert(11);
    avl->insert(16);
    avl->insert(100);
    avl->insert(50);
    avl->insert(91);
    avl->insert(73);
    avl->insert(5);

    avl->displayPreOrder();//30, 16, 11, 5, 27, 50, 35, 91, 73, 100, 
    cout<<endl<<avl->getHeight()<<endl;//3
    avl->displayPretty();
    cout<<endl;
}