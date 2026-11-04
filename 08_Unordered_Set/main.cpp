#include <iostream>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>
#include <string>
#include <algorithm>
#include <unordered_set>


// Print the number of elements, bucket count and average elements per bucket.
template <typename T>
static void print_stats(const char* msg, const T& unordered_set) {

    std::cout << std::format("{:s}", msg) << std::endl;
    std::cout << std::format("size: {}", unordered_set.size()) << std::endl;
    std::cout << std::format("bucket_count: {:d}", unordered_set.bucket_count()) << std::endl;
    std::cout << std::format("load_factor: {:.4f}", unordered_set.load_factor()) << std::endl;
}


// Print the container's statistics and the contents of each non-empty bucket.
static void print_buckets(const char* msg, const std::unordered_set<std::string>& container) {

    std::cout << "\n----------------------------------------" << std::endl;

    print_stats(msg, container);

    std::cout << "\nNon-empty buckets:" << std::endl;

    // Visit each bucket, skipping those that contain no elements.
    for (size_t i = 0; i < container.bucket_count(); ++i) {
        if (container.bucket_size(i)) {
            std::cout << std::format("bucket {:2d}: ", i);

            // Local iterators visit only the elements in the current bucket.
            for (auto iter = container.begin(i); iter != container.end(i); ++iter) {
                std::cout << std::format("'{}' ", *iter);
            }

            std::cout << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;
}


// Convert a copy of the string to uppercase and return it.
// Pass each character as unsigned char so std::toupper receives a valid value.
static std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
            // static_cast<int(*)(int)>(std::toupper)         // Unsafe for negative char values.
            // [](int c){ return std::toupper(c); }           // Unsafe if a negative char is passed.
            // [](char c){ return std::toupper(c); }          // Unsafe when char is signed and negative.
                   [](unsigned char c){ return std::toupper(c); } // Convert to unsigned char first.
    );

    return s;
}


// Earlier version: the function did not return the set.
//static void unordered_set_example_1()

// Build a set, add individual elements, then insert a range and return the result.
static std::unordered_set<std::string> unordered_set_example_1() {

    std::cout << "\n========== Unordered set example 1: construction and insertion ==========" << std::endl;


    // Create the initial set. The geographical names are preserved as example data.
    std::cout << "\n--- Creating us1 ---" << std::endl;

    std::unordered_set<std::string> us1 {
            "Golfo de Alaska",
            "Mar del Caribe",
            "Mar Negro",
            "Mar Rojo",
            "Golfo de Tailandia",
            "Mar de Bering",
    };

    print_buckets("us1 (initial values):", us1);


    // Insert individual values with insert().
    std::cout << "\n--- Adding individual elements with insert() ---" << std::endl;

    us1.insert("Mar Baltico");
    us1.insert("Mar Mediterraneo");
    us1.insert("Golfo de Mexico");


    // Construct additional elements with emplace().
    std::cout << "\n--- Adding individual elements with emplace() ---" << std::endl;

    us1.emplace("Mar Ross");
    us1.emplace("Mar Amarillo");
    us1.emplace("Mar Greenland");

    print_buckets("us1 (after insert & emplace):", us1);


    // Prepare another group of values to insert into us1.
    std::cout << "\n--- Preparing an array of additional elements ---" << std::endl;

    std::array<std::string, 6> a1 {
            "Mar Labrador",
            "Golfo de Amundsen",
            "Mar del Norte",
            "Mar Adriatico",
            "Mar de las Antillas Australes",
            "Golfo de Vizcaya",
    };


    // Select the insertion approach according to library feature support.
#if __cpp_lib_containers_ranges >= 202202L
    std::cout << "\n--- Inserting the array with insert_range() ---" << std::endl;

    us1.insert_range(a1);
    print_buckets("us1 (after insert_range):", us1);
#else
    std::cout << "\n--- Inserting the array with std::ranges::copy and std::inserter ---" << std::endl;

    std::ranges::copy(a1, std::inserter(us1, us1.begin()));
    print_buckets("us1 (after ranges::copy):", us1);
#endif


    // Return the completed set for use in the next example.
    std::cout << "\n--- Returning us1 to the caller ---" << std::endl;

    return us1;
}


// Explore merging sets, checking membership and modifying extracted elements.
static void unordered_set_example_2(std::unordered_set<std::string> us1) {

    std::cout << "\n========== Unordered set example 2: merge, contains and extract ==========" << std::endl;


    // Create a second set containing some values that also appear in us1.
    std::cout << "\n--- Creating us2 and displaying both sets ---" << std::endl;

    std::unordered_set<std::string> us2{
            "Mar Amarillo",
            "Mar Rojo",
            "Mar Arabico",
            "Baia de Baffin",
            "Mar del Norte",
            "Mar de Beaufort",
            "Mar Caspio",
            "Golfo de Biscay",
    };

    print_buckets("us1 (initial values):", us1);
    print_buckets("us2 (initial values):", us2);


    // Transfer elements from us1 into us2.
    // Values already present in us2 remain in us1 because duplicates are not allowed.
    std::cout << "\n--- Merging us1 into us2 ---" << std::endl;
    std::cout << "Elements with matching values remain in us1." << std::endl;

    us2.merge(us1);

    print_buckets("us1 (after merge):", us1);
    print_buckets("us2 (after merge):", us2);


    // Check whether each requested value exists without changing the set.
    std::cout << "\n--- Checking membership with contains() ---" << std::endl;

    std::cout << std::format("us2.contains('Mar de Java'): {:s}", us2.contains("Mar de Java")) << std::endl;
    std::cout << std::format("us2.contains('Mar del Norte'): {:s}", us2.contains("Mar del Norte")) << std::endl;


    // Extract each requested element so its value can be modified outside the set.
    std::cout << "\n--- Extracting elements, converting them to uppercase and reinserting them ---" << std::endl;

    std::array<std::string, 3> extract_seas{
            "Mar Negro", "Mar Verde", "Mar Rojo",
    };

    for(const auto &extract_sea : extract_seas){

        std::cout << "\n--- Processing the next requested value ---" << std::endl;

        std::cout << std::format("extract_sea: {:s}", extract_sea)<<std::endl;
        auto node_handle = us2.extract(extract_sea);

        // A non-empty node handle means the element was found and extracted.
        if(!node_handle.empty()){
            std::cout<<"Found !!!"<<std::endl;

            node_handle.value() = str_toupper(extract_sea);

            std::cout << "Reinserting the extracted element after uppercase conversion." << std::endl;

            us2.insert(std::move(node_handle));
        }else{
            std::cout<<"Not found !!!"<<std::endl;
        }
    }


    // Display the set after all extraction and reinsertion attempts.
    std::cout << "\n--- Final contents of us2 ---" << std::endl;

    print_buckets("us2 (after extract):", us2);
}


int main() {

    std::cout << "Unordered set !!!" << std::endl;

    // Run example 1 on its own.
    // unordered_set_example_1();

    // Build the set in example 1, then pass the returned set to example 2.
    unordered_set_example_2(unordered_set_example_1());

    return 0;
}
