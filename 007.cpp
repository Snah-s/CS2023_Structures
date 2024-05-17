#include <iostream>
#include <forward_list>
#include <unordered_set>
using namespace std;

#define MAX_COLISION 3

template<typename TK, typename TV>
class DSHash{
private:
    struct Entry{
        TK key;
        TV value;
        Entry(TK _k, TV _v): key(_k), value(_v) {}
    };
    
    forward_list<Entry>* array;
    int capacity;
    int size;

public:
    DSHash(int cap=3){
        this->size = 0;
        this->capacity = cap;
        this->array = new forward_list<Entry>[this->capacity];
    }   

    ~DSHash(){
        delete[] array;
    }
    
    void insert(TK key, TV value){
        if(find(key))
            return;
        size_t index = getHashCode(key) % this->capacity;
        array[index].push_front(Entry(key, value));
        ++this->size;

        if (this->size >= this->capacity * MAX_COLISION)
            rehashing();
    }

    TV* find(TK key){
        size_t index = getHashCode(key) % this->capacity;
        for(auto& e : array[index]){
            if(e.key == key)
                return &e.value;
        }
        return nullptr;
    }

    void Union(TK elem1, TK elem2){
        TV* val1 = find(elem1);
        TV* val2 = find(elem2);

        if (val1 && val2) {
            *val2 = *val1;
        }
    }

    void remove(TK key){
        size_t index = getHashCode(key) % this->capacity;
        array[index].remove_if([&](const Entry& e) { return e.key == key; });
    }

    void display(){
        for(int i=0; i<this->capacity; i++){
            for(auto& e : array[i]){
                cout << e.key << ":'" << e.value << "', ";
            }
        }
        cout << endl;
    }

private:
    size_t getHashCode(TK key){
        hash<TK> fhash;
        return fhash(key);
    }

    void rehashing(){
        int old_capacity = this->capacity;
        this->capacity *= 2;
        forward_list<Entry>* new_array = new forward_list<Entry>[this->capacity];

        for(int i=0; i<old_capacity; i++){
            for(auto& e : array[i]){
                size_t index = getHashCode(e.key) % this->capacity;
                new_array[index].push_front(e);
            }
        }

        delete[] this->array;
        this->array = new_array;
    }
};

int main(){
    DSHash<int, char> myds;
    myds.insert(1, 'A');
    myds.insert(2, 'B');
    myds.insert(3, 'C');
    myds.insert(4, 'D');
    myds.insert(5, 'E');
    myds.insert(6, 'F');
    myds.insert(7, 'A');
    myds.insert(7, 'G');
    //test 1
    myds.Union(1, 2);
    cout<<myds.find(2)<<endl;//A
    myds.Union(3, 6);
    myds.Union(1, 6);    
    cout<<(myds.find(2) == myds.find(6))<<endl;//1
    myds.display();
    //1:'A', 2:'A', 3:'A', 4:'D', 5:'E', 6:'A', 7:'G'
    //test 2
    myds.Union(4, 7);
    myds.remove(2);
    myds.Union(4, 1);
    myds.display(); 
}
