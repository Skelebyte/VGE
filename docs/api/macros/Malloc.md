# `#define Malloc(size)`

_Located in `engine/inc/memory.hpp`_

#### Behavior

Calls `internal_Malloc` from the `Pointer` struct, passing `size` along with `VGE_CALL_INFO` for logging purposes.
Must be called from a `Pointer` object.

##### Parameters

- `size`: The number of elements to allocate.

#### Example

```cpp
Pointer<int> ptr;
ptr.Malloc(3); // allocates 3 ints
...
```
