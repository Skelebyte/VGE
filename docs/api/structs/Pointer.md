# `template <typename T> struct Pointer`

_Located in `engine/inc/memory.hpp`_

## Member Functions

### Public

#### `Pointer()`

Constructor for the `Pointer` struct. Records the size of `T`.

#### `~Pointer()`

Destructor for the `Pointer` struct. Automatically frees the `data` member variable using `internal_Free`.

#### `bool internal_Malloc(size_t amount, const String &file, const String &func, const uint32 line)`

Allocates memory for the `Pointer` struct using `amount * typeSize`. Returns `true` if successful, `false` otherwise.

!!! warning
    Use the macro `Malloc` instead of calling this function directly.

##### Parameters

- `amount`: The amount of memory to allocate. Use this as the number of `T` elements to allocate.
- `file`: The file where the allocation occurred.
- `func`: The function where the allocation occurred.
- `line`: The line number where the allocation occurred.

#### `bool internal_Free(const String &file, const String &func, const uint32 line)`

Frees the memory allocated by `internal_Malloc`. Returns `true` if successful, `false` otherwise.

!!! warning
    Use the macro `Free` instead of calling this function directly.

##### Parameters

- `file`: The file where the allocation occurred.
- `func`: The function where the allocation occurred.
- `line`: The line number where the allocation occurred.

#### `T *GetData()`, `T *GetData() const`

Returns a pointer to the data allocated by `internal_Malloc`.

#### `size_t GetAllocationSize() const`

Returns the `allocationSize` member variable.

#### `size_t GetAmountAllocated() const`

Returns the `count` member variable.

#### `T &operator[](int i)`, `T &operator[](int i) const`

Returns a reference to the element at index `i` from the `data` member variable.

#### `bool operator!()`

Returns `true` if the `data` member variable is `nullptr`, `false` otherwise.

### Private

## Member Variables

### Protected

#### `size_t count`

The number of `T` elements allocated.

#### `size_t allocationSize`

The size of the allocation in bytes.

#### `size_t typeSize`

The size of the `T` type in bytes.

#### `T *data`

The pointer to the allocated memory.

#### `MemoryState state`

The state of the memory allocation.
