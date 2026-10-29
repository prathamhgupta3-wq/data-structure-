
#include<iostream> 


class order {

    public: 
    std::string orderName;
    int orderId;

    order() {
    this->orderName = "";
    this->orderId = 0;
    }

    order(const std::string& orderName , const int& orderId) {
        this->orderName = orderName;
        this->orderId = orderId;
    }

  	

};

template<typename T>

class circular_queue {

public :
size_t f = 0;
size_t capacity_d = 1;
size_t size_d = 0;
T* cq = NULL;
public :

circular_queue() {
this->capacity_d = 1;
this->size_d = 0;
this->cq = new T[capacity_d];

}

void resize() {
	size_t old_capacity = capacity_d;

	capacity_d = capacity_d*2;
	T* cq_new = new T[capacity_d];
	for(size_t x = 0; x != size_d; x++ ) {
		*(cq_new + x) = *(cq + (f + x) % old_capacity);
	}
	f = 0;
	delete [] cq;

	cq =  cq_new;    
}


void push_back(T x) {

if(size_d == capacity_d) {
	resize();
}


*(cq + (size_d+f) % capacity_d) = x;
size_d += 1;
}



int orderAt(const int& orderId) {

    // order temp;
    for(int x = 0 ; x < this->size_d ; x++  ) {
        if(this->cq[(x + f)%this->capacity_d].orderId == orderId ) {
            return x + 1;
        }
    }

    return -1;

}

void display() {
    
	for(int x = 0 ; x < this->size_d ; x++  ) {
        std::cout << " "<<  this->cq[(x + f)%capacity_d].orderName << this->cq[(x + f)%this->capacity_d].orderId << " -> " ;
    
	}

}





void push_front(T x) {

	if(capacity_d == size_d ) {
		resize();
	}

f = (f + capacity_d - 1) % capacity_d;

*(cq + f) = x;

size_d++;

}


template<typename... U>
void emplace_back(U&& ...x) {

if(size_d == capacity_d) {
	resize();

}

*(cq + (size_d+f) % capacity_d) = T(std::forward<U>(x)...);
size_d += 1;


}

template<typename... U>
void emplace_front(U&& ...x) {


if(size_d == capacity_d) {
	resize();
}

f = (f + capacity_d - 1) % capacity_d;

*(cq + f) = T(std::forward<U>(x)...);

size_d += 1;
}




inline __attribute__ ((always_inline)) void pop_back() {
if(size_d == 0){
return;
}
*(cq + (f + size_d - 1) % capacity_d ) = T();

size_d--;

}

inline __attribute__ ((always_inline)) void pop_front() {

if(size_d == 0){
return;
}
*(cq + f) = T();
f = ((f + capacity_d + 1) % capacity_d);
size_d--;

}
inline __attribute__ ((always_inline)) T& at(int x) {
	return *(cq + (f + x) % capacity_d);
}

};



int main() {

	circular_queue<order> cq;

    std::cout << " \n********** main menu **********    \n\n 1. add order \n 2. pop order \n 3. order delay \n 4. display all orders \n 5.order at \n 6. exit" << std::endl;
	
    int x = 0;
do{

	std::cout << " enter your choice : ";
	std::cin >> x;

switch(x) {
    
    case 1 : {

                std::cout << " welcome to our cafe \n enter order name : ";
                std::string orderName;
                int orderId;
                std::cin >> orderName;
                std::cout << " enter order id : " ;
                std::cin >> orderId;

                order* o = new order(orderName , orderId);
                cq.emplace_back(*o);

             };
             break;
    
    case 2 : {

                cq.pop_front();

             };
             break;
    case 3 : {

                std::cout << " enter id to be tracked : ";
                int orderId ;
                std::cin >> orderId;
                std::cout << " \nyour order is at : " << cq.orderAt(orderId) << "\n\n" ;
                
             };
             break;
    case 5: {
		    std::cout << "check : ";
			    int x;
			    std::cin >> x; 
			    std::cout << "\n\n" <<  cq.at(x).orderName  << " : " << cq.at(x).orderId << "\n\n" ;
	    }
	    break;
	case 6 : {
		 	std::cout << " \n\n exitinggggggg............ \n\n";
		 }

    case 4 : {

                cq.display();

             };
             break;
    default : {

             };
  
    }
            
}while(x != 6);
	
return 0;

} 



/*

       ************* output ****************
 
********** main menu **********    

 1. add order 
 2. pop order 
 3. order delay 
 4. display all orders 
 5.order at 
 6. exit
 enter your choice : 1
 welcome to our cafe 
 enter order name : avi
 enter order id : 101
 enter your choice : 1
 welcome to our cafe 
 enter order name : kash 
 enter order id : 102
 enter your choice : 4
 avi101 ->  kash102 ->  enter your choice : 2
 enter your choice : 4
 kash102 ->  enter your choice : 5
check : 1


 : 0

 enter your choice : 5
check : 0


kash : 102

 enter your choice : 9
 enter your choice : 6
 

 exitinggggggg............ 
*/
