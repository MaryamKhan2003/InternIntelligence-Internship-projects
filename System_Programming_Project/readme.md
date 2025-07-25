# **Basic Memory Management System**
This repository contains a simple, custom-implemented dynamic memory management system in C++. It demonstrates fundamental concepts of memory allocation and deallocation using a fixed-size memory pool, a first-fit allocation strategy, and explicit block coalescing to prevent fragmentation.

**Table of Contents**
Features

How it Works

Memory Pool

BlockHeader

Initialization

Allocation (myMalloc)

Deallocation (myFree)

Memory Layout Visualization (printMemoryLayout)

Building and Running

Testing

Future Improvements



# **Features**
Custom malloc and free: Implementations of basic memory allocation and deallocation functions.

Fixed Memory Pool: Manages memory within a predefined static array.

First-Fit Allocation: Searches for the first available block large enough to satisfy an allocation request.

Block Splitting: Divides larger free blocks to fulfill smaller allocation requests, leaving a new free block.

Coalescing: Merges physically adjacent free blocks during deallocation to reduce external fragmentation.

Memory Layout Visualization: A utility function to print the current state of the entire memory pool, showing both allocated and free blocks.

**## How it Works**
The system operates on a global char array, memoryPool, which serves as the raw memory space. Memory is managed using BlockHeader structures embedded within this pool.

**### Memory Pool**
The memoryPool is a static array of chars with a size defined by MEMORY_POOL_SIZE (defaulting to 1024 bytes). All memory operations occur within this confined space.

**#### BlockHeader**
Each contiguous segment of memory (whether allocated or free) is prefixed by a BlockHeader struct:

struct BlockHeader {
    size_t size;    // Size of the usable data portion (excluding the header itself)
    bool isFree;    // True if the block is available for allocation
    BlockHeader* next; // Pointer to the next FREE block in the linked list (used by myMalloc)
};

**##### Initialization**
The initializeMemory() function sets up the memory pool by treating the entire pool (minus the initial BlockHeader size) as one large free block. This block is then set as the freeListHead.

###### **Allocation (myMalloc)**
The myMalloc(size_t size) function implements a first-fit allocation strategy:

It traverses a linked list of freeListHead (which only contains free blocks).

It looks for the first free block whose size is greater than or equal to the requested size.

Splitting: If a suitable free block is found and its remaining size after fulfilling the request is large enough to accommodate a MIN_SPLIT_SIZE (another BlockHeader plus at least 1 byte of data), the block is split. The initial part becomes the allocated block, and the remainder becomes a new, smaller free block, which is inserted into the free list.

No Splitting: If the remaining size is too small to be useful, the entire free block is allocated to avoid creating tiny, unusable fragments.

The allocated block's isFree flag is set to false, and it's removed from the freeListHead linked list.

A pointer to the usable data area (after the BlockHeader) is returned.

If no suitable block is found, nullptr is returned.

**###### Deallocation (myFree)**
The myFree(void* ptr) function handles memory release:

It converts the user-provided ptr back to a BlockHeader* by subtracting sizeof(BlockHeader).

The isFree flag of the block is set to true.

The freed block is added to the head of the freeListHead linked list.

Coalescing: This is a crucial step to prevent external fragmentation. The function then iterates through the entire physical memory pool (not just the free list). If it finds two physically adjacent blocks that are both marked as free, it merges them into a single larger free block. The merged block is then removed from the freeListHead linked list to ensure it's not referenced twice. This process continues until no more adjacent free blocks can be merged.

###### **Memory Layout Visualization (printMemoryLayout)**
The printMemoryLayout() utility function provides a debugging view of the memory pool. It traverses the memoryPool from its beginning, interpreting each segment based on its BlockHeader and size, and prints whether each block is free or allocated, along with its address and size. This helps in understanding the dynamic state of the memory.

**###### Building and Running**
To compile and run this program, you will need a C++ compiler (like g++).

Save the code: Save the provided C++ code (from the Canvas document) into a file named memory_manager.cpp.

Compile: Open a terminal or command prompt and navigate to the directory where you saved the file. Then, compile using:

g++ memory_manager.cpp -o memory_manager

Run: Execute the compiled program:

./memory_manager

**Testing**
The testMemoryManager() function provides a series of allocation and deallocation scenarios to demonstrate the system's functionality, including:

Initial memory state.

Multiple allocations.

Deallocating blocks.

Allocating into previously freed space.

Demonstrating coalescing by freeing adjacent blocks and then attempting a larger allocation.

Edge cases like allocating a very large block or 0 bytes.

Observe the output of printMemoryLayout() after each operation to see how the memory pool changes.

**Future Improvements**
More Sophisticated Free List Management: Instead of just adding freed blocks to the head, maintain the free list sorted by memory address. This would simplify and potentially optimize the coalescing process.

Best-Fit/Worst-Fit: Implement different allocation strategies.

Error Handling: More robust error handling for myMalloc (e.g., custom error codes or exceptions).

Thread Safety: Add mutexes or other synchronization mechanisms if this system were to be used in a multi-threaded environment.

Memory Alignment: Ensure allocated memory is aligned to specific boundaries (e.g., 8-byte or 16-byte alignment) for performance with certain data types.

Boundary Tags: Implement boundary tags (footers) in addition to headers to allow for constant-time backward coalescing without needing to traverse the entire pool.

