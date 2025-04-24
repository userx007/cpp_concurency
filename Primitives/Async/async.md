### What is a future?
In a nutshell, a future is an asynchronous function call. You call a function, but don’t wait until it completes–the body of the function executes in a separate thread.
 Instead you get a future, a promise to deliver the result at some later point in time.
 Only when your program desperately needs that value, do you synchronize on the future.
 If the calculation hasn’t been completed by then, you block until it has. Otherwise you get the result of the calculation.