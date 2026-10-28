#ifndef INC_2026_II_SW305_HELPERS_H
#define INC_2026_II_SW305_HELPERS_H

#include <iostream>
#include <map>
#include <format>


// Print the container's elements, with an optional message and limit per line.
// Set epl_max to 0 to print all elements on one line.
template <typename T>
static void print_container(const char *msg, const T &container, size_t epl_max = 0) {

    // Print the message if one was provided.
    if (msg != nullptr) {
        std::cout << msg << std::endl;
    }

    // Indicate that the container is empty and stop printing.
    if(container.empty()){
        std::cout<<"<empty>"<<std::endl;
        return;
    }

    // epl counts the elements printed; epl_max sets the elements per line.
    size_t epl{};

    for (const auto &e : container) {

        std::cout << e << " ";

        // Start a new line whenever the element count reaches a multiple of epl_max.
        if (epl_max != 0) {
            if (++epl % epl_max == 0) {
                std::cout << std::endl;
            }
        }
    }

    // End the final line unless the loop already ended it.
    if(epl_max==0 || container.size() % epl_max != 0){
        std::cout << std::endl;
    }

}


// Print each multimap entry as a (key, value) pair.
// Set epl_max to 0 to print all pairs on one line.
template <typename T, typename U>
void print_multimap(const char* msg,const std::multimap<T, U>& container, size_t epl_max = 0) {

    // Print the message if one was provided.
    if (msg != nullptr) {
        std::cout << msg << std::endl;
    }

    // Indicate that the multimap is empty and stop printing.
    if (container.empty()) {
        std::cout << "<empty>" << std::endl;
        return;
    }

    // Count the pairs printed to control line breaks.
    size_t epl{0};

    for (const auto& [key, value] : container) {
        std::cout << std::format("({}, {}) ", key, value) ;

        // Start a new line after each group of epl_max pairs.
        if (epl_max != 0) {
            if (++epl % epl_max == 0) {
                std::cout << std::endl;
            }
        }
    }

    // End the final line unless the loop already ended it.
    if (epl_max == 0 || container.size() % epl_max != 0) {
        std::cout << std::endl;
    }
}


// Copy the map entries into a multimap to reuse print_multimap.
template <typename T, typename U>
void print_map(const char *msg, const std::map<T, U> &container, size_t epl_max =0){

    std::multimap<T, U> map(container.begin(), container.end());

    print_multimap(msg, map, epl_max);
}


#endif //INC_2026_II_SW305_HELPERS_H
