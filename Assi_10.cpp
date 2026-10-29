#include<iostream>
#include<queue>

template<typename T>

class node {

public :
	T data;
	node<T>* lnode = NULL;
	node<T>* rnode = NULL;
	int height;

public :
	node() {
	
	this->data = T();
	this->lnode = NULL;
	this->rnode = NULL;
	this->height = 1;
	
	}

};

template<typename T>
class avl {
public :
size_t size_a = 0;
//size_t n_count = 0;
long height_a = -1 ;
node<T>* root = NULL;

public :
avl() {
this->size_a = 0;
//this->n_count = 0;
this->height_a = 0;
this->root = NULL;
}

// checkbalance 
long height(node<T>* n ) {
	if(n != NULL ){
		return n->height;
	}
	return -1;
}

int updateheight(node<T>* temp) {
if(temp == NULL ) {
return -1;
}
//std::cout << temp->data << " "<< temp->height << std::endl;

temp->height = 1 + std::max(updateheight(temp->lnode),updateheight(temp->rnode));
//std::cout << temp->data << " "<< temp->height << std::endl;
// std::cout << balance(temp) << std::endl;
return temp->height;
}
int balance(node<T>* temp) {
int height_balance = height(temp->lnode) - height(temp->rnode);
return height_balance;
}


void balance_avl(node<T>* n ) {
updateheight(this->root);
if(n == NULL  ) {
	return;
}

if(n == this->root ) {
return;
}
node<T>* temp = this->root;
node<T>* temp1 = this->root;
node<T>* temp2 = this->root;
node<T>* temp3 = this->root;

while(temp != NULL && temp->data != n->data ) {
	temp3 = temp2;
	temp2 = temp1;
	temp1 = temp;
	if(temp->data < n->data ) {
		temp = temp->rnode;
	}else{
		temp = temp->lnode;
	}
} 
//std::cout << "data " <<   temp->data  << std::endl; 
/*if(temp1 == this->root) {
	if(balance(this->root) > 1 ) {
		this->root = temp1->lnode;
		temp1->lnode->rnode = temp1;
	}else if(balance(this->root) < -1){
		this->root = temp1->rnode;
		temp1->lnode->rnode = temp1;
	}
	return;
}*/
if(temp2 == this->root && temp1 != this->root  ) {
	if(balance(this->root) > 1 ) {
		this->root = temp1;
		temp2->lnode = temp1->rnode;
		temp1->rnode = temp2;
	}else if(balance(this->root) < -1){
		this->root = temp1;
		temp2->rnode = temp1->lnode;
		temp1->lnode = temp2;
	}
	return;

}
//std::cout << balance(temp2) << std::endl;
//std::cout << balance(temp1) << std::endl;
if(temp2 != this->root) {
if(balance(temp2) > 1){
// ll
if(balance(temp1) >= 0) {
if(temp3->lnode == temp2 ) {
	temp3->lnode = temp1;
}else {
	temp3->rnode = temp1;
}
temp2->lnode = temp1->rnode;
temp1->rnode = temp2;

updateheight(this->root);
// lr
}else if(balance(temp1) < 0) {
	temp2->lnode = temp;
	temp1->rnode = temp->lnode;
	temp->lnode = temp1;
	
if(temp2 == temp3->lnode) {
	temp3->lnode = temp;
}else {
	temp3->rnode = temp;
}
	temp2->lnode = temp->rnode;
	temp->rnode = temp2;


updateheight(this->root);
}
}else if(balance(temp2) < -1 ) {
// rr
if(balance(temp1) <= 0) {

if(temp2 == temp3->lnode) {
	temp3->lnode = temp1;
}else {
	temp3->rnode = temp1;
}
temp2->rnode = temp1->lnode;
temp1->lnode = temp2;
updateheight(this->root);
// rl
}else if(balance(temp1) > 0) {
temp2->rnode = temp;
temp1->lnode = temp->rnode;
temp->rnode = temp1;

if(temp2 == temp3->lnode) {
	temp3->lnode = temp;
}else {
	temp3->rnode = temp;
}
temp2->rnode = temp->lnode;
temp->lnode = temp2;

updateheight(this->root);
}	
}
}
balance_avl(temp1);
}
void push(T x) {
node<T>* n = new node<T>();
n->rnode = NULL;
n->lnode = NULL;
n->data = x;
if(this->root == NULL ) {
this->root = n;
std::cout << n->data << std::endl;
updateheight(this->root);
this->size_a++;
return;
}
node<T>* temp = this->root;
node<T>* temp1 = NULL;
while(temp != NULL ) {
temp1 = temp;
if(x < temp->data ) {
temp = temp->lnode;
}else if(x > temp->data ) {
// std::cout << temp->data << std::endl;
// std::cout << temp->rnode << std::endl;
temp = temp->rnode;
// std::cout << temp << std::endl;

}else{
delete n;
return;
}
// std::cout << temp->data << std::endl;
}
 // std::cout << n->data << std::endl;
if(temp1->data < x) {
temp1->rnode = n;
 std::cout << temp1->rnode->data << std::endl;
}else{
temp1->lnode = n;
 std::cout << temp1->lnode->data << std::endl;
}

this->size_a++;
//this->preorder(this->root );
//std::cout << "root " << this->root->data << std::endl; 
updateheight(this->root);
balance_avl(n);

}

void preorder(node<T>* temp) {
if(temp == NULL ) {
	return;
}
std::cout << temp->data /*<< " ( "  << balance(temp) << " ) "*/ << "-> ";
preorder(temp->lnode);
preorder(temp->rnode);
}

void postorder(node<T>* temp) {
if(temp == NULL ) {
return;
}
postorder(temp->lnode);
postorder(temp->rnode);
std::cout << temp->data /*<< " ( "  << balance(temp) << " ) "*/ << "-> ";
}

void inorder(node<T>* temp) {
if(temp == NULL ) {
return;
}
inorder(temp->lnode);
std::cout << temp->data /*<< " ( "  << balance(temp) << " ) "*/ << "-> ";
inorder(temp->rnode);
}

void levelorder(node<T>* temp ) {
	if(temp == NULL ) {
		return;
	}
std::queue<node<T>*> q;
size_t node_a = size_a;
q.push(this->root);
while(temp != NULL && node_a != 0 ) {
std::cout << q.front()->data << "-> ";
if(q.front()->lnode != NULL ) {
	q.push(q.front()->lnode);
}
if(q.front()->rnode != NULL ) {
q.push(q.front()->rnode);
}
q.pop();
node_a--;
}
std::cout << std::endl;
}

// iterators 

class iterator {
public :
node<T>* iptr = NULL;
node<T>* root = NULL;
node<T>* next = NULL;
public :
iterator() {
this->iptr = NULL;
this->root = NULL;
this->next = NULL;
}


bool operator!=(avl<T>::iterator& itr ) {
return this->iptr != itr.iptr;
}

node<T>*  nexty(node<T>* temp ) {
if(temp == NULL ) {
return NULL;
}
nexty(temp->lnode);
if(this->next == NULL ) {
if(temp->data > this->iptr->data ) {
	this->next = temp;
}
}
nexty(temp->rnode);

return this->next;
}

avl<T>::iterator& operator++() {
	// std::cout << this->root->data << std::endl;
	this->next = NULL;
	this->iptr = nexty(this->root);
	this->next = NULL;
	// std::cout << this->next->data << std::endl;
return *this;
}

void operator=(avl<T>::iterator& itr) {
this->iptr = itr.iptr;
this->root = itr.root;
this->next = itr.next;
}

T& operator*() {
return this->iptr->data;
}
};

avl<T>::iterator& begin()  {
	// std::cout << "begin called " << std::endl;
	// std::cout << this->root->data << std::endl;
avl<T>::iterator* itr = new avl<T>::iterator();
itr->iptr = this->min();
itr->root = this->root;
itr->next = NULL;
return *itr;
}

avl<T>::iterator& end() const  {
avl<T>::iterator* itr = new avl<T>::iterator();
itr->root = this->root;
itr->iptr = NULL;
itr->next = NULL;
return *itr;
}

node<T>* min() {
node<T>* temp = this->root;
while(temp->lnode != NULL ) {
temp = temp->lnode;	
}
return temp;
}
node<T>* max() {
node<T>* temp = this->root;
while(temp->rnode != NULL ) {
temp = temp->rnode;	
}
return temp;
}

void erase(T x) {
node<T>* temp = this->root;
node<T>* temp1 = this->root;        

while(temp != NULL && temp->data != x ) {
temp1 = temp;
if(x > temp->data ) {
temp = temp->rnode;
}else{
temp = temp->lnode;
}
}
if(temp == NULL ) {
return;
}
if(temp == this->root ) { 
	if(temp->lnode == NULL && temp->rnode == NULL ) {
		delete temp;
		this->root = NULL;
		size_a--;
		return;
	}else if(temp->lnode != NULL && temp->rnode != NULL ) {
		if(balance(temp) >= 0) {
			node<T>* temp2 = temp->rnode;
			this->root = temp->lnode;
			while(temp2->lnode != NULL ) {
				temp2 = temp2->lnode;
			}
			temp2->lnode = this->root->rnode;
			this->root->rnode = temp->rnode;
			delete temp;
			size_a--;
			updateheight(this->root);
		}else if(balance(temp) < 0) {
			node<T>* temp2 = temp->lnode;
			this->root = temp->rnode;
			while(temp2->rnode != NULL ) {
				temp2 = temp2->rnode;
			}
			temp2->rnode = this->root->lnode;
			this->root->lnode = temp->lnode;
			delete temp;
			size_a--;
			updateheight(this->root);
		}
		balance_all();
		return;
	}else if(temp->lnode == NULL ) {
		this->root = temp->rnode;
		delete temp;
		size_a--;
		updateheight(this->root);
		balance_all();
		return;
	}else if(temp->rnode == NULL ) {
		this->root = temp->lnode;
		delete temp;
		size_a--;
		updateheight(this->root);
		balance_all();
		return;
	}  
}
std::cout << temp1->data << " " << temp->data << std::endl;

if(temp->lnode == NULL && temp->rnode == NULL ) {
	std::cout << "no child " << std::endl; 
	if(temp1->rnode == temp) {
	temp1->rnode = NULL;
	}else{
	temp1->lnode = NULL;
	}
	delete temp;
	size_a--;
	this->updateheight(this->root);
	// std::cout << temp1->data << std::endl;
	// this->balance_avl(this->root);
this->balance_all();
// std::cout << temp1->data << std::endl;
// std::cout << this->root->data << std::endl;

	return;
}

if(temp->lnode != NULL && temp->rnode != NULL  ) {
if(temp1->lnode == temp ) {
temp1->lnode = temp->lnode;
}else{
temp1->rnode = temp->lnode;
} 

node<T>* temp2 = temp->lnode;
while(temp2->rnode != NULL ) {
temp2 = temp2->rnode;
}
std::cout << temp2->data << std::endl;
temp2->rnode = temp->rnode;
//std::cout << temp2->rnode->data << std::endl;
delete temp;
size_a--;
this->updateheight(this->root);
this->balance_all();
return;
}

if(temp->lnode == NULL || temp->rnode == NULL ) {

if(temp1->lnode == temp ) {
	if(temp->lnode != NULL ) { 
	temp1->lnode = temp->lnode;
	}else{
		temp1->lnode = temp->rnode;
	} 
}else if(temp1->rnode == temp ){
if(temp->lnode != NULL ) { 
	temp1->rnode = temp->lnode;
	}else{
		temp1->rnode = temp->rnode;
	}
} 
delete temp;
size_a--;
updateheight(this->root);
balance_all();
return;
}

}



/*void balance_all() {
	std::cout << "balanace all called " << std::endl;
std::queue<node<T>*> q;
std::queue<node<T>*> q1;
size_t size_n  = this->size_a;
q.push(this->root);
	std::cout << "balanace all called " << std::endl;

while(size_n != 0 ) {
	//std::cout << size_n << std::endl;
std::cout << q.front()->data << std::endl;
	q1.push(q.front());
	if(q.front()->lnode != NULL ){
	q.push(q.front()->lnode);
	}
	if(q.front()->lnode != NULL ){
	q.push(q.front()->rnode);
	}
	q.pop();
size_n--;
}
size_t x = this->size_a;
std::cout << "done " << std::endl; 
while(x != 0 ) {
	std::cout << q1.front()->data << std::endl;
	q1.pop();
	x--;
}*/

void balance_all() {
std::queue<node<T>*> q;
std::queue<node<T>*> q1;
// std::cout << "balance all called " << std::endl; 
size_t node_a = size_a;
q.push(this->root);

while(node_a != 0 ) {
	q1.push(q.front());
if(q.front()->lnode != NULL ) {
	q.push(q.front()->lnode);
}
if(q.front()->rnode != NULL ) {
q.push(q.front()->rnode);
}
q.pop();
node_a--;
}
node_a = this->size_a;
while(node_a != 0 ){
    std::cout << node_a << "-> " ;
    std::cout << q1.front()->data << std::endl;
	updateheight(this->root);
	balance_avl(q1.front());
	std::cout << "balanced " << q1.front()->data << std::endl;
	q1.pop();
	node_a--;

}

}
};

int main() {

	// node<int>* node1 = new node<int>();
	// avl<int> a;

	// a.push(13);
	// a.push(14);
	// a.push(15);
	// a.push(12);
	// a.push(11);
	// a.push(17);
	// a.push(16);
	// a.push(8);
	// a.push(9);
	// a.push(1);
	// // a.push(11);
	// a.preorder(a.root);
	// std::cout << std::endl;
	// a.postorder(a.root);
	// std::cout << std::endl;
	// a.inorder(a.root);
	// std::cout << std::endl;
	// a.levelorder(a.root);
	// // std::cout << a.min()->data << std::endl;
	// avl<int>::iterator itr;

	// for(itr = a.begin(); itr != a.end(); ++itr) {
	// 	std::cout << *(itr) << "-> ";
	// }
	// std::cout << std::endl;
	// a.erase(1);
	// a.erase(9);
	// a.erase(15);
	// a.erase(17);
    // a.erase(16);
    // a.erase(16);
    // a.erase(8);
    // a.erase(14);
    // a.erase(11);
    // a.erase(13);
    // a.erase(12);
	// a.levelorder(a.root);	
	
    return 0;

}