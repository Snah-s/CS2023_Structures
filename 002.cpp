#include <bits/stdc++.h>
using namespace std;

int COUNT;
struct Node
{
    int data;
    Node* next;
    Node* prev;
};


void push_front(Node* &head, int data){
    Node* newNode = new Node();
    newNode -> data = data;
    newNode -> next = head;
    newNode -> prev = nullptr;

    if (head != nullptr){head->prev = newNode;}

    head = newNode;
}

void display(Node* head){
    while (head != nullptr){
        cout << head->data<< " -> ";
        head = head->next;
    }
    cout<<endl;
}

void transpose(Node* &head, Node*& node){
    if (node == head || node == nullptr){return;}

    Node* prevNode = node->prev;
    Node* nextNode = node->next;

    if(nextNode){nextNode->prev = nextNode;}
    prevNode->next = nextNode;

    int mid = COUNT/2;
    Node* tmp = head;
    for (int i=1; i<mid && tmp; ++i){
        tmp = tmp->next;
    }
    if (tmp == head){
        node->next = head;
        node->prev = node;
        head = node;
    }else{
        node->prev = tmp -> prev;
        node->next = tmp;
        tmp->prev->next = node;
        tmp->prev = node;
    }
}

bool search(Node*& head, int value)
{
    Node* temp = head;
    while(temp != nullptr){
        COUNT++;
        if (temp->data == value){
            transpose(head, temp);
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int main(){
    Node* head = nullptr;
    for(int i=0; i<10; i++)
        push_front(head, (10-i)*2);
    display(head);//
    bool result = false;
    for(int i=0;i<9;i++)
    {
        COUNT = 0;
        result = search(head, 78);
        cout<<result<<"("<<COUNT<<")"<<endl;
    }
    display(head);//
    // 1 (8)
    // 1 (4)
    // 1 (2)
    // 1 (1)
    // 1 (1)
    return 0;
}