#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
using namespace std;


class small{
public:
    int a;
    int b;
    virtual void display(void);
};

void small::display(void){
    std::cout << "Base function" << std::endl;
}


class big {
public:
    vector<small*> myVec;

    big(int i){
        vector<small*> myVec(i);
        std::cout << myVec.size() << std::endl; 
    }
    void display(void);
};


void big::display(){
    small * test = new small;
    myVec.insert(myVec.begin(), test);
    std::cout << myVec.size() << std::endl; 
}


int main(){
    small* myPtr = new small;
    myPtr->display();
    vector<small*> myVec(2);
    myVec[0] = new small;
    myVec[1] = new small;
    myVec[0]->display();
    std::cout << "test\n";
    
}
