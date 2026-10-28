#include <iostream>
#include <cmath>
#include <algorithm>
#include "../01_BuildingBlocks/Helpers.h"
#include <vector>
#include <format>


// Explore vector construction, element access and modification.
static void vector_example_1(){

    std::cout << "\n========== Vector example 1: construction and access ==========" << std::endl;

    // Create a vector with explicit values, one with zero-initialised elements,
    // and another filled with 7.
    std::cout << "\n--- Creating the initial vectors ---" << std::endl;

    std::vector<int> v1{10, 20, 30, 40, 50};
    std::vector<int> v2(v1.size());
    std::vector<int> v3(v1.size(), 7);

    print_container("v1: ", v1);
    print_container("v2 (initial values):", v2);
    print_container("v3: ", v3);


    // Multiply matching elements using operator[] and at().
    std::cout << "\n--- Element-wise multiplication using operator[] and at() ---" << std::endl;

    for(size_t i = 0; i < v1.size(); ++i){
        v2[i] = v1[i] * v3.at(i);
    }

    print_container("v2 (after operation):", v2);


    // For these vectors, parentheses select size-based constructors.
    // Braces select an initialiser list: v6 contains one element equal to v4.size().
    std::cout << "\n--- Comparing parentheses and brace initialisation ---" << std::endl;

    std::vector<unsigned long long> v4{100, 200, 300, 400, 500, 600, 700, 800};
    std::vector<unsigned long long> v5(v4.size(), 100);
    std::vector<unsigned long long> v6{v4.size()};
    std::vector<unsigned long long> v7{};

    print_container("v4: ", v4);
    print_container("v5: ", v5);
    print_container("v6: ", v6);
    print_container("v7: ", v7);


    // Advance both iterators together and store half of each v4 value in v5.
    std::cout << "\n--- Modifying v5 through iterators ---" << std::endl;

    auto it4 = v4.begin();
    auto it5 = v5.begin();

    for(; it4 != v4.end(); ++it4, ++it5){
        *it5 = *it4 / 2;
    }

    print_container("v5 (after operation)", v5);


    // Access the first and last elements of v4.
    std::cout << "\n--- Accessing the first and last elements: front() and back() ---" << std::endl;

    std::cout << std::format("v4.front(): {:6d}", v4.front())<<std::endl;
    std::cout << std::format("v4.back(): {:6d}", v4.back())<<std::endl;


    // Remove all elements from v5.
    std::cout << "\n--- Clearing v5 with clear() ---" << std::endl;

    v5.clear();
    print_container("v5 (after clear): ", v5);
}


// Explore adding, inserting and erasing vector elements.
static void vector_example_2(){

    std::cout << "\n========== Vector example 2: insertion and erasure ==========" << std::endl;

    constexpr size_t n{10};
    std::vector <double> v1{};


    // Append the square roots of 1 through n.
    std::cout << "\n--- Appending square roots with push_back() ---" << std::endl;

    for(size_t i = 0; i<n; i++){
        v1.push_back(std::sqrt(i+1));
    }

    print_container("v1 (initial values): ", v1);


    // Remove the last element repeatedly until the size is less than n/2.
    std::cout << "\n--- Removing elements from the end with pop_back() ---" << std::endl;

    while(v1.size() >= n/2){
        v1.pop_back();
    }

    print_container("v1 (after pop_back()): ", v1);


    // Insert all elements of a1 before the element at index 2.
    std::cout << "\n--- Inserting an array at index 2 ---" << std::endl;

    std::array<double, n> a1{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    v1.insert(v1.begin()+2, a1.begin(), a1.end());

    print_container("v1 (after insert):", v1);


    // Insert all elements of a2 at the end.
    std::cout << "\n--- Inserting another array at the end ---" << std::endl;

    std::array<double, 6> a2{-10.0, -20.0, -30.0, -40.0, -50.0, -60.0};
    v1.insert(v1.end(), a2.begin(), a2.end());

    print_container("v1 (after 2nd insert):", v1);


    // Erase the elements at indices 3 and 4; the end iterator is excluded.
    std::cout << "\n--- Erasing the range [3, 5) ---" << std::endl;

    v1.erase(v1.begin() + 3, v1.begin()+ 5);

    print_container("v1 (after erase):", v1);
}


// In CLion, select a variable or function name and press Shift + F6
// to rename it and update its references.
static void vector_example3(){

    std::cout << "\n========== Vector example 3: copying, searching and sorting ==========" << std::endl;

    std::vector<std::string> planets1;
    const char *planets_cstr1[] = {"Mercury", "Venus", "Earth", "Mars"};
    const char *planets_cstr2[] = {"Jupiter", "Saturn", "Uranus", "Neptune" };


    // Copy the planet names into planets1, appending each through a back inserter.
    std::cout << "\n--- Copying names with std::ranges::copy ---" << std::endl;

    std::ranges::copy(planets_cstr1, std::back_inserter(planets1));

    print_container("planets1: ", planets1);


    // Copy planets1, then construct four more strings at the end of planets2.
    std::cout << "\n--- Adding more planets with emplace_back() ---" << std::endl;

    std::vector<std::string> planets2(planets1);
    planets2.emplace_back(planets_cstr2[0]);
    planets2.emplace_back(planets_cstr2[1]);
    planets2.emplace_back(planets_cstr2[2]);
    planets2.emplace_back(planets_cstr2[3]);

    print_container("planets2: ", planets2);


    // Find Mars and check whether the returned iterator differs from end().
    // Mars is present in this example, so dereferencing the iterator is valid.
    std::cout << "\n--- Searching for Mars with std::ranges::find ---" << std::endl;

    auto it_mars = std::ranges::find(planets2, "Mars");
    bool found_mars = (it_mars !=planets2.end());

    std::cout<<(found_mars ? "Found":"Not found")<<std::endl;
    std::cout<< "Value: " <<*it_mars<<std::endl;


    // Copy planets2 and sort the copy alphabetically.
    std::cout << "\n--- Sorting a copy with std::ranges::sort ---" << std::endl;

    auto planets3 {planets2};

    print_container("planets3 (before sort): ", planets3);

    std::ranges::sort(planets3);

    print_container("planets3 (after sort): ", planets3);


    // Equality compares both the values and their order.
    std::cout << "\n--- Comparing planets2 and planets3 ---" << std::endl;

    std::cout<<std::format("planets2 == planets3: {:s}", planets2 == planets3)<<std::endl;


    // Exchange the elements at indices 3 and 4.
    std::cout << "\n--- Swapping two elements with std::swap ---" << std::endl;

    std::swap(planets3[3], planets3[4]);

    print_container("planets3 (after swap)", planets3);
}


// Compare the remove-erase approach with std::erase.
static void vector_example4(){

    std::cout << "\n========== Vector example 4: removing matching values ==========" << std::endl;

    constexpr double rem_val{-1.0};
    std::vector<double> v1{10, 20, rem_val, 30, 40, rem_val, 50, rem_val, 60, 70, 80};
    std::vector<double> v2{v1};
    std::vector<double> v3{v1};

    print_container("v1 (initial values): ", v1);


    // Move the values to keep towards the front without changing the vector's size.
    // The returned range is the trailing range to erase, not a collection of removed values.
    std::cout << "\n--- Logical removal with std::ranges::remove ---" << std::endl;

    auto removed_items = std::ranges::remove(v1, rem_val);

    print_container("v1 (after remove): ", v1);
    std::cout<<"size v1: "<<v1.size() << std::endl;

    std::cout << "The trailing values below are unspecified; they are not necessarily the removed values." << std::endl;
    print_container("Trailing range to erase: ", removed_items);


    // Erase the trailing range to reduce the vector's size.
    std::cout << "\n--- Erasing the trailing range with the vector's erase() ---" << std::endl;

    v1.erase(removed_items.begin(), v1.end());

    print_container("v1 (after erase): ", v1);


    // Remove every matching value in one call and return the number erased.
    std::cout << "\n--- Removing matching values directly with std::erase ---" << std::endl;

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