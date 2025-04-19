Lambda captures in C++ allow lambdas to access variables from their surrounding scope.
There are several ways to capture variables, each with different implications. Let's dive into the details:

### 1. **Capture by Value**
When you capture a variable by value, the lambda makes a copy of the variable. Changes to the variable inside the lambda do not affect the original variable outside the lambda.
```cpp
int x = 10;
auto lambda = x { return x + 5; };
x = 20;
int result = lambda(); // result is 15, because x was captured by value
```

### 2. **Capture by Reference**
Capturing by reference allows the lambda to access and modify the original variable.
```cpp
int x = 10;
auto lambda = &x { x += 5; };
lambda();
int result = x; // result is 15, because x was captured by reference and modified
```

### 3. **Capture All Variables by Value**
You can capture all variables in the surrounding scope by value using `[=]`. This is useful when you need to access multiple variables without specifying each one individually.
```cpp
int a = 1, b = 2, c = 3;
auto lambda = = { return a + b + c; };
int result = lambda(); // result is 6
```

### 4. **Capture All Variables by Reference**
Similarly, you can capture all variables by reference using `[&]`.
```cpp
int a = 1, b = 2, c = 3;
auto lambda = & { a += b + c; };
lambda();
int result = a; // result is 6, because a was modified
```

### 5. **Mixed Captures**
You can mix capture methods to capture some variables by value and others by reference.
```cpp
int a = 1, b = 2, c = 3;
auto lambda = a, &b, &c { b += a + c; };
lambda();
int result = b; // result is 6, because b was modified
```

### 6. **Default Capture Mode with Specific Captures**
You can specify a default capture mode and override it for specific variables.
```cpp
int a = 1, b = 2, c = 3;
auto lambda = =, &b { b += a + c; };
lambda();
int result = b; // result is 6, because b was captured by reference and modified
```

### 7. **Mutable Lambdas**
By default, lambdas that capture variables by value are const. To modify captured values, you need to use the `mutable` keyword.
```cpp
int x = 10;
auto lambda = x mutable { x += 5; return x; };
int result = lambda(); // result is 15, but x outside the lambda is still 10
```

### 8. **Capturing `this` Pointer**
In member functions, you can capture the `this` pointer to access member variables and functions.
```cpp
class MyClass {
public:
    int value = 10;
    void do_something() {
        auto lambda = this { value += 5; };
        lambda();
    }
};

MyClass obj;
obj.do_something();
int result = obj.value; // result is 15, because value was modified
```

### 9. **Capturing by Move**
You can capture variables by move, which is useful for capturing unique pointers or other move-only types.
```cpp
std::unique_ptr<int> ptr = std::make_unique<int>(10);
auto lambda = p = std::move(ptr) { return *p + 5; };
int result = lambda(); // result is 15
```

These examples cover various ways to capture variables in C++ lambdas. Do you have any specific questions or scenarios you'd like to explore further?