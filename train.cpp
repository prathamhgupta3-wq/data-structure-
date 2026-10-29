


#include<iostream> 

class station {

public :
std::string sta_Name;
std::string sta_Id;
station* next;
station* pre;

};


class station_Record {

public :
size_t sta_count = 0;
station* head = NULL;
station* tail = NULL;

station_Record() {
this->sta_count = 0;	
this->head = NULL;
this->tail = NULL;
}

void push_back(const std::string& sta_Name , const std::string& sta_Id) {
station* s = new station();
s->sta_Name = sta_Name;
s->sta_Id = sta_Id;

if(this->head == NULL ) {

s->next = NULL;
s->pre = NULL;
this->head = s;
this->tail = s;
return;

}

this->tail->next = s;
s->pre = this->tail;
this->tail = s;

return;

}

void display() {

station* temp = this->head;

while(temp != NULL ) { 
std::cout << " " << temp->sta_Name << "( " << temp->sta_Id << " ) -> ";
temp = temp->next;
}

std::cout << std::endl;

}

void reverse_display() {

station* temp = this->tail;

while(temp != NULL ) { 
std::cout << " " << temp->sta_Name << "( " << temp->sta_Id << " ) -> ";
temp = temp->pre;
}

std::cout << std::endl;

}

station* search(std::string id ) {

station* temp = this->head;
while(temp != NULL ) {
if(temp->sta_Id == id ) {
	std::cout << " data found " << std::endl;
return temp;
}
temp = temp->next;
}
	std::cout << " data not found " << std::endl;
return NULL;

}

void insert(const std::string& sta_Id_o , const std::string sta_Name , const std::string sta_Id )  {

	
station* sta = search(sta_Id_o );

if(this->head == NULL || sta == NULL ) {
	// std::cout << " " << 1   << std::endl;
this->push_back(sta_Name , sta_Id ); 
return;
}

station* s = new station();

s->sta_Name = sta_Name;
s->sta_Id = sta_Id;

s->next = sta->next;
if(sta->next != NULL ) {
sta->next->pre = s;
}
sta->next = s;
s->pre = sta;
return;

//std::string sta = search(sta_Id);

}

void delete_station (const std::string& sta_Id ) {

station* sta = this->search(sta_Id ); 
// std::cout << sta->sta_Name << std::endl;

if(sta == NULL ) {
	return;
}

if(sta == this->head  ) {
sta->next->pre = NULL;
this->head = sta->next;
delete sta;
return;
}
if(sta == this->tail ) {
sta->pre->next = NULL;
this->tail = sta->pre;
delete sta;
return;
}

sta->pre->next = sta->next;
sta->next->pre = sta->pre;
delete sta;
}

};




int main() {

station_Record* r = new station_Record();
int x = 0;


do {

std::cout << "\n ________________________________________\n|                         	         |\n|  ***********     MENU     **********   |\n|________________________________________|\n\n 1. enter station \n 2. display \n 3. display reverse \n 4. delete station \n 5. search station \n 6. insert station \n 7. exit \n\n enter your choice : " ;
std::cin >> x;

switch(x ) {

case 1 : {
		 long x;
		 std::cout << " enter numbrer of statioins to be added : ";
		 std::cin >> x; 
		 while(x != 0 ) {
		 std::string sta_Name;
		 std::string sta_Id;

		 std::cout << " enter station name : ";
		 std::cin >> sta_Name;
		 std::cout << " enter station id   : ";
		 std::cin >> sta_Id;

		 r->push_back( sta_Name , sta_Id );
		 x--;
		 }
	 };
	 break;
case 2 : {
		 r->display();	 
	 };
	 break;
case 3 : {
		 r->reverse_display();	 
	};
	 	break;
case 4 : {
		 std::string sta_Id;
		 std::cout << " delete station with id : " ;
		 std::cin >> sta_Id;
		 r->delete_station(sta_Id);
	 	
	 };
	 break;
case 5 : {
		 std::string sta_Id;
		 std::cout << " enter station id : ";
		 std::cin >> sta_Id;

		 station* sta = r->search(sta_Id );

		 if(sta != NULL ) {
		 std::cout << " " << sta->sta_Name << "( " << sta->sta_Id << " ) -> ";
		 }


	 };
	 break;
case 6 : {
		 std::string sta_Name;
		 std::string sta_Id;
		 std::string sta_Id_o;

		 std::cout << " enter station name : ";
		 std::cin >> sta_Name;
		 std::cout << " enter station id   : ";
		 std::cin >> sta_Id;
		 std::cout << " enter pre station id   : ";
		 std::cin >> sta_Id_o;

		 r->insert( sta_Id_o , sta_Name , sta_Id );
	 
	 };
	 break;assignment
Assignment 4a Polymorphism: method overloading  
Dr. Jaya Dewan
•
Aug 24
100 points
|
Due 11:59 PM
case 7 : {
		 std::cout << " exittingggggggggggggggg................. \n\n" << std::endl;
	 
	 };
	 break;
default : {
	 	std::cout << " invalid selection \n\n" << std::endl;
	 };
	 break;


} 



}while(x != 7 );


}




/*
*************** output ******************
pratham@pratham-Swift-SFG14-71:~/all/ds_lab$ ./a.out  

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 1
 enter numbrer of statioins to be added : 5
 enter station name : morewadi
 enter station id   : 2806 
 enter station name : nashik_phata
 enter station id   : 9890
 enter station name : district_court 
 enter station id   : 9094
 enter station name : Bopodi
 enter station id   : 7678
 enter station name : sant_tukaram_nagar 
 enter station id   : 545678

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 2
 morewadi( 2806 ) ->  nashik_phata( 9890 ) ->  district_court( 9094 ) ->  Bopodi( 7678 ) ->  sant_tukaram_nagar( 545678 ) -> 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 3
 sant_tukaram_nagar( 545678 ) ->  Bopodi( 7678 ) ->  district_court( 9094 ) ->  nashik_phata( 9890 ) ->  morewadi( 2806 ) -> 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 4
 delete station with id : 7678
 data found 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 2
 morewadi( 2806 ) ->  nashik_phata( 9890 ) ->  district_court( 9094 ) ->  sant_tukaram_nagar( 545678 ) -> 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 5
 enter station id : 2806
 data found 
 morewadi( 2806 ) -> 
 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 5       
 enter station id : 0987
 data not found 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 6
 enter station name : chikhli
 enter station id   : 122806
 enter pre station id   : 2806
 data found 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 2
 morewadi( 2806 ) ->  chikhli( 122806 ) ->  nashik_phata( 9890 ) ->  district_court( 9094 ) ->  sant_tukaram_nagar( 545678 ) -> 

 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 8
 invalid selection 



 ________________________________________
|                         	         |
|  ***********     MENU     **********   |
|________________________________________|

 1. enter station 
 2. display 
 3. display reverse 
 4. delete station 
 5. search station 
 6. insert station 
 7. exit 

 enter your choice : 7
 exittingggggggggggggggg................. 


pratham@pratham-Swift-SFG14-71:~/all/ds_lab$ 

*/
