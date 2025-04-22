### **Consequences of Missing `noexcept`**

When `noexcept` is missing from move constructors or move assignment operators, several issues can arise:

1. **Performance Impact**:
   - **Optimizations**: Without `noexcept`, the compiler cannot perform certain optimizations. For example, standard library containers like `std::vector` use `std::move_if_noexcept` to decide whether to move or copy elements. If the move constructor is not marked `noexcept`, the container may opt to copy elements instead, which can be less efficient [1](https://stackoverflow.com/questions/10787766/when-should-i-really-use-noexcept).
   - **Example**:
     ```cpp
     class MyClass {
     public:
         MyClass(MyClass&& other) { /* Move constructor */ }
         MyClass& operator=(MyClass&& other) { /* Move assignment operator */ }
     };
     ```

2. **Exception Safety**:
   - **std::terminate**: If an exception is thrown from a move constructor or move assignment operator that is not marked `noexcept`, it can lead to a call to `std::terminate`, abruptly ending the program [2](https://www.devgem.io/posts/understanding-noexcept-in-c-applications-and-considerations). This is because the standard library assumes that move operations are safe and will not throw exceptions.
   - **Example**:
     ```cpp
     class MyClass {
     public:
         MyClass(MyClass&& other) noexcept { /* Move constructor */ }
         MyClass& operator=(MyClass&& other) noexcept { /* Move assignment operator */ }
     };
     ```

3. **Code Clarity**:
   - **Intent**: Marking functions as `noexcept` provides a clear indication to both the compiler and other developers that the function is guaranteed not to throw exceptions [2](https://www.devgem.io/posts/understanding-noexcept-in-c-applications-and-considerations). This can improve code readability and maintainability.
   - **Example**:
     ```cpp
     class MyClass {
     public:
         MyClass(MyClass&& other) noexcept { /* Move constructor */ }
         MyClass& operator=(MyClass&& other) noexcept { /* Move assignment operator */ }
     };
     ```

### **Best Practices for Using Move Semantics**

1. **Use `noexcept` for Move Operations**:
   - Always mark move constructors and move assignment operators as `noexcept` to enable optimizations and ensure exception safety.
   - Example:
     ```cpp
     MyClass(MyClass&& other) noexcept;
     MyClass& operator=(MyClass&& other) noexcept;
     ```

2. **Test Thoroughly**:
   - Ensure that all code paths within `noexcept` functions are truly non-throwing. Use tools like static analyzers to verify this.
   - Example:
     ```cpp
     void foo() noexcept {
         // Ensure all operations here are non-throwing
     }
     ```

3. **Conditional `noexcept`**:
   - Use conditional `noexcept` expressions in templates to handle cases where template parameters might throw exceptions.
   - Example:
     ```cpp
     template <typename T>
     void bar(T&& t) noexcept(noexcept(T(std::forward<T>(t)))) {
         // Conditional noexcept based on T's constructor
     }
     ```

By understanding and applying these practices, you can effectively leverage move semantics to optimize performance and ensure robust exception handling in your C++ programs.

### **Example of `noexcept` in Action**

Let's create a class that manages a dynamic array and properly uses `noexcept` in its move constructor and move assignment operator.

```cpp
#include <iostream>
#include <utility> // For std::move

class MyArray {
public:
    MyArray(size_t size) : size(size), data(new int[size]) {
        std::cout << "Constructor called\n";
    }

    ~MyArray() {
        delete[] data;
    }

    // Move constructor
    MyArray(MyArray&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        std::cout << "Move constructor called\n";
    }

    // Move assignment operator
    MyArray& operator=(MyArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
            std::cout << "Move assignment operator called\n";
        }
        return *this;
    }

    void print() const {
        std::cout << "Size: " << size << "\n";
    }

private:
    size_t size;
    int* data;
};

int main() {
    MyArray arr1(10);
    MyArray arr2 = std::move(arr1); // Move constructor
    arr2.print();

    MyArray arr3(5);
    arr3 = std::move(arr2); // Move assignment operator
    arr3.print();

    return 0;
}
```

In this example, the move constructor and move assignment operator are marked with `noexcept`, indicating that they will not throw exceptions. This allows the compiler to optimize the code better and ensures that these operations are exception-safe.

### **Benefits of Using `noexcept`**

1. **Performance Optimizations**:
   - **Compiler Optimizations**: The compiler can perform certain optimizations when it knows that a function will not throw exceptions. For example, standard library containers like `std::vector` can use `std::move_if_noexcept` to decide whether to move or copy elements, leading to more efficient code.
   - **Example**:
     ```cpp
     class MyClass {
     public:
         MyClass(MyClass&& other) noexcept; // Allows optimizations
         MyClass& operator=(MyClass&& other) noexcept;
     };
     ```

2. **Exception Safety**:
   - **Preventing `std::terminate`**: If an exception is thrown from a move constructor or move assignment operator that is not marked `noexcept`, it can lead to a call to `std::terminate`, abruptly ending the program. Marking these functions as `noexcept` ensures that they are exception-safe.
   - **Example**:
     ```cpp
     class MyClass {
     public:
         MyClass(MyClass&& other) noexcept; // Ensures exception safety
         MyClass& operator=(MyClass&& other) noexcept;
     };
     ```

3. **Code Clarity**:
   - **Intent**: Marking functions as `noexcept` provides a clear indication to both the compiler and other developers that the function is guaranteed not to throw exceptions. This improves code readability and maintainability.
   - **Example**:
     ```cpp
     void foo() noexcept {
         // Clear indication that this function will not throw
     }
     ```

4. **Conditional `noexcept`**:
   - **Template Functions**: In template functions, `noexcept` can be conditionally applied based on the noexcept status of the operations performed within the function. This ensures that the function is as exception-safe as possible.
   - **Example**:
     ```cpp
     template <typename T>
     void bar(T&& t) noexcept(noexcept(T(std::forward<T>(t)))) {
         // Conditional noexcept based on T's constructor
     }
     ```

By using `noexcept` appropriately, you can enhance the performance, safety, and clarity of your C++ code.