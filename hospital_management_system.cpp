
#include<iostream>


class patient {                                // patient class 
public :
std::string name;
int patient_id;
std::string condition;

public :
patient(std::string& name , int& p_id , std::string& condition ) {
this->name = name;
this->patient_id = p_id;
this->condition = condition;
}
};
	

template<typename T>
class node {                                  // node class 

public :
T data;
node<T>* next = NULL;

template<typename... U> 
node(U&& ...x):data(std::forward<U>(x)...) {

}


};


std::ostream& operator<<(std::ostream& rittu , patient& data ) {                                                                                    // opearator << overloading 
	rittu << " patient name      : " << data.name << '\n' << " patient id        : " << data.patient_id << "\n patient condition : "<< data.condition << "\n\n";
       return rittu;	
}

bool operator==(const patient& data , const patient& data1 ) {
return (data.name == data1.name) && (data.patient_id == data1.patient_id) && (data.condition == data1.condition); 
} 


template<typename T>                                       // linked list logic 
class list {
node<T>* head = NULL;

	public :

void push_back(const T& data ) {                            // push back functions 
node<T>* n = new node<T>();
n->data = data;

if(this->head == NULL ) {
this->head = n;
return;
}
node<T>* temp = this->head;
while(temp->next != NULL ) {
temp = temp->next;
}
temp->next = n;
return;

}


void display () {                                        // display function 
 
if(this->head == NULL ) {
return;
}

node<T>* temp = this->head;
size_t x = 0;
std::cout << '\n';
while(temp != NULL ) {
std::cout << temp->data;
temp = temp->next;
x++;
}

std::cout << '\n';
}

void insert(int x,const T& data) {

node<T>* n = new node<T>();
n->data = data;

if(this->head == NULL ) {
this->head = n;
std::cout << "\n****** done insertion ******* \n";
return;
}
if(x == 0 ) {
n->next = this->head;
this->head = n;
std::cout << "\n****** done insertion ******* \n";
return;
}
int z = 0;
node<T>* temp = this->head;
node<T>* temp1 = temp;
while(temp != NULL && z != x ) {
temp1 = temp;
temp = temp->next;
z++;
}

if(temp1 != NULL && temp == NULL ) {
temp1->next = n;
std::cout << "\n****** done insertion ******* \n";
return;
}

temp1->next = n;
n->next = temp;
std::cout << "\n****** done insertion ******* \n";

}

node<T>* search(const T& data ) {                                        // searching function 
node<T>* temp = this->head;
node<T>* temp1 = this->head;
while(temp != NULL ) {
temp1 = temp;
temp = temp->next;
if(temp != NULL && temp->data == data ) {
		std::cout << "data found " << std::endl;
	return temp1;
}
} 
std::cout << "\ndata not found " << std::endl;
return NULL;
}

node<T>* search_index(int x ) {
node<T>* temp = this->head;
node<T>* temp1 = this->head;
int z = 0;
while(temp != NULL && z != x ) {
temp1 = temp;
z++;
temp = temp->next;
} 
return temp1;
}

void delete_node(const T& x ) {                               // node deletion 
if(this->head == NULL ) {
return;
}
 
if(x == this->head->data ) {
node<T>* temp = this->head; 
this->head = this->head->next;
delete temp;
return;
}

node<T>* temp1 = this->search(x);

if(temp1 == NULL) {
return; 
}


if(temp1->next == NULL ) {
return;
}else if(temp1->next->next == NULL ){
delete temp1->next;
temp1->next = NULL;
return;
}else{
node<T>* temp = temp1->next;
temp1->next = temp1->next->next;
delete temp;
return;
} 

} 

template<typename... U>
void emplace_back(U&& ...x) {                                                         // emplace function to save memory 

node<T>* n = new node<T>(std::forward<U>(x)...);
n->next = NULL;
//n->data = T(std::forward<U>(x)...);

if(this->head == NULL ) {
this->head = n;
return;
}

node<T>* temp = this->head;

while(temp->next != NULL) {
	temp = temp->next;
//	std::cout << temp->next << std::endl;
}

temp->next = n;

}


};

/*int& list::operator->(node<patient>* n , patient& data ) {
return data.patient_id;
}*/


int main() {                                                                        // main function 
list<patient> l;
int x = 0;
do{
	std::cout << " __________________________________\n|                                  |\n|************* Menu ************** |\n|__________________________________|\n 1. enter patient  \n 2. display patients list  \n 3. delete patient record  \n 4. search patient \n 5. exit \n\n";		
	std::cout << "enter your choice : ";
	std::cin >> x;

switch (x) {
	
	case 1 : {
		   std::cout << "enter number of patients to be added : ";
		  int x = 0;
		  std::cin >> x;
		 int w = 0; 

		  do{
			  std::cout << "\n ********* Record " <<  w + 1 << " ********** \n" << std::endl;
			  std::string name;
			  int id;
			  std::string condition;

			  std::cout << " enter patient name      : ";
			  std::cin >> name;
			  std::cout << " enter patient id        : ";
			  std::cin >> id;
			  std::getchar();
			  std::cout << " enter patient condition : ";
			  std::cin >> condition;
			patient* z = new patient(name , id , condition);
			//std::cout << z->name << z->patient_id << z->condition;
			l.emplace_back(*z);
			w++;
		   x--;
		  }while(x != 0);
		 
		 };
	 	break;	 
	case 2 : {
		  l.display();
		 };
	 	break;	 
	case 3 : {
			  std::string name;
			  int id;
			  std::string condition;

			  std::cout << " enter patient name      : ";
			  std::cin >> name;
			  std::cout << " enter patient id        : ";
			  std::cin >> id;
			  std::getchar();
			  std::cout << " enter patient condirion : ";
			  std::cin >> condition;
		 	//std::cout << "delete node at index : ";
			//int id;
			//std::cin >> id;
				patient p(name , id , condition);
			l.delete_node(p);
		 };
	 	break;	 
	case 4 : {
			  std::string name;
			  int id;
			  std::string condition;

			  std::cout << " enter patient name      : ";
			  std::cin >> name;
			  std::cout << " enter patient id        : ";
			  std::cin >> id;
			  std::getchar();
			  std::cout << " enter patient condirion : ";
			  std::cin >> condition;
		 	//std::cout << "delete node at index : ";
			//int id;
			//std::cin >> id;
				patient p(name , id , condition);
			
			if(l.search(p) != NULL ) {
				std::cout << l.search(p)->next->data << std::endl;
			}
		 };
	 	break;	  
	case 5 : {
		 	std::cout << "\nexittinggggggggggg \n"; 
		 };
	 	break;	 
	default : {
			       std::cout << "\nenter valid choice \n";
		 }
	
}

}while(x != 5);
return 0;
}












/*

********************* out put **************************

 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 1
enter number of patients to be added : 5

 ********* Record 1 ********** 

 enter patient name      : pratham 
 enter patient id        : 2806 
 enter patient condition : good 

 ********* Record 2 ********** 

 enter patient name      : rituja 
 enter patient id        : 040607 
 enter patient condition : good 

 ********* Record 3 ********** 

 enter patient name      : arnav 
 enter patient id        : 989
 enter patient condition : good 

 ********* Record 4 ********** 

 enter patient name      : piyush 
 enter patient id        : 090
 enter patient condition : good 

 ********* Record 5 ********** 

 enter patient name      : pooja 
 enter patient id        : 0989
 enter patient condition : good 
 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 2

 patient name      : pratham
 patient id        : 2806
 patient condition : good

 patient name      : rituja
 patient id        : 40607
 patient condition : good

 patient name      : arnav
 patient id        : 989
 patient condition : good

 patient name      : piyush
 patient id        : 90
 patient condition : good

 patient name      : pooja
 patient id        : 989
 patient condition : good


 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 3
 enter patient name      : piyush 
 enter patient id        : 90
 enter patient condirion : good 
data found 
 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 2

 patient name      : pratham
 patient id        : 2806
 patient condition : good

 patient name      : rituja
 patient id        : 40607
 patient condition : good

 patient name      : arnav
 patient id        : 989
 patient condition : good

 patient name      : pooja
 patient id        : 989
 patient condition : good


 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 4
 enter patient name      : rituja 
 enter patient id        : 040607
 enter patient condirion : good 
data found 
data found 
 patient name      : rituja
 patient id        : 40607
 patient condition : good


 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 4
 enter patient name      : pooja  
 enter patient id        : 989 
 enter patient condirion : good 
data found 
data found 
 patient name      : pooja
 patient id        : 989
 patient condition : good


 __________________________________
|                                  |
|************* Menu ************** |
|__________________________________|
 1. enter patient  
 2. display patients list  
 3. delete patient record  
 4. search patient 
 5. exit 

enter your choice : 5

exittinggggggggggg 













*/
