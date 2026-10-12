#include <iostream>
template<typename T>
void static Swap(T &a, T &b) {
    T tmp;

    tmp = a;

    a = b;

    b = tmp;

}

static void Print2(int A[], size_t const size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << A[i] << " "<<std::endl;
    }
}
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


    //Print2(A,2):
    Print(A);
    Swap(A[0], A[1]);
    Print(A);
    //Print2(A,2)

    //Print2(B,2):
    Print(B);
    Swap(B[0], B[1]);
    Print(B);
    //Print2(B,2)

    return 0;
}