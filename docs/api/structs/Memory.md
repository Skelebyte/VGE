# `struct Memory : Singleton<Memory>`

_Located in `engine/inc/memory.hpp`_

## Member Functions

### Public

#### `static void IncreaseUsedMemory(size_t amount)`

Increases the private member `usedMemory` by `amount`.

#### `static void DecreaseUsedMemory(size_t amount)`

Decreases the private member `usedMemory` by `amount`.

## Member Variables

### Public

#### `bool logMallocSizes = true`

Toggles logging of malloc sizes.

#### `bool logFreeSizes = true`

Toggles logging of free sizes.

### Private

#### `size_t usedMemory`

Tracks the amount of memory currently in use.
Specifically, the amount of memory allocated by the engine. This does not include memory allocated by SDL or other dependencies.
