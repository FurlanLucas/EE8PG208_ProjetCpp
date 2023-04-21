#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>


class base{
public:
    int a;
    int b;
    virtual void display(void);
};

void base::display(void){
    std::cout << "Base function" << std::endl;
}

class derived1 : public base{
public:
    void display(void);
};

void derived1::display(void){
    std::cout << "Derived one function" << std::endl;
}

class derived2 : public base{
public:
    void display(void);
};

void derived2::display(void){
    std::cout << "Derived two function" << std::endl;
}



template <typename T, typename C, size_t const Size> 
class dummy_array_iterator_type 
{ 
public: 
    dummy_array_iterator_type(C& collection,  
                            size_t const index) : 
    index(index), collection(collection) 
    { } 

bool operator!= (dummy_array_iterator_type const & other) const 
{ 
    return index != other.index; 
} 

T const & operator* () const 
{ 
    return collection.GetAt(index); 
} 

dummy_array_iterator_type const & operator++ () 
{ 
    ++index; 
    return *this; 
} 

private: 
    size_t   index; 
    C&       collection; 
};

int main(){
  std::vector<base> myBaseVector(0);
    for (auto & element : myBaseVector) 
        element.display();
}
