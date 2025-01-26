#include <iostream>
#include "Vector.hpp"

int main()
{
    Vector<int> int_vec;
    Vector<std::string> str_vec;

    //int tmp = int_vec.back();
    int_vec.push_back(1);
    int_vec.emplace_back(2);
    int_vec.print();

    //str_vec.pop_back();
    //std::string s = str_vec.back();
    str_vec.push_back("aaa");
    str_vec.emplace_back("bbb");
    str_vec.print();
    std::cout << str_vec[0] << std::endl;
}