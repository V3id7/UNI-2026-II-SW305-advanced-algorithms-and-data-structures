#include <array>
#include <iostream>
#include <algorithm>
#include <deque>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>


// Explore deque construction, indexed access and modification through iterators.
static void deque_example_1() {

    std::cout << "\n========== Deque example 1: construction and access ==========" << std::endl;

    std::deque<int> d1{10, 20, 30, 40, 50};
    std::deque<int> d2(d1.size());


    // Create d2 with the same size as d1 and zero-initialised elements.
    std::cout << "\n--- Initial values of d2 ---" << std::endl;

    print_container("d2:", d2);


    // Read each element of d1 with at() and store its value times 5 in d2.
    std::cout << "\n--- Multiplying elements using operator[] and at() ---" << std::endl;

    for (size_t i = 0; i < d1.size(); ++i) {
        d2[i] = d1.at(i) * 5;
    }

    print_container("d2(after initialization):", d2);


    // Create d3 with explicit values and fill d4 with 1000.
    std::cout << "\n--- Creating another pair of deques ---" << std::endl;

    std::deque<long> d3{100, 200, 300, 400, 500};
    std::deque<long> d4(d3.size(), 1000);

    print_container("d4(after initialization):", d4);


    // Advance both iterators together and store half of each d3 value in d4.
    std::cout << "\n--- Modifying d4 through iterators ---" << std::endl;

    auto it3 = d3.begin();
    auto it4 = d4.begin();

    for (; it3 != d3.end(); ++it3, ++it4) {
        *it4 = *it3 / 2;
    }

    print_container("d4 (after iterators):", d4);
}


// Explore adding elements at both ends and inserting a range in the middle.
static void deque_example_2() {

    std::cout << "\n========== Deque example 2: adding and inserting elements ==========" << std::endl;

    std::deque<double>d1{};


    // Append each value to the back of the deque.
    std::cout << "\n--- Adding elements at the back with push_back() ---" << std::endl;

    d1.push_back(50);
    d1.push_back(60);
    d1.push_back(70);
    d1.push_back(80);

    print_container("d1 (after push_back):", d1);


    // Prepend each value to the front of the deque.
    std::cout << "\n--- Adding elements at the front with push_front() ---" << std::endl;

    d1.push_front(40);
    d1.push_front(30);
    d1.push_front(20);
    d1.push_front(10);

    print_container("d1 (after push_front):", d1);


    // Insert all array elements before the element at index 2.
    std::cout << "\n--- Inserting an array at index 2 ---" << std::endl;

    std::array<double, 5> array1{1000, 2000, 3000, 4000, 5000};
    d1.insert(d1.begin() + 2, array1.begin(), array1.end());

    print_container("d1 (after insert): ", d1);
}


// Explore range insertion, alphabetical sorting and deque comparisons.
static void deque_example_3(){

    std::cout << "\n========== Deque example 3: insertion, sorting and comparison ==========" << std::endl;


    // Store the first six months and copy them into d2 before modifying d1.
    std::cout << "\n--- Initial month names ---" << std::endl;

    std::deque<std::string> d1{"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    print_container("d1 (initial values): ", d1);

    std::array<std::string, 6> array1{"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    std::deque<std::string> d2{d1};


    // Disabled alternative: use the feature-test macro to select append_range()
    // when available, or iterator-based insertion otherwise.
    /*#ifdef __cpp_lib_containers_ranges
    std::cout << "C++23" << std::endl;
    d1.append_range(array1);
#else
    std::cout << "C++20" << std::endl;
    d1.insert(d1.end(), array1.begin(), array1.end());
#endif*/


    // Append the remaining months using an iterator range.
    std::cout << "\n--- Appending the remaining months with insert() ---" << std::endl;

    d1.insert(d1.end(), array1.begin(), array1.end());

    print_container("d1 (after insert): ", d1);


    // Sort the strings alphabetically, rather than by calendar order.
    std::cout << "\n--- Sorting in ascending alphabetical order ---" << std::endl;

    std::ranges::sort(d1);

    print_container("d1 (after sort): ", d1);


    // Reverse the sorting order by using std::greater.
    std::cout << "\n--- Sorting in descending alphabetical order ---" << std::endl;

    std::ranges::sort(d1, std::greater());

    print_container("d1 (after sort(greater)): ", d1);


    // Display the original copy before comparing it with the modified deque.
    std::cout << "\n--- Original copy: d2 ---" << std::endl;

    print_container("d2 : ", d2);


    // Equality checks matching elements and size.
    // Ordering comparisons are lexicographical: the first differing pair decides.
    std::cout << "\n--- Comparing d1 and d2 ---" << std::endl;

    std::cout << std::format("d1 == d2: {:s}", d1 == d2)<<std::endl;
    std::cout << std::format("d1 <= d2: {:s}", d1 <= d2)<<std::endl;
    std::cout << std::format("d1 >= d2: {:s}", d1 >= d2)<<std::endl;
}


// Explore conditional range appending, sorting, comparisons and element swapping.
static void deque_example_4() {

    std::cout << "\n========== Deque example 4: range appending and sorting ==========" << std::endl;


    // Initialise the deque with the first six months.
    std::cout << "\n--- Initial month names ---" << std::endl;

    std::deque<std::string> d1{"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    print_container("d1 (initial values):", d1);


    // Store the remaining months in an array.
    std::array<std::string, 6> array1{"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


    // Check library support for container range operations at compile time.
    // Use append_range() when available; otherwise, append with insert().
    std::cout << "\n--- Appending the remaining months ---" << std::endl;

#ifdef __cpp_lib_containers_ranges
    d1.append_range(array1);
#else
    std::cout << "C++20" << std::endl;
    d1.insert(d1.end(), array1.begin(), array1.end());
#endif

    print_container("d1 after append:", d1);


    // Sort alphabetically using std::ranges::sort.
    // The commented line shows the iterator-based std::sort alternative.
    std::cout << "\n--- Sorting d1 in ascending alphabetical order ---" << std::endl;

    // std::sort(d1.begin(), d1.end());
    std::ranges::sort(d1);

    print_container("d1 after sort using operator< :", d1);


    // Use std::greater to sort in descending alphabetical order.
    std::cout << "\n--- Sorting d1 in descending alphabetical order ---" << std::endl;

    // std::sort(d1.begin(), d1.end(), std::greater<>());
    std::ranges::sort(d1, std::greater<>());

    print_container("d1 after sort using operator> :", d1);


    // Copy d1 into d2 and sort the copy in ascending order.
    std::cout << "\n--- Copying d1 and sorting d2 in ascending order ---" << std::endl;

    std::deque d2{d1};
    std::ranges::sort(d2);

    print_container("d2 after ranges::sort using operator< :", d2);


    // Sort d2 in descending order using the same comparison object.
    std::cout << "\n--- Sorting d2 in descending alphabetical order ---" << std::endl;

    std::ranges::sort(d2, std::greater<>());

    print_container("d2 after ranges::sort using operator> :", d2);


    // Compare the deques after both have been sorted in descending order.
    // Equality checks the full sequence; ordering comparisons are lexicographical.
    std::cout << "\n--- Comparing d1 and d2 ---" << std::endl;

    std::cout << std::format("d1 == d2: {:s}", d1 == d2) << std::endl;
    std::cout << std::format("d1 <= d2: {:s}", d1 <= d2) << std::endl;
    std::cout << std::format("d1 >= d2: {:s}", d1 >= d2) << std::endl;


    // Exchange the elements at indices 5 and 7.
    std::cout << "\n--- Swapping two elements in d1 ---" << std::endl;

    std::swap(d1[5], d1[7]);

    print_container("d1 after swap :", d1);
}


// Compare the remove-erase approach with direct removal using std::erase.
static void deque_example_5() {

    std::cout << "\n========== Deque example 5: removing matching values ==========" << std::endl;

    constexpr size_t epl_max{10};
    constexpr double rem_val{-1.0};

    std::deque<double> d1{10.0, 20.0, rem_val, 30.0, 40.0, rem_val, 50.0, rem_val, 60.0, 70.0};
    std::deque<double> d2(d1);


    // Display the original deque and its size.
    std::cout << "\n--- Initial values of d1 ---" << std::endl;

    print_container("d1 (initial values):", d1, epl_max);
    std::cout << std::format("d1.size(): {}", d1.size()) << std::endl;


    // Move the values to keep towards the front without changing the deque's size.
    // The returned range identifies the trailing elements to erase.
    std::cout << "\n--- Logical removal with std::ranges::remove ---" << std::endl;

    auto residual_elements = std::ranges::remove(d1, rem_val);

    print_container("d1 (after remove):", d1, epl_max);
    std::cout << std::format("d1.size(): {}", d1.size()) << std::endl;


    // The trailing values are unspecified and are not necessarily the removed values.
    std::cout << "\n--- Trailing range to erase ---" << std::endl;
    std::cout << "These trailing values are unspecified; they are not necessarily the removed values." << std::endl;

    print_container("residual_elements:", residual_elements, epl_max);
    std::cout << std::format("residual_elements.size(): {}", residual_elements.size()) << std::endl;


    // Erase the trailing range to reduce the deque's size.
    std::cout << "\n--- Erasing the trailing range with erase() ---" << std::endl;

    d1.erase(residual_elements.begin(), d1.end());

    print_container("d1 (after erase):", d1, epl_max);
    std::cout << std::format("d1.size(): {}", d1.size()) << std::endl;


    // Display the unchanged copy to demonstrate the second removal approach.
    std::cout << "\n--- Initial values of d2 ---" << std::endl;

    print_container("d2 (initial values):", d2, epl_max);
    std::cout << std::format("d2.size(): {}", d2.size()) << std::endl;


    // Remove every matching value in one call and return the number erased.
    std::cout << "\n--- Removing matching values directly with std::erase ---" << std::endl;

    auto erased_elements_number = std::erase(d2, rem_val);

    std::cout << "erased_elements_number: " << erased_elements_number << std::endl;

    print_container("d2 (after std::erase):", d2, epl_max);
    std::cout << std::format("d2.size(): {}", d2.size()) << std::endl;
}


int main(){

    std::cout << "Deque !!!"<<std::endl;

    deque_example_1();

    deque_example_2();

    deque_example_3();

    deque_example_4();

    deque_example_5();

    return 0;
}