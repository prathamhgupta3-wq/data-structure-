

#include<iostream> 


/*class student {

public :
int students = 4;
int subjects = 4;
int** marks;

student() {
this->students = 4;
this->subjects = 4;
this->marks = new int*[4];
}

};

*/

class sparse{

int* spa = NULL;
int** span = NULL;
int rows = 0;
int columns = 0;
sparse(long rows , long columns ) {
this->rows = rows;
this->columns = columns;
this->spa = new int[rows*columns]; 
this->span[rows*columns][3];
}

};


int main() {

sparse s = new sparse(10,5);
int* arr[3] = {{1,0,0,0,0} , {0,2,0,0,0}{}{}{}{}{}{}{}{}{}{}}



}
