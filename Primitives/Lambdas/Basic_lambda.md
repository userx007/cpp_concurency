Sure! Here are some examples of C++ lambdas for various situations:

### 1. Basic Lambda
A simple lambda that takes two integers and returns their sum:
```cpp
auto sum =  { return a + b; };
int result = sum(3, 4); // result is 7
```

### 2. Lambda with Captures
A lambda that captures a variable from the surrounding scope:
```cpp
int factor = 2;
auto multiply = factor { return a * factor; };
int result = multiply(5); // result is 10
```

### 3. Lambda with Mutable Capture
A lambda that modifies a captured variable:
```cpp
int count = 0;
auto increment = &count mutable { count++; };
increment();
increment();
// count is now 2
```

### 4. Lambda as a Predicate
Using a lambda as a predicate in a standard algorithm:
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};
auto is_even =  { return n % 2 == 0; };
auto even_numbers = std::count_if(numbers.begin(), numbers.end(), is_even); // even_numbers is 2
```

### 5. Lambda with Return Type
Specifying the return type of a lambda explicitly:
```cpp
auto divide =  -> double {
    if (b == 0) throw std::runtime_error("Division by zero");
    return static_cast<double>(a) / b;
};
double result = divide(10, 2); // result is 5.0
```

### 6. Lambda in a Function
Passing a lambda to a function:
```cpp
void apply_to_each(const std::vector<int>& vec, const std::function<void(int)>& func) {
    for (int v : vec) {
        func(v);
    }
}

std::vector<int> values = {1, 2, 3, 4, 5};
apply_to_each(values,  { std::cout << v << " "; }); // prints: 1 2 3 4 5
```

### 7. Lambda for Sorting
Using a lambda to sort a collection:
```cpp
std::vector<int> numbers = {5, 3, 1, 4, 2};
std::sort(numbers.begin(), numbers.end(),  { return a < b; });
// numbers is now {1, 2, 3, 4, 5}
```

### 8. Recursive Lambda
Creating a recursive lambda:
```cpp
std::function<int(int)> factorial = & -> int {
    return (n <= 1) ? 1 : n * factorial(n - 1);
};
int result = factorial(5); // result is 120
```

### 9. Lambda with Default Arguments
A lambda with default arguments:
```cpp
auto greet =  { std::cout << "Hello, " << name << "!\n"; };
greet(); // prints: Hello, World!
greet("Alice"); // prints: Hello, Alice!
```

### 10. Lambda in a Class
Using a lambda within a class:
```cpp
class MyClass {
public:
    void do_something() {
        auto print_message = this { std::cout << "Message from MyClass\n"; };
        print_message();
    }
};

MyClass obj;
obj.do_something(); // prints: Message from MyClass
```

