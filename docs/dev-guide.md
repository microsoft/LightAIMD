# Development Guide
## Programming language
We use pure C, don't mix C and C++.

## Memory management
Use the following functions declared in mm.h to allocate and free memory buffers: <br>
```c
void *x_malloc(u64 size)
void *x_calloc(u64 count, u64 size)
void x_free(void *ptr)
```

You can use print_mm_status() to check whether the number of memory allocations match that of deallocations.

## Naming convention
As we use C, don't name the functions in an object-oriented style.

## Pull request
Make each pull request small. It is easier to code review small pull requests.
