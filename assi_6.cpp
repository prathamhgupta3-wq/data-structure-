
#include<iostream>
#include<string>

class node {																// node class 

public: 
	std::string task;

node() {
	this->task = "";
}

node( const std::string& task ) {
this->task = task;
}

std::ostream& operator<<(const node& n ) {                                                 // operator over loading 
	std::cout << n.task;
       return std::cout;	
}

};

template<typename T>                                                  // using template for making stack generic 
class stack {


	public :
int size_s = 0;
T* arr;
int capacity_s = 1;

stack() {                                                        // stack constructor 
this->size_s = 0;
this->capacity_s = 1;
this->arr = new T[capacity_s];
}


void resize() {                                     					// resize if stack is full 

	std::cout << " stack is full " << std::endl; 
	this->capacity_s = this->capacity_s*2;
	T* new_arr = new T[capacity_s];
	int x = 0;
	while(x != this->size_s) {
	new_arr[x] = this->arr[x];

	x = x + 1;
	}
	delete [] this->arr;
	this->arr = new_arr;

}




void push_front( const T& data ) {            														// pushing elements 
if(this->size_s == this->capacity_s ) {
this->resize();
}
this->arr[size_s] = data;
size_s++;
}

template <typename ...U>                                                               // emplace will help to protect memory wastage of memory 
void emplace_front(U&& ...x) {

if(this->size_s == this->capacity_s) {
this->resize();
}

this->arr[size_s]  = T(std::forward<U>(x)...);
this->size_s = this->size_s + 1;

}


void pop() {                                                                // poooping elemetn from top to perform undo ooperation 
	if(size_s == 0) {
		std::cout << " stack is empty " << std::endl;
		return;
	}

this->arr[size_s - 1] = T();
this->size_s =  this->size_s - 1;
}

inline __attribute__ ((always_inline)) T& top() {
return this->arr[this->size_s - 1];
}

void display() {        												/// displaying srtack elements 
int x = this->size_s - 1;

while(x != -1) {
	std::cout << this->arr[x].task << " "  ;
	x = x - 1;
}

std::cout << std::endl;


}

};

int main() {


	stack<node> s;

	std::cout << " \n 1. enter string  \n 2. undo \n 3. display \n 4.exit \n\n";
int x;
do{

	std::cout << " enter your choice : ";
	std::cin >> x;

	switch(x) {
	
		case 1 : {
				 std::cout << " enter anyline : ";
				 
				 std::string task ;
				 std::getchar();
				 std::getline(std::cin , task , '\n');
			 	node* n = new node(task);
				s.emplace_front(*n);
			 };
			 break;

		case 2: {

				s.pop();
			
			};
			break;
		case 3: {
				s.display();
			};
			break;
		case 4: {
				std::cout <<  " \n\n exitingggggggggg............. \n\n ";
			};
			break;
		default :{
			 	std::cout << " \n\n enter valid option \n\n ";
			 };
			 break;
			
	
	}

	

}while(x != 4);	


}







/*

***************** output *************************

 1. enter string  
 2. undo 
 3. display 
 4.exit 

 enter your choice : 1
 enter anyline : east
 enter your choice : 1
 enter anyline : the
 stack is full 
 enter your choice : 1
 enter anyline : in
 stack is full 
 enter your choice : 1
 enter anyline : rises
 enter your choice : 1
 enter anyline : sun
 stack is full 
 enter your choice : 3
sun rises in the east 
 enter your choice : 2
 enter your choice : 3
rises in the east 
 enter your choice : 2
 enter your choice : 3
in the east 
 enter your choice : 2
 enter your choice : 3
the east 
 enter your choice : 2
 enter your choice : 3
east 
 enter your choice : 2
 enter your choice : 3

 enter your choice : 2
 stack is empty 
 enter your choice : 3

 enter your choice : 4
 

 exitingggggggggg............. 




*/