#include <iostream>
#include <list>
#include <array>
#include "../01_BuildingBlocks/Helpers.h"


// Explore element access, insertion and removal in a list.
static void list_example_1() {

    std::cout << "\n========== List example 1: access, insertion and removal ==========" << std::endl;


    // Display the initial elements, size, first value and last value.
    std::cout << "\n--- Initial values: size(), front() and back() ---" << std::endl;

    std::list<int> l1{20, 30, 40, 50, 60, 70, 80};
    print_container("l1 (initial values): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;


    // Add one element at the front and another at the back.
    std::cout << "\n--- Adding elements with push_front() and push_back() ---" << std::endl;

    l1.push_front(10);
    l1.push_back(90);

    print_container("l1 (after push): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;


    // Move the iterator forward by half the list's size.
    // std::advance changes the iterator itself.
    std::cout << "\n--- Reaching the middle with std::advance ---" << std::endl;

    auto it_mid = l1.begin();
    std::advance(it_mid, l1.size()/2);

    std::cout<<"it_mid: "<<*it_mid<<std::endl;


    // Insert the array's elements before the element pointed to by it_mid.
    std::cout << "\n--- Inserting a range before the middle element ---" << std::endl;

    std::array<int,3> more_values{-40, -50, -60};
    l1.insert(it_mid, more_values.begin(), more_values.end());

    print_container("l1 (after insert): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;


    // Remove every occurrence of 40 and 70.
    std::cout << "\n--- Removing specific values with remove() ---" << std::endl;

    l1.remove(40);
    l1.remove(70);

    print_container("l1 (after remove): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;


    // Remove every value divisible by 60 using a lambda predicate.
    // The lambda uses [] for captures, () for parameters and {} for its body.
    std::cout << "\n--- Removing multiples of 60 with remove_if() ---" << std::endl;

    auto rem_pred = [](int x){ return x % 60 == 0; };
    l1.remove_if(rem_pred);

    print_container("l1 (after remove_if): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;


    // Remove the last element, then the first element.
    std::cout << "\n--- Removing elements with pop_back() and pop_front() ---" << std::endl;

    l1.pop_back();
    l1.pop_front();

    print_container("l1 (after pop): ", l1);
    std::cout<<"l1.size(): "<< l1.size()<<std::endl;
    std::cout<<"l1.front(): "<< l1.front()<<std::endl;
    std::cout<<"l1.back(): "<< l1.back()<<std::endl;
}


// Transfer elements between lists using splice().
static void list_example_2(){

    std::cout << "\n========== List example 2: transferring elements with splice() ==========" << std::endl;


    // Split the month names between two lists.
    std::cout << "\n--- Initial values of both lists ---" << std::endl;

    std::list<std::string> l1{"Jan", "Feb", "Mar", "Apr", "Sep", "Oct", "Nov", "Dec"};
    std::list<std::string> l2{"May", "Jun", "Jul", "Aug"};

    print_container("l1 (initial values): ", l1);
    print_container("l2 (initial values): ", l2);


    // Move the iterator from January to September, the insertion position.
    std::cout << "\n--- Locating the insertion position with std::advance ---" << std::endl;

    auto it_splice = l1.begin();
    std::cout<< "it_splice(initial value) : " << *it_splice<< std::endl;

    std::advance(it_splice, l1.size()/2);
    std::cout<< "it_splice(after advance) : " << *it_splice<< std::endl;


    // Transfer all elements from l2 into l1 before September.
    // l2 becomes empty, and it_splice still points to September.
    std::cout << "\n--- First splice: moving all elements from l2 into l1 ---" << std::endl;

    l1.splice(it_splice, l2);

    print_container("l1 (after 1st splice): ", l1);
    print_container("l2 (after 1st splice): ", l2);
    std::cout<< "it_splice(after splice) : " << *it_splice<< std::endl;


    // Transfer the full range of l1 to the beginning of l2.
    // l1 becomes empty.
    std::cout << "\n--- Second splice: moving the full range from l1 into l2 ---" << std::endl;

    l2.splice(l2.begin(), l1, l1.begin(), l1.end());

    print_container("l1 (after 2nd splice): ", l1);
    print_container("l2 (after 2nd splice): ", l2);
}


// Add matching elements from two lists and store the results in a third.
static void list_example_3(){

    std::cout << "\n========== List example 3: element-wise addition ==========" << std::endl;

    std::list<int> l1{10, 20, 30, 40, 50, 60, 70, 80 };
    std::list<int> l2{-1, -2, -3, -4, -5, -6, -7, -8};
    std::list<int> l3(l1.size());


    // Check that both input lists have the same number of elements.
    std::cout << "\n--- Checking that the input lists have equal lengths ---" << std::endl;

    if(l1.size() != l2.size()){
        throw std::runtime_error("The lists must have equal lengths. ");
    }


    // l3 initially contains zero-initialised elements.
    std::cout << "\n--- Initial values of the three lists ---" << std::endl;

    print_container("l1 (initial values): ", l1);
    print_container("l2 (initial values): ", l2);
    print_container("l3 (initial values): ", l3);


    // Use constant iterators to read l1 and l2, and a mutable iterator to write l3.
    std::cout << "\n--- Adding matching elements through iterators ---" << std::endl;

    auto it1 = l1.cbegin();
    auto it2 = l2.cbegin();
    auto it3 = l3.begin();

    // Store the sum at the current output position, then advance it3.
    for(; it1 != l1.cend(); ++it1, ++it2){
        *it3++ = *it1 + *it2;
    }

    print_container("l3 (after for loop): ", l3);
};


// Explore emplacement, sorting, merging and reversing.
static void list_example_4(){

    std::cout << "\n========== List example 4: emplacement, sorting and merging ==========" << std::endl;

    std::list<std::string> l1{};
    std::list<std::string> l2{};


    // Construct strings directly at the front or back of each list.
    std::cout << "\n--- Building both lists with emplace_front() and emplace_back() ---" << std::endl;

    l1.emplace_back(("Peru"));
    l2.emplace_back(("Argentina"));
    l1.emplace_front(("Chile"));
    l2.emplace_front(("Brazil"));

    l1.emplace_back(("Uruguay"));
    l2.emplace_back(("Paraguay"));
    l1.emplace_front(("Colombia"));
    l2.emplace_front(("Ecuador"));

    l1.emplace_back(("Bolivia"));
    l2.emplace_back(("Venezuela"));
    l1.emplace_front(("Panama"));
    l2.emplace_front(("Costa Rica"));

    l1.emplace_back(("Nicaragua"));
    l2.emplace_back(("Guyana"));
    l1.emplace_front(("French Guiana"));
    l2.emplace_front(("Suriname"));


    // Display both lists before sorting.
    std::cout << "\n--- Initial values of both lists ---" << std::endl;

    print_container("l1 (initial values): ", l1);
    print_container("l2 (initial values): ", l2);


    // Sort both lists alphabetically before merging.
    // merge() requires both lists to be sorted using the same ordering.
    std::cout << "\n--- Sorting both lists with list::sort ---" << std::endl;

    l1.sort();
    l2.sort();

    print_container("l1 (after sort): ", l1);
    print_container("l2 (after sort): ", l2);


    // Transfer l2's elements into l1 while preserving the sorted order.
    // l2 becomes empty.
    std::cout << "\n--- Merging l2 into l1 with list::merge ---" << std::endl;

    l1.merge(l2);

    print_container("l1 (after merge): ", l1);
    print_container("l2 (after merge): ", l2);


    // Reverse the current order without comparing values.
    std::cout << "\n--- Reversing l1 with list::reverse ---" << std::endl;

    l1.reverse();

    print_container("l1 (after reverse): ", l1);
}


int main() {

    std::cout << "Lists !!!" << std::endl;

    list_example_1();

    list_example_2();

    list_example_3();

    list_example_4();

    return 0;
}