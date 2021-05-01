#!/usr/bin/python
import matplotlib.pyplot as plt
import numpy as np
import timeit

problem_size = 40   #problem size

runtime_rec = []        #holds runtimes corresponds to recusion implementation
runtime_iter = []       #holds runtimes corresponds to iteration implementation


def fib_r(x) :
    if (x <= 2):
        return 1

    return fib_r(x-1) + fib_r(x-2)


def fib_i(x) :

    a = 1
    b = 1
    fib = 1
    i = 2

    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1

    return fib


for x in range(problem_size + 1):

    start = timeit.default_timer()  #get the starting time
    y = fib_i(x)
    stop = timeit.default_timer()       #calculate the stopping moment time
    runtime_iter.append(stop - start)   #append the time duration to the runtime_iter list

print(runtime_iter)

for x in range(problem_size + 1):

    start = timeit.default_timer()  #get the starting time
    y = fib_r(x)
    stop = timeit.default_timer()       #calculate the stopping moment time
    runtime_rec.append(stop - start)   #append the time duration to the runtime_rec list

print(runtime_rec)


# Prepare the data
x = list(range(0, problem_size + 1))
# Plot the data
plt.plot(x, runtime_rec, label='recursion')
plt.plot(x, runtime_iter, label='iteration')

# Add a legend
plt.legend()

# Add graph details iter
# plt.xlabel('problem size (n)')
# plt.ylabel('runtime (nano seconds)')
# plt.title('Fibonacci Series (Iterative)')
# plt.grid(True)

# Add graph details rec
# plt.xlabel('problem size (n)')
# plt.ylabel('runtime (seconds)')
# plt.title('Fibonacci Series (Recursive)')
# plt.grid(True)

# Add graph details 
plt.xlabel('problem size (n)')
plt.ylabel('runtime (seconds)')
plt.title('Fibonacci Series')
plt.grid(True)

# Show the plot
plt.show()