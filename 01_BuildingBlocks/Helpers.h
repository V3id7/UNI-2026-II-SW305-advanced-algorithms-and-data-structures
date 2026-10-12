//
// Created by Alvaro Coronel on 9/21/2026.
//

#ifndef INC_2026_II_SW305_HELPERS_H
#define INC_2026_II_SW305_HELPERS_H

#include <iostream>

template <typename T>
static void print_container(const char *msg, T &container, size_t epl_max = 0) {
    if (msg != nullptr) {
        std::cout << msg << std::endl;
    }

    size_t epl{};
    size_t num_elem{};

    for (const auto &e : container) {
        ++num_elem;
        std::cout << e << " ";

        if (epl_max != 0) {
            if (++epl % epl_max == 0) {
                std::cout << std::endl;
            }
        }
    }

    if (num_elem == 0) {
        std::cout << "<empty>" << std::endl;
    }

    std::cout << std::endl;
}

#endif //INC_2026_II_SW305_HELPERS_H
