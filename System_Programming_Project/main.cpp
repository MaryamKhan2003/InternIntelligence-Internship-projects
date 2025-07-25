// #include <iostream>
// #include <cstring> // For memset

// #define MEMORY_POOL_SIZE 1024  // You can increase this as needed
// // Minimum size for a new block after splitting.
// // It must be at least large enough to hold a BlockHeader.
// // Adding 1 byte ensures there's at least 1 usable byte after the header,
// // preventing creation of blocks that are just headers with no data space.
// #define MIN_SPLIT_SIZE (sizeof(BlockHeader) + 1)

// using namespace std;
// //@brief:
// // BlockHeader structure defines the metadata for each memory block.
// // Each block in the memory pool (whether free or allocated) will have this header.
// struct BlockHeader {
//     size_t size; //@brief: Size of the usable data portion of the block (excluding the header itself)
//     bool isFree; //@brief: True if the block is free, false if allocated
//     BlockHeader* next; // Pointer to the next FREE block in the linked list of free blocks (first-fit list)
// };

// //@brief: Global memory pool: The raw memory array that our manager will control.
// char memoryPool[MEMORY_POOL_SIZE];
// //@brief: Head of the linked list of free blocks. This list is used by myMalloc.
// BlockHeader* freeListHead = nullptr;

// //@brief: Initializes the entire memory pool as one large free block.
// void initializeMemory() {
//     //@brief: The first BlockHeader is placed at the very beginning of the memory pool.
//     freeListHead = (BlockHeader*)memoryPool;
//     //@brief: The size of this initial free block is the total pool size minus the size of its own header.
//     freeListHead->size = MEMORY_POOL_SIZE - sizeof(BlockHeader);
//     freeListHead->isFree = true; // Mark it as free.
//     freeListHead->next = nullptr; // Initially, there are no other free blocks in the list.
// }

// //@brief: Custom malloc implementation using the first-fit strategy.
// //@brief: It searches for the first available free block that can satisfy the request.
// void* myMalloc(size_t size) {
//     //@brief: We need to find a block that can hold 'size' bytes of data.
//     //@brief: The BlockHeader itself is prepended to this data.

//     BlockHeader* current = freeListHead; // @brief:Start searching from the head of the free list.
//     BlockHeader* prev = nullptr;         //@brief: Keep track of the previous block in the free list
//     // @brief:to correctly update links when a block is removed or split.

//     while (current != nullptr) {
//         //@brief: Check if the current free block is large enough to fulfill the request.
//         //@brief: 'current->size' is the usable data size of the free block.
//         if (current->isFree && current->size >= size) {
//             //@brief: Option 1: The block is large enough and can be split.
//             //@brief: This happens if the remaining space after allocation is big enough to form a new,
//             //@brief: useful free block (i.e., it can hold at least a BlockHeader + 1 byte for data).
//             if (current->size >= size + MIN_SPLIT_SIZE) {
//                 //@brief: Calculate the address for the header of the new, smaller free block.
//                 //@brief: It's placed immediately after the allocated portion of the current block.
//                 BlockHeader* newFreeBlock = (BlockHeader*)((char*)current + sizeof(BlockHeader) + size);

//                 //@brief: Set up the new free block's properties.
//                 newFreeBlock->size = current->size - size - sizeof(BlockHeader);
//                 newFreeBlock->isFree = true;
//                 newFreeBlock->next = current->next; //@brief: The new block inherits the 'next' of the original 'current' block.

//                 //@brief: Update the original 'current' block, which is now being allocated.
//                 current->size = size;     //@brief: Its size becomes the requested size.
//                 current->isFree = false;  //@brief: Mark it as allocated.

//                 //@brief: Update the free list: 'newFreeBlock' effectively replaces 'current'.
//                 if (prev == nullptr) {
//                     //@brief: If 'current' was the head of the free list, the new free block becomes the new head.
//                     freeListHead = newFreeBlock;
//                 }
//                 else {
//                     //@brief: Otherwise, link the previous block in the free list to the new free block.
//                     prev->next = newFreeBlock;
//                 }
//             }
//             else {
//                 //@brief: Option 2: The block is large enough but not big enough to split.
//                 //@brief: Allocate the entire block to avoid creating tiny, unusable fragments.
//                 current->isFree = false; // Mark the entire block as allocated.

//                 //@brief: Remove 'current' block from the free list.
//                 if (prev == nullptr) {
//                     //@brief: If 'current' was the head, the next block in the free list becomes the new head.
//                     freeListHead = current->next;
//                 }
//                 else {
//                     //@brief: Otherwise, link the previous block to the next block after 'current'.
//                     prev->next = current->next;
//                 }
//             }
//             //@brief: Return a pointer to the usable memory area (after the BlockHeader).
//             return (char*)current + sizeof(BlockHeader);
//         }

//         //@brief: Move to the next block in the free list.
//         prev = current;
//         current = current->next;
//     }

//     //@brief: No suitable free block found.
//     return nullptr;
// }

// //@brief: Custom free implementation.
// // Marks a block as free and attempts to coalesce it with physically adjacent free blocks.
// void myFree(void* ptr) {
//     if (ptr == nullptr) return; // Cannot free a null pointer.

//     //@brief: Get the BlockHeader by moving back from the user's pointer.
//     BlockHeader* freedBlock = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
//     freedBlock->isFree = true; // Mark the block as free.

//     // Add the newly freed block to the head of the free list.
//     // This is a simple strategy; for performance, one might insert it in address-sorted order.
//     freedBlock->next = freeListHead;
//     freeListHead = freedBlock;

//     // @brief:Coalescing: Iterate through the entire memory pool to find and merge
//     // physically adjacent free blocks. This is crucial to prevent fragmentation.
//     BlockHeader* currentPhysicalBlock = (BlockHeader*)memoryPool;
//     while ((char*)currentPhysicalBlock < memoryPool + MEMORY_POOL_SIZE) {
//         // Calculate the address of the next physically adjacent block.
//         // It's located after the current block's header and its data area.
//         BlockHeader* nextPhysicalBlock = (BlockHeader*)((char*)currentPhysicalBlock + sizeof(BlockHeader) + currentPhysicalBlock->size);

//         // Check if 'nextPhysicalBlock' is within the bounds of the memory pool
//         // and if its calculated size makes sense (i.e., it's not pointing past the end).
//         // The `nextPhysicalBlock->size > 0` check is a safeguard against reading garbage
//         // if the pointer calculation went wrong or if the last block is malformed.
//         if ((char*)nextPhysicalBlock < memoryPool + MEMORY_POOL_SIZE && nextPhysicalBlock->size >= 0) { // size can be 0 for last block if no data
//             //@brief: If both the current physical block and the next physical block are free, merge them.
//             if (currentPhysicalBlock->isFree && nextPhysicalBlock->isFree) {
//                 // Merge: Add the size of the next block (plus its header) to the current block's size.
//                 currentPhysicalBlock->size += sizeof(BlockHeader) + nextPhysicalBlock->size;

//                 //@brief: Remove 'nextPhysicalBlock' from the free list, as it's now part of 'currentPhysicalBlock'.
//                 BlockHeader* freeListCurrent = freeListHead;
//                 BlockHeader* freeListPrev = nullptr;
//                 while (freeListCurrent != nullptr && freeListCurrent != nextPhysicalBlock) {
//                     freeListPrev = freeListCurrent;
//                     freeListCurrent = freeListCurrent->next;
//                 }

//                 //@brief: If 'nextPhysicalBlock' was found in the free list, remove it.
//                 if (freeListCurrent == nextPhysicalBlock) {
//                     if (freeListPrev == nullptr) { // It was the head of the free list.
//                         freeListHead = freeListCurrent->next;
//                     }
//                     else { //@brief: It was somewhere in the middle or end.
//                         freeListPrev->next = freeListCurrent->next;
//                     }
//                 }
//                 //@brief: Do NOT advance currentPhysicalBlock; it has grown and might be mergeable with its new physical next.
//                 continue; // Re-check coalescing from the current (now larger) block.
//             }
//         }
//         else {
//             //@brief: If nextPhysicalBlock is out of bounds or invalid, we've reached the end of valid blocks.
//             break;
//         }
//         // Move to the next physical block in the memory pool.
//         currentPhysicalBlock = nextPhysicalBlock;
//     }
// }

// //@brief: Utility function to print the layout of all blocks (free or allocated) in the memory pool.
// void printMemoryLayout() {
//     cout << "\n--- Memory Layout ---\n";
//     BlockHeader* current = (BlockHeader*)memoryPool; // Start from the beginning of the raw memory pool.
//     int blockNum = 0;
//     //@brief: Iterate through the memory pool by jumping from one block's end to the next block's start.
//     while ((char*)current < memoryPool + MEMORY_POOL_SIZE) {
//         //@brief: Print details of the current block.
//         cout << "[Block " << blockNum++ << " @ " << (void*)current << "] Size: " << current->size
//             << " Free: " << (current->isFree ? "Yes" : "No") << endl;

//         //@brief: Calculate the address of the next physical block.
//         // This relies on the current block's size to find the start of the next one.
//         current = (BlockHeader*)((char*)current + sizeof(BlockHeader) + current->size);

//         //@brief: Safety break: if the calculated next 'current' points outside the pool,
//         // or if somehow the size led to an invalid jump, prevent infinite loop.
//         if ((char*)current > memoryPool + MEMORY_POOL_SIZE) {
//             cout << "Warning: Calculated next block address is out of bounds. Breaking traversal.\n";
//             break;
//         }
//     }
//     cout << "---------------------\n";
// }

// //@brief: Test function to demonstrate the memory manager's functionality.
// void testMemoryManager() {
//     initializeMemory();
//     cout << "Initial Memory Layout:";
//     printMemoryLayout();

//     cout << "\n--- Test Allocations ---" << endl;

//     cout << "Allocating a = myMalloc(100)";
//     void* a = myMalloc(100);
//     if (a) {
//         memset(a, 'A', 100); //@brief: Write some data to verify allocation
//         cout << " -> Allocated at " << a << endl;
//     }
//     else {
//         cout << " -> Allocation failed for a (size 100)" << endl;
//     }
//     printMemoryLayout();

//     cout << "\nAllocating b = myMalloc(200)";
//     void* b = myMalloc(200);
//     if (b) {
//         memset(b, 'B', 200);
//         cout << " -> Allocated at " << b << endl;
//     }
//     else {
//         cout << " -> Allocation failed for b (size 200)" << endl;
//     }
//     printMemoryLayout();

//     cout << "\n--- Test Deallocations and Coalescing ---" << endl;

//     cout << "Freeing a";
//     myFree(a);
//     cout << " -> Freed a" << endl;
//     printMemoryLayout();

//     cout << "\nAllocating c = myMalloc(50) (should fit in the freed 'a' space or split)";
//     void* c = myMalloc(50);
//     if (c) {
//         memset(c, 'C', 50);
//         cout << " -> Allocated at " << c << endl;
//     }
//     else {
//         cout << " -> Allocation failed for c (size 50)" << endl;
//     }
//     printMemoryLayout();

//     cout << "\nFreeing b";
//     myFree(b);
//     cout << " -> Freed b" << endl;
//     printMemoryLayout();

//     cout << "\nFreeing c";
//     myFree(c);
//     cout << " -> Freed c" << endl;
//     printMemoryLayout();

//     cout << "\n--- Test Coalescing Effectiveness ---" << endl;

//     cout << "Allocating d = myMalloc(400) (should now fit after coalescing of a, b, c)";
//     void* d = myMalloc(400);
//     if (d) {
//         memset(d, 'D', 400);
//         cout << " -> Allocated at " << d << endl;
//     }
//     else {
//         cout << " -> Allocation failed for d (size 400). Coalescing might not be working as expected or pool too small." << endl;
//     }
//     printMemoryLayout();

//     cout << "\nFreeing d";
//     myFree(d);
//     cout << " -> Freed d" << endl;
//     printMemoryLayout();

//     cout << "\n--- Test Edge Cases ---" << endl;

//     cout << "Attempting to allocate a very large block (should fail if pool is small)";
//     void* large = myMalloc(MEMORY_POOL_SIZE); //@brief: Requesting more than available
//     if (large) {
//         cout << " -> Allocated large block at " << large << endl;
//     }
//     else {
//         cout << " -> Allocation failed for large block (expected, as it exceeds total pool capacity)." << endl;
//     }
//     printMemoryLayout();

//     cout << "\nAttempting to allocate 0 bytes";
//     void* zero_alloc = myMalloc(0);
//     if (zero_alloc) {
//         cout << " -> Allocated 0 bytes at " << zero_alloc << endl;
//         myFree(zero_alloc); //@brief: Free it if allocated
//     }
//     else {
//         cout << " -> Allocation failed for 0 bytes (expected, as 0-byte allocations are often disallowed or return nullptr)." << endl;
//     }
//     printMemoryLayout();
// }

// //@brief: Entry point of the program.
// int main() {
//     testMemoryManager();
//     return 0;
// }


