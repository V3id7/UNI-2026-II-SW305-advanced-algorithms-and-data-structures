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


// Explore insertion, emplacement and searching with airport codes.
static void map_example_2() {

    std::cout << "\n========== Map example 2: insertion, emplacement and searching ==========" << std::endl;

    constexpr size_t epl_max{1};


    // string_view provides read-only access to character data without owning it.
    // These keys refer to string literals, which remain valid throughout the program.
    std::cout << "\n--- Creating a map of airport codes and descriptions ---" << std::endl;

    std::map<std::string_view, std::string> m1{
            {"ORD", "O'Hare International (Chicago, IL USA)"},
            {"LHR", "Heathrow Airport (London, England UK)"},
            {"ZRH", "Flughanfen Zurich (Zurich, Switzerland)"},
            {"AKL", "Auckland Airport (Auckland, New Zealand)"},
    };

    auto print_resume = [&m1](const char *msg) -> void {
        print_map(msg, m1, epl_max);
        std::cout << std::format("m1.size(): {}", m1.size()) << std::endl;
    };

    print_resume("m1 (initial values):");


    // Insert a new key and assign its associated value using operator[].
    std::cout << "\n--- Adding an airport with operator[] ---" << std::endl;

    m1["SYD"] = "Sydney Airport (Sydney, Australia)";

    print_resume("m1 (after insertions):");


    // Create a pair and attempt to insert it with emplace().
    // The returned iterator identifies the entry; the boolean reports insertion success.
    std::cout << "\n--- Adding a key-value pair with emplace() ---" << std::endl;

    std::pair p = std::make_pair("NRT", "Narita International (Tokyo, Japan)");
    auto [iter1, status1] = m1.emplace(p);

    if (status1) {
        std::cout << "m1.emplace() - new entry added to map m1" << std::endl;
        std::cout << std::format("key: {}, value: {}", iter1->first, iter1->second) << std::endl;
    } else {
        std::cout << "m1.emplace() - key already exists in map m1" << std::endl;
        std::cout << std::format("{}, {}", iter1->first, iter1->second) << std::endl;
    }


    // Construct the mapped value only if the key does not already exist.
    std::cout << "\n--- Adding an airport with try_emplace() ---" << std::endl;

    auto [iter2, status2] = m1.try_emplace("DXB", "Dubai International Airport (Dubai, UAE)");

    if (status2) {
        std::cout << "m1.try_emplace() - new entry added to map m1" << std::endl;
        std::cout << std::format("key: {}, value: {}", iter2->first, iter2->second) << std::endl;
    } else {
        std::cout << "m1.try_emplace() - key already exists in map m1" << std::endl;
    }

    std::cout << std::endl;
    print_resume("m1 (after emplacements):");


    // Search for each key. find() returns end() when the key is absent.
    std::cout << "\n--- Searching for airport codes with find() ---" << std::endl;

    std::array<std::string_view, 4> keys{"ZRH", "LAK", "MCD", "AKL"};

    for (const auto &key : keys) {

        std::cout << "\n--- Next search ---" << std::endl;

        std::cout << std::format("key: {}", key) << std::endl;

        if (auto iter = m1.find(key); iter != m1.end()) {
            std::cout << std::format("found [{}, {}]", iter->first, iter->second) << std::endl;
        } else {
            std::cout << std::format("not found [{}]", key) << std::endl;
        }
    }
}


// Define a reusable multimap type with string-view keys and string values.
using multimap_t = std::multimap<std::string_view, std::string>;


// Explore duplicate keys, insertion, counting and membership checks.
static void multimap_example_3(){

    std::cout << "\n========== Multimap example 3: insertion, counting and membership ==========" << std::endl;

    constexpr size_t epl_max{3};


    // Define the state names used as keys.
    std::string_view ca{"California"};
    std::string_view fl{"Florida"};
    std::string_view il{"Illinois"};
    std::string_view ny{"New York"};
    std::string_view oh{"Ohio"};
    std::string_view tx{"Texas"};
    std::string_view wi{"Wisconsin"};


    // A multimap allows multiple entries with the same key.
    std::cout << "\n--- Creating a multimap of states and cities ---" << std::endl;

    multimap_t mm1{
            {ca, "Los Angeles"}, {ca, "San Francisco"}, {ca, "Fresno"},
            {il, "Chicago"}, {il, "Peoria"}, {il, "Rockford"},
            {oh, "Cleveland"}, {oh, "Columbus"}, {oh, "Cincinnati"},
            {tx, "Houston"},{tx, "Dallas"},{tx, "Austin"}, {tx, "El Paso"},
    };

    print_multimap("mm1(initial values)", mm1, epl_max);

    auto print_resume = [&mm1](const char *msg) -> void {
        print_multimap(msg, mm1, epl_max);
        std::cout << std::format("mm1.size(): {}", mm1.size()) << std::endl;
    };

    print_resume("mm1 (initial values) : ");


    // Insert Florida entries, including the same key-value pair twice.
    // A multimap accepts both repeated keys and repeated pairs.
    std::cout << "\n--- Adding key-value pairs with insert() ---" << std::endl;

    mm1.insert(std::pair{fl, "Orlando"});
    mm1.insert(std::pair{fl, "Miami"});
    mm1.insert(std::pair{fl, "Jacksonville"});
    mm1.insert(std::pair{fl, "Orlando"});

    print_resume("mm1 (after insertions): ");


    // Construct additional entries associated with the New York key.
    std::cout << "\n--- Adding cities with emplace() ---" << std::endl;

    mm1.emplace(ny, "New york City");
    mm1.emplace(ny, "Buffalo");
    mm1.emplace(ny, "Albany");
    mm1.emplace(ny, "Yorkers");
    mm1.emplace(ny, "Syracuse");

    print_resume("mm1 (after emplacements): ");


    // Count the entries associated with each requested key.
    std::cout << "\n--- Counting entries by key with count() ---" << std::endl;

    auto count_il = mm1.count(il);
    auto count_tx = mm1.count(tx);

    std::cout << std::format("count_il: {}", count_il)<<std::endl;
    std::cout << std::format("count_tx: {}", count_tx)<<std::endl;


    // Check whether at least one entry exists for each key.
    std::cout << "\n--- Checking whether keys exist with contains() ---" << std::endl;

    std::cout<<std::format("mm1 contains the key '{}': {}", wi, mm1.contains(wi))<<std::endl;
    std::cout<<std::format("mm1 contains the key '{}': {}", oh, mm1.contains(oh))<<std::endl;
}


// Explore two ways to retrieve entries sharing the same key.
static void multimap_example_4(){

    std::cout << "\n========== Multimap example 4: find() and equal_range() ==========" << std::endl;

    constexpr size_t epl_max{3};


    // Define the country names used as keys.
    std::string_view ar{"Argentina"};
    std::string_view br{"Brasil"};
    std::string_view ca{"Canada"};
    std::string_view in{"India"};
    std::string_view mx{"Mexico"};


    // Store several cities under each country key.
    std::cout << "\n--- Creating a multimap of countries and cities ---" << std::endl;

    multimap_t mm1{
            {br, "Sau Paulo"}, {br, "Rio de Janeiro"}, {br, "Brasilia"},
            {ca, "Montreal"}, {ca, "Toronto"}, {ca, "Edmonton"}, {ca, "Calgary"}, {ca, "Vancouver"},
            {in, "New Delhi"}, {in, "Chennai"},
            {mx, "Mexico city"}, {mx, "Tijuana"}, {mx, "Ecatepec"},
    };

    auto print_resume = [&mm1](const char *msg) -> void {
        print_multimap(msg, mm1, epl_max);
        std::cout << std::format("mm1.size(): {}", mm1.size()) << std::endl;
    };

    print_resume("mm1 (initial values) : ");


    // Find a matching entry, then advance while the following entries share its key.
    // The loop stops if the iterator reaches the end of the multimap.
    std::cout << "\n--- Searching with find() and an iterator loop ---" << std::endl;

    std::array<std::string_view, 3> keys{ar, ca, in};

    for (const auto &key : keys){

        std::cout << "\n--- Next search ---" << std::endl;

        std::cout<<std::format("key: {}", key)<<std::endl;

        if (auto iter = mm1.find(key); iter != mm1.end()) {
            while(iter->first == key){
                std::cout << std::format("found [{}, {}]", iter->first, iter->second) << std::endl;

                if(++iter == mm1.end()){
                    break;
                };
            }
        } else {
            std::cout << std::format("not found [{}]", key) << std::endl;
        }
    }


    // equal_range() returns the beginning and end of the matching range.
    // The end iterator is excluded from the range.
    std::cout << "\n--- Searching with equal_range() ---" << std::endl;

    std::cout<<"Searching mm1 using equal_range"<<std::endl;

    for (const auto &key : keys){

        std::cout << "\n--- Next search ---" << std::endl;

        std::cout<<std::format("key: {}", key)<<std::endl;

        auto p = mm1.equal_range(key);

        if (p.first->first != key ) {
            std::cout << "Not found !!!" << std::endl;
        } else {
            for(auto it = p.first; it != p.second; it++){
                std::cout<<std::format("[{}, {}]", it->first, it->second)<<std::endl;
            }
        }
    }

}


int main() {

    std::cout << "Map !!!" << std::endl;

    map_example_1();

    map_example_2();

    multimap_example_3();

    multimap_example_4();

    return 0;
}