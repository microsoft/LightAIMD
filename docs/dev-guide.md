# Development Guide
## Programming language
Whenever possible, we use pure C and avoid mixing C and C++. When the use of C++ code is inevitable, we interface it through the cpp_bridge.h and cpp_bridge.cpp files.

## Memory management
Use the following functions declared in mm.h to allocate and free memory buffers:

```c
void *x_malloc(u64 size)
void *x_calloc(u64 count, u64 size)
void x_free(void *ptr)
```

You can use print_mm_status() to check whether the number of memory allocations match that of deallocations.

## Naming convention
As we use C, don't name the functions in an object-oriented style.

## Pull request
Make each pull request small. It is easier to review small pull requests.
