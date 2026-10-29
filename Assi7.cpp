

#include<iostream>
#include<stack>
#include<string>


class printOrders {

std::string inputStr;

	public : 
printOrders(const std::string& inputStr) {
this->inputStr = inputStr;
}
void prefix() {
std::stack<char> temp;

    for (char ch : this->inputStr) {
        temp.push(ch);
    }

std::stack<char> st;
std::stack<char> st1;

std::cout << " pre fix : ";

while (temp.empty() != 1) {

        char ch = temp.top();
        temp.pop();
if ((ch >= 'A' && ch <= 'Z') ||(ch >= 'a' && ch <= 'z')) {
st.push(ch);
}else if (ch == ')' || ch == '}' || ch == ']') {

st1.push(ch);

}else if (ch == '(' || ch == '{' || ch == '[') {

	while (st1.empty() != 1  && st1.top() != ')' &&st1.top() != '}' &&st1.top() != ']') {
                st.push(st1.top());
                st1.pop();
			}
if (!st1.empty()) {
    st1.pop();
}

}else if (ch == '*' || ch == '+' || ch == '-' || ch == '/') {

while (st1.empty() != 0 && st1.top() != ')' && st1.top() != '}' && st1.top() != ']' &&
                   precendance(st1.top()) > precendance(ch)) {
st.push(st1.top());
 st1.pop();
 }
 st1.push(ch);
 }
}

    while (st1.empty() != 1) {

        st.push(st1.top());
        st1.pop();
    }

    while (st.empty() != 0) {

        std::cout << st.top() << " ";
        st.pop();
    }

    std::cout << std::endl;
}

int precendance(char c) {
	if(c == '/') return 3;
	if(c == '*') return 3;
	if(c == '+' || c == '-') return 2;
	if(c == '(' || c == '[' || c == '{'  ) return 0;
	return -1;
}
void postfix( ) {
	std::string temp = this->inputStr;
	std::stack<char> st;
	std::cout << " post fix : ";
for( char ch : temp) {
if((ch > 64 && ch < 91) || ( ch > 96 && ch < 123 )  ) {
	 std::cout << ch << " ";
}else if(ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '(' || ch == '{' || ch == '[' ) {
	if(ch == '(' || ch == '[' || ch == '{'  ) {

	}else if(st.empty() != 1 && precendance(st.top()) > precendance(ch)) {
		while(st.empty() != 1) {
	if(st.top() == '(' ||st.top() == '{' ||st.top() == '[') std::cout << "";		
		else std::cout << st.top();
			st.pop();
		}
	 // st.push(ch);		
	} 
	st.push(ch);		
}else if( ch == ')' || ch == '}' || ch == ']') {
 while((st.empty() != 1) && (st.top() != '(' || st.top() != '{' || st.top() != '[') ) {
	if(st.top() == '(' ||st.top() == '{' ||st.top() == '[') std::cout << "";		
		else std::cout << st.top() << " ";
	 st.pop(); 
 }
 if(!st.empty()) {
 st.pop();
 }
}

}

while(!st.empty() ) {std::cout << st.top() ; st.pop(); }

std::cout << std::endl;

}

};

int main() {

printOrders* pr = new printOrders("a + b*c - d/e");
pr->postfix();
pr->prefix();

printOrders* pr1 = new printOrders("(a+b)*(c-d)");
pr1->postfix();
pr1->prefix();

printOrders* pr2 = new printOrders("a*(b+c)-d");
pr2->postfix();
pr2->prefix();

printOrders* pr3 = new printOrders("(a+b)/(c-d)");
pr3->postfix();
pr3->prefix();

return 0;
}




/* output

 post fix : a b + c d - * 
 pre fix : + - * a b c d 


*/