#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Heap
{
private:
    T *elements;    
    int n;
    
public:
    Heap(){
        elements = nullptr;
        n = 0;
    }

    
    ~Heap(){ 
        delete [] elements;
    }

    void buildFromArray(T *elements, int n){
        this->n = n;
        this->elements = new T[n];
        for(int i = 0; i < n; i++){
            this->elements[i] = elements[i];
            }
        for(int i = n/2 - 1; i >= 0; i--){
            heapify_down(i);
            } 
    }

    void push(T value){
        T* newElements = new T[n+1];
        for(int i = 0; i < n; i++){
            newElements[i] = elements[i];
        }
        newElements[n] = value;
        n++;
        delete [] elements;
        elements = newElements;
        heapify_up(n-1);
    }

    
    T pop(){
    if(n == 0){
        throw ("Heap is empty");
    }
    T root = elements[0];
    elements[0] = elements[n-1];
    n--;
    heapify_down(0);
    return root;
    }

    T top(){
    if(n == 0){
        throw ("Heap is empty");
    }
    return elements[0];
    }

    static void sortAsc(T* arr, int n){
    Heap<T> heap;
    heap.buildFromArray(arr, n);
    for(int i = n - 1; i >= 0; i--){
        arr[i] = heap.top();
        heap.pop();
        }
    }

private:
    int Parent(int i){
        return (i - 1) / 2;
    }

    int Left(int i){
        return (2 * i + 1);
    }

    int Right(int i){
        return (2 * i + 2);
    }

    void heapify_down(int i){
        int left = Left(i);
        int right = Right(i);
        int largest = i;
        if (left < n && elements[left] > elements[largest])
        largest = left;
        if (right < n && elements[right] > elements[largest])
        largest = right;
        if (largest != i)
        {
        swap(elements[i], elements[largest]);
        heapify_down(largest);
        }
    }

    void heapify_up(int i){ 
        while (i != 0 && elements[Parent(i)] < elements[i]){
        swap(elements[i], elements[Parent(i)]);
        i = Parent(i);
        }
    }
};

int main(){
    //test 1
    Heap<int>* heap = new Heap<int>();    
    int array[8] = {23, 10, 49, 50, 13, 12, 9, 45};  
    heap->buildFromArray(array, 8);
    cout<<heap->top()<<endl;//50
    heap->push(8);
    heap->push(55);
    heap->push(18);
    cout<<heap->top()<<endl;//55    
    heap->pop();
    heap->pop();
    cout<<heap->top()<<endl;//49    
    //test 2
    int array2[8] = {23, 10, 49, 50, 13, 12, 9, 45};  
    Heap<int>::sortAsc(array2, 8);
    for(int i=0;i<8;i++)
        cout<<array2[i]<<",";
    cout<<endl;
}