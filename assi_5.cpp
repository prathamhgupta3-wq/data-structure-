


#include<iostream>

template<typename t>

class node {
T task;
node( T task ) {
this->task = task;
}
};

template<typename T>
class Todo {

    node<T>* head = NULL;
    node<T>* tail = NULL;

Todo() {
this->head = NULL;
this->tail = NULL;
}

void push_task( T task ) {

    node<T>* n = new node<T>( task );

if( this->head == NULL ) {
    this->head = n;
    this->tail = n;
    return;
}

}

};

int main() {



}
