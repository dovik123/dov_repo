#include <iostream>

using namespace std;



class test {

private:



string name ;
int age;


public :

test( string n , int a): name(n) , age(a) {}
int get_age()const{

    return age;
}

};

int main()
{

test tst("dov",7);

std::cout<< " name "<< tst.get_age() <<std::endl;
    return 0;
}