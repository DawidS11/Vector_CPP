#include <iostream>
#include <cassert>

#include "Vector.hpp"

int main()
{
    Vector<int> v0(5);
    Vector<int> v1(v0);
    Vector<int> v2(std::move(v1));

    Vector<int> int_vec;
    Vector<std::string> str_vec;

    int_vec.push_back(1);
    int_vec.emplace_back(2);
    int_vec.print();
    assert(int_vec.front() == 1);
    assert(int_vec.back() == 2);
    assert(int_vec.get(0) == 1);
    assert(int_vec[0] == 1);

    str_vec.push_back("aaa");
    str_vec.emplace_back("bbb");
    str_vec.print();
    assert(str_vec.front() == "aaa");
    assert(str_vec.back() == "bbb");
    assert(str_vec.get(0) == "aaa");
    assert(str_vec[0] == "aaa");


    // ----- iterators -----
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    int tmp = 1;

    std::cout << "Incrementing: ";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << " ";
        assert(*it == tmp++);
    }
    std::cout << "OK" << std::endl;

    tmp = 4;
    std::cout << "Decrementing: ";
    for (auto it = --v.end(); it != --v.begin(); --it)
    {
        std::cout << *it << " ";
        assert(*it == tmp--);
    }
    std::cout << "OK" << std::endl;

    v.pop_back();
    v.pop_back();
    std::cout << "Comparing: ";
    Vector<int>::Iterator it1 = v.begin();
    Vector<int>::Iterator it2 = --v.end();
    assert(it1 != it2);
    assert(it1 == --it2);
    std::cout << "OK" << std::endl;
}