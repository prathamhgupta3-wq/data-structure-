

#include<iostream> 


template<typename T>

class deque {

public :
size_t f = 0;
size_t capacity_d = 1;
size_t size_d = 0;
T* dq = NULL;

public :

deque() {
this->capacity_d = 1;
this->size_d = 0;
this->dq = new T[capacity_d];

}

void resize() {
	size_t old_capacity = capacity_d;

	capacity_d = capacity_d*2;
	T* dq_new = new T[capacity_d];
	for(size_t x = 0; x != size_d; x++ ) {
		*(dq_new + x) = *(dq + (f + x) % old_capacity);
	}
	f = 0;
	delete [] dq;

	dq =  dq_new;    
}


void push_back(T x) {

if(size_d == capacity_d) {
	resize();
}


*(dq + (size_d+f) % capacity_d) = x;
size_d += 1;
}



/*void push_front(T x) {

if(f == 0) {                                                                    instead of doin all this use circular indexing 

T* dq_new = new T[capacity_d];
*(dq_new + f) = x;

for(int x = 0; x != size_d; x++ ) {
*(dq_new + f + x + 1) = *(dq + f + x);
}
delete dq;
dq = dq_new;    
}else{
*(dq + f -1) = x;

}
size_d += 1;
}*/

void push_front(T x) {

	if(capacity_d == size_d ) {
		resize();
	}

f = (f + capacity_d - 1) % capacity_d;

*(dq + f) = x;

size_d++;

}

/*template<typename U>                                               // not perfect one 
void emplace_back(U& x) {

if(size_d == capacity_d) {
	resize;

}

*(dq + size_d) = x;
size_d += 1;


}

template<typename U>
void emplace_front(U& x) {


if(size_d == capacity_d) {
	resize();
}

f = (f + capacity_d - 1) % capacity_d;

*(dq + f) = x;

si`aze_d += 1;
}*/

template<typename... U>
void emplace_back(U&& ...x) {

if(size_d == capacity_d) {
	resize();

}

*(dq + (size_d+f) % capacity_d) = T(std::forward<U>(x)...);
size_d += 1;


}

template<typename... U>
void emplace_front(U&& ...x) {


if(size_d == capacity_d) {
	resize();
}

f = (f + capacity_d - 1) % capacity_d;

*(dq + f) = T(std::forward<U>(x)...);

size_d += 1;
}




inline __attribute__ ((always_inline)) void pop_back() {
if(size_d == 0){
return;
}
*(dq + (f + size_d - 1) % capacity_d ) = T();

size_d--;

}

inline __attribute__ ((always_inline)) void pop_front() {

if(size_d == 0){
return;
}
*(dq + f) = T();
f = ((f + capacity_d + 1) % capacity_d);
size_d--;

}
inline __attribute__ ((always_inline)) T& at(int x) {
	return *(dq + (f + x) % capacity_d);
}

};

class demo {

};

int main() {

	deque<int> dq;


	return 0;
} 