Using lambdas can be quite handy, but there are some common pitfalls to watch out for:

1. **Readability**: Lambdas can make code harder to read, especially if overused or used in complex expressions. It's often better to use named functions for clarity.

2. **Debugging**: Debugging lambdas can be challenging since they don't have names. This can make stack traces harder to interpret.

3. **Performance**: Lambdas can sometimes introduce performance overhead, particularly if they capture variables from their enclosing scope.

4. **Scope and Lifetime**: Be cautious with lambdas capturing variables by reference. This can lead to issues if the lambda outlives the variable it references.

5. **Complexity**: Using lambdas for complex logic can make the code harder to maintain. It's usually better to keep lambdas simple and straightforward.

Sure! Here are some examples illustrating the common pitfalls when using lambdas:

1. **Readability**:
   ```python
   # Complex lambda expression
   result = map(lambda x: x**2 + 2*x + 1, range(10))
   # Named function for clarity
   def quadratic(x):
       return x**2 + 2*x + 1
   result = map(quadratic, range(10))
   ```

2. **Debugging**:
   ```python
   # Lambda in a stack trace
   result = filter(lambda x: x > 5, range(10))
   # Named function in a stack trace
   def is_greater_than_five(x):
       return x > 5
   result = filter(is_greater_than_five, range(10))
   ```

3. **Performance**:
   ```python
   # Lambda capturing a variable
   y = 10
   result = map(lambda x: x + y, range(10))
   # Named function without capturing
   def add_ten(x):
       return x + 10
   result = map(add_ten, range(10))
   ```

4. **Scope and Lifetime**:
   ```python
   # Lambda capturing a variable by reference
   def create_lambda():
       x = 10
       return lambda y: y + x
   my_lambda = create_lambda()
   # If x goes out of scope, my_lambda might cause issues
   ```

5. **Complexity**:
   ```python
   # Complex logic in a lambda
   result = filter(lambda x: (x % 2 == 0 and x > 5) or (x % 3 == 0 and x < 5), range(10))
   # Simplified logic with named functions
   def is_even_and_greater_than_five(x):
       return x % 2 == 0 and x > 5
   def is_divisible_by_three_and_less_than_five(x):
       return x % 3 == 0 and x < 5
   result = filter(lambda x: is_even_and_greater_than_five(x) or is_divisible_by_three_and_less_than_five(x), range(10))
   ```

These examples should give you a clearer picture of how these pitfalls can manifest in code.