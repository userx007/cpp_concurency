
### 1. **Capturing Variables by Reference and Value**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int a = 10;
    int b = 20;

    auto lambda = a, &b mutable {
        a += 10; // Captured by value, so changes won't affect the original 'a'
        b += 10; // Captured by reference, so changes will affect the original 'b'
        std::cout << "Inside lambda: a = " << a << ", b = " << b << std::endl;
    };

    lambda();
    std::cout << "Outside lambda: a = " << a << ", b = " << b << std::endl;

    return 0;
}
```

### 2. **Using Lambdas with Standard Algorithms**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Using lambda with std::transform
    std::transform(vec.begin(), vec.end(), vec.begin(),  { return x * x; });

    std::cout << "Squared values: ";
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 3. **Lambda as a Comparator in Sorting**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    // Sorting by age using lambda
    std::sort(people.begin(), people.end(),  {
        return a.age < b.age;
    });

    std::cout << "Sorted by age: ";
    for (const auto &person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 4. **Capturing Everything by Reference**

```cpp
#include <iostream>

int main() {
    int x = 10;
    int y = 20;

    auto lambda = & {
        x += 5;
        y += 5;
        std::cout << "Inside lambda: x = " << x << ", y = " << y << std::endl;
    };

    lambda();
    std::cout << "Outside lambda: x = " << x << ", y = " << y << std::endl;

    return 0;
}
```

### 5. **Lambda with Multiple Statements**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Using lambda with multiple statements
    std::for_each(vec.begin(), vec.end(),  {
        x *= 2;
        std::cout << "Value doubled: " << x << std::endl;
    });

    return 0;
}
```

These examples demonstrate various ways to use lambdas in C++, including capturing variables, using lambdas with standard algorithms, sorting with lambdas, and more.

### Detailed Explanation of Lambda Expressions in C++

Lambda expressions are a feature in C++ that allow you to define anonymous functions directly in your code. They are particularly useful for short snippets of code that are used only once or a few times, such as in algorithms or event handlers. Here's a breakdown of their components:

#### **Syntax**

```cpp
capture -> return_type {
    // body
}
```

- **Capture**: Specifies which variables from the surrounding scope are accessible inside the lambda. It can capture by value (`[a]`), by reference (`[&a]`), or both (`[a, &b]`). You can also use `[=]` to capture all variables by value or `[&]` to capture all variables by reference.
- **Parameters**: The input parameters for the lambda function, similar to regular function parameters.
- **Return Type**: (Optional) Specifies the return type of the lambda. If omitted, the compiler will deduce it.
- **Body**: The code that gets executed when the lambda is called.

### Examples with STL Containers

#### **1. Using Lambda with `std::for_each`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::for_each(vec.begin(), vec.end(),  {
        x *= 2;
        std::cout << "Value doubled: " << x << std::endl;
    });

    return 0;
}
```

#### **2. Using Lambda with `std::transform`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> result(vec.size());

    std::transform(vec.begin(), vec.end(), result.begin(),  {
        return x * x;
    });

    std::cout << "Squared values: ";
    for (int v : result) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### **3. Using Lambda with `std::sort`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    std::sort(people.begin(), people.end(),  {
        return a.age < b.age;
    });

    std::cout << "Sorted by age: ";
    for (const auto &person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### **4. Using Lambda with `std::find_if`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    auto it = std::find_if(vec.begin(), vec.end(),  {
        return x > 3;
    });

    if (it != vec.end()) {
        std::cout << "First element greater than 3: " << *it << std::endl;
    } else {
        std::cout << "No element greater than 3 found." << std::endl;
    }

    return 0;
}
```

#### **5. Using Lambda with `std::accumulate`**

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    int sum = std::accumulate(vec.begin(), vec.end(), 0,  {
        return total + x;
    });

    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}
```

These examples show how lambda expressions can be used with various STL containers and algorithms to perform operations like transformation, sorting, finding elements, and accumulating values.

### Capturing Modes in Lambdas

Lambda expressions can capture variables from their surrounding scope in different ways. Here are the main capturing modes:

#### **1. Capture by Value (`[a]`)**

Captures the variable `a` by value. Any modifications to `a` inside the lambda do not affect the original variable.

```cpp
int a = 10;
auto lambda = a {
    std::cout << "Captured by value: " << a << std::endl;
};
lambda();
```

#### **2. Capture by Reference (`[&a]`)**

Captures the variable `a` by reference. Any modifications to `a` inside the lambda affect the original variable.

```cpp
int a = 10;
auto lambda = &a {
    a += 5;
    std::cout << "Captured by reference: " << a << std::endl;
};
lambda();
std::cout << "Outside lambda: " << a << std::endl;
```

#### **3. Capture All by Value (`[=]`)**

Captures all variables in the surrounding scope by value.

```cpp
int a = 10, b = 20;
auto lambda = = {
    std::cout << "Captured all by value: a = " << a << ", b = " << b << std::endl;
};
lambda();
```

#### **4. Capture All by Reference (`[&]`)**

Captures all variables in the surrounding scope by reference.

```cpp
int a = 10, b = 20;
auto lambda = & {
    a += 5;
    b += 5;
    std::cout << "Captured all by reference: a = " << a << ", b = " << b << std::endl;
};
lambda();
std::cout << "Outside lambda: a = " << a << ", b = " << b << std::endl;
```

#### **5. Mixed Capture (`[a, &b]`)**

Captures `a` by value and `b` by reference.

```cpp
int a = 10, b = 20;
auto lambda = a, &b {
    b += a;
    std::cout << "Mixed capture: a = " << a << ", b = " << b << std::endl;
};
lambda();
std::cout << "Outside lambda: b = " << b << std::endl;
```

### Using Lambda with Custom Data Structures

You can use lambda expressions with custom data structures just like with STL containers. Here are some examples:

#### **1. Custom Data Structure with `std::sort`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    std::sort(people.begin(), people.end(),  {
        return a.age < b.age;
    });

    std::cout << "Sorted by age: ";
    for (const auto &person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### **2. Custom Data Structure with `std::find_if`**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    auto it = std::find_if(people.begin(), people.end(),  {
        return p.age > 30;
    });

    if (it != people.end()) {
        std::cout << "First person older than 30: " << it->name << std::endl;
    } else {
        std::cout << "No person older than 30 found." << std::endl;
    }

    return 0;
}
```

#### **3. Custom Data Structure with `std::accumulate`**

```cpp
#include <iostream>
#include <vector>
#include <numeric>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    int totalAge = std::accumulate(people.begin(), people.end(), 0,  {
        return sum + p.age;
    });

    std::cout << "Total age: " << totalAge << std::endl;

    return 0;
}
```

These examples demonstrate how to use lambda expressions with custom data structures for sorting, finding elements, and accumulating values.

### Lambda Return Types in C++

Lambda expressions can have explicit or implicit return types. The return type specifies what type of value the lambda will return when called. Here are the details:

#### **Implicit Return Type**

If the return type is not specified, the compiler will deduce it based on the return statement within the lambda. This is often sufficient for simple lambdas.

```cpp
auto lambda =  {
    return x * 2; // Compiler deduces the return type as int
};
int result = lambda(5);
std::cout << "Result: " << result << std::endl;
```

#### **Explicit Return Type**

You can specify the return type explicitly using the `->` syntax. This is useful when you need to ensure a specific return type or when the lambda has complex logic.

```cpp
auto lambda =  -> double {
    return x * 2.5; // Explicitly specifying the return type as double
};
double result = lambda(5);
std::cout << "Result: " << result << std::endl;
```

### Examples with Different Return Types

#### **1. Returning a Simple Type**

```cpp
auto add =  -> int {
    return a + b;
};
int sum = add(3, 4);
std::cout << "Sum: " << sum << std::endl;
```

#### **2. Returning a Custom Type**

```cpp
struct Point {
    int x, y;
};

auto createPoint =  -> Point {
    return Point{x, y};
};
Point p = createPoint(3, 4);
std::cout << "Point: (" << p.x << ", " << p.y << ")" << std::endl;
```

#### **3. Returning a Container**

```cpp
#include <vector>

auto generateVector =  -> std::vector<int> {
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(i);
    }
    return vec;
};
std::vector<int> vec = generateVector(5);
std::cout << "Vector: ";
for (int v : vec) {
    std::cout << v << " ";
}
std::cout << std::endl;
```

#### **4. Returning a Lambda**

You can even return another lambda from a lambda, which can be useful for creating higher-order functions.

```cpp
auto createMultiplier =  -> std::function<int(int)> {
    return factor {
        return x * factor;
    };
};
auto multiplier = createMultiplier(3);
int result = multiplier(5);
std::cout << "Result: " << result << std::endl;
```

These examples illustrate how to use implicit and explicit return types in lambda expressions, including returning simple types, custom types, containers, and even other lambdas.

Using lambdas with smart pointers in C++ can be very powerful, especially for managing resources and ensuring proper cleanup. Here are some examples to illustrate how you can use lambdas with `std::unique_ptr` and `std::shared_ptr`.

### Example 1: Using Lambda with `std::unique_ptr`

`std::unique_ptr` is a smart pointer that owns and manages another object through a pointer and disposes of that object when the `std::unique_ptr` goes out of scope.

```cpp
#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_unique<int>(10);

    auto lambda =  {
        std::cout << "Value: " << *p << std::endl;
    };

    lambda(ptr);

    return 0;
}
```

### Example 2: Using Lambda with `std::shared_ptr`

`std::shared_ptr` is a smart pointer that retains shared ownership of an object through a pointer. Multiple `std::shared_ptr` instances can manage the same object.

```cpp
#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_shared<int>(20);

    auto lambda =  {
        std::cout << "Value: " << *p << std::endl;
    };

    lambda(ptr);

    return 0;
}
```

### Example 3: Capturing Smart Pointers in Lambdas

You can capture smart pointers in lambdas by value or by reference, depending on your needs.

#### **Capture by Value**

Capturing by value ensures that the lambda has its own copy of the smart pointer, which can be useful for ensuring the object stays alive as long as the lambda is alive.

```cpp
#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_shared<int>(30);

    auto lambda = ptr {
        std::cout << "Captured by value: " << *ptr << std::endl;
    };

    lambda();

    return 0;
}
```

#### **Capture by Reference**

Capturing by reference allows the lambda to access the original smart pointer, which can be useful for modifying the object or managing its lifetime more flexibly.

```cpp
#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_shared<int>(40);

    auto lambda = &ptr {
        *ptr += 10;
        std::cout << "Captured by reference: " << *ptr << std::endl;
    };

    lambda();
    std::cout << "Outside lambda: " << *ptr << std::endl;

    return 0;
}
```

### Example 4: Using Lambda with Custom Deleter

You can use lambdas as custom deleters for smart pointers, which can be useful for managing resources that require special cleanup.

```cpp
#include <iostream>
#include <memory>

struct Resource {
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

int main() {
    auto deleter =  {
        std::cout << "Custom deleter called\n";
        delete r;
    };

    std::unique_ptr<Resource, decltype(deleter)> ptr(new Resource, deleter);

    return 0;
}
```

These examples demonstrate how to use lambdas with smart pointers for various purposes, including capturing smart pointers, using custom deleters, and ensuring proper resource management.

### Custom Deleters in Detail

Custom deleters are functions or function objects that you can specify to manage the cleanup of resources when a smart pointer goes out of scope. This is particularly useful for resources that require special handling, such as file handles, network connections, or custom memory management.

#### **Why Use Custom Deleters?**

- **Special Cleanup**: Some resources need specific actions to be taken when they are no longer needed.
- **Avoid Memory Leaks**: Ensures proper cleanup of resources, preventing memory leaks.
- **Flexibility**: Allows you to define how resources should be released, which can be tailored to your application's needs.

#### **How to Define Custom Deleters**

Custom deleters can be defined using regular functions, function objects, or lambdas.

##### **Using Regular Functions**

```cpp
#include <iostream>
#include <memory>

void customDeleter(int* p) {
    std::cout << "Custom deleter called\n";
    delete p;
}

int main() {
    std::unique_ptr<int, decltype(&customDeleter)> ptr(new int(10), customDeleter);
    return 0;
}
```

##### **Using Function Objects**

```cpp
#include <iostream>
#include <memory>

struct CustomDeleter {
    void operator()(int* p) const {
        std::cout << "Custom deleter called\n";
        delete p;
    }
};

int main() {
    std::unique_ptr<int, CustomDeleter> ptr(new int(20));
    return 0;
}
```

##### **Using Lambdas**

```cpp
#include <iostream>
#include <memory>

int main() {
    auto deleter =  {
        std::cout << "Custom deleter called\n";
        delete p;
    };

    std::unique_ptr<int, decltype(deleter)> ptr(new int(30), deleter);
    return 0;
}
```

### Using Lambdas with Containers and Smart Pointers

Combining lambdas with containers and smart pointers can be very powerful for managing collections of resources. Here are some examples:

#### **Example 1: Using Lambda with `std::vector` and `std::unique_ptr`**

```cpp
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<int>> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::make_unique<int>(i));
    }

    auto print =  {
        std::cout << *p << " ";
    };

    std::for_each(vec.begin(), vec.end(), print);
    std::cout << std::endl;

    return 0;
}
```

#### **Example 2: Using Lambda with `std::map` and `std::shared_ptr`**

```cpp
#include <iostream>
#include <map>
#include <memory>

int main() {
    std::map<int, std::shared_ptr<int>> myMap;
    for (int i = 0; i < 5; ++i) {
        myMap[i] = std::make_shared<int>(i * 10);
    }

    auto print =  {
        std::cout << p.first << ": " << *p.second << std::endl;
    };

    std::for_each(myMap.begin(), myMap.end(), print);

    return 0;
}
```

#### **Example 3: Using Lambda with `std::vector` and Custom Deleter**

```cpp
#include <iostream>
#include <vector>
#include <memory>

struct Resource {
    Resource(int id) : id(id) { std::cout << "Resource " << id << " acquired\n"; }
    ~Resource() { std::cout << "Resource " << id << " released\n"; }
    int id;
};

int main() {
    auto deleter =  {
        std::cout << "Custom deleter called for Resource " << r->id << "\n";
        delete r;
    };

    std::vector<std::unique_ptr<Resource, decltype(deleter)>> vec;
    for (int i = 0; i < 3; ++i) {
        vec.emplace_back(new Resource(i), deleter);
    }

    return 0;
}
```

These examples demonstrate how to use custom deleters and lambdas with containers and smart pointers to manage resources effectively.

### Performance Implications of Using Lambdas in C++

Lambda expressions in C++ can have various performance implications, both positive and negative. Here are some key points to consider:

#### **1. **Inlining and Optimization**

Lambdas are essentially function objects, which means they can be inlined by the compiler. This can lead to better performance compared to regular function pointers, as the compiler can optimize the lambda more effectively [1](https://stackoverflow.com/questions/13722426/why-can-lambdas-be-better-optimized-by-the-compiler-than-plain-functions) [2](https://shaharmike.com/cpp/lambdas-and-functions/).

```cpp
auto lambda =  { return x * 2; };
std::vector<int> vec = {1, 2, 3, 4, 5};
std::transform(vec.begin(), vec.end(), vec.begin(), lambda);
```

#### **2. **Capture Overhead**

Capturing variables by value or reference can introduce overhead. Capturing by value involves copying the captured variables, which can be costly if the variables are large or complex [3](https://stackoverflow.com/questions/18619035/understanding-the-overhead-of-lambda-functions-in-c11). Capturing by reference can be more efficient but requires careful management to avoid dangling references.

```cpp
int a = 10;
auto lambda = a { return a * 2; }; // Captured by value
```

#### **3. **Type Erasure with `std::function`**

Using lambdas with `std::function` can introduce additional overhead due to type erasure. `std::function` provides a uniform interface for different callable objects, but this flexibility comes at the cost of performance [3](https://stackoverflow.com/questions/18619035/understanding-the-overhead-of-lambda-functions-in-c11).

```cpp
#include <functional>
std::function<int(int)> func =  { return x * 2; };
```

#### **4. **Memory Allocation**

Lambdas that capture variables may require dynamic memory allocation, especially if the captured variables are complex or if the lambda is used with `std::function`. This can lead to increased memory usage and potential performance degradation [3](https://stackoverflow.com/questions/18619035/understanding-the-overhead-of-lambda-functions-in-c11).

#### **5. **Comparison with Functors**

Lambdas can be more efficient than functors due to better compiler optimization opportunities. The transition from functors to lambdas in C++ has generally been seen as a move towards more expressive and efficient code [4](https://www.gyata.ai/c-plus-plus/lambda-functions).

### Using Lambdas with Containers and Smart Pointers

Combining lambdas with containers and smart pointers can be very powerful for managing collections of resources. Here are some examples:

#### **Example 1: Using Lambda with `std::vector` and `std::unique_ptr`**

```cpp
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<int>> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(std::make_unique<int>(i));
    }

    auto print =  {
        std::cout << *p << " ";
    };

    std::for_each(vec.begin(), vec.end(), print);
    std::cout << std::endl;

    return 0;
}
```

#### **Example 2: Using Lambda with `std::map` and `std::shared_ptr`**

```cpp
#include <iostream>
#include <map>
#include <memory>

int main() {
    std::map<int, std::shared_ptr<int>> myMap;
    for (int i = 0; i < 5; ++i) {
        myMap[i] = std::make_shared<int>(i * 10);
    }

    auto print =  {
        std::cout << p.first << ": " << *p.second << std::endl;
    };

    std::for_each(myMap.begin(), myMap.end(), print);

    return 0;
}
```

#### **Example 3: Using Lambda with `std::vector` and Custom Deleter**

```cpp
#include <iostream>
#include <vector>
#include <memory>

struct Resource {
    Resource(int id) : id(id) { std::cout << "Resource " << id << " acquired\n"; }
    ~Resource() { std::cout << "Resource " << id << " released\n"; }
    int id;
};

int main() {
    auto deleter =  {
        std::cout << "Custom deleter called for Resource " << r->id << "\n";
        delete r;
    };

    std::vector<std::unique_ptr<Resource, decltype(deleter)>> vec;
    for (int i = 0; i < 3; ++i) {
        vec.emplace_back(new Resource(i), deleter);
    }

    return 0;
}
```

These examples demonstrate how to use lambdas with containers and smart pointers to manage resources effectively.