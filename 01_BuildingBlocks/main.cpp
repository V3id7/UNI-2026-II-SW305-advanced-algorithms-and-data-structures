#include <iostream>


// Swap two values of the same type using a temporary variable.
template<typename T>
void static Swap(T &a, T &b) {
    T tmp;

    tmp = a;

    a = b;

    b = tmp;

}


// Print each element of an integer array using its size.
static void Print2(int A[], size_t const size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << A[i] << " "<<std::endl;
    }
}


// Print each element using a range-based for loop.
template<typename T>
static void Print(const T& array) {
    for (auto element: array) {
        std::cout << element << " "<<std::endl;
    }
}


int main() {

    std::cout << "Building Blocks !!!" << std::endl;

    int A[] ={3,6};
    double B[] ={3.6,6.3};


    // Disabled example: print individual elements before and after swapping them.
    /**std::cout<<A[0]<<std::endl;
    std::cout<<A[1]<<std::endl;
    Swap(A[0],A[1]);
    std::cout<<A[0]<<std::endl;
    std::cout<<A[1]<<std::endl;



    std::cout<<B[0]<<std::endl;
    std::cout<<B[1]<<std::endl;
    Swap(B[0],B[1]);
    std::cout<<B[0]<<std::endl;
    std::cout<<B[1]<<std::endl;
    **/


    // Print the integer array, swap its two elements, and print it again.
    std::cout << "\n========== Integer array A ==========" << std::endl;

    std::cout << "\nBefore swapping:" << std::endl;
    //Print2(A,2):
    Print(A);

    std::cout << "\nSwapping A[0] and A[1]..." << std::endl;
    Swap(A[0], A[1]);

    std::cout << "\nAfter swapping:" << std::endl;
    Print(A);
    //Print2(A,2)


    // Repeat the same steps with the double array.
    std::cout << "\n========== Double array B ==========" << std::endl;

    std::cout << "\nBefore swapping:" << std::endl;
    //Print2(B,2):
    Print(B);

    std::cout << "\nSwapping B[0] and B[1]..." << std::endl;
    Swap(B[0], B[1]);

    std::cout << "\nAfter swapping:" << std::endl;
    Print(B);
    //Print2(B,2)

    return 0;
}