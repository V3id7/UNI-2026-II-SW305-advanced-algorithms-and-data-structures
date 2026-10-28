#include <iostream>
#include <map>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>
#include <string>


// Explore accessing, modifying, inserting and erasing map entries.
static void map_example_1() {

    std::cout << "\n========== Map example 1: access and modification ==========" << std::endl;

    constexpr size_t epl_max{5};


    // Associate each unique integer key with a string value.
    // Entries are stored in ascending key order by default.
    std::cout << "\n--- Creating a map with integer keys and string values ---" << std::endl;

    std::map<int, std::string> m1{
            {0, "zero"},
            {1, "one"},
            {2, "two"},
            {3, "three"},
            {4, "four"},
            {5, "five"},
            {6, "six"},
            {7, "seven"},
            {8, "eight"},
            {9, "nine"},
    };

    // Reuse this lambda to print the map and its size.
    auto print_resume = [&m1](const char* msg){
        print_map(msg, m1, epl_max);
        std::cout<< std::format("m1.size(): {:d}", m1.size())<<std::endl;
    };

    print_resume("m1 (initial values) : ");


    // Use operator[] to change the values associated with existing keys.
    // The German words are example data and are intentionally preserved.
    std::cout << "\n--- Modifying existing values with operator[] ---" << std::endl;

    m1[0] = "null";
    m1[1] = "eins";
    m1[2] = "zwei";
    m1[3] = "drei";

    print_resume("m1 (after modifications) : ");


    // When a key is absent, operator[] inserts an entry before assigning its value.
    std::cout << "\n--- Adding new entries with operator[] ---" << std::endl;

    m1[10] = "zenh";
    m1[11] = "elf";

    std::cout<<std::endl;
    print_resume("m1 (after insertions) : ");


    // at() accesses the value associated with an existing key.
    // Unlike operator[], it throws std::out_of_range if the key is absent.
    std::cout << "\n--- Accessing an existing value with at() ---" << std::endl;

    std::cout << std::format ("m1.at({:d}) = {:s}", 2, m1.at(2)) <<std::endl;

    // Disabled example: key 45 is absent, so this call would throw an exception.
    //std::cout << std::format ("m1.at({:d}) = {:s}", 45, m1.at(45)) <<std::endl;


    // Remove the entries whose keys are 5 and 6.
    std::cout << "\n--- Erasing entries by key with erase() ---" << std::endl;

    m1.erase(5);
    m1.erase(6);

    std::cout<<std::endl;
    print_resume("m1 (after erasing) : ");


    // Remove every entry from the map.
    std::cout << "\n--- Removing all entries with clear() ---" << std::endl;

    m1.clear();

    std::cout<<std::endl;
    print_resume("m1 (after clear) : ");
}


int main() {

    std::cout << "Map !!!" << std::endl;

    map_example_1();
}