#include <iostream>
using namespace  std;

template <class T>
class CircularArray
{
private:
    T* array;
    int capacity;
    int back, front;
public:

    class iterator {
    private:
        CircularArray* arr;
        int index;
    public:
        iterator() : arr(nullptr), index(-1) {}
        iterator(CircularArray* arr, int index) : arr(arr), index(index) {}
        T& operator*() {
            return (*arr)[index];
        }
        iterator& operator++() {
            index++;
            return *this;
        }
        iterator& operator--() {
            index--;
            return *this;
        }
        bool operator!=(const iterator& other) const {
            return index != other.index || arr != other.arr;
        }
        bool operator==(const iterator& other) const {
            return index == other.index && arr == other.arr;
        }
    };

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, size());
    }


    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void display();
    string to_string(string sep=" ");
    void clear();
    T& operator[](int);
    
private:
    int next(int);
    int prev(int);    
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(10);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->front = this->back = -1;
    this->array = new T[_capacity];
}

template <class T>
CircularArray<T>::~CircularArray()
{ 
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index){    
    return (index==0)? capacity - 1: index -1;
}

template <class T>
int CircularArray<T>::next(int index){
    return (index + 1) % capacity;
}

template <class T>
bool CircularArray<T>::is_empty()
{
    return front == -1;
}

template <class T>
bool CircularArray<T>::is_full()
{
    return front == next(back) && !is_empty();
}

template <class T>
int CircularArray<T>::size()
{
    if(is_empty()) return 0;    
    return (back>=front)? back - front + 1: capacity - front + back + 1;
}

template <class T>
T& CircularArray<T>::operator[](int pos)
{
    if(pos >= capacity) throw "index out of range";
    return array[(front + pos) % capacity];
}

template <class T>
void CircularArray<T>::push_front(T data)
{
    if(is_full()) throw "The array is full";
    if(is_empty()) front = back = 0;
    else front = prev(front);
    array[front] = data;
}

template <class T>
void CircularArray<T>::push_back(T data)
{
    if(is_full()) throw "The array is full";
    if(is_empty()) front = back = 0;
    else back = next(back);
    array[back] = data;
}

template <class T>
T CircularArray<T>::pop_front()
{
    if(is_empty()) throw "The array is empty";
    T temp = array[front];
    if(front == back) front = back = -1;
    else front = next(front);
    return temp;
}

template <class T>
T CircularArray<T>::pop_back()
{
    if(is_empty()) throw "The array is empty";
    T temp = array[back];
    if(front == back) front = back = -1;
    else back = prev(back);
    return temp;
}

template <class T>
void CircularArray<T>::insert(T data, int pos)
{
    int n = size();
    if(pos < 0 || pos > n) throw "index out of range";
    if(n == capacity) throw "The array is full";        
    if(pos == 0)
        push_front(data);
    else {
        for (int i = n - 1; i >= pos; i--)
            (*this)[i+1] = (*this)[i];
        (*this)[pos] = data;
        back = next(back);
    }
}

template <class T>
void CircularArray<T>::display()
{    
    for (int i = 0; i < size(); i++)
        cout<<(*this)[i]<<",";        
    cout<<endl;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = "";
    for(int i=0; i < size(); i++)
        result += std::string((*this)[i])  + sep;
    return result;
}


template <class T>
void CircularArray<T>::clear()
{
    front = back = -1;
}

int main()
{
    CircularArray<int> arr(5); 
    CircularArray<int>::iterator ptr;

    arr.push_front(10);
    arr.push_front(12);
    arr.push_back(2);
    arr.push_back(4);       

    for (ptr = arr.begin(); ptr != arr.end(); ++ptr)
        cout << *ptr << ",";
    cout<<endl;
    //12,10,2,4,

    arr.pop_back();arr.pop_back();arr.pop_back();
    arr.push_back(10);arr.push_back(8);arr.push_back(6);arr.push_back(4);       
    for (ptr = arr.begin(); ptr != arr.end(); ++ptr)
        cout << *ptr << ",";
    cout<<endl;        
    //12,10,8,6,4,

    ptr = arr.begin();
    ptr = ++ptr;    
    ptr = --ptr;
    cout<<*ptr<<endl;//12
            
    return 0; 
}