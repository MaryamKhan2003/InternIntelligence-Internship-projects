# **C/C++ Math and Data Structure Library**
This repository contains a comprehensive C/C++ library designed to provide essential mathematical computations and fundamental data structures. It's built with reusability and clear API design in mind, making it easy to integrate into various C++ projects.

##  **Features**
*Mathematical Utilities (MathUtils):*

Calculate factorials of non-negative integers.

Determine if a number is prime.

Compute the greatest common divisor (GCD) of two integers.

Calculate the power of a base raised to an exponent.

Generic Stack Data Structure (Stack):

A templated Last-In, First-Out (LIFO) data structure.

Supports push, pop, peek, isEmpty, and isFull operations.

Handles overflow_error and underflow_error for robust usage.

 ### **Getting Started**
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

 #### **Prerequisites**
You will need a C++ compiler installed on your system. Popular choices include:

GCC (GNU Compiler Collection): g++

Clang: clang++

#####  **File Structure**
The library is organized into distinct header (.h) and source (.cpp) files for each module:

.
├── MathUtils.h         // Header for mathematical utility functions
├── MathUtils.cpp       // Implementation of mathematical utility functions
├── Stack.h             // Header for the templated Stack data structure
├── Stack.cpp           // Implementation of the templated Stack (see note below)
├── main_math.cpp       // Example usage and testing for MathUtils
├── main_stack.cpp      // Example usage and testing for Stack
└── README.md           // This file

Note on Stack.cpp: For templated classes in C++, it's common practice to include the implementation directly within the header file (Stack.h) to simplify compilation. If you encounter linker errors related to Stack, consider moving the contents of Stack.cpp into Stack.h or explicitly including Stack.cpp in your compilation unit (as shown in the main_stack.cpp example).

######  **Compilation**
To compile and run the example applications, navigate to the root directory of the library in your terminal.

Compiling MathUtils Example (main_math.cpp)
g++ -std=c++11 MathUtils.cpp main_math.cpp -o math_example
./math_example

Compiling Stack Example (main_stack.cpp)
g++ -std=c++11 main_stack.cpp -o stack_example
./stack_example

Combined Compilation (for both modules in one application):

If you have a single main.cpp that uses both modules, you can compile them together:

g++ -std=c++11 MathUtils.cpp main.cpp -o my_application
./my_application

**Usage**
*Using MathUtils*
Include MathUtils.h in your source file and use the functions within the MathUtils namespace.

// Example: main_math.cpp
#include <iostream>
#include "MathUtils.h" // Include the header for MathUtils

int main() {
    // Option 1: Use fully qualified names
    std::cout << "Factorial(5) = " << MathUtils::factorial(5) << std::endl;

    // Option 2: Use the namespace for convenience
    using namespace MathUtils;
    std::cout << "IsPrime(17) = " << (isPrime(17) ? "Yes" : "No") << std::endl;
    std::cout << "GCD(48, 18) = " << gcd(48, 18) << std::endl;
    std::cout << "Power(3, 4) = " << power(3, 4) << std::endl;

    // Test edge cases
    std::cout << "Factorial(0) = " << factorial(0) << std::endl; // Expected: 1
    std::cout << "IsPrime(1) = " << (isPrime(1) ? "Yes" : "No") << std::endl;   // Expected: No
    std::cout << "GCD(10, 0) = " << gcd(10, 0) << std::endl;     // Expected: 10
    std::cout << "Power(2, 0) = " << power(2, 0) << std::endl;   // Expected: 1

    return 0;
}

*Using Stack*
Include Stack.h and (if separate) Stack.cpp in your source file. Remember to specify the data type for the stack.

// Example: main_stack.cpp
#include <iostream>
#include <string>
#include <stdexcept> // For catching exceptions
#include "Stack.h"
#include "Stack.cpp" // Include the implementation for template instantiation (or merge into Stack.h)

int main() {
    // Example with integers
    Stack<int> intStack(3); // Stack with capacity 3

    try {
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        std::cout << "Int Stack Top: " << intStack.peek() << std::endl; // Expected: 30

        // Attempt to push to a full stack (uncomment to test overflow)
        // intStack.push(40); // This would throw std::overflow_error

        std::cout << "Popping from int stack: " << intStack.pop() << std::endl; // Expected: 30
        std::cout << "Popping from int stack: " << intStack.pop() << std::endl; // Expected: 20
        std::cout << "Int Stack Empty? " << (intStack.isEmpty() ? "Yes" : "No") << std::endl; // Expected: No
        std::cout << "Popping from int stack: " << intStack.pop() << std::endl; // Expected: 10

        std::cout << "Int Stack Empty? " << (intStack.isEmpty() ? "Yes" : "No") << std::endl; // Expected: Yes

        // Attempt to pop from an empty stack (uncomment to test underflow)
        // intStack.pop(); // This would throw std::underflow_error

    } catch (const std::overflow_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::underflow_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::exception& e) { // Catch any other standard exceptions
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    std::cout << "\n--- String Stack Example ---" << std::endl;
    Stack<std::string> stringStack(2);
    try {
        stringStack.push("Hello");
        stringStack.push("World");
        std::cout << "String Stack Top: " << stringStack.peek() << std::endl; // Expected: World
        stringStack.pop();
        std::cout << "String Stack Top after pop: " << stringStack.peek() << std::endl; // Expected: Hello
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

 ###### **API Reference**
For a detailed breakdown of all functions and methods available in this library, including their parameters, return values, and specific behaviors, please refer to the Comprehensive User Documentation.

MathUtils Namespace:

int factorial(int n)

bool isPrime(int n)

int gcd(int a, int b)

int power(int base, int exp)

Stack<T> Class:

Stack(int size = 100) (Constructor)

~Stack() (Destructor)

void push(T value)

T pop()

T peek() const

bool isEmpty() const

bool isFull() const

######  **Testing**
The main_math.cpp and main_stack.cpp files serve as basic test suites for their respective modules. They demonstrate various scenarios, including edge cases and error handling for the Stack.

To run the tests, simply compile and execute the example files as described in the Compilation section.

 ###### **Contributing**
Contributions are welcome! If you have suggestions for improvements, new features, or bug fixes, please feel free to:

Fork the repository.

Create a new branch (git checkout -b feature/YourFeature).

Make your changes.

Commit your changes (git commit -m 'Add some feature').

Push to the branch (git push origin feature/YourFeature).

Open a Pull Request.

