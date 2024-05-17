#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* sorted_insert(Node* head, int data) {
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;

    if (head == nullptr || head->data >= node->data) {
        node->next = head;
        head = node;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data < node->data) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    return head;
}

void push_front(Node*& head, int data) {
    Node* node = new Node();
    node->data = data;
    node->next = head;
    head = node;
}

void reverse(Node* &head){
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

Node* union_lists(Node* head1, Node* head2) {

    Node* head3 = nullptr;

    while (head1 != nullptr || head2 != nullptr) {
        if (head1 == nullptr) {
            push_front(head3, head2->data);
            head2 = head2->next;
        } else if (head2 == nullptr) {
            push_front(head3, head1->data);
            head1 = head1->next;
        } else {
            if (head1->data < head2->data) {
                push_front(head3, head1->data);
                head1 = head1->next;
            } else if (head1->data > head2->data) {
                push_front(head3, head2->data);
                head2 = head2->next;
            } else {
                push_front(head3, head1->data);
                head1 = head1->next;
                head2 = head2->next;
            }
        }
    }

    reverse(head3);

    return head3;
}

void display(Node* head) {
    while (head != nullptr) {
        cout << head->data << "->";
        head = head->next;
    }
    cout << endl;
}

void test1(){
    
    Node* head = nullptr;
    sorted_insert(head, 10);//O(n)
    sorted_insert(head, 5);
    sorted_insert(head, 4);
    sorted_insert(head, 8);
    sorted_insert(head, 12);
    display(head);//4->5->8->10->12->
}

void test2()
{
    Node* head1 = nullptr;
    push_front(head1, 10);
    push_front(head1, 8);
    push_front(head1, 6);
    push_front(head1, 2);
    Node* head2 = nullptr;
    push_front(head2, 12);
    push_front(head2, 11);
    push_front(head2, 8);
    push_front(head2, 7);
    push_front(head2, 4);
    push_front(head2, 2);
    Node* head3 = union_lists(head1, head2);//O(n)
    display(head1);//2->6->8->10->
    display(head2);//2->4->7->8->11->12->
    display(head3);//2->4->6->7->8->10->11->12->
}

int main(){
    //1- Inserta ordenado
   test1();
   //2- Union de listas ordenadas
   test2();
}