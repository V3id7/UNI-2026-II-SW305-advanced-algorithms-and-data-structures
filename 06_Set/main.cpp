#include <iostream>
#include <set>
#include "../01_BuildingBlocks/Helpers.h"
#include <format>
#include <string>


// Explore set construction and insertion.
// epl_max sets the maximum number of elements printed per line.
static void set_example_1(){

    std::cout << "\n========== Set example 1: construction and insertion ==========" << std::endl;

    constexpr size_t epl_max{10};


    // A set stores unique values in ascending order by default.
    std::cout << "\n--- Creating an integer set ---" << std::endl;

    std::set<int> s1{20, 40, 100, 50, 90, 70, 10, 30};

    // Reuse this lambda to print the set and its size.
    auto print_resume = [&s1](const char* msg) -> void {
        print_container(msg, s1, epl_max);
        std::cout << std::format("s1.size(): {}", s1.size()) << std::endl;
    };

    // print_container("s1 (initial values):", s1, epl_max);
    // std::cout << std::format("s1.size(): {}", s1.size()) << std::endl;

    print_resume("s1 (initial values):");


    // insert() returns an iterator and a boolean indicating whether insertion occurred.
    // If the value already exists, the iterator points to that existing value.
    std::cout << "\n--- Inserting values with insert() ---" << std::endl;
    std::cout << "Each result shows (value, insertion succeeded)." << std::endl;

    std::array<int, 3> a1{80, 50, 60};

    for (auto val : a1) {
        auto p = s1.insert(val);
        std::cout << std::format("({:d}, {:s})", *p.first, p.second)
                  << std::endl;
    }

    // print_container("s1 (after insertions):", s1, epl_max);

    print_resume("s1 (after insertions): ");


    // Create a string set; names are stored in ascending lexicographical order.
    std::cout << "\n--- Creating a string set ---" << std::endl;

    std::set<std::string> s2{"New york", "Los Angeles", "Chicago", "Houston", "Phoenix", "Philadelphia", "San Antonio", "San Diego"};

    auto print_resume2 = [&s2](const char* msg) -> void {
        print_container(msg, s2, epl_max);
        std::cout << std::format("s2.size(): {}", s2.size()) << std::endl;
    };

    print_resume2("s2 (initial values):");


    // emplace() constructs an element in the set if no equivalent value exists.
    std::cout << "\n--- Adding names with emplace() ---" << std::endl;
    std::cout << "Each result shows (value, insertion succeeded)." << std::endl;

    std::array<std::string, 3> a2{"Dallas", "Phoenix", "Austin"};

    for(const auto& val : a2){
        auto p = s2.emplace(val);
        std::cout<<std::format("({:s},{:s})", *p.first, p.second)<<std::endl;
    }

    print_resume2("s2 (after emplacements):");
}


// Use a custom ordering and explore range insertion and iteration.
static void set_example_2(){

    std::cout << "\n========== Set example 2: descending order and range insertion ==========" << std::endl;

    constexpr size_t epl_max{10};


    // std::greater stores the names in descending lexicographical order.
    std::cout << "\n--- Creating a set with std::greater ---" << std::endl;

    std::set<std::string, std::greater<std::string>> s1{
            "California", "Texas", "Florida",
            "New York", "Pennsylvania", "Illinois", "Ohio"
    };

    auto print_resume = [&s1](const char* msg) -> void {
        print_container(msg, s1, epl_max);
        std::cout << std::format("s1.size(): {}", s1.size())
                  << std::endl;
    };

    print_resume("s1 (initial values):");


    // Insert the array's values; existing values are not duplicated.
    std::cout << "\n--- Inserting an iterator range ---" << std::endl;

    std::array<std::string, 4> a1{"Georgia", "Florida", "North Carolina", "Michigan"};
    s1.insert(a1.begin(), a1.end());

    print_resume("s1 (after insertion):");


    // Use insert_range() only when the library provides container range operations.
    std::cout << "\n--- Checking support for insert_range() ---" << std::endl;

#ifdef __cpp_lib_containers_ranges
    std::array<std::string, 3> a2{"South Carolina", "Vermont", "Indiana"};
    s1.insert_range(a2);
    print_resume("s1 (after insert_range):");
#else
    std::cout << "std::set::insert_range() requires C++23" << std::endl;
#endif


    // Iterate in the set's configured order.
    // Set elements cannot be modified through iterators.
    std::cout << "\n--- Reading elements through iterators ---" << std::endl;

    for(auto it = s1.begin(); it != s1.end(); ++it){
        //it*= += "test"; // Modifying an element through a set iterator is not allowed.
        std::cout<<std::format("{:s}", *it)<<std::endl;
    }
}


// Compare sets as ordered sequences, rather than as mathematical subsets.
static void set_example_3(){

    std::cout << "\n========== Set example 3: relational comparisons ==========" << std::endl;

    constexpr size_t epl_max{10};

    std::set<int> s1{100, 200, 300, 400, 500, 600};
    std::set<int> s2{100, 200, 150, 400, 500, 600};
    std::set<int> s3{100, 200, 300, 400, 500, 600};
    std::set<int> s4{100, 200, 300, 450, 500, 600};


    // Display the ascending sequences used in the comparisons.
    std::cout << "\n--- Initial values of the ascending sets ---" << std::endl;

    print_container("s1 (initial values):", s1, epl_max);
    print_container("s2 (initial values):", s2, epl_max);
    print_container("s3 (initial values):", s3, epl_max);
    print_container("s4 (initial values):", s4, epl_max);
    std::cout<<std::endl;


    // Ordering comparisons use the first differing pair of elements.
    std::cout << "--- Comparing s1 and s2 ---" << std::endl;

    std::cout<<std::format("s1 == s2: {:s}", s1 == s2)<<std::endl;
    std::cout<<std::format("s1 != s2: {:s}", s1 != s2)<<std::endl;
    std::cout<<std::format("s1 < s2: {:s}", s1 < s2)<<std::endl;
    std::cout<<std::format("s1 <= s2: {:s}", s1 <= s2)<<std::endl;
    std::cout<<std::format("s1 > s2: {:s}", s1 > s2)<<std::endl;
    std::cout<<std::format("s1 >= s2: {:s}", s1 >= s2)<<std::endl;

    std::cout<<std::endl;


    // These two sets contain identical sequences.
    std::cout << "--- Comparing s1 and s3 ---" << std::endl;

    std::cout<<std::format("s1 == s3: {:s}", s1 == s3)<<std::endl;
    std::cout<<std::format("s1 < s3: {:s}", s1 < s3)<<std::endl;
    std::cout<<std::format("s1 > s3: {:s}", s1 > s3)<<std::endl;

    std::cout<<std::endl;


    // The first difference is 400 in s1 versus 450 in s4.
    std::cout << "--- Comparing s1 and s4 ---" << std::endl;

    std::cout<<std::format("s1 == s4: {:s}", s1 == s4)<<std::endl;
    std::cout<<std::format("s1 < s4: {:s}", s1 < s4)<<std::endl;
    std::cout<<std::format("s1 > s4: {:s}", s1 > s4)<<std::endl;


    // Define a type alias for sets that store integers in descending order.
    std::cout << "\n--- Creating descending sets with a type alias ---" << std::endl;

    using set_t = std::set<int, std::greater<int>>;
    set_t s5 {100, 300, 400, 200, 500};
    set_t s6 {100, 300, 400, 200, 680};
    set_t s7 {100, 300, 400, 200, 500};

    std::cout<<std::endl;
    print_container("s5 (initial values):", s5, epl_max);
    print_container("s6 (initial values):", s6, epl_max);
    print_container("s7 (initial values):", s7, epl_max);

    std::cout<<std::endl;


    // Relational operators compare the stored sequences using element comparisons.
    // std::greater controls storage order, not the meaning of operator<.
    std::cout << "--- Comparing s5 and s6 ---" << std::endl;

    std::cout<<std::format("s5 == s6: {:s}", s5 == s6)<<std::endl;
    std::cout<<std::format("s5 < s6: {:s}", s5 < s6)<<std::endl;
    std::cout<<std::format("s5 > s6: {:s}", s5 > s6)<<std::endl;

    std::cout<<std::endl;


    // Both descending sets contain identical sequences.
    std::cout << "--- Comparing s5 and s7 ---" << std::endl;

    std::cout<<std::format("s5 == s7: {:s}", s5 == s7)<<std::endl;
    std::cout<<std::format("s5 < s7: {:s}", s5 < s7)<<std::endl;
    std::cout<<std::format("s5 > s7: {:s}", s5 > s7)<<std::endl;
}


// Find and erase selected values, then check membership with contains().
static void set_example_4() {

    std::cout << "\n========== Set example 4: searching and erasing ==========" << std::endl;

    constexpr size_t epl_max{10};


    // Create the string set used for the searches.
    std::cout << "\n--- Initial values ---" << std::endl;

    std::set<std::string> s1{"Wyoming", "Vermont", "Chicago", "Alaska", "North Dakota",  "South Dakota", "Delaware", "Rhode Island", "Montana", "Maine"};

    print_container("s1 (initial values): ", s1, epl_max);


    // find() returns an iterator to the value, or end() if it is absent.
    // Erase a value only when the search succeeds.
    std::cout << "\n--- Finding values and erasing matches ---" << std::endl;

    std::array<std::string, 4> find_vals {"New Hampshire", "Alaska", "Hawaii", "Maine"};

    for(const auto& find_val: find_vals){
        std::cout << std::format("s1.find({:s})", find_val);
        auto it = s1.find(find_val);

        if (it != s1.end()){
            s1.erase(it);
            std::cout<<" - removed!";
        }else{
            std::cout<<" - not found";
        }

        std::cout<<std::endl;
    }

    print_container("s1 (after erase operation): ", s1, epl_max);


    // contains() reports whether a value exists without modifying the set.
    std::cout << "\n--- Checking membership with contains() ---" << std::endl;

    std::array<std::string, 3> contains_vals {"Kansas", "South Dakota", "Nebraska"};

    for(const auto& contains_val: contains_vals){
        bool b = s1.contains(contains_val);
        std::cout<<std::format("s1.contains({:s}) : {:s}", contains_val, b)<<std::endl;
    }
}


// Transfer unique values between sets and clear the destination.
static void set_example_5() {

    std::cout << "\n========== Set example 5: merging and clearing ==========" << std::endl;

    // Allow numerical constants to be written without the std::numbers prefix.
    using namespace std::numbers;


    // Create two sets with some shared numerical constants.
    std::cout << "\n--- Initial values of both sets ---" << std::endl;

    std::set<double> s1{pi, e, inv_pi, sqrt2};
    std::set<double> s2{sqrt2, phi, pi, sqrt3, log2e};

    print_container("s1(initial values) : ", s1);
    print_container("s2(initial values) : ", s2);


    // Transfer values from s2 only when s1 has no equivalent value.
    // Shared values remain in s2 because a set does not accept duplicates.
    std::cout << "\n--- Merging s2 into s1 ---" << std::endl;

    s1.merge(s2);

    std::cout<<std::endl;
    print_container("s1(after merge) : ", s1);
    print_container("s2(after merge) : ", s2);


    // Clear s1; the remaining elements of s2 are unaffected.
    std::cout << "\n--- Clearing s1 ---" << std::endl;

    s1.clear();

    std::cout<<std::endl;
    print_container("s1(after clear) : ", s1);
    print_container("s2(after clear) : ", s2);

}


// Explore insertion and counting in a multiset, which accepts duplicates.
static void multiset_example_6() {

    std::cout << "\n========== Multiset example 6: insertion and counting ==========" << std::endl;

    constexpr size_t epl_max{10};

    std::multiset<int> ms1{20, 40, 100, 50, 90, 70, 10, 80, 30};

    auto print_resume = [&ms1](const char* msg) -> void {
        print_container(msg, ms1, epl_max);
        std::cout << std::format("ms1.size(): {}", ms1.size())
                  << std::endl;
    };


    std::cout << "\n--- Initial values ---" << std::endl;

    print_resume("ms1 (initial values):");


    // Insert all values, including additional occurrences of 90 and 80.
    std::cout << "\n--- Inserting values, including duplicates ---" << std::endl;

    ms1.insert(110);
    ms1.insert(90);
    ms1.insert(80);
    ms1.insert(60);

    print_resume("ms1 (after inserts): ");


    // Count how many elements have the requested value.
    std::cout << "\n--- Counting occurrences with count() ---" << std::endl;

    int count_val {80};
    auto n = ms1.count(count_val);

    std::cout<< std::format("ms1.count({:d}): {}", count_val, n)<<std::endl;
}


// Explore emplacement and two ways to erase elements from a multiset.
static void multiset_example_7(){

    std::cout << "\n========== Multiset example 7: emplacement and erasure ==========" << std::endl;

    constexpr size_t epl_max{10};

    std::multiset<std::string, std::greater<std::string>> ms1{"Pittsburg", "Atlanta", "Charlotte", "Denver", "Seatle", "Miami", "Atlanta", "Dallas", "Denver", "Boise"};

    auto print_resume = [&ms1](const char* msg) -> void {
        print_container(msg, ms1, epl_max);
        std::cout << std::format("ms1.size(): {}", ms1.size())
                  << std::endl;
    };


    // Values are stored in descending order, including duplicates.
    std::cout << "\n--- Initial values ---" << std::endl;

    print_resume("ms1 (initial values): ");


    // Construct additional elements; duplicate names are accepted.
    std::cout << "\n--- Adding names with emplace() ---" << std::endl;

    ms1.emplace("Portland");
    ms1.emplace("Atlanta");
    ms1.emplace("Cleveland");
    ms1.emplace("Detroid");

    std::cout<<std::endl;
    print_resume("ms1 (after emplacements): ");


    // Erasing by key removes every occurrence of that value.
    std::cout << "\n--- Erasing every occurrence of Atlanta ---" << std::endl;

    ms1.erase("Atlanta");

    std::cout<<std::endl;
    print_resume("ms1 (after erase): ");


    // Erase names beginning with D.
    // erase(it) returns the next iterator, allowing the loop to continue safely.
    std::cout << "\n--- Erasing names beginning with D using a loop ---" << std::endl;

    auto it = ms1.begin();

    while(it != ms1.end()){
        if ((*it)[0] == 'D' ) {
            it = ms1.erase(it);
        }else{
            ++it;
        }
    }

    std::cout<<std::endl;
    print_resume("ms1 (after erase with a loop): ");
}


int main(){

    std::cout<<"Set !!!"<<std::endl;

    set_example_1();

    set_example_2();

    set_example_3();

    set_example_4();

    set_example_5();

    multiset_example_6();

    multiset_example_7();

    return 0;
}