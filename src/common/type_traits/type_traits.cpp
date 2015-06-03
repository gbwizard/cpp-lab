#include <iostream>

//! @brief is_void type trait
template <typename T>
struct is_void {
    static const bool value = false;
};

template <>
struct is_void<void> {
    static const bool value = true;
};

//! @brief is_pointer type trait
template <typename T>
struct is_pointer {
    static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

int main(int argc, char* argv[]) {
    std::cout << "is_void type trait:" << std::endl;
    std::cout << std::boolalpha << "is_void<int>::value = " << is_void<int>::value << std::endl;
    std::cout << std::boolalpha << "is_void<void>::value = " << is_void<void>::value << std::endl;

    std::cout << "is_pointer type trait:" << std::endl;
    std::cout << std::boolalpha << "is_pointer<void>::value = " << is_pointer<void>::value << std::endl;
    std::cout << std::boolalpha << "is_pointer<int>::value = " << is_pointer<int>::value << std::endl;
    std::cout << std::boolalpha << "is_pointer<int*>::value = " << is_pointer<int*>::value << std::endl;
}
