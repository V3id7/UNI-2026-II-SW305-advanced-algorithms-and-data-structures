#include <algorithm>
#include <iostream>
#include <array>
#include <bits/locale_facets_nonio.h>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>


// Explore different ways to access and print the same array.
static void array_example_1() {

    std::cout << "\n========== Array example 1: accessing elements ==========" << std::endl;

    std::array<int, 9> x_vals{100,200,300,400,500,600,700,800,900};
    std::cout<<"size: "<<x_vals.size()<<std::endl;


    // Access each element by index using at().
    std::cout << "\n--- Indexed access with at() ---" << std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (int i=0; i<x_vals.size(); i++) {
        std::cout<<x_vals.at(i)<<" ";
    }
    std::cout<<std::endl;


    // Visit each value directly using a range-based for loop.
    std::cout << "\n--- Range-based for loop ---" << std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto value : x_vals) {
        std::cout<<value<<" ";
    }
    std::cout<<std::endl;


    // Print each integer in a field at least six characters wide.
    std::cout << "\n--- Formatted output with std::format ---" << std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto value : x_vals) {
        //std::cout<<value<<" ";
        std::cout<<std::format("{:6d} ", value);
    }
    std::cout<<std::endl;


    // Move from the first element to the last using forward iterators.
    std::cout << "\n--- Forward iterators: begin() to end() ---" << std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:7d} ", *it);
    }
    std::cout<<std::endl;


    // Move from the last element to the first using reverse iterators.
    std::cout << "\n--- Reverse iterators: rbegin() to rend() ---" << std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto it = x_vals.rbegin(); it != x_vals.rend(); ++it) {
        std::cout<<std::format("{:5d} ", *it);
    }
    std::cout<<std::endl;
}


// Modify the array's elements through reverse iterators.
static void array_example_2() {

    std::cout << "\n========== Array example 2: modifying elements ==========" << std::endl;

    std::array<long,10> x_vals{10,20,30,40,50,60,70,80,90,100};


    // Print the original values using forward iterators.
    std::cout << "\n--- Before modification ---" << std::endl;

    std::cout<<"x_vals array example2: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:6d} ", *it);
    }
    std::cout<<std::endl;


    // Visit the elements in reverse order and add 5 to each one.
    std::cout << "\n--- Adding 5 through reverse iterators ---" << std::endl;

    std::cout<<"Adding 5 to each element ...."<<std::endl;
    for (auto it=x_vals.rbegin(); it != x_vals.rend(); ++it) {
        *it += 5;
    }


    // Print the updated values in their original order.
    std::cout << "\n--- After modification ---" << std::endl;

    std::cout<<"x_vals array example2: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:6d} ", *it);
    }
    std::cout<<std::endl;
}


// Use two arrays to associate each radius with its circle's area.
static void array_example_3() {

    std::cout << "\n========== Array example 3: calculating circle areas ==========" << std::endl;

    std::array<double, 8> radios{1.0, 1.4, 2.0, 2.8, 4.0, 5.6, 8.0, 11.0};
    std::array<double, radios.size()> areas{};


    // Advance both iterators together to store each calculated area at the matching position.
    std::cout << "\n--- Calculating each area using pi * radius * radius ---" << std::endl;

    auto it_a = areas.begin();

    for (auto it_r = radios.begin(); it_r != radios.end(); ++it_r, ++it_a) {
        *it_a = std::numbers::pi * *it_r * *it_r;
    }


    // Return to the first area and print the matching radii and areas.
    std::cout << "\n--- Results: radius and corresponding area ---" << std::endl;

    std::cout << std::format("{:6s} {:12s}", "Radii", "Areas") << std::endl;

    it_a = areas.begin();

    for (auto it_r = radios.begin(); it_r != radios.end(); ++it_r, ++it_a) {
        std::cout << std::format("{:6.1f} {:12.6f}", *it_r, *it_a) << std::endl;
    }
}


// Explore container printing, sorting and array comparison.
static void array_example_4 () {

    std::cout << "\n========== Array example 4: sorting and comparison ==========" << std::endl;

    constexpr size_t epl_max{5};
    std::array<std::string, 15> colors_1{"Red", "Green", "Blue", "Cyan", "Magenta", "Yellow", "Black", "White", "Gray", "Orange", "Brown", "Pink", "Purple", "Amber", "Teal"};
    auto colors_2 {colors_1};


    // Check the printing helper with a limit of five elements per line.
    std::cout << "\n--- Initial values ---" << std::endl;

    print_container("colors_1 (initial values)", colors_1, epl_max);
    print_container("colors_2 (initial values)", colors_2, epl_max);


    // Sort colors_1 by passing its iterator range to std::sort.
    std::cout << "\n--- Sorting colors_1 with std::sort ---" << std::endl;

    std::sort(colors_1.begin(), colors_1.end());
    print_container("colors_1 (after sort)", colors_1, epl_max);


    // Sort colors_2 by passing the container directly to std::ranges::sort.
    std::cout << "\n--- Sorting colors_2 with std::ranges::sort ---" << std::endl;

    std::ranges::sort(colors_2);
    print_container("colors_2 (after ranges::sort)", colors_2, epl_max);


    // Compare both arrays: matching elements in the same order produce true.
    std::cout << "\n--- Comparing colors_1 and colors_2 ---" << std::endl;

    std::cout << std::format("colors_1 == colors_2: {:s}", colors_1 == colors_2);

    std::cout << std::endl;
}


int main() {

    std::cout << "Arrays" << std::endl;

    array_example_1();

    array_example_2();

    array_example_3();

    array_example_4();

    return 0;
}