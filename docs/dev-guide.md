# Development Guide
## Programming language
We use pure C and avoid mixing C and C++ whenever possible.

## Memory management
Use the following functions declared in `src/mm.h` to allocate and free memory buffers:

```c
void *x_malloc(u64 size)
void *x_calloc(u64 count, u64 size)
void x_free(void *ptr)
```

You can use `print_mm_status()` to check whether the number of memory allocations match that of deallocations at the end of your program.

## Numeric types
Use the following types declared in `src/numeric_types.h` for numeric types:

| Type | Description |
| ---- | ----------- |
| i8   | 8-bit signed integer |
| u8   | 8-bit unsigned integer |
| i16  | 16-bit signed integer |
| u16  | 16-bit unsigned integer |
| i32  | 32-bit signed integer |
| u32  | 32-bit unsigned integer |
| i64  | 64-bit signed integer |
| u64  | 64-bit unsigned integer |
| f32  | 32-bit floating point number |
| f64  | 64-bit floating point number |

## Naming convention
As we use C, don't name the functions in an object-oriented style.

## Pull request
Make each pull request small. It is easier to review small pull requests.
