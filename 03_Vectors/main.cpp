#include <iostream>
#include <cmath>
#include <algorithm>
#include "../01_BuildingBlocks/Helpers.h"
#include <vector>
#include <format>
static void vector_example_1(){
    std::vector<int> v1{10, 20, 30, 40, 50};
    std::vector<int> v2(v1.size());
    std::vector<int> v3(v1.size(), 7);
    print_container("v1: ", v1);
    print_container("v2 (initial values):", v2);
    print_container("v3: ", v3);
    //operator[].at()
    for(size_t i = 0; i < v1.size(); ++i){
        v2[i] = v1[i] * v3.at(i);
    }
    print_container("v2 (after operation):", v2);
    //More vectors
    std::vector<unsigned long long> v4{100, 200, 300, 400, 500, 600, 700, 800};
    std::vector<unsigned long long> v5(v4.size(), 100);
    std::vector<unsigned long long> v6{v4.size()};
    std::vector<unsigned long long> v7{};
    //{} initialiser      () constructor
    print_container("v4: ", v4);
    print_container("v5: ", v5);
    print_container("v6: ", v6);
    print_container("v7: ", v7);
    //Iterators
    auto it4 = v4.begin();
    auto it5 = v5.begin();
    for(; it4 != v4.end(); ++it4, ++it5){
        *it5 = *it4 / 2;
    }
    print_container("v5 (after operation)", v5);
    //front(), back()
    std::cout << std::format("v4.front(): {:6d}", v4.front())<<std::endl;
    std::cout << std::format("v4.back(): {:6d}", v4.back())<<std::endl;
    //clear()
    v5.clear();
    print_container("v5 (after clear): ", v5);
}

static void vector_example_2(){
    constexpr size_t n{10};
    std::vector <double> v1{};
    //push back
    for(size_t i = 0; i<n; i++){
        v1.push_back(std::sqrt(i+1));
    }
    print_container("v1 (initial values): ", v1);
    while(v1.size() >= n/2){
        v1.pop_back();
    }

    print_container("v1 (after pop_back()): ", v1);
    //add element
    std::array<double, n> a1{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    v1.insert(v1.begin()+2, a1.begin(), a1.end());
    print_container("v1 (after insert):", v1);
    //add elements
    std::array<double, 6> a2{-10.0, -20.0, -30.0, -40.0, -50.0, -60.0};
    v1.insert(v1.end(), a2.begin(), a2.end());
    print_container("v1 (after 2nd insert):", v1);
    //remove
    v1.erase(v1.begin() + 3, v1.begin()+ 5);
    print_container("v1 (after erase):", v1);
}
// In CLion, select a variable or function name and press Shift + F6 to rename it and update its references.
static void vector_example3(){
    std::vector<std::string> planets1;
    const char *planets_cstr1[] = {"Mercury", "Venus", "Earth", "Mars"};
    const char *planets_cstr2[] = {"Jupiter", "Saturn", "Uranus", "Neptune" };
    //std::ranges::copy
    std::ranges::copy(planets_cstr1, std::back_inserter(planets1));
    print_container("planets1: ", planets1);
    //emplace_back()
    std::vector<std::string> planets2(planets1);
    planets2.emplace_back(planets_cstr2[0]);
    planets2.emplace_back(planets_cstr2[1]);
    planets2.emplace_back(planets_cstr2[2]);
    planets2.emplace_back(planets_cstr2[3]);
    print_container("planets2: ", planets2);
    //std::ranges::find
    auto it_mars = std::ranges::find(planets2, "Mars");
    bool found_mars = (it_mars !=planets2.end());
    std::cout<<(found_mars ? "Found":"Not found")<<std::endl;
    std::cout<< "Value: " <<*it_mars<<std::endl;
    //sort
    auto planets3 {planets2};
    print_container("planets3 (before sort): ", planets3);
    std::ranges::sort(planets3);
    print_container("planets3 (after sort): ", planets3);
    //relational
    std::cout<<std::format("planet2 == planet3: {:s}", planets2 == planets3)<<std::endl;
    //swap
    std::swap(planets3[3], planets3[4]);
    print_container("planet 3 (after swap)", planets3);
}

static void vector_example4(){
    constexpr double rem_val{-1.0};
    std::vector<double> v1{10, 20, rem_val, 30, 40, rem_val, 50, rem_val, 60, 70, 80};
    std::vector<double> v2{v1};
    std::vector<double> v3{v1};
    print_container("v1(initial values): ", v1);
    //std::ranges::remove
    auto removed_items = std::ranges::remove(v1, rem_val);
    print_container("v1 (after remove): ", v1);
    std::cout<<"size v1: "<<v1.size() << std::endl;
    print_container("removed items: ", removed_items);
    //erase (vector member function)
    v1.erase(removed_items.begin(), v1.end());
    print_container("v1 (after erase): ", v1);
    //std::erase (from the standard library)
    print_container("v2 (initial values): ", v2);
    auto num_erased  = std::erase(v2, rem_val);
    std::cout<<std::format("num_erased: {:d}", num_erased)<<std::endl;
    print_container("v2 (after std::erase): ", v2);
};



int main() {
    std::cout << "Vectors!!!" << std::endl;
    vector_example_1();
    vector_example_2();
    vector_example3();
    vector_example4();
    return 0;
}