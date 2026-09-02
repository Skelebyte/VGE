# `#define Free()`

_Located in `engine/inc/memory.hpp`_

#### Behavior

Calls `internal_Free` from the `Pointer` struct, passing `VGE_CALL_INFO` for logging purposes.
Must be called from a `Pointer` object.

#### Example

```cpp
Pointer<int> ptr;
...
ptr.Free(); // frees the memory
```
