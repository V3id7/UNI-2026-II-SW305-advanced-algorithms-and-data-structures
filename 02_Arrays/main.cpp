#include <algorithm>
#include <iostream>
#include <array>
#include <bits/locale_facets_nonio.h>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>

static void array_example_1() {
    std::array<int, 9> x_vals{100,200,300,400,500,600,700,800,900};
    std::cout<<"size: "<<x_vals.size()<<std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (int i=0; i<x_vals.size(); i++) {
        std::cout<<x_vals.at(i)<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto value : x_vals) {
        std::cout<<value<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"x_vals: "<<std::endl;
    for (auto value : x_vals) {
        //std::cout<<value<<" ";
        std::cout<<std::format("{:6d} ", value);
    }
    std::cout<<std::endl;

    //Iterators
    std::cout<<"x_vals: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:7d} ", *it);
    }
    std::cout<<std::endl;

    //Reverse iterators
    std::cout<<"x_vals: "<<std::endl;
    for (auto it = x_vals.rbegin(); it != x_vals.rend(); ++it) {
        std::cout<<std::format("{:5d} ", *it);
    }
    std::cout<<std::endl;
}

static void array_example_2() {

    std::array<long,10> x_vals{10,20,30,40,50,60,70,80,90,100};

    std::cout<<"x_vals array example2: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:6d} ", *it);
    }
    std::cout<<std::endl;

    std::cout<<"Adding 5 to each element ...."<<std::endl;
    for (auto it=x_vals.rbegin(); it != x_vals.rend(); ++it) {
        *it += 5;
    }

    std::cout<<"x_vals array example2: "<<std::endl;
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout<<std::format("{:6d} ", *it);
    }
    std::cout<<std::endl;
}

static void array_example_3() {
    std::array<double, 8> radios{1.0, 1.4, 2.0, 2.8, 4.0, 5.6, 8.0, 11.0};
    std::array<double, radios.size()> areas{};

    // Calculation
    auto it_a = areas.begin();

    for (auto it_r = radios.begin(); it_r != radios.end(); ++it_r, ++it_a) {
        *it_a = std::numbers::pi * *it_r * *it_r;
    }

    // print
    std::cout << std::format("{:6s} {:12s}", "Radii", "Areas") << std::endl;

    it_a = areas.begin();

    for (auto it_r = radios.begin(); it_r != radios.end(); ++it_r, ++it_a) {
        std::cout << std::format("{:6.1f} {:12.6f}", *it_r, *it_a) << std::endl;
    }
}

static void array_example_4 () {
    constexpr size_t epl_max{5};
    std::array<std::string, 15> colors_1{"Red", "Green", "Blue", "Cyan", "Magenta", "Yellow", "Black", "White", "Gray", "Orange", "Brown", "Pink", "Purple", "Amber", "Teal"};
    auto colors_2 {colors_1};
    //Check that print_container works
    print_container("colors_1 (initial values)", colors_1, epl_max);
    print_container("colors_2 (initial values)", colors_1, epl_max);
    // sort: part of the STL
    std::sort(colors_1.begin(), colors_1.end());
    print_container("colors_1 (after sort)", colors_1, epl_max);
    std::ranges::sort(colors_2);
    print_container("colors_2(after ranges::sort)", colors_1, epl_max);
    // Comparison
    std::cout << std::format("colors_1 == colors_2: {:s}", colors_1 == colors_2);

}



int main() {
    std::cout << "Arrays" << std::endl;
    array_example_1();
    array_example_2();
    array_example_3();
    array_example_4();
    return 0;
}