#include "header.hpp"

int main(){
    vector<int> V;
    V.reserve(10);
    std::cout << V.capacity() << std::endl;

    int a = 4;
    V.insert(0, a);
    V.insert(0, std::move(a));
    V.insert(1, {2, 3});
    V.emplace(3, 75);
    V.print();
    V.erase(3);
    V.erase(0, 2);
    V.print();
    V.push_back(102);
    V.emplace_back(103);
    V.pop_back();
    V.print();

    return 0;
}