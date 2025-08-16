#include "header.hpp"
#include <string>
int main(){
    // vector<int> V;
    // V.reserve(10);
    // std::cout << V.capacity() << std::endl;

    // int a = 4;
    // V.insert(0, a);
    // V.insert(0, std::move(a));
    // V.insert(1, {2, 3});
    // V.emplace(3, 75);
    // V.print();
    // V.erase(3);
    // V.erase(0, 2);
    // V.print();
    // V.push_back(102);
    // V.emplace_back(103);
    // V.pop_back();
    // vector<int> V2(10);
    // V2.push_back(2);
    // V2.resize(12, 5);
    // V2.print();

    // vector<int> lv(5), rv(5);
    // lv.insert(0, {2, 2, 3, 4, 5});
    // rv.insert(0, {1, 2, 3, 4, 5});
    // lv.print();
    // rv.print();
    // std::cout << (lv > rv) << std::endl;

    vector<int> v1(3);
    v1.insert(0, {1, 2, 3});
    vector<int> v2(3, 4);

    v1.swap(v2);

    v1.print();
    std::cout << std::endl;
    v2.print();


    return 0;
}
