#include <iostream>
#include <vector>
using namespace std;

const unsigned ALPHA_SIZE = 26; // tamanio del alfabeto de letras minusculas

class TrieSimple
{
private:
    struct TrieNode
    {        
        TrieNode **children;
        bool endWord; // indica si es final de una palabra
        int count = 0;

        TrieNode()
        {
            endWord = false;
            count = 0;
            children = new TrieNode*[ALPHA_SIZE];
            for (int i = 0; i < ALPHA_SIZE; i++)
                children[i] = nullptr;
        }

        ~TrieNode()
        {
            for (int i = 0; i < ALPHA_SIZE; i++) {
                if (children[i] != nullptr) {
                    delete children[i];
                }
            }
            delete[] children;
        }
    };

    TrieNode *root;

public:
    TrieSimple() : root(nullptr) {  }

    void insert(string key)
    {
       if (root == nullptr) {root = new TrieNode();}
        TrieNode* temp = root;
        for (int i = 0; i < key.size(); i++){
            int index = key[i] - 'a';
            if (temp->children[index] == nullptr) {temp->children[index] = new TrieNode();}
            temp = temp->children[index];
        }
        temp->endWord = true;
    }

    bool search(string key)
    {
        if (root == nullptr) {return false;}
        TrieNode* temp = root;
        for (int i = 0; i < key.size(); i++){
            int index = key[i] - 'a';
            if (temp->children[index] == nullptr) {return false;}
            temp = temp->children[index];
        }
        return temp->endWord;
    }

    void remove(string key) {
        remove(root, key, 0);
    }

    // imprimir ordenado linea por linea
    string toString(string sep)
    {
        return toString(root, sep, "");
    }

    

private:
    string toString(TrieNode *node, string sep, string prefix)
    {
        string result = "";
        if (node->endWord) {
            result += prefix + sep;
        }
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char c = 'a' + i;
                result += toString(node->children[i], sep, prefix + c);
            }
        }
        return result;
    }

    TrieNode* remove(TrieNode* node, const string &key, int depth) {
        if (!node) {return nullptr;}

        if (depth == key.size()) {
            node->endWord = false;
            if (isLeaf(node)) {
                delete node;
                return nullptr;
            }
        } else {
            int index = key[depth] - 'a';
            node->children[index] = remove(node->children[index], key, depth + 1);
            if (isLeaf(node) && !node->endWord) {
                delete node;
                return nullptr;
            }
        }
        return node;
    }

    bool isLeaf(TrieNode* node) {
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (node->children[i]) return false;
        }
        return true;
    }
};


void testTrie(TrieSimple* trie, vector<string> diccionario){
    for(string word : diccionario)
        trie->insert(word);
    cout<<trie->toString(" ")<<endl;
    trie->insert("romanos");
    cout<<trie->search("amor")<<endl;
    cout<<trie->search("rosa")<<endl;
    trie->remove("romano");
    trie->remove("amor");
    cout<<trie->toString(",")<<endl;
}

int main(){
    vector<string> diccionario = {"romano", "roma", "romario", "rosario", "rata", "amor", "amorfo", "amorcito", "amiga"};
    
    testTrie(new TrieSimple(), diccionario);
    
    return 0;
}